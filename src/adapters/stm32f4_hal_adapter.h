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
#if	!defined(__STM32_HAL_FELIS_USB_ADAPTER_H__)
#define	__STM32_HAL_FELIS_USB_ADAPTER_H__

#include "cortex_m_adapter.h"
#include "stm32f4xx_hal.h"

#define	fusbd_adapter_t					PCD_HandleTypeDef

// define the total size of the dedicate ram for the fifo of USB
#if	!defined(USB_PBUFFER_TOTAL_SIZE)
	#define	USB_PBUFFER_TOTAL_SIZE	(1024 + 256)
#endif

// define the minus size of the fifo item of the USB
#define	MIN_USB_FIFO_ITEM_SIZE		(16)

/**
 * @defgroup Adapter_Functions
 * @{
 */

/**
 * @brief open an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @param nMps the max_packet_size of the endpoint
 * @param nType the type of the transmition of the endpoint
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_open(fusbd_adapter_t * pInst, uint8_t nEpAddr, size_t nMps, uint8_t nType)
{
	return (int)HAL_PCD_EP_Open(pInst, nEpAddr, nMps, nType);
}

/**
 * @brief close an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @return int 0 for address
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_close(fusbd_adapter_t * pInst, uint8_t nEpAddr)
{
	return (int)HAL_PCD_EP_Close(pInst, nEpAddr);
}

/**
 * @brief set an endpoint to stall
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @return int 0 for address
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_stall(fusbd_adapter_t * pInst, uint8_t nEpAddr)
{
	return (int)HAL_PCD_EP_SetStall(pInst, nEpAddr);
}

/**
 * @brief clear stall state for an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @return int 0 for address
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_stall_clr(fusbd_adapter_t * pInst, uint8_t nEpAddr)
{
	return (int)HAL_PCD_EP_ClrStall(pInst, nEpAddr);
}

/**
 * @brief check if an endpoint is in stall state
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @return int 0 for address
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_isstall(fusbd_adapter_t * pInst, uint8_t nEpAddr)
{
	if(0 != (nEpAddr & 0x80))
  {
    return pInst->IN_ep[nEpAddr & 0x7F].is_stall;
  }
  else
  {
    return pInst->OUT_ep[nEpAddr & 0x7F].is_stall;
  }
}	

/**
 * @brief flush an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_adpt_ep_flush(fusbd_adapter_t * pInst, uint8_t nEpAddr)
{
	return (int)HAL_PCD_EP_Flush(pInst, nEpAddr);
}

/**
 * @brief transmit data by an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_adpt_transmit(fusbd_adapter_t *pInst, uint8_t nEpAddr, uint8_t *pBuf, size_t nSize)
{
  return (int)HAL_PCD_EP_Transmit(pInst, nEpAddr, pBuf, nSize);
}

/**
 * @brief receive data from an endpoint
 * 
 * @param pInst the instance of the adapter
 * @param nEpAddr the address of the endpoint
 * @param pBuf the buffer for receiving the data
 * @param nSize the size of the data would be received
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_adpt_prepare_receive(fusbd_adapter_t *pInst, uint8_t nEpAddr, void *pBuf, size_t nSize)
{
	return (int)HAL_PCD_EP_Receive(pInst, nEpAddr, (uint8_t*)pBuf, nSize);
}

/**
 * @brief get the tick count
 * 
 * @param pInst the instance of the adapter
 * @return uint32_t the tick count
 */
__STATIC_FORCEINLINE uint32_t fusbd_adpt_get_tickcount(fusbd_adapter_t *pInst)
{
	return HAL_GetTick();
}

/** @} */

#endif	// __STM32_HAL_FELIS_USB_ADAPTER_H__
