# 使用说明

## 使用Felis USB构建应用
可按照以下步骤使用Felis USB协议栈构建应用：
- 新建应用工程，并添加必要的板级支持代码，例如：在STM32处理器环境下，用STM32Cube新建工程，并启用USB设备功能，使能USB中断，生成默认USB中断处理程序
- 向工程中添加协议栈源码FelisUsbDevice.c
- 向工程中添加设备类源码，例如：FelisUsbDClassHID.c
- 向工程中添加目标板适配层源码，例如：stm32f4_hal_adapter.c
- 新建目标板配置头文件FelisUsbBoard.h，并在其中添加对目标板适配层的引用，以及其他全局配置
- 新建代码文件，定义设备描述符、配置描述符、字符串描述符等各类USB描述符数据
- 在应用源码中引用协议栈头文件FelisUSB.h
- 在应用源码中引用使用到的设备类头文件，例如：FelisUsbDClassHID.h
- 在应用源码中声明设备类实例，并进行应用回调代码的编写
- 在应用源码中声明协议栈设备实例，关联描述符和设备类示例
- 在应用源码中调用启动协议栈的代码

以下是示例代码片段（完整示例代码可以sample目录下的内容）：
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

## 向Felis USB添加新的设备类
向Felis USB添加新的设备类主要包括以下三项工作：
- **设计设备类的设计时数据**
设备类的设计时数据指的是不随设备类运行状态变化而变化的数据，比如：设备类所需的额外的配置信息、设备类自定义的应用回调、设备类需要使用的额外缓冲区等等。
设备类的设计时数据需要继承基础设备类设计时数据。在结构体定义时，所有成员之前插入一句INHERIT_FUSBD_CLASS;即可实现继承关系。
将设备类的设计时数据与运行时数据分离，是为了有效节省对RAM的开销。

- **设计设备类的运行时数据**
设备类的运行时数据指的是在设备运行过程中发生变化的数据，比如：设备的运行状态、与主机交互的过程数据等等。
设备类的运行时数据需要继承基础设备类运行时数据。在结构体定义时，所有成员之前插入一句INHERIT_FUSBD_CLASS_RUNTIME;即可实现继承关系。
合理规划运行时数据，有助于控制RAM的开销。

- **实现设备类关注的各项回调函数**
设备类的所有协议栈标准回调定义在fusbd_class_methods_t结构体中，设备类可根据自身的实际需求来实现其中的部分或所有回调函数。

**示例：** 请参考src/classes下的设备类实现文件。

# 移植说明

将FelisUSB移植到其他处理上时，只需要提供匹配的适配层头文件以及适配层代码文件即可。适配层重点实现的是适配层函数，和适配层事件回调处理两个部分。为了性能考虑，适配层函数最好以内联函数或者函数形态的宏的形式给出。具体实现可参考目前已提供的适配层代码。

# SDK参考
- [FelisUSB核心API](./api/api-FelisUSB.md)
- [描述符信息提取工具集](./api/api-toolkits.md)
- [适配层函数说明](./api/api-Adapter_Functions.md)
- [适配层事件回调说明](./api/api-Adapter_Event_Callbacks.md)
