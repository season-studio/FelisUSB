# How to use the Felis USB

## Use for application
Use the FelisUSB for application as follow：
- create a project, and add the BSP code. For example: create a project by STM32Cube, enable the USB module, enable and generating the default code of the interrupt of the USB
- add FelisUsbDevice.c into the project
- add the code of the usb device interface class into the project, such as FelisUsbDClassHID.c
- add the code of the adapter into yhe project, such as stm32f4_hal_adapter.c
- create a header file named "FelisUsbBoard.h" for the global configuration
- create a code file for declaretion the descriptors
- include "FelisUSB.h" in the application code
- include the header of the usb device interface class you need in the application code, such as FelisUsbDClassHID.h
- declare the instance of the usb device interface class you need, and write the application callback
- declare the intsance of the usb device, and assign the descriptors and the instance of interface class to it
- invoke the SDK to start the stack

Example（The whole code is stored in the sample folder）：
``` C
///////////////////////////////////////////////////////////
/// FeliseUsbBoard.h 示例
#if	!defined(__FELIS_USB_BOARD_H__)
#define	__FELIS_USB_BOARD_H__

#include "adapters/stm32f4_hal_adapter.h"

#define FUSBD_ADPT_SPEED								(PCD_SPEED_FULL)

#define FUSB_DEBUG_OUT									(3)

#endif	// __FELIS_USB_BOARD_H__

///////////////////////////////////////////////////////////
/// 应用代码示例
#include "FelisUSB.h"
#include "classes/FelisUsbDClassHID.h"
#include "desc.h"

extern fusbd_device_t gUsbDev;

uint8_t HidBuf[64];

static int OnHidReceived(fusbd_hid_pt pHid, void * pBuf)
{
	// TODO: ...
}

const fusbd_hid_t gHidClass = FUSBD_HID_CLASS(
	&gUsbDev,
	HidReportDescriptor, 
	FUSBD_HID_CLASS_RUNTIME(HidBuf),
	.OnReceived = OnHidReceived
);

fusbd_device_t gUsbDev = FUSBD_DEVICE(
	&FUSBD_DEVICE_CONFIG(
		&FUsbDeviceDescriptors,
		(fusbd_class_pt)&gHidClass
	)
);

...

int main()
{
	...
	fusbd_device_init(&gUsbDev);
	fusbd_device_start(&gUsbDev);
	fusbd_device_check_configed(&gUsbDev, FUSBD_TIMEOUT_INFINITY);
	// TODO: after the usb device is configed by the host
	...
}
```

## Write a new device interface class base on the FelisUSB
There are three tasks for writing a new device interface class:
- **Define the design-time data**
The design-time data is no changed in run-time. Such as the configuration of the device, the callback function, the buffer space, and so on. The design-time data of a special device interface class must inherit the basic class. So you must write "INHERIT_FUSBD_CLASS;" as the first line of the struct of the design-time data.

- **Define the run-time data**
The run-time data is the variable data of the class. Such as the status of the device, the processing data during the communication with the host, and so on.
You must write "INHERIT_FUSBD_CLASS_RUNTIME;" as the first line of the struct of the run-time data to inherit the basic class for the special device interface class.

- **Implement the callbacks**
All the callbacks are declared in the fusbd_class_methods_t. You can implement some of them as needed.

**Example:** reference the code in "src/classes".

# Porting the Felis USB

For porting the Felis USB, the code and header of a new adapter should be provided. The adapter contains adapter functions and adapter event callbacks. It is better to provide the adapter functions as inline functions or macro for performance reason. You can create a new adapter reference from the exist code in "./src/adapters".

# SDK
- [Core API of FelisUSB](./api/api-FelisUSB.md)
- [Toolkits for getting information from descriptors](./api/api-toolkits.md)
- [Adapter functions](./api/api-Adapter_Functions.md)
- [Adapter event callbacks](./api/api-Adapter_Event_Callbacks.md)
