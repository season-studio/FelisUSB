/**
 * Felis USB
 * 
 * Copyright (c) 2021 Season Studio
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in the 
 * Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 * Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "stm32f4_hal_adapter.h"

#include "FelisUSB.h"
#include "FelisUsbDebug.h"

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

#if	!defined(FUSBD_ADPT_SOF)
	#define	FUSBD_ADPT_SOF									(DISABLE)
#endif

#if	!defined(FUSBD_ADPT_DMA)
	#define	FUSBD_ADPT_DMA									(DISABLE)
#endif

#if	!defined(FUSBD_ADPT_SPEED)
	#define	FUSBD_ADPT_SPEED								(PCD_SPEED_FULL)
#endif

/**
 * @defgroup Adapter_Event_Callbacks
 * @{
 */

/**
 * @brief event callback when the usb device object is initializing
 * 
 * @param pDev the usb device object
 * @return int 0 for success
 */
int on_fusbd_adpt_init(fusbd_device_pt pDev)
{
	hpcd_USB_OTG_FS.pData = pDev;
	pDev->pAdapter = &hpcd_USB_OTG_FS;
	
	hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = FUSBD_ADPT_DMA;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = FUSBD_ADPT_SOF;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  
	return HAL_PCD_Init(&hpcd_USB_OTG_FS);
}

/**
 * @brief event callback for starting the usb device
 * 
 * @param pInst the instance of the adapter
 * @return int 0 for success
 */
int on_fusbd_adpt_start(fusbd_adapter_t *pInst)
{
	return HAL_PCD_Start(pInst);
}

/**
 * @brief event callback for setting the address of the usb device
 * 
 * @param pInst the instance of the adapter
 * @param nAddr the address
 * @return int 0 for success
 */
int on_fusbd_adpt_set_address(fusbd_adapter_t *pInst, uint8_t nAddr)
{
	return (int)HAL_PCD_SetAddress(pInst, nAddr);
}

#if	1		// End Point Functions

/**
 * @brief event callback for initializing the endpoints assigned to the usb device
 * 
 * @param pDev the usb device
 * @param pFirstEP the pointer to the first entry of the link list of the endpoints
 * @return int 0 for success
 */
int on_fusbd_adpt_init_endpoints(fusbd_device_pt pDev, fusbd_endpoint_pt pFirstEP)
{
	size_t nMaxSize;
	size_t nUsedSize;
	uint8_t nCountInEP;
	uint8_t nLastEP;
	uint8_t nEp0Size = pDev->pConfig->pDescriptors->pDeviceDescriptor[7];
	
	FUsbLogL3("init_endpoints\n");
	
	// close the ep 0;
	HAL_PCD_EP_Close(pDev->pAdapter, 0);
	HAL_PCD_EP_Close(pDev->pAdapter, 0x80);
	
	// search the max size of the rx ep
	nMaxSize = MAX(nEp0Size, (MIN_USB_FIFO_ITEM_SIZE << 2));
	nCountInEP = 1;
	for (fusbd_endpoint_pt lpEP = pFirstEP; NULL != lpEP; lpEP = lpEP->pNext)
	{
		uint8_t nEpAddr = fusb_ep_addr_from_desc(lpEP->pDesc);
		if (0 == (nEpAddr & 0x80))
		{
			nCountInEP ++;
			HAL_PCD_EP_Close(pDev->pAdapter, nEpAddr);
			size_t nRxSize = ((fusb_ep_mps_from_desc(lpEP->pDesc) + 3) & (~3));
			if (USBD_EP_TYPE_ISOC == fusb_ep_type_from_desc(lpEP->pDesc))
			{
				nRxSize <<= 1;
			}
			if (nRxSize > nMaxSize)
			{
				nMaxSize = nRxSize;
			}
		}
	}
	// set the rx fifo
	FUsbLogL3("  max mps: %u\n", nMaxSize);
	nMaxSize = (((nMaxSize / 4) + 1) * 2) + 13 + 1 + (nCountInEP * 2);
	if (nUsedSize < MIN_USB_FIFO_ITEM_SIZE) 
	{
		nUsedSize = MIN_USB_FIFO_ITEM_SIZE;
	}
	HAL_PCDEx_SetRxFiFo(pDev->pAdapter, nMaxSize);
	FUsbLogL3("  set rx fifo: %u\n", nMaxSize);
	
	// set the tx fifo
	nUsedSize = (nMaxSize << 2) + nEp0Size;
	#define	FUsbSetTxFiFoItem(nAddr, nSize)	\
		do {	\
			if (0 != nAddr)	{	\
				HAL_PCD_EP_Close(pDev->pAdapter, (nAddr | 0x80));	\
				if ((nUsedSize += nSize) > USB_PBUFFER_TOTAL_SIZE) {	\
					BreakProcess();	\
				} \
				HAL_PCDEx_SetTxFiFo(pDev->pAdapter, nAddr, (nSize >> 2)); \
				FUsbLogL3("  set tx fifo: %u, %u\n", nAddr, (nSize >> 2));	\
			} \
		} while(0)
		
	// set the ep0 first
	HAL_PCDEx_SetTxFiFo(pDev->pAdapter, 0, (nEp0Size >> 2));
	FUsbLogL3("  set tx fifo: 0, %u\n", (nEp0Size >> 2));
	nLastEP = 0;
	nMaxSize = (MIN_USB_FIFO_ITEM_SIZE << 2);
	for (fusbd_endpoint_pt lpEP = pFirstEP; NULL != lpEP; lpEP = lpEP->pNext)
	{
		uint8_t nEpAddr = fusb_ep_addr_from_desc(lpEP->pDesc);
		if (0 != (nEpAddr & 0x80))
		{
			uint8_t nCurEP = (nEpAddr & 0x7F);
			if (nLastEP < nCurEP)
			{
				// ep addr changed means there is ep need to be setted;
				FUsbSetTxFiFoItem(nLastEP, nMaxSize);
				// alloc the min size of fifo item for the the unspecialized ep
				for (nLastEP++; nLastEP < nCurEP; nLastEP++)
				{
					HAL_PCDEx_SetTxFiFo(pDev->pAdapter, nLastEP, MIN_USB_FIFO_ITEM_SIZE);
				}
				// record the init size of the current ep
				nMaxSize = MAX((MIN_USB_FIFO_ITEM_SIZE << 2), ((fusb_ep_mps_from_desc(lpEP->pDesc) + 3) & (~3)));
			}
			else
			{
				// update the max size of the current ep
				size_t nTxSize = ((fusb_ep_mps_from_desc(lpEP->pDesc) + 3) & (~3));
				if (nTxSize > nMaxSize)
				{
					nMaxSize = nTxSize;
				}
			}
		}
	}
	// set the last ep in the queue
	FUsbSetTxFiFoItem(nLastEP, nMaxSize);
	#undef FUsbSetTxFiFoItem
	
	// open the ep0
	pDev->nEP0DataInRemain = 0;
	pDev->nEP0DataOutRemain = 0;
	pDev->nEP0DataOutTotal = 0;
	HAL_PCD_EP_Open(pDev->pAdapter, 0, nEp0Size, USBD_EP_TYPE_CTRL);
	HAL_PCD_EP_Open(pDev->pAdapter, 0x80, nEp0Size, USBD_EP_TYPE_CTRL);

	return 0;
}

#endif	// End Point Functions

/** @} */

#if	1		// Begin callbacks for the HAL library

__USED void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_SetupStageCallback\n");
	
	fusbd_device_pt pDev = hpcd->pData;
	
	if (NULL != pDev)
	{
		on_fusbd_setup_request(pDev, (uint8_t*)&(hpcd->Setup));
	}
}

__USED void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_ResetCallback\n");
		
	fusbd_device_pt pDev = hpcd->pData;
		
	fusbd_set_speed(pDev, USBD_SPEED_FULL);
	on_fusbd_reset(pDev);
}

__USED void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	// FUsbLogX("HAL_PCD_DataOutStageCallback\n");
	fusbd_device_pt pDev = (fusbd_device_pt)hpcd->pData;
	PCD_EPTypeDef* pEP = &hpcd->OUT_ep[epnum];
	
	if (0 == epnum)
  {
		if (0 != pDev->nEP0OutFlag)
		{
			if (pDev->nEP0DataOutRemain > pEP->maxpacket)
			{
				pDev->nEP0DataOutRemain -= pEP->maxpacket;

				fusbd_adpt_prepare_receive(hpcd, epnum, pEP->xfer_buff, MIN(pDev->nEP0DataOutRemain, pEP->maxpacket));
			}
			else
			{
				pDev->nEP0OutFlag = 0;
				
				if (USBD_STATE_CONFIGURED == pDev->nState)
				{
					on_fusbd_data_out(pDev, epnum);
				}
				pDev->fnEP0OutCallback = NULL;
				pDev->nEP0DataOutTotal = 0;
				pDev->pEP0OutBuf = NULL;

				fusbd_ctrl_send_status(pDev);
			}
		}
	}
	else
	{
		if (USBD_STATE_CONFIGURED == pDev->nState)
		{
			on_fusbd_data_out(pDev, epnum);
		}
	}
}

__USED void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	// FUsbLogX("HAL_PCD_DataInStageCallback\n");
	fusbd_device_pt pDev = (fusbd_device_pt)hpcd->pData;
	PCD_EPTypeDef* pEP = &hpcd->IN_ep[epnum];
	
	if (0 == epnum)
	{
		if (0 != pDev->nEP0InFlag)
		{
			if (pDev->nEP0DataInRemain > pEP->maxpacket)
			{
				pDev->nEP0DataInRemain -= pEP->maxpacket;
				fusbd_adpt_transmit(hpcd, 0, hpcd->IN_ep[epnum].xfer_buff, pDev->nEP0DataInRemain);
				fusbd_ctrl_receive(pDev, NULL, 0, NULL, NULL);
			}
			else
			{
				pDev->nEP0InFlag = 0;
				
				if (pDev->nEP0DataInRemain == pEP->maxpacket)
				{
					pDev->nEP0DataInRemain = 0;
					fusbd_adpt_transmit(hpcd, 0, NULL, 0);
					fusbd_ctrl_receive(pDev, NULL, 0, NULL, NULL);
				}
				else
				{
					pDev->nEP0DataInRemain = 0;
					if (USBD_STATE_CONFIGURED == pDev->nState)
					{
						on_fusbd_data_in(pDev, epnum);
					}
					fusbd_adpt_ep_stall(hpcd, 0x80);
					fusbd_ctrl_receive(pDev, NULL, 0, NULL, NULL);
				}
			}
		}
		else
		{
			fusbd_ctrl_receive(pDev, NULL, 0, NULL, NULL);
		}
	}
	else
	{
		if (USBD_STATE_CONFIGURED == pDev->nState)
		{
			on_fusbd_data_in(pDev, epnum);
    }
	}
}

__USED void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_SOFCallback\n");
	on_fusbd_sof((fusbd_device_pt)hpcd->pData);
}

__USED void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_SuspendCallback\n");
	
	on_fusbd_suspend((fusbd_device_pt)hpcd->pData);
	
	__HAL_PCD_GATE_PHYCLOCK(hpcd);
	if (hpcd->Init.low_power_enable)
	{
		SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
	}
}

__USED void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_ResumeCallback\n");
	
	on_fusbd_resume((fusbd_device_pt)hpcd->pData);
}

__USED void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	// FUsbLogX("HAL_PCD_ISOOUTIncompleteCallback\n");
}

__USED void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	// FUsbLogX("HAL_PCD_ISOINIncompleteCallback\n");
}

__USED void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_ConnectCallback\n");
}

__USED void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
	// FUsbLogX("HAL_PCD_DisconnectCallback\n");
}

#endif	// End callbacks for the HAL library
