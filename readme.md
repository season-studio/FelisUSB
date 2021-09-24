# Felis USB
![FelisUSB](https://season-studio.github.io/logo/FelisUSB.png)
-----------
**中文** | [英文](./readme_en.md)


## 概述
Felis USB 是一个嵌入式USB协议栈。它不依赖于软件系统支持，可以轻量级迁移使用。
Felis USB is an USB stack for embedded system. See introduction in English [here](./readme_en.md).

## 为什么开发Felis USB
在开发Felis USB之前，我所在的公司有个技术预研的项目，需要用STM32单片机开发一个UVC和HID设备杂合的USB设备样机。STM32 HAL库中所带的USB协议栈抽象层实现稍微繁琐了一些，造成较多的空间资源消耗，而且默认没有实现多接口设备类的框架。我尝试了TinyUSB协议栈以及TeenyUSB协议栈。然而，TinyUSB协议栈没有支持ISOC端点的分配；TeenyUSB似乎存在一些问题，造成USB设备枚举速度慢、UVC接口多次切换后控制端点通讯异常等BUG。并且，这些协议栈都存在没有合理规划常数据和可变数据存储空间的问题，有部分常数据占用RAM空间，一定程度上带来RAM空间的浪费。
所以，经过综合考虑，我在中秋假期中自行开发了这款USB设备协议栈的第一个版本。

## 特点
- FelisUSB协议栈不需要软件系统支持，可以在裸机和带OS的工程中自由迁移
- FelisUSB协议栈支持多个USB配置，支持多个USB接口设备类的分模块实现，确保设备类接口层协议实现时的模块化和可伸缩性
- FelisUSB协议栈归一化USB相关配置，在USB设备描述符和USB配置描述符中已配置的信息，就不需要在代码中另行配置，确保了工程配置信息修改时能够一步到位，减少配置不同步可能造成的BUG
- FelisUSB协议栈进行了抽象，倡导从设备类接口层开始的代码不再关注端点号等硬件细节，只需要面向类对象、端点对象等抽象抽象体进行编程，让应用与硬件、逻辑与配置可以充分分离

## 主要功能更新与计划
目前版本中：
- Felis USB协议栈只支持USB 2.0的Device端协议；
- 硬件适配层只提供了STM32F4的实现；
- 设备类接口只提供了自定义HID、非压缩帧的UVC设备类的实现

后续计划：
- 这个真说不好。我的所学比较杂，目前也不主做嵌入式产品研发了。而且，说实在的，以中国大多数企业的现状来看，我所处的岗位甚至可能都不应该动手去写这样的协议栈。所以，我做这个可以说是用爱发电。后续计划就真谈不上明确的时间表。暂时的想法是，可能会先补充一些设备协议类的实现以及WCID的实现吧。

## 如何使用

### 使用Felis USB构建应用
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

#define FUSBD_ADPT_SPEED                (PCD_SPEED_FULL)

#define FUSB_DEBUG_OUT                  (3)

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

### 向Felis USB添加新的设备类
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

### 详情使用介绍
请参考 [usage_cn.md](./docs/usage_cn.md)

## 设计说明
请参考 [design_cn.md](./docs/design_cn.md)

## 参考与借鉴
正如前文所说，我在开发Felis USB之前，已经看过STM32 HAL库中的USB协议栈实现，也尝试过TinyUSB和TeenyUSB。所以，我的实现中对这三者有所参考和借鉴。
主要内容如下：
- 对于USB底层通讯逻辑的实现，参考了STM32 HAL库的代码，主要是其中HAL几个回调的处理，以及Setup Request的处理
- 借鉴了TinyUSB中，对于配置描述符的解析处理，即遇到接口描述符时，由设备类接口回调进行匹配，并越过被设备类接口回调所处理过的描述符
- 借鉴了TeenyUSB在Set Config过程中进行端点PMA/FiFo缓冲区配置的思路
- 借鉴了TeenyUSB中HID对Setup Request的处理逻辑
