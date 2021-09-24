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
#if	!defined(__FELIS_USB_DEF_TYPE_H__)
#define	__FELIS_USB_DEF_TYPE_H__

#include "utility.h"

#include "FelisUsbDef.h"
#include "FelisUsbStdType.h"

#include "FelisUsbBoard.h"

/**
 * @defgroup FelisUSB
 * @{
 */

/**
 * @brief pointer type of the fusb device
 */
typedef struct _tag_fusbd_device * fusbd_device_pt;

/**
 * @cond
 * @enum fusbd_speed_enum_t
 * @brief enum type of the speed of the usb device
 */
typedef enum
{
	USBD_SPEED_FULL = 0,
	USBD_SPEED_HIGH,
	USBD_SPEED_LOW
} fusbd_speed_enum_t;
/** @endcode */

/**
 * @cond
 * @enum fusbd_device_state_enum_t
 * @brief enum type of the state of the usb device
 */
typedef enum
{
	USBD_STATE_UNKNOWN = 0,
	USBD_STATE_DEFAULT = 1,
	USBD_STATE_ADDRESSED,
	USBD_STATE_CONFIGURED,
	USBD_STATE_SUSPENDED = 0x80
} fusbd_device_state_enum_t;
/** @endcode */

/**
 * @struct fusbd_descriptor_set_t
 * @brief type of the set of the descriptors of the usb deivce
 * 
 */
typedef struct 
{
	const uint8_t *	pDeviceDescriptor;	///< point to the device descriptor
	const uint8_t* const*	pHSConfigDescriptorList;	///< point to the set of the configuration descriptors in high speed mode
	const uint8_t* const*	pFSConfigDescriptorList;	///< point to the set of the configuration descriptors in full speed mode
	const uint8_t* const*	pOtherSpeedConfigDescriptorList;	///< point to the set of the configuration descriptors in other speed mode
	const uint8_t *	pBOSDescriptor;	///< point to the BOS descriptor
	const uint8_t * pDeviceQualifierDescriptor;	///< point to the device qualifier descriptor
	const fusb_str_descriptor_t* const* pStringDescriptorList;	///< point to the set of the string descriptors
	uint8_t					nHSConfigCount;	///< count of the configuration descriptors in high speed mode
	uint8_t					nFSConfigCount;	///< count of the configuration descriptors in full speed mode
	uint8_t					nOtherSpeedConfigCount;	///< count of the configuration descriptors in other speed mode
	uint8_t					nStringCount;	///< count of the string descriptors
} fusbd_descriptor_set_t;

/**
 * @cond
 */
/**
 * @defgroup flags of the endpoint
 * @{
 */
// flag to show the endpoint is opned
#define	FUSBD_EP_FLAG_OPEN			(1)
// flag to show the endpoint is in transmiting
#define	FUSBD_EP_FLAG_XFER			(2)
/** @} */
/** @endcond */

/**
 * @struct fusbd_endpoint_t
 * @brief type of the endpoint of the usb device
 */
typedef struct _tag_fusbd_endpoint
{
	struct _tag_fusbd_endpoint *	pNext;	///< point to the next endpoint
	const uint8_t * 							pDesc;	///< point to the descriptor of this endpoint
	uint8_t												nIntf;	///< the index of the interface use this endpoint
	volatile uint8_t							nFlag;	///< the flag of this endpoint
	uint16_t											nXferSize;	///< the size of the data being transmited by this endpoint
	void *												pXferBuf;	///< the buffer contains the data being transmited by this endpoint
} fusbd_endpoint_t;

/**
 * @brief type of the pointer of the endpoint
 */
typedef fusbd_endpoint_t * fusbd_endpoint_pt;

#if	!defined(FUSBD_INTF_MAXCOUNT)
	#define	FUSBD_INTF_MAXCOUNT		(32)
#endif

#define	FUsbIntfMarkIdx(n)			(((uint32_t)(n)) >> 5)
#define	FUsbIntfMarkBit(n)			(1 << ((n) & 31))
#define	FUSBD_INTF_MARK_COUNT		((FUSBD_INTF_MAXCOUNT + 31) / 32)

/**
 * @brief toolkit for inheriting the basic members of the class's runtime
 */
#define	INHERIT_FUSBD_CLASS_RUNTIME	\
	uint32_t		nIntfMark[FUSBD_INTF_MARK_COUNT]

/**
 * @brief type of the pointer of the class
 */
typedef const struct _tag_fusbd_class * fusbd_class_pt;

/**
 * @struct fusbd_class_runtime_t
 * @brief type of the class's runtime
 */
typedef struct
{
	INHERIT_FUSBD_CLASS_RUNTIME;
	
} fusbd_class_runtime_t;

/**
 * @brief type of the pointer of the class's runtime
 */
typedef fusbd_class_runtime_t * fusbd_class_runtime_pt;

/**
 * @brief type of the callback for initializing the class
 */
typedef int (*fusbd_class_Init_fn_t)(fusbd_class_pt pClass);
/**
 * @brief type of the callback for configing the class when the usb device is configed by the host
 */
typedef size_t (*fusbd_class_Config_fn_t)(fusbd_class_pt pClass, const uint8_t * pDesc);
/**
 * @brief type of the callback for finishing configing the class when the usb device is configed by the host
 */
typedef int (*fusbd_class_ConfigDone_fn_t)(fusbd_class_pt pClass);
/**
 * @brief type of the callback for unconfiging the class when the configuration of the usb device is changed by the host
 */
typedef int (*fusbd_class_Unconfig_fn_t)(fusbd_class_pt pClass);
/**
 * @brief type of the callback for assigning an endpoint to a class when the usb device is config by the host
 */
typedef fusbd_endpoint_pt (*fusbd_class_AssignEndPoint_fn_t)(fusbd_class_pt pClass, const uint8_t * pEpDesc, const uint8_t * pIntfDesc);
/**
 * @brief type of the callback when the usb device receive a setup request from the host
 */
typedef int (*fusbd_class_SetupRequest_fn_t)(fusbd_class_pt pClass, fusb_setup_reuqest_pt pReq);
/**
 * @brief type of the callback when a transmiting is completed in an endpoint
 */
typedef int (*fusbd_class_DataIn_fn_t)(fusbd_class_pt pClass, fusbd_endpoint_pt pEndPoint);
/**
 * @brief type of the callback when some data is received in an endpoint
 */
typedef int (*fusbd_class_DataOut_fn_t)(fusbd_class_pt pClass, fusbd_endpoint_pt pEndPoint);
/**
 * @brief type of the callback when the usb device is suspended by the host
 */
typedef int (*fusbd_class_Suspend_fn_t)(fusbd_class_pt pClass);
/**
 * @brief type of the callback when the usb device is resumed by the host
 */
typedef int (*fusbd_class_Resume_fn_t)(fusbd_class_pt pClass);
/**
 * @brief type of the callback when a SOF signal is sent from the host
 */
typedef int (*fusbd_class_SOF_fn_t)(fusbd_class_pt pClass);

/**
 * @struct fusbd_class_methods_t
 * @brief type of the set of the callbacks of the class
 */
typedef struct
{
	#define	_FUSBD_CLASS_METHOD(name)		fusbd_class_##name##_fn_t	name
	_FUSBD_CLASS_METHOD(Init);	///< the callback function for initializing the class
	_FUSBD_CLASS_METHOD(Config);	///< the callback function for configing the class when the usb device is configed by the host
	_FUSBD_CLASS_METHOD(ConfigDone);	///< the callback function for finishing configing the class when the usb device is configed by the host
	_FUSBD_CLASS_METHOD(Unconfig);	///< the callback function for unconfiging the class when the usb device is configed by the host
	_FUSBD_CLASS_METHOD(AssignEndPoint); ///< the callback function for assigning an endpoint to the class when the usb device is configed by the host
	_FUSBD_CLASS_METHOD(SetupRequest);	///< the callback function for processing the request when the usb device received setup request from ths host
	_FUSBD_CLASS_METHOD(DataIn);	///< the callback function when a transmiting is completed in an endpoint
	_FUSBD_CLASS_METHOD(DataOut);	///< the callback function when some data is received from the host
	_FUSBD_CLASS_METHOD(Suspend);	///< the callback function for suspending the class when the usb device is suspended by the host
	_FUSBD_CLASS_METHOD(Resume);	///< the callback function for resuming the class when the usb device is resumed by the host
	_FUSBD_CLASS_METHOD(SOF);	///< the callback function for processing the SOF signal
	#undef	_FUSBD_CLASS_METHOD
} fusbd_class_methods_t;

/**
 * @brief toolkit for invoke a method of a class
 * @param lpClass pointer to the instance of the device interface class
 * @param name the name of the method
 * @param ... arguments passed to the method
 */
#define	fusbd_call_class_method(lpClass, name, ...)		((NULL != (lpClass)->pMethods->name) ? (lpClass)->pMethods->name(lpClass, ##__VA_ARGS__) : 0)

/**
 * @brief toolkit for starting the declaration of a set of methods for a class
 * @param name the name of the set of the methods
 */
#define	BEGIN_FUSBD_CLASS_METHODS(name)		const fusbd_class_methods_t name = {

/**
 * @brief toolkit for declaring a method of a class
 * @param name the name of the method
 * @param fn the function assign to the method
 */
#define	FUSBD_CLASS_METHOD(name, fn)			.name = (fusbd_class_##name##_fn_t)fn

/**
 * @brief toolkit for ending the declaration of a set of methods for a class
 */
#define	END_FUSBD_CLASS_METHODS()					}

/**
 * @brief toolkit for externalizing the set of the methods for a class
 * @param name the name of the set of the methods
 */
#define	EXTERN_FUSBD_CLASS_METHODS(name)	extern const fusbd_class_methods_t name

/**
 * @brief toolkit fot inheriting the basic member of a usb class
 */
#define	INHERIT_FUSBD_CLASS	\
  fusbd_device_pt pDev;	\
	const fusbd_class_methods_t * pMethods;	\
	fusbd_class_runtime_pt const pRuntime

/**
 * @struct fusbd_class_t
 * @brief type of the usb class
 */
typedef struct _tag_fusbd_class
{
	INHERIT_FUSBD_CLASS;
} fusbd_class_t;

/**
 * @brief check if the class has been marked with any interface
 * 
 * @param pClass point to a usb class
 * @return bool true for marked, false for none
 */
__STATIC_FORCEINLINE bool fusbd_class_intf_marked(const void * pClass)
{
	for (int i = 0; i < FUSBD_INTF_MARK_COUNT; i++)
	{
		if (0 != ((fusbd_class_pt)pClass)->pRuntime->nIntfMark[i])
		{
			return true;
		}
	}
	
	return false;
}

/**
 * @brief type of the callback function when some data is received in the endpoint 0
 */
typedef void (*fusbd_ep0_out_callback_fn_t)(const void *pUser, void * pBuf, size_t nSize);

/**
 * @struct fusbd_device_config_t
 * @brief type of the configuration of the usb device
 */
typedef struct
{
	const fusbd_descriptor_set_t * pDescriptors;	///< pointer to the descriptors for the device
	fusbd_class_pt zClassPtrs[];	///< array of the classes assigned to the device, this array must be ended by NULL
} fusbd_device_config_t;

/**
 * @struct fusbd_device_t
 * @brief type of the usb device
 */
typedef struct _tag_fusbd_device
{
	const fusbd_device_config_t * pConfig;	///< pointer to the configuration of the device

	fusbd_adapter_t * pAdapter;	///< pointer to the instance of the adapter of the USB hardware

	uint8_t nRemoteWakeup;	///< record the state of the remote_wakeup
	uint8_t	nSpeed;	///< record the speed of the usb device
	uint8_t nConfigIndex;	///< record the index of the configuration the host selected
	volatile uint8_t nState;	///< record the state of the usb device
	
	uint16_t nEP0DataInRemain;	///< record the size of the data remained for transmiting in endpoint 0
	uint16_t nEP0DataOutRemain;	///< record the size of the data remained for receiving in endpoint 0
	uint16_t nEP0DataOutTotal;	///< record the total size of the data needed receiving in endpoint 0
	uint8_t nEP0InFlag;	///< record the state of the transmiting in endpoint 0
	uint8_t nEP0OutFlag;	///< record the state of the receiving in endpoint 0
	void * pEP0OutBuf;	///< record the buffer of for receiving the data in endpoint 0
	const void * pEP0CallbackUser;	///< the user data passed to the callback function when some data is received in the endpoint 0
	fusbd_ep0_out_callback_fn_t fnEP0OutCallback;	///<< the callback function when some data is received in the endpoint 0
	
	fusbd_endpoint_pt pEndPoints;	///< record the first pointer of the endpoint of the link list of all endpoints assigned to the classes in the usb device
	
	uint32_t gCtrlResp;	///< a temporary buffer for storing the simple response sent from the controlling transmition
} fusbd_device_t;

/**
 * @brief toolkit for declaring the configuration of the usb device
 * @param pDescs pointer to the list of all descriptors
 * @param ... list of the pointers to the instance of the device interface classes
 */
#define	FUSBD_DEVICE_CONFIG(pDescs, ...)	\
	(const fusbd_device_config_t) { .pDescriptors = pDescs, .zClassPtrs = { ##__VA_ARGS__, NULL } }

/**
 * @brief toolkit for declaring the usb device object
 * @param pCfg the pointer to the configuration of the usb device
 */
#define	FUSBD_DEVICE(pCfg, ...)	(fusbd_device_t){ .pConfig = pCfg, ##__VA_ARGS__ }

/** @} */

#endif	// __FELIS_USB_DEF_TYPE_H__
