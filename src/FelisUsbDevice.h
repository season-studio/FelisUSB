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
#if	!defined(__FELIS_USB_DEVICE_H__)
#define	__FELIS_USB_DEVICE_H__

#include "FelisUsbDefType.h"

/**
 * @defgroup FelisUSB
 * @{
 */

#define	FUSBD_TIMEOUT_INFINITY					((uint32_t)-1)

#if	1		// Basic Functions

/**
 * @brief send an error signal for the controlling transmition
 * 
 * @param pDev the usb device
 * @param pReq the request buffer
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_ctrl_error(fusbd_device_pt pDev, fusb_setup_reuqest_t * pReq)
{
	UNUSED(pReq);
	
	fusbd_adpt_ep_stall(pDev->pAdapter, 0x80);
	fusbd_adpt_ep_stall(pDev->pAdapter, 0x00);

	return 0;
}

/**
 * @brief send data by the controlling transmition
 * 
 * @param pDev the usb device
 * @param pBuf the buffer contains the data to be sent
 * @param nSize the size of the data to be sent
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_ctrl_send_data(fusbd_device_pt pDev, const void * pBuf, size_t nSize)
{
	pDev->nEP0InFlag = ((nSize > 0) ? 1 : 0);
	pDev->nEP0DataInRemain = nSize;
	return fusbd_adpt_transmit(pDev->pAdapter, 0, (uint8_t *)pBuf, nSize);
}

/**
 * @brief send a simple response by the controlling transmition
 * 
 * @param pDev the usb device
 * @param nVal the value of the simple response
 * @param nSize the size of the simple response
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_ctrl_send_resp(fusbd_device_pt pDev, uint32_t nVal, size_t nSize)
{
	pDev->gCtrlResp = nVal;
	return fusbd_ctrl_send_data(pDev, &pDev->gCtrlResp, nSize);
}

/**
 * @brief send a zere length packet by the controlling transmition
 * 
 * @param pDev the usb device
 * @return int 0 for success 
 */
__STATIC_FORCEINLINE int fusbd_ctrl_send_status(fusbd_device_pt pDev)
{
	return fusbd_adpt_transmit(pDev->pAdapter, 0, NULL, 0);
}

/**
 * @brief start receiving data from the controlling transmition
 * 
 * @param pDev the usb device
 * @param pBuf the buffer for receiveing the data
 * @param nSize the size of the data would be received
 * @param pfnCallback the callback function need being invoked when the data is received, can be NULL
 * @param pUser the user data will passed to the callback function
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_ctrl_receive(fusbd_device_pt pDev, void * pBuf, size_t nSize, fusbd_ep0_out_callback_fn_t pfnCallback, const void * pUser)
{
	pDev->nEP0DataOutRemain = nSize;
	pDev->nEP0DataOutTotal = nSize;
	pDev->pEP0OutBuf = pBuf;
	pDev->nEP0OutFlag = ((nSize > 0) ? 1 : 0);
	pDev->fnEP0OutCallback = pfnCallback;
	pDev->pEP0CallbackUser = pUser;
	return fusbd_adpt_prepare_receive(pDev->pAdapter, 0, pBuf, nSize);
}

/**
 * @cond
 * @brief set speed of the usb device
 * 
 * @param pDev the usb device
 * @param nSpeed the speed
 * @return int 0 for success
 */
__STATIC_FORCEINLINE int fusbd_set_speed(fusbd_device_pt pDev, uint8_t nSpeed)
{
	pDev->nSpeed = nSpeed;
	return 0;
}
/**
 * @endcond
 */

int fusbd_device_init(fusbd_device_pt pDev);
int fusbd_device_start(fusbd_device_pt pDev);
uint8_t fusbd_device_check_configed(fusbd_device_pt pDev, uint32_t nTimeout);
int fusbd_ep_open(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
int fusbd_ep_close(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
int fusbd_ep_stall(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
int fusbd_ep_stall_clr(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
bool fusbd_ep_isstall(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
int fusbd_ep_flush(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP);
bool fusbd_ep_is_busy(fusbd_endpoint_pt pUEP);
bool fusbd_ep_is_opened(fusbd_endpoint_pt pUEP);
int fusbd_send_data(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize, uint32_t nTimeout);
int fusbd_send_data_sync(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize);
int fusbd_send_data_async(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, const void * pBuf, size_t nSize);
int fusbd_prepare_receive(fusbd_device_pt pDev, fusbd_endpoint_pt pUEP, void * pBuf, size_t nSize);

	#if	1		// Macro packaging of basic functions for class
		/**
		 * @brief toolkit for opening an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_open(pClass, pUEP)				fusbd_ep_open((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for closing an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_close(pClass, pUEP)			fusbd_ep_close((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for setting an endpoint to stall state in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_stall(pClass, pUEP)			fusbd_ep_stall((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for clearing the stall state for an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_stall_clr(pClass, pUEP)	fusbd_ep_stall_clr((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for checking if an endpoint is set to stall state in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_isstall(pClass, pUEP)		fusbd_ep_isstall((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for flushing an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 */
		#define	fusbd_class_ep_flush(pClass, pUEP)			fusbd_ep_flush((pClass)->pDev, pUEP)
		/**
		 * @brief toolkit for sending data from an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 * @param pBuf the data to send
		 * @param nSize the size of the data in the buffer
		 * @param nTimeout time out for waiting the transmit complete
		 */
		#define	fusbd_class_send_data(pClass, pUEP, pBuf, nSize, nTimeout)	\
				fusbd_send_data((pClass)->pDev, pUEP, pBuf, nSize, nTimeout)
		/**
		 * @brief toolkit for sending data from an endpoint in a usb class until the transmition is completed
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 * @param pBuf the data to send
		 * @param nSize the size of the data in the buffer
		 */
		#define	fusbd_class_send_data_sync(pClass, pUEP, pBuf, nSize)	\
				fusbd_send_data_sync((pClass)->pDev, pUEP, pBuf, nSize)
		/**
		 * @brief toolkit for sending data from an endpoint in a usb class without waiting
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 * @param pBuf the data to send
		 * @param nSize the size of the data
		 */
		#define	fusbd_class_send_data_async(pClass, pUEP, pBuf, nSize)	\
				fusbd_send_data_async((pClass)->pDev, pUEP, pBuf, nSize)
		/**
		 * @brief toolkit for preparing receiving data from an endpoint in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pUEP pointer to the endpoint
		 * @param pBuf the buffer to receive the data
		 * @param nSize the size of the buffer
		 */
		#define	fusbd_class_prepare_receive(pClass, pUEP, pBuf, nSize)	\
				fusbd_prepare_receive((pClass)->pDev, pUEP, pBuf, nSize)
		/**
		 * @brief toolkit for sending data by controlling transmition in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pBuf the data to send
		 * @param nSize the size of the data
		 */
		#define	fusbd_class_ctrl_send_data(pClass, pBuf, nSize)	\
				fusbd_ctrl_send_data((pClass)->pDev, pBuf, nSize)
		/**
		 * @brief toolkit for receiving data by controlling transmition in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pBuf the buffer to receive the data
		 * @param nSize the size of the buffer
		 * @param fn the callback fucntion
		 * @param pUser the argument pass to the callback function
		 */
		#define	fusbd_class_ctrl_receive(pClass, pBuf, nSize, fn, pUser)	\
				fusbd_ctrl_receive((pClass)->pDev, pBuf, nSize, (fusbd_ep0_out_callback_fn_t)fn, pUser)
		/**
		 * @brief toolkit for sending a zero length packet by controlling transmition in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 */
		#define	fusbd_class_ctrl_send_status(pClass)					fusbd_ctrl_send_status((pClass)->pDev)
		/**
		 * @brief toolkit for sending an error signal by controlling transmition in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param pReq the content of the request
		 */
		#define	fusbd_class_ctrl_error(pClass, pReq)					fusbd_ctrl_error((pClass)->pDev, pReq)
		/**
		 * @brief toolkit for sending a simple response by controlling transmition in a usb class
		 * @param pClass pointer to the instance of the device interface class
		 * @param val the value of the simple response
		 * @param nSize the size of the simple reponse, must no greater then 4byte
		 */
		#define	fusbd_class_ctrl_send_resp(pClass, val, nSize)	\
				fusbd_ctrl_send_resp((pClass)->pDev, val, nSize)
	#endif	// Macro packaging of basic functions for class

#endif	// Basic Functions

#if	1		// Event Callback Functions
void on_fusbd_reset(fusbd_device_pt pDev);
void on_fusbd_setup_request(fusbd_device_pt pDev, uint8_t *pReqBuf);
void on_fusbd_data_in(fusbd_device_pt pDev, uint8_t nEpAddr);
void on_fusbd_data_out(fusbd_device_pt pDev, uint8_t nEpAddr);
void on_fusbd_suspend(fusbd_device_pt pDev);
void on_fusbd_resume(fusbd_device_pt pDev);
void on_fusbd_sof(fusbd_device_pt pDev);
#endif	// Event Callback Functions

#if	1		// Adapter event callbacks
int on_fusbd_adpt_init(fusbd_device_pt pDev);
int on_fusbd_adpt_start(fusbd_adapter_t *pInst);
int on_fusbd_adpt_set_address(fusbd_adapter_t *pInst, uint8_t nAddr);
int on_fusbd_adpt_init_endpoints(fusbd_device_pt pDev, fusbd_endpoint_pt pFirstEP);
#endif	// Adapter event callbacks

/** @} */

#endif	// __FELIS_USB_DEVICE_H__
