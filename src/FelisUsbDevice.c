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
#include "FelisUsbDevice.h"

#include "FelisUsbDebug.h"

#include <string.h>

/**
 * @defgroup FelisUSB
 * @{
 */

#if	1		// Begin Basic Functions

#define	ASSERT_DEV_EP(pDev, pUEP, fAction)	do { if ((NULL == pDev) || (NULL == pUEP)) fAction; } while(0)
#define	ASSERT_EP_OPENED(pUEP, fAction)			do { if (0 == (pUEP->nFlag & FUSBD_EP_FLAG_OPEN)) fAction; } while(0)
#define	ASSERT_EP_IN(pUEP, fAction)					do { if (!fusb_ep_desc_is_in(pUEP->pDesc)) fAction; } while(0)
#define	ASSERT_EP_OUT(pUEP, fAction)				do { if (fusb_ep_desc_is_in(pUEP->pDesc)) fAction; } while(0)

/**
 * @brief open an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint to be opened
 * @return int 0 for success
 */
int fusbd_ep_open(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	
	int iRet = (0 == (pUEP->nFlag & FUSBD_EP_FLAG_OPEN))
								? fusbd_adpt_ep_open(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc), fusb_ep_mps_from_desc(pUEP->pDesc), fusb_ep_type_from_desc(pUEP->pDesc))
								: 0;
	if (0 == iRet)
	{
		pUEP->nFlag = FUSBD_EP_FLAG_OPEN;
	}
	
	return iRet;
}

/**
 * @brief close an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint to be closed
 * @return int 0 for success
 */
int fusbd_ep_close(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	
	int iRet;
	
	if (0 == (pUEP->nFlag & FUSBD_EP_FLAG_OPEN))
	{
		iRet = 0;
	}
	else
	{
		// flush before closing
		fusbd_adpt_ep_flush(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
	
		// close the endpoint and set the flag
		iRet = fusbd_adpt_ep_close(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
		if (0 == iRet)
		{
			pUEP->nFlag = 0;
		}
	}
	
	return iRet;
}

/**
 * @brief set an endpoint to the stall state
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @return int 0 for success
 */
int fusbd_ep_stall(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	
	return fusbd_adpt_ep_stall(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
}

/**
 * @brief clear the stall state for an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @return int 0 for success
 */
int fusbd_ep_stall_clr(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	
	return fusbd_adpt_ep_stall_clr(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
}

/**
 * @brief check if an endpoint is set to stall state
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @return bool 
 */
bool fusbd_ep_is_stall(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return false);
	
	return 0 != fusbd_adpt_ep_isstall(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
}

/**
 * @brief flush an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @return int 0 for success
 */
int fusbd_ep_flush(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	
	return fusbd_adpt_ep_flush(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc));
}

/**
 * @brief check if an endpoint is in transmition
 * 
 * @param pUEP the endpoint
 * @return bool
 */
bool fusbd_ep_is_busy(fusbd_endpoint_pt pUEP)
{
	return ((NULL == pUEP) || (0 != (pUEP->nFlag & FUSBD_EP_FLAG_XFER)));
}

/**
 * @brief check if an endpoint is opened
 * 
 * @param pUEP the endpoint
 * @return bool
 */
bool fusbd_ep_is_opened(fusbd_endpoint_pt pUEP)
{
	return ((NULL == pUEP) || (0 != (pUEP->nFlag & FUSBD_EP_FLAG_OPEN)));
}

/**
 * @cond
 * @brief core for sending data in an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @param nTimeout time for waiting the transmition completing in MS uint, 0 for no wait, -1 for no timeout
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_send_data_core(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize, uint32_t nTimeout)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	ASSERT_EP_OPENED(pUEP, return -2);
	ASSERT_EP_IN(pUEP, return -3);
	ASSERT(0 == (pUEP->nFlag & FUSBD_EP_FLAG_XFER), return -4);
	
	#define	_SET_EP_NFALG(n, action)		(n action)
	
	// set the transmtion flag
	felis_atomic_exchange(&(pUEP->nFlag), _SET_EP_NFALG, | FUSBD_EP_FLAG_XFER);
	pUEP->pXferBuf = (void *)pBuf;
	pUEP->nXferSize = nSize;
	
	// starting the transmition
	int iRet = fusbd_adpt_transmit(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc), (uint8_t*)pBuf, nSize);
	
	if (0 != iRet)
	{
		// if fail in starting transmition, clear the flag
		felis_atomic_exchange(&(pUEP->nFlag), _SET_EP_NFALG, & (~FUSBD_EP_FLAG_XFER));
	}
	else if (0 != nTimeout)
	{
		// if success in starting transmition, waiting until completed
		uint32_t nOriTick = fusbd_adpt_get_tickcount(pDev->pAdapter);
		while (0 != (pUEP->nFlag & FUSBD_EP_FLAG_XFER))
		{
			if (FUSBD_TIMEOUT_INFINITY != nTimeout)
			{
				if ((fusbd_adpt_get_tickcount(pDev->pAdapter) - nOriTick) > nTimeout)
				{
					break;
				}
			}
		}
	}
	
	#undef	_SET_EP_NFALG
	
	return iRet;
}
/**
 * @endcond
 */

/**
 * @brief send data in an endpoint
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @param nTimeout time for waiting the transmition completing in MS uint, 0 for no wait, -1 for no timeout
 * @return int 0 for success
 */
int fusbd_send_data(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize, uint32_t nTimeout)
{
	return fusbd_send_data_core(pDev, pUEP, pBuf, nSize, nTimeout);
}

/**
 * @brief send data in an endpoint until the transmition is completed
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @return int 0 for success
 */
int fusbd_send_data_sync(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize)
{
	return fusbd_send_data_core(pDev, pUEP, pBuf, nSize, FUSBD_TIMEOUT_INFINITY);
}

/**
 * @brief send data in an endpoint without waiting the transmition completed
 * 
 * @param pDev the usb device
 * @param pUEP the endpoint
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @return int 0 for success
 */int fusbd_send_data_async(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize)
{
	return fusbd_send_data_core(pDev, pUEP, pBuf, nSize, 0);
}

/**
 * @brief starting receiving data from an endpoint
 * 
 * @param pDev the usd device
 * @param pUEP the endpoint
 * @param pBuf the buffer for receiving the data
 * @param nSize the size of the data would be received
 * @return int 0 for success
 */
int fusbd_prepare_receive(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, void * pBuf, size_t nSize)
{
	ASSERT_DEV_EP(pDev, pUEP, return -1);
	ASSERT_EP_OPENED(pUEP, return -2);
	ASSERT_EP_OUT(pUEP, return -3);
	
	pUEP->pXferBuf = pBuf;
	pUEP->nXferSize = nSize;
	
	return fusbd_adpt_prepare_receive(pDev->pAdapter, fusb_ep_addr_from_desc(pUEP->pDesc), (uint8_t*)pBuf, nSize);
}

/**
 * @cond
 * @brief reset the internal data of the usb device object
 * 
 * @param pDev the usb device
 */
__STATIC_INLINE void fusbd_reset_dev_obj(fusbd_device_pt pDev)
{
	pDev->nState = 0;
	
	pDev->nConfigIndex = 0;
	pDev->nRemoteWakeup = 0;
	pDev->pEndPoints = NULL;
	pDev->nEP0DataInRemain = 0;
	pDev->nEP0DataOutRemain = 0;
	pDev->pEP0OutBuf = NULL;
	pDev->nEP0DataOutTotal = 0;
	pDev->fnEP0OutCallback = NULL;
}
/** @endcond */

#endif	// End Basic Functions

#if	1		// Begin Class Functions

/** @cond */

/**
 * @brief toolkit for begining the interation of the classes in an usb device
 */
#define	BeginIterateClass(pDev, varItem)		\
	if (NULL != (pDev)->pConfig)	\
		for (fusbd_class_pt const* _pp##varItem = pDev->pConfig->zClassPtrs;	\
				 NULL != *_pp##varItem;	\
				 _pp##varItem++)	\
	{	fusbd_class_pt varItem = (*_pp##varItem);
		
/**
 * @brief toolkit for ending the interation of the classes in an usb device
 */
#define	EndIterateClass(pDev)								}

/**
 * @brief select a class by the index of the interface
 * 
 * @param pDev the usb device
 * @param nIntfIdx the index of the interface
 * @return fusbd_class_pt the pointer to the matched class
 */
__STATIC_INLINE fusbd_class_pt FUsbSelectClassByIntf(fusbd_device_pt pDev, uint8_t nIntfIdx)
{
	uint32_t idx = FUsbIntfMarkIdx(nIntfIdx);
	uint32_t bit = FUsbIntfMarkBit(nIntfIdx);
	
	BeginIterateClass(pDev, lpClass);
		if (0 != (lpClass->pRuntime->nIntfMark[idx] & bit))
		{
			return lpClass;
		}
	EndIterateClass(pDev);
		
	return NULL;
}

/**
 * @brief select a class by the address of an endpoint
 * 
 * @param pDev the usb device
 * @param nEpAddr the address of an endpoint
 * @return fusbd_class_pt the pointer to the matched class
 */
__STATIC_INLINE fusbd_class_pt FUsbSelectClassByEP(fusbd_device_pt pDev, uint8_t nEpAddr)
{
	for (fusbd_endpoint_pt lpUEP = pDev->pEndPoints; NULL != lpUEP; lpUEP = lpUEP->pNext)
	{
		if (nEpAddr == fusb_ep_addr_from_desc(lpUEP->pDesc))
		{
			return FUsbSelectClassByIntf(pDev, lpUEP->nIntf);
		}
	}
	return NULL;
}

/**
 * @brief select an endpoint by the address
 * 
 * @param pDev the usb device
 * @param nEpAddr the address
 * @return fusbd_endpoint_pt the pointer to the matched endpoint 
 */
__STATIC_INLINE fusbd_endpoint_pt FUsbSelectEndPoint(fusbd_device_pt pDev, uint8_t nEpAddr)
{
	for (fusbd_endpoint_pt lpUEP = pDev->pEndPoints; NULL != lpUEP; lpUEP = lpUEP->pNext)
	{
		if (nEpAddr == fusb_ep_addr_from_desc(lpUEP->pDesc))
		{
			return lpUEP;
		}
	}
	return NULL;
}

/**
 * @brief unconfig the usb device
 * 
 * @param pDev the usb device
 */
static void FUsbDUnconfigClass(fusbd_device_pt pDev)
{
	ASSERT(NULL != pDev, return);
	
	// unconfig all classes assigned to this device
	BeginIterateClass(pDev, lpClass);
		fusbd_call_class_method(lpClass, Unconfig);
	EndIterateClass(pDev);
}

/**
 * @brief config the usb device
 * 
 * @param pDev the usb device
 * @param pConfigDescriptor the descriptor of the configuration selected by the host
 */
static void FUsbDConfigClass(fusbd_device_pt pDev, const uint8_t * pConfigDescriptor)
{
	ASSERT(NULL != pDev, return);
	
	if (USB_CONFIGURATION_DESCRIPTOR_TYPE == fusb_desc_type(pConfigDescriptor))
	{
		const uint8_t * lpDesc = pConfigDescriptor + fusb_desc_len(pConfigDescriptor);
		const uint8_t * lpEnd = pConfigDescriptor + MAKEWORD(pConfigDescriptor[2], pConfigDescriptor[3]);
		
		const uint8_t * lpIntfDesc = NULL;
		fusbd_class_pt lpClass = NULL;
		fusbd_endpoint_pt lpFirstEP = NULL;
		uint8_t nIntfIdx = 0;
		
		// clear all marked of all classes
		BeginIterateClass(pDev, lpClsItem);
			memset(lpClsItem->pRuntime->nIntfMark, 0, sizeof(lpClsItem->pRuntime->nIntfMark));
		EndIterateClass(pDev);
		
		// iterate each descriptor in the configuration
		while (lpDesc < lpEnd)
		{
			switch (fusb_desc_type(lpDesc))
			{
				case USB_INTERFACE_DESCRIPTOR_TYPE:
					do
					{
						// call the 'Config' method of each class to test the interface matched to which class
						lpIntfDesc = lpDesc;
						size_t nRet = 0;
						lpClass = NULL;
						nIntfIdx = 0;
						BeginIterateClass(pDev, lpClsItem);
							nRet = fusbd_call_class_method(lpClsItem, Config, lpDesc);
							if (0 != nRet)
							{
								lpClass = lpClsItem;
								nIntfIdx = fusb_intf_desc_idx(lpDesc);
								lpClass->pRuntime->nIntfMark[FUsbIntfMarkIdx(nIntfIdx)] |= FUsbIntfMarkBit(nIntfIdx);
								break;
							}
						EndIterateClass(pDev);
						// skip descriptors processed by the class
						lpDesc += ((0 != nRet) ? nRet : fusb_desc_len(lpDesc));
					} while (0);
					break;
				
				case USB_ENDPOINT_DESCRIPTOR_TYPE:
					if (NULL != lpClass)
					{
						// try to assign an endpoint descriptor to a class
						fusbd_endpoint_pt pUEP = fusbd_call_class_method(lpClass, AssignEndPoint, lpDesc, lpIntfDesc);
						if (NULL != pUEP)
						{
							pUEP->pDesc = lpDesc;
							pUEP->nIntf = nIntfIdx;
							pUEP->nXferSize = 0;
							pUEP->nFlag = 0;
							pUEP->pNext = NULL;
							// insert the endpoint into the link list
							if (NULL == lpFirstEP)
							{
								lpFirstEP = pUEP;
							}
							else
							{
								fusbd_endpoint_pt lpCurEP, lpLastEP;
								for (lpCurEP = lpFirstEP, lpLastEP = NULL; NULL != lpCurEP; lpLastEP = lpCurEP, lpCurEP = lpCurEP->pNext)
								{
									if ((fusb_ep_addr_from_desc(lpCurEP->pDesc) & 0x7F) > (fusb_ep_addr_from_desc(pUEP->pDesc) & 0x7F))
									{
										if (NULL == lpLastEP)
										{
											lpFirstEP = pUEP;
										}
										else
										{
											lpLastEP->pNext = pUEP;
										}
										pUEP->pNext = lpCurEP;
										break;
									}
								}
								if (NULL == lpCurEP)
								{
									if (NULL == lpLastEP)
									{
										lpFirstEP = pUEP;
									}
									else 
									{
										lpLastEP->pNext = pUEP;
									}
								}
							}
						}
					}
				
				default:
					// skip the descriptor if it is neither intreface nor endpoint
					lpDesc = fusb_next_desc_ptr(lpDesc);
					break;
			}
		}
		
		// record the first pointer of the link list of the endpoints
		pDev->pEndPoints = lpFirstEP;
		
		// call the adpater for initializing the endpoints assigned to the usb device
		on_fusbd_adpt_init_endpoints(pDev, lpFirstEP);
		
		// call each class for finishing the configing
		BeginIterateClass(pDev, lpClass)
			fusbd_call_class_method(lpClass, ConfigDone);
		EndIterateClass(pDev);
	}
}

/** @endcond */

#endif	// End Class Functions

#if	1		// Begin Request Actions

/** @cond */

/**
 * @brief processing getting a descriptor
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_get_descriptor(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	const fusbd_descriptor_set_t * lpDescriptors = pDev->pConfig->pDescriptors;
	const uint8_t *pDest = NULL;
	size_t nDestLen = 0;

	// locate the descriptor
	switch (pReq->ucValue[1])
	{
    case USB_BOS_DESCRIPTOR_TYPE:
			pDest = lpDescriptors->pBOSDescriptor;
			nDestLen = (NULL != pDest) ? MAKEWORD(pDest[2], pDest[3]) : 0;
			break;
			
		case USB_DEVICE_DESCRIPTOR_TYPE:
			pDest = lpDescriptors->pDeviceDescriptor;
			nDestLen = (NULL != pDest) ? fusb_desc_len(pDest) : 0;
      break;

    case USB_CONFIGURATION_DESCRIPTOR_TYPE:
		{
			uint8_t idx = pReq->ucValue[0];
			if (pDev->nSpeed == USBD_SPEED_HIGH) 
			{
				pDest = (idx < lpDescriptors->nHSConfigCount) ? lpDescriptors->pHSConfigDescriptorList[idx] : NULL;
			}
			else
			{
				pDest = (idx < lpDescriptors->nFSConfigCount) ? lpDescriptors->pFSConfigDescriptorList[idx] : NULL;
      }
			nDestLen = (NULL != pDest) ? MAKEWORD(pDest[2], pDest[3]) : 0;
			break;
		}

    case USB_STRING_DESCRIPTOR_TYPE:
		{
			uint8_t idx = pReq->ucValue[0];
			pDest = (idx < lpDescriptors->nStringCount) ? (uint8_t*)(lpDescriptors->pStringDescriptorList[idx]) : NULL;
			nDestLen = (NULL != pDest) ? fusb_desc_len(pDest) : 0;
			break;
		}
		
    case USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
			if (pDev->nSpeed == USBD_SPEED_HIGH)
			{
				pDest = lpDescriptors->pDeviceQualifierDescriptor;
				nDestLen = (NULL != pDest) ? fusb_desc_len(pDest) : 0;
      }
      break;

    case USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE:
			if (pDev->nSpeed == USBD_SPEED_HIGH)
			{
				uint8_t idx = pReq->ucValue[0];
				pDest = (idx < lpDescriptors->nOtherSpeedConfigCount) ? lpDescriptors->pOtherSpeedConfigDescriptorList[idx] : NULL;
				nDestLen = (NULL != pDest) ? MAKEWORD(pDest[2], pDest[3]) : 0;
			}
			break;

		default:
			break;
	}

	// send the descriptor, or send error signal if the descriptor is not located
	if (NULL == pDest)
	{
		fusbd_ctrl_error(pDev, pReq);
	}
	else if (0 != pReq->wLength)
  {
		if (0 != nDestLen)
    {
      nDestLen = MIN(nDestLen, pReq->wLength);
			fusbd_ctrl_send_data(pDev, pDest, nDestLen);
    }
    else
    {
			fusbd_ctrl_error(pDev, pReq);
    }
  }
  else
  {
    fusbd_ctrl_send_status(pDev);
  }
}

/**
 * @brief processing setting the address of the device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_set_address(fusbd_device_pt pDev,fusb_setup_reuqest_pt pReq)
{
	uint8_t  nAddr;

	if ((pReq->wIndex == 0) && (pReq->wLength == 0) && (pReq->wValue < 128))
	{
		if (pDev->nState == USBD_STATE_CONFIGURED)
		{
			fusbd_ctrl_error(pDev, pReq);
		}
		else
		{
			nAddr = pReq->wValue & 0x007F;
    
			on_fusbd_adpt_set_address(pDev->pAdapter, nAddr);
			fusbd_ctrl_send_status(pDev);

			if (nAddr != 0U)
			{
				pDev->nState = USBD_STATE_ADDRESSED;
			}
			else
			{
				pDev->nState = USBD_STATE_DEFAULT;
			}
		}
	}
  else
	{
		fusbd_ctrl_error(pDev, pReq);
	}
}

/**
 * @brief processing setting the configuration of the device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_set_config(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	uint8_t nCfgIdx;
	const uint8_t * const * lpDescriptors;
	uint8_t nCfgCount;
	
	// selected the list of the configuration descriptors by the speed
	if (pDev->nSpeed == USBD_SPEED_HIGH) 
	{
		nCfgCount = pDev->pConfig->pDescriptors->nHSConfigCount;
		lpDescriptors = pDev->pConfig->pDescriptors->pHSConfigDescriptorList;
	}
	else
	{
		nCfgCount = pDev->pConfig->pDescriptors->nFSConfigCount;
		lpDescriptors = pDev->pConfig->pDescriptors->pFSConfigDescriptorList;
	}

	// check if the index of the configuration if out of range
  nCfgIdx = pReq->ucValue[0];
	if (nCfgIdx > nCfgCount)
	{
		FUsbLogL1("  SetCfg Out of Range (%u:%u)\n", nCfgIdx, nCfgCount);
		fusbd_ctrl_error(pDev, pReq);
	}
	else
	{
		switch (pDev->nState)
		{
			case USBD_STATE_ADDRESSED:
				// config the classes if a valid configuration is selected after the address is set to the usb device
				if (0 != nCfgIdx)
				{
					pDev->nConfigIndex = nCfgIdx;

					FUsbDConfigClass(pDev, lpDescriptors[nCfgIdx - 1]);
					fusbd_ctrl_send_status(pDev);
					pDev->nState = USBD_STATE_CONFIGURED;
				}
				else
				{
					fusbd_ctrl_send_status(pDev);
				}
				break;

			case USBD_STATE_CONFIGURED:
				if (0 == nCfgIdx)
				{
					// unconfig the classes and return to the state of after the address is set to the usb device
					// if the 0 is selected by the host
					pDev->nState = USBD_STATE_ADDRESSED;
					pDev->nConfigIndex = nCfgIdx;
					FUsbDUnconfigClass(pDev);
				}
				else if (nCfgIdx != pDev->nConfigIndex)
				{
					// if a new configuration is selected, 
					// unconfig the classes first, and then config the classes with new configuration
					FUsbDUnconfigClass(pDev);
					pDev->nConfigIndex = nCfgIdx;
					FUsbDConfigClass(pDev, lpDescriptors[nCfgIdx - 1]);
				}
				else
				{
					// nothing need if the configuration no changed					
				}
				fusbd_ctrl_send_status(pDev);
				break;

			default:
				// changing of configuration is denid in an other state
				FUsbLogL1("  SetCfg in unknown state(%u)\n", pDev->nState);
				FUsbDUnconfigClass(pDev);
				fusbd_ctrl_error(pDev, pReq);
				break;
		}
  }
}

/**
 * @brief processing getting the configuration
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_get_config(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	if (1 != pReq->wLength)
  {
		fusbd_ctrl_error(pDev, pReq);
	}
	else
	{
		switch (pDev->nState)
    {
			case USBD_STATE_DEFAULT:
			case USBD_STATE_ADDRESSED:
				pDev->nConfigIndex = 0;
			
			case USBD_STATE_CONFIGURED:
        fusbd_ctrl_send_data(pDev, &pDev->nConfigIndex, 1);
        break;

			default:
				fusbd_ctrl_error(pDev, pReq);
				break;
		}
	}
}

/**
 * @brief processing getting the status of the device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_get_status(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	switch (pDev->nState)
	{
		case USBD_STATE_DEFAULT:
		case USBD_STATE_ADDRESSED:
		case USBD_STATE_CONFIGURED:
			if (2 != pReq->wLength)
			{
				fusbd_ctrl_error(pDev, pReq);
      }
			else
			{
				uint16_t nStatus = 0;
				uint8_t nCfgIdx = pDev->nConfigIndex;
				
				if (nCfgIdx > 0)
				{
					const uint8_t * pDesc;
					const fusbd_descriptor_set_t * lpDescriptors = pDev->pConfig->pDescriptors;
					
					nCfgIdx -= 1;
					if (pDev->nSpeed == USBD_SPEED_HIGH) 
					{
						pDesc = (nCfgIdx < lpDescriptors->nHSConfigCount) ? lpDescriptors->pHSConfigDescriptorList[nCfgIdx] : NULL;
					}
					else
					{
						pDesc = (nCfgIdx < lpDescriptors->nFSConfigCount) ? lpDescriptors->pFSConfigDescriptorList[nCfgIdx] : NULL;
					}
					if ((NULL != pDesc) && (0 != (pDesc[7] & 0x40)))
					{
						nStatus |= USB_CONFIG_SELF_POWERED;
					}
				}

				if (0 != pDev->nRemoteWakeup != 0U)
				{
					nStatus |= USB_CONFIG_REMOTE_WAKEUP;
				}

				fusbd_ctrl_send_resp(pDev, nStatus, 2);
			}
      break;

		default:
			fusbd_ctrl_error(pDev, pReq);
			break;
	}
}

/**
 * @brief processing setting the feature of the device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_set_feature(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	if (USB_FEATURE_REMOTE_WAKEUP == pReq->wValue)
	{
		// only support the remote_wakeup feature at present
		pDev->nRemoteWakeup = 1;
	}
	fusbd_ctrl_send_status(pDev);
}

/**
 * @brief processing clearing the feature of the device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_clr_feature(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	switch (pDev->nState)
	{
		case USBD_STATE_DEFAULT:
		case USBD_STATE_ADDRESSED:
		case USBD_STATE_CONFIGURED:
			if (USB_FEATURE_REMOTE_WAKEUP == pReq->wValue)
			{
				// only support the remote_wakeup feature at present
				pDev->nRemoteWakeup = 0;
			}
			fusbd_ctrl_send_status(pDev);
			break;

		default:
			fusbd_ctrl_error(pDev, pReq);
			break;
	}
}

/**
 * @brief processing the setup request for device
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_dev_request(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	switch (pReq->bmRequest & USB_REQ_TYPE_MASK)
	{
		case USB_REQ_TYPE_CLASS:
		case USB_REQ_TYPE_VENDOR:
			// if the request is defined by class or vendor, try to process it by the classes 
			BeginIterateClass(pDev, lpClass);
				fusbd_call_class_method(lpClass, SetupRequest, pReq);
			EndIterateClass(pDev);
			break;

		case USB_REQ_TYPE_STANDARD:
			// processing the stander request
			switch (pReq->bRequest)
      {
				case USB_REQ_GET_DESCRIPTOR:
					_fusbd_get_descriptor(pDev, pReq);
					break;

				case USB_REQ_SET_ADDRESS:
					_fusbd_set_address(pDev, pReq);
					break;

				case USB_REQ_SET_CONFIGURATION:
					_fusbd_set_config(pDev, pReq);
					break;

				case USB_REQ_GET_CONFIGURATION:
					_fusbd_get_config(pDev, pReq);
					break;

				case USB_REQ_GET_STATUS:
					_fusbd_get_status(pDev, pReq);
					break;

				case USB_REQ_SET_FEATURE:
					_fusbd_set_feature(pDev, pReq);
					break;

				case USB_REQ_CLEAR_FEATURE:
					_fusbd_clr_feature(pDev, pReq);
					break;

				default:
					fusbd_ctrl_error(pDev, pReq);
					break;
			}
			break;

		default:
			fusbd_ctrl_error(pDev, pReq);
			break;
	}
}

/**
 * @brief processing the setup request for the interface
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_intf_request(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
	switch (pReq->bmRequest & USB_REQ_TYPE_MASK)
	{
		case USB_REQ_TYPE_CLASS:
		case USB_REQ_TYPE_VENDOR:
		case USB_REQ_TYPE_STANDARD:
			switch (pDev->nState)
			{
				case USBD_STATE_DEFAULT:
				case USBD_STATE_ADDRESSED:
				case USBD_STATE_CONFIGURED:
					do
					{
						// selecting the class marked with the special interface and processing the request by the class
						uint8_t nIntfIdx = pReq->ucIndex[0];
						fusbd_class_pt lpClass = FUsbSelectClassByIntf(pDev, nIntfIdx);
						int iRet = -1;
						if (NULL != lpClass)
						{
							iRet = fusbd_call_class_method(lpClass, SetupRequest, pReq);
						}
						// if the process is fail, send an error signal to the host,
						// else send a zero length packet to the host when the length of the data requested by the host is zero.
						// it means if some data is requested by the host, the class must sent it manually and return 0 in the callback fucntion.
						if (iRet == 0)
						{
							if (0 == pReq->wLength)
							{
								fusbd_ctrl_send_status(pDev);
							}
						}
						else
						{
							fusbd_ctrl_error(pDev, pReq);
						}
					} while (0);
					break;

				default:
					fusbd_ctrl_error(pDev, pReq);
					break;
			}
			break;

		default:
			fusbd_ctrl_error(pDev, pReq);
			break;
	}
}

/**
 * @brief processing the setup request for the endpoint
 * 
 * @param pDev the usb device
 * @param pReq the request
 */
static void _fusbd_ep_request(fusbd_device_pt pDev, fusb_setup_reuqest_pt pReq)
{
  uint8_t nEpAddr = pReq->ucIndex[0];

	switch (pReq->bmRequest & USB_REQ_TYPE_MASK)
	{
		case USB_REQ_TYPE_CLASS:
		case USB_REQ_TYPE_VENDOR:
			do
			{
				// it the request is defined by the class or vendor, send the request to the class assigned with the special endpoint
				fusbd_class_pt lpClass = FUsbSelectClassByEP(pDev, nEpAddr);
				if (NULL != lpClass)
				{
					fusbd_call_class_method(lpClass, SetupRequest, pReq);
				}
			} while (0);
			break;

		case USB_REQ_TYPE_STANDARD:
			switch (pReq->bRequest)
			{
				case USB_REQ_SET_FEATURE:
					switch (pDev->nState)
					{
						case USBD_STATE_ADDRESSED:
							if (0 != (nEpAddr & 0x7F))
							{
								fusbd_adpt_ep_stall(pDev->pAdapter, nEpAddr);
								fusbd_adpt_ep_stall(pDev->pAdapter, 0x80);
							}
              else
              {
								fusbd_ctrl_error(pDev, pReq);
							}
							break;

						case USBD_STATE_CONFIGURED:
							if (USB_FEATURE_EP_HALT == pReq->wValue)
              {
                if ((0 != (nEpAddr & 0x7F)) && (0 == pReq->wLength))
								{
									fusbd_adpt_ep_stall(pDev->pAdapter, nEpAddr);
								}
							}
							fusbd_ctrl_send_status(pDev);
							break;

						default:
							fusbd_ctrl_error(pDev, pReq);
							break;
					}
					break;

				case USB_REQ_CLEAR_FEATURE:
					switch (pDev->nState)
					{
						case USBD_STATE_ADDRESSED:
              if (0 != (nEpAddr & 0x7F))
              {
                fusbd_adpt_ep_stall(pDev->pAdapter, nEpAddr);
								fusbd_adpt_ep_stall(pDev->pAdapter, 0x80);
							}
							else
							{
								fusbd_ctrl_error(pDev, pReq);
							}
							break;

						case USBD_STATE_CONFIGURED:
							if (USB_FEATURE_EP_HALT == pReq->wValue)
							{
								if (0 != (nEpAddr & 0x7F))
								{
									fusbd_adpt_ep_stall_clr(pDev->pAdapter, nEpAddr);
								}
								fusbd_ctrl_send_status(pDev);
								fusbd_class_pt lpClass = FUsbSelectClassByEP(pDev, nEpAddr);
								if (NULL != lpClass)
								{
									fusbd_call_class_method(lpClass, SetupRequest, pReq);
								}
							}
							break;

						default:
							fusbd_ctrl_error(pDev, pReq);
							break;
					}
					break;

				case USB_REQ_GET_STATUS:
					switch (pDev->nState)
					{
						case USBD_STATE_ADDRESSED:
							if (0 != (nEpAddr & 0x7F))
							{
								fusbd_ctrl_error(pDev, pReq);
							}
							else
							{
								fusbd_ctrl_send_resp(pDev, 0, 2);
							}
              break;

            case USBD_STATE_CONFIGURED:
							fusbd_ctrl_send_resp(pDev,
									(0 == (nEpAddr & 0x7F)) ? 0
																					: ((0 == fusbd_adpt_ep_isstall(pDev->pAdapter, nEpAddr)) ? 0 : 1),
									2);
              break;

						default:
							fusbd_ctrl_error(pDev, pReq);
							break;
					}
					break;
						
				default:
					fusbd_ctrl_error(pDev, pReq);
					break;
			}
			break;

		default:
			fusbd_ctrl_error(pDev, pReq);
			break;
	}
}

/** @endcond */

#endif	// End Request Actions

#if	1		// Begin Event

/** 
 * @defgroup event callback of the usb device 
 * @{
 */

/**
 * @brief event callback for the reset signal appearing in the BUS
 * 
 * @param pDev the usb device
 */
void on_fusbd_reset(fusbd_device_pt pDev)
{
	fusbd_reset_dev_obj(pDev);
	
	pDev->nState = USBD_STATE_DEFAULT;
	
	on_fusbd_adpt_init_endpoints(pDev, NULL);
}

/**
 * @brief event callback for a setup request being received from the host
 * 
 * @param pDev the usb device
 * @param pReqBuf the buffer contains the request 
 */
void on_fusbd_setup_request(fusbd_device_pt pDev, uint8_t *pReqBuf)
{
	fusb_setup_reuqest_t vReq;
	
	memcpy(&vReq, pReqBuf, sizeof(vReq));
	
	FUsbLogL4("Setup: %02X %02X %04X %04X %04X\n", vReq.bmRequest, vReq.bRequest, vReq.wValue, vReq.wIndex, vReq.wLength);
	
	switch (vReq.bmRequest & 0x1F)
	{
		case USB_REQ_RECIPIENT_DEVICE:
			_fusbd_dev_request(pDev, &vReq);
      break;

    case USB_REQ_RECIPIENT_INTERFACE:
			_fusbd_intf_request(pDev, &vReq);
      break;

    case USB_REQ_RECIPIENT_ENDPOINT:
      _fusbd_ep_request(pDev, &vReq);
      break;

    default:
			fusbd_adpt_ep_stall(pDev->pAdapter, vReq.bmRequest & 0x80);
      break;
  }
}

/**
 * @brief event callback for a transmition being completed in an endpoint
 * 
 * @param pDev the usb device
 * @param nEpAddr the address of the endpoint
 */
void on_fusbd_data_in(fusbd_device_pt pDev, uint8_t nEpAddr)
{
	if (0 != (nEpAddr & 0x7F))
	{
		fusbd_endpoint_pt pEP = FUsbSelectEndPoint(pDev, nEpAddr | 0x80);
		if (NULL != pEP)
		{
			pEP->nFlag &= (~FUSBD_EP_FLAG_XFER);
			fusbd_class_pt lpClass = FUsbSelectClassByIntf(pDev, pEP->nIntf);
			if (NULL != lpClass)
			{
				fusbd_call_class_method(lpClass, DataIn, pEP);
			}
		}
	}
}

/**
 * @brief event callback for some data being received in an endpoint
 * 
 * @param pDev the usb device
 * @param nEpAddr the address of the endpoint
 */
void on_fusbd_data_out(fusbd_device_pt pDev, uint8_t nEpAddr)
{
	if (0 == (nEpAddr & 0x7F))
	{
		if (NULL != pDev->fnEP0OutCallback)
		{
			pDev->fnEP0OutCallback(pDev->pEP0CallbackUser, pDev->pEP0OutBuf, pDev->nEP0DataOutTotal);
		}
	}
	else
	{
		fusbd_endpoint_pt pEP = FUsbSelectEndPoint(pDev, nEpAddr & 0x7F);
		if (NULL != pEP)
		{
			fusbd_class_pt lpClass = FUsbSelectClassByIntf(pDev, pEP->nIntf);
			if (NULL != lpClass)
			{
				fusbd_call_class_method(lpClass, DataOut, pEP);
			}
		}
	}
}

/**
 * @brief event callback for a suspend signal being received from the host
 * 
 * @param pDev the usb device
 */
void on_fusbd_suspend(fusbd_device_pt pDev)
{
	pDev->nState |= USBD_STATE_SUSPENDED;
	
	BeginIterateClass(pDev, lpClass);
		fusbd_call_class_method(lpClass, Suspend);
	EndIterateClass(pDev);
}

/**
 * @brief event callback for a resume signal being received from the host
 * 
 * @param pDev the usb device
 */
void on_fusbd_resume(fusbd_device_pt pDev)
{
	pDev->nState &= ~(USBD_STATE_SUSPENDED);
	
	BeginIterateClass(pDev, lpClass);
		fusbd_call_class_method(lpClass, Resume);
	EndIterateClass(pDev);
}

/**
 * @brief event callback for a sof signal being received from the host
 * 
 * @param pDev the usb device
 */
void on_fusbd_sof(fusbd_device_pt pDev)
{
	pDev->nState &= ~(USBD_STATE_SUSPENDED);
	
	BeginIterateClass(pDev, lpClass);
		fusbd_call_class_method(lpClass, SOF);
	EndIterateClass(pDev);
}

/** @} */

#endif	// End Event

#if	1		// Begin Global Functions

/**
 * @brief initialize a special usb device
 * 
 * @param pDev pointer to an usb device
 * @return int 0 for success
 */
int fusbd_device_init(fusbd_device_pt pDev)
{
	int iRet = -1;
	
	if ((NULL != pDev) && (NULL != pDev->pConfig->pDescriptors))
	{
		fusbd_reset_dev_obj(pDev);
		
		iRet = on_fusbd_adpt_init(pDev);
		
		if (0 == iRet)
		{
			BeginIterateClass(pDev, lpClass)
				fusbd_call_class_method(lpClass, Init);
			EndIterateClass(pDev)
			#if	0
			on_fusbd_adpt_init_endpoints(pDev, NULL);
			#endif
		}
	}
	
	return iRet;
}

/**
 * @brief start a special usb device
 * 
 * @param pDev pointer to an usb device
 * @return int 0 for success
 */
int fusbd_device_start(fusbd_device_pt pDev)
{
	ASSERT(NULL != pDev, return -1);
	
	return on_fusbd_adpt_start(pDev->pAdapter);
}

/**
 * @brief check if a configuration is selected by the host to the special usb device
 * 
 * @param pDev pointer to an usb device
 * @param nTimeout timeout for waiting the configaration selected, 0 for without waiting, -1 for without timeout
 * @return uint8_t 0 for no configed, other is the index of the configuration selected by the host
 */
uint8_t fusbd_device_check_configed(fusbd_device_pt pDev, uint32_t nTimeout)
{
	uint32_t nOriTick = fusbd_adpt_get_tickcount(pDev->pAdapter);
	int iRet = 0;
	
	if (NULL != pDev)
	{
		do
		{
			iRet = ((pDev->nState == USBD_STATE_CONFIGURED) ? pDev->nConfigIndex : 0);
			if ((uint32_t)-1 != nTimeout)
			{
				if ((fusbd_adpt_get_tickcount(pDev->pAdapter) - nOriTick) > nTimeout)
				{
					nTimeout = 0;
				}
			}
		} while ((0 != nTimeout) && (0 == iRet));
	}
	
	return iRet;
}

#endif	// End Global Functions

/** @} */
