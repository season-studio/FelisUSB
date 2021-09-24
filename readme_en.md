# Felis USB
![alt FelisUSB](./FelisUSB.png)
-----------
[中文](./readme.md) | **英文**

## What
Felis USB is an USB stack for embedded system. It is light weight, and no depending on any software system.

## Why
There was a requirement of developing a composite USB device base on STM32 mcu for a technology researching in our company. The usb stack in the HAL library is too large. We try the tinyUSB and teenyUSB instead. But the tinyUSB does not support ISOC transmition. And the teenyUSB has some BUG when we implement UVC interface. And also, all the three stack do not divide the constant data from the variable data. That cause many occupation of RAM.
Because of this situation, I write the first edition of this USB stack in my mid-autumn festival holidays.

## Characteristic
- There is no requirement of any software system for the FelisUSB
- The FelisUSB supports multi-configuration in a USB device
- The FelisUSB supports modular device interface class
- The FelisUSB reads configuration information from the descriptors as much as possible. This reduces the bugs caused by the mistake in synchronization of the duplicate data in the code.
- The SDK of FelisUSB is absract. The information of hardware is no need for the application code, such as the address of endpoint and so on.

## The feature and The Update plan
Features in the current version:
- Support device stack base on USB 2.0 protocol
- Provide the adapter code for stm32f4 mcu
- Provide the device interface class implementation of HID and UVC

Update plan:
- Indeterminacy.
Embedded debelopment is not my main job at present. So there is no clear plan for updating this project.

## How

### Use for application
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

### Write a new device interface class base on the FelisUSB
There are three tasks for writing a new device interface class:
- **Define the design-time data**
The design-time data is no changed in run-time. Such as the configuration of the device, the callback function, the buffer space, and so on. The design-time data of a special device interface class must inherit the basic class. So you must write "INHERIT_FUSBD_CLASS;" as the first line of the struct of the design-time data.

- **Define the run-time data**
The run-time data is the variable data of the class. Such as the status of the device, the processing data during the communication with the host, and so on.
You must write "INHERIT_FUSBD_CLASS_RUNTIME;" as the first line of the struct of the run-time data to inherit the basic class for the special device interface class.

- **Implement the callbacks**
All the callbacks are declared in the fusbd_class_methods_t. You can implement some of them as needed.

**Example:** reference the code in "src/classes".

### Detail introduction of the usage
Reference [usage_en.md](./docs/usage_en.md)

## Introduction of the designing
Reference [design_en.md](./docs/design_en.md)

## Reference
- The processing logic of the low-level communication reference from the STM32 HAL Library
- The parsing the configuration descriptor in set-config step reference from the tinyUSB
- The initialization of the endpoints reference from the teenyUSB
- The processing of the setup-request in the HID interface class reference from the teenyUSB
