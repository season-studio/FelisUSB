#include "desc.h"

#define	COUNT_INTERFACE			(UVC_USED + HID_USED)

// Device Descriptor
__ALIGN_BEGIN const uint8_t DeviceDescriptor [] __ALIGN_END = {
BYTE_LEN_STREAM(1,
	USB_DEVICE_DESCRIPTOR_TYPE,			/* bDescriptorType */
  LE_WORD(0x0200),								/* bcdUSB */

#if	(COUNT_INTERFACE > 1)
	0xEF,
  0x02,
  0x01,
#else
	0x00,
	0x00,
	0x00,
#endif
	
  0x40,														/* bMaxPacketSize */
  LE_WORD(USBD_VID),							/* idVendor */
  LE_WORD(USBD_PID),							/* idProduct */
  LE_WORD(0x0100),								/* bcdDevice */
  0x01,														/* iManufacturer */
  0x02,														/* iProduct */
  0x03,														/* iSerial */
  0x01														/* bNumConfigurations */
)};

// HID Report Descriptor : report descriptor for general input/output
__ALIGN_BEGIN const uint8_t HidReportDescriptor[] __ALIGN_END = {
#if	1
	0x06, 0x00, 0xFF,  			// Usage Page (Vendor Defined 0xFF00)
	0x09, 0x01,        			// Usage (0x01)
	0xA1, 0x01,        			// Collection (Application)
	0x09, 0x01,        			//   Usage (0x01)
	0x15, 0x00,        			//   Logical Minimum (0)
	0x26, 0xFF, 0x00,  			//   Logical Maximum (255)
	0x75, 0x08,        			//   Report Size (8)
	0x95, 0x40,							//   Report Count (64)
	0x09, 0x01,
	0x81, 0x02,        			//   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x40,
	0x09, 0x01,        			//   Usage (0x01)
	0x91, 0x02,        			//   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x01,
	0x09, 0x01,
	0xB1, 0x02,
	0xC0               // End Collection
#else
	0x00, 0xC0
#endif
};

// Config Descriptor
__ALIGN_BEGIN const uint8_t ConfigDescriptor [] __ALIGN_END = 
{
	/* Config Descriptor */
  0x09,
  USB_CONFIGURATION_DESCRIPTOR_TYPE,
WORD_LEN_STREAM(4, 
  COUNT_INTERFACE,								/* bNumInterfaces */
  0x01,														/* bConfigurationValue */
  0x00,														/* iConfiguration */
  0x80,														/* bmAttributes */
  0xFA,														/* Max power */
		
#if	UVC_USED
	/* IAD Descriptor */
	0x08,     /* bLength */
	USB_IAD_DESCRIPTOR_TYPE,
	0x00,			/* bFirstInterface: Interface number of the VideoControl interface that is associated with this function*/
	0x02,			/* Number of contiguous Video interfaces that are associated with this function */
	0x0E,			/* bFunction Class: CC_VIDEO*/
	0x03,			/* bFunction sub Class: SC_VIDEO_INTERFACE_COLLECTION */
	0x00,			/* bFunction protocol : PC_PROTOCOL_UNDEFINED*/
	0x02,			/* iFunction */
	
	#if	1 // 3.7 VideoControl Interface Descriptors 
	
		#if 1 // 3.7.1 Standard VC Interface Descriptor
			0x09,			/* bLength */
			USB_INTERFACE_DESCRIPTOR_TYPE,
			0x00,			/* bInterfaceNumber */
			0x00,			/* bAlternateSetting */
			0x00,			/* bNumEndpoints:1 endpoint (interrupt endpoint) */
			USB_CLASS_VIDEO,			/* bInterfaceClass : CC_VIDEO */
			UVC_SC_VIDEOCONTROL,	/* bInterfaceSubClass : SC_VIDEOCONTROL */
			0x00,			/* bInterfaceProtocol : PC_PROTOCOL_UNDEFINED */
			0x02,			/* iInterface:Index to string descriptor that contains the string <Your Product Name> */
		#endif // 3.7.1 Standard VC Interface Descriptor
	
		#if 1 // 3.7.2 Class-Specific VC(VideoControl) Interface Descriptor
			0x0d,									/* bLength */
			USB_FUCNTION_DESCRIPTOR_TYPE,
			0x01,									/* bDescriptorSubType : VC_HEADER subtype */
			LE_WORD(0x0110),			/* bcdUVC : Revision of class specification that this device is based upon. For this example, the device complies with Video Class specification version 1.1 */
		WORD_LEN_STREAM(7,			/* wTotalLength :  */
			LE_DWORD(UVC_CLOCK_FREQ), /* dwClockFrequency : 0x005b8d80 -> 6,000,000 == 6MHz*/
			0x01,									/* bInCollection : Number of streaming interfaces. */
			0x01,									/* baInterfaceNr(1) : VideoStreaming interface 1 belongs to this VideoControl interface.*/
	
			#if 1 // 3.7.2.1 Input Terminal Descriptor (Composite)
			BYTE_LEN_STREAM(1,		/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				0x02,									/* bDescriptorSubType : VC_INPUT_TERMINAL subtype */
				0x02,									/* bTerminalID: ID of this input terminal */
				LE_WORD(0x0201),			/* wTerminalType: 0x0401 COMPOSITE_CONNECTOR type. This terminal is the composite connector. */
				0x00,									/* bAssocTerminal: No association */
				0x00,									/* iTerminal: Unused*/
				// begin: Camera Input Terminal Data
				LE_WORD(0),						/* wObjectiveFocalLengthMin */
				LE_WORD(0),						/* wObjectiveFocalLengthMax */
				LE_WORD(0),						/* wOcularFocalLength */
				0x03,									/* bControlSize */
				0x00, // 0x06,	// 0x0E,
				0x00, // 0x2A,
				0x00
				// end: Camera Input Terminal Data
			),
			#endif
	
			#if	1 // 3.7.2.2 Output Terminal Descriptor
				0x09,									/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				0x03,									/* bDescriptorSubType : VC_OUTPUT_TERMINAL subtype */
				0x03,									/* bTerminalID: ID of this output terminal */
				LE_WORD(0x0101),      /* wTerminalType: 0x0101 TT_STREAMING type. This terminal is a USB streaming terminal. */
				0x00,									/* bAssocTerminal: No association */
				0x02,									/* bSourceID: The input pin of this unit is connected to the output pin of unit 2. */
				0x00									/* iTerminal: Unused*/
			#endif // 3.7.2.2 Output Terminal Descriptor
		),
		#endif // 3.7.2 Class-Specific VC Interface Descriptor
	#endif // // 3.7 VideoControl Interface Descriptors 

	#if 1 // 3.8 VideoControl Endpoint Descriptors
		// Because endpoint 0 is used as the VideoControl control endpoint, there is no dedicated standard control endpoint descriptor.
	#endif	// 3.8 VideoControl Endpoint Descriptors
	
	#if 1 // 3.9 VideoStreaming Interface Descriptors

		#if 1 // 3.9.1 Standard VS(VideoStream) Interface Descriptor 
			0x09,									/* bLength */
			USB_INTERFACE_DESCRIPTOR_TYPE,
			0x01,									/* bInterfaceNumber: Index of this interface */
			0x00,									/* bAlternateSetting: Index of this alternate setting */
			0x00,									/* bNumEndpoints : 0 endpoints 每 no bandwidth used*/
			USB_CLASS_VIDEO,			/* bInterfaceClass : CC_VIDEO */
			UVC_SC_VIDEOSTREAMING,/* bInterfaceSubClass : SC_VIDEOSTREAMING */
			0x00,									/* bInterfaceProtocol : PC_PROTOCOL_UNDEFINED */
			0x00,									/* iInterface : unused */
		#endif // 3.9.1 Standard VS(VideoStream) Interface Descriptor 
	
		#if 1 // 3.9.2 Class-Specific VS Interface Descriptors
			#if 1 // 3.9.2.1 Input Header Descriptor 
				0x0e,									/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				0x01,									/* bDescriptorSubType : VC_HEADER subtype */
				0x01,									/* bNumFormats : One format descriptor follows. */
			WORD_LEN_STREAM(6,			/* wTotalLength : */
				(UVC_EP | 0x80),			/* bEndpointAddress : 0x82 */
				0x00,									/* bmInfo : No dynamic format change supported. */
				0x03,									/* bTerminalLink : This VideoStreaming interface supplies terminal ID 3 (Output Terminal). */
				0x00,									/* bStillCaptureMethod : Device supports still image capture method 0. */
				0x00,									/* bTriggerSupport : Hardware trigger supported for still image capture */
				0x00,									/* bTriggerUsage : Hardware trigger should initiate a still image capture. */
				0x01,									/* bControlSize : Size of the bmaControls field */
				0x00,									/* bmaControls : No VideoStreaming specific controls are supported.*/
			#endif // 3.9.2.1 Input Header Descriptor 
	
			#if 1 // 3.9.2.3 Payload Format Descriptors  
				/* Class-specific VideoStream Format(YUV422) Descriptor */
			BYTE_LEN_STREAM(1,			/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				UVC_VS_FORMAT_UNCOMPRESSED,	/* bDescriptorSubType : VS_FORMAT_UNCOMPRESSED subtype */
				0x01,									/* bFormatIndex : First (and only) format descriptor */
				0x02,//1,									/* bNumFrameDescriptors : One frame descriptor for this format follows. */
				UVC_FORMAT_GUID,			/* guidFormat: */
				UVC_BITS_PER_PIX,			/* bBitsPerPixel: */
				0x01,									/* bDefaultFrameIndex : Default frame index is 1. */
				0x00,									/* bAspectRatioX : Non-interlaced stream 每 not required. */
				0x00,									/* bAspectRatioY : Non-interlaced stream 每 not required. */
				0x00,									/* bmInterlaceFlags : Non-interlaced stream */
				0x00									/* bCopyProtect : No restrictions imposed on the duplication of this video stream. */
			),
			#endif // 3.9.2.3 Payload Format Descriptors  
			
			#if	UVC_FRAME_SELECT //== 128 // 3.9.2.4 Video Frame Descriptor 
				/* Class-specific VideoStream Frame Descriptor */
			BYTE_LEN_STREAM(1,			/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				UVC_VS_FRAME_UNCOMPRESSED,/* bDescriptorSubType : VS_FRAME_UNCOMPRESSED */
				0x01,									/* bFrameIndex : First (and only) frame descriptor */
				0x02,									/* bmCapabilities : Still images using capture method 0 are supported at this frame setting.D1: Fixed frame-rate. */
				LE_WORD(USBD_UVC_IMAGE_WIDTH/2),		/* wWidth : Width of frame, pixels. */
				LE_WORD(USBD_UVC_IMAGE_HEIGHT),    	/* wHeight : Height of frame, pixels. */
				LE_DWORD(UVC_BITRATE_PER_SEC/2),		/* dwMinBitRate : Min bit rate in bits/s  */
				LE_DWORD(UVC_BITRATE_PER_SEC/2),		/* dwMaxBitRate : Max bit rate in bits/s  */
				LE_DWORD(UVC_IMAGEFRAME_SIZE/2),		/* dwMaxVideoFrameBufSize : Maximum video or still frame size, in bytes. */
				LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwDefaultFrame Interval time, unit=100ns */
				0x01,									              /* bFrameIntervalType : Continuous frame interval */
				LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwMinFrameInterval: dwDefaultFrame Interval time, unit=100ns */
				//LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwMaxFrameInterval: dwDefaultFrame Interval time, unit=100ns */
				//LE_DWORD(0),          							/* dwFrameIntervalStep : No frame interval step supported. */
			)
			#endif // 3.9.2.4 Video Frame Descriptor 
			
			#if	UVC_FRAME_SELECT //== 256 // 3.9.2.4 Video Frame Descriptor 
				/* Class-specific VideoStream Frame Descriptor */
			BYTE_LEN_STREAM(1,			/* bLength */
				USB_FUCNTION_DESCRIPTOR_TYPE,
				UVC_VS_FRAME_UNCOMPRESSED,/* bDescriptorSubType : VS_FRAME_UNCOMPRESSED */
				0x02,									/* bFrameIndex : First (and only) frame descriptor */
				0x02,									/* bmCapabilities : Still images using capture method 0 are supported at this frame setting.D1: Fixed frame-rate. */
				LE_WORD(USBD_UVC_IMAGE_WIDTH),			/* wWidth : Width of frame, pixels. */
				LE_WORD(USBD_UVC_IMAGE_HEIGHT),    	/* wHeight : Height of frame, pixels. */
				LE_DWORD(UVC_BITRATE_PER_SEC),			/* dwMinBitRate : Min bit rate in bits/s  */
				LE_DWORD(UVC_BITRATE_PER_SEC),			/* dwMaxBitRate : Max bit rate in bits/s  */
				LE_DWORD(UVC_IMAGEFRAME_SIZE),			/* dwMaxVideoFrameBufSize : Maximum video or still frame size, in bytes. */
				LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwDefaultFrame Interval time, unit=100ns */
				0x01,									              /* bFrameIntervalType : Continuous frame interval */
				LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwMinFrameInterval: dwDefaultFrame Interval time, unit=100ns */
				//LE_DWORD(USBD_UVC_FRAME_INTERVAL),  /* dwMaxFrameInterval: dwDefaultFrame Interval time, unit=100ns */
				//LE_DWORD(0),          							/* dwFrameIntervalStep : No frame interval step supported. */
			)
			#endif // 3.9.2.4 Video Frame Descriptor 
		)
		#endif // 3.9.2 Class-Specific VS Interface Descriptors
	#endif // 3.9 VideoStreaming Interface Descriptors
	
	#if	1 // Operational Alternate Setting 1
		#if 1 // 3.9.1 Standard VS(VideoStream) Interface Descriptor 
			0x09,									/* bLength */
			USB_INTERFACE_DESCRIPTOR_TYPE,
			0x01,									/* bInterfaceNumber: Index of this interface */
			0x01,									/* bAlternateSetting: Index of this alternate setting */
			0x01,									/* bNumEndpoints: endpoints, 1 每 data endpoint */
			USB_CLASS_VIDEO,			/* bInterfaceClass: CC_VIDEO */
			UVC_SC_VIDEOSTREAMING,/* bInterfaceSubClass: SC_VIDEOSTREAMING */
			0x00,									/* bInterfaceProtocol: PC_PROTOCOL_UNDEFINED */
			0x00,									/* iInterface: Unused */
		#endif // 3.9.1 Standard VS(VideoStream) Interface Descriptor 
	
		#if 1 // 3.10.1.1 Standard VS Isochronous Video Data Endpoint Descriptor
			0x07,									/* bLength */
			0x05,									/* bDescriptorType: ENDPOINT */
			(UVC_EP | 0x80),			/* bEndpointAddress: IN endpoint 1 */
			0x05,									/* bmAttributes: Isochronous transfer type. Asynchronous synchronization type. */
			LE_WORD(USBD_UVC_PACKET_SIZE),/* wMaxPacketSize: Max packet size, in bytes */
			1,										/* bInterval: One frame interval */
		#endif // 3.10.1.1 Standard VS Isochronous Video Data Endpoint Descriptor
	#endif // Operational Alternate Setting 1
#endif	// UVC Function

#if	HID_USED  // HID Function
	/* HID Interface */
  0x09,
  USB_INTERFACE_DESCRIPTOR_TYPE,
  (0x00 + UVC_USED),							/* bInterfaceNumber */
  0x00,														/* bAlternateSetting */
  0x02,														/* bNumEndpoints */
  USB_CLASS_HID,									/* bInterfaceClass : CC_HID */
  0x00,														/* bInterfaceSubClass */
  0x00,														/* bInterfaceProtocol */
  0x04,														/* iInterface */

		/* HID FUNCTION DESC */
		0x09,
		USB_HID_DESCRIPTOR_TYPE,
		0x00,
		0x01,
		0x00,
		0x01,
		0x22,
		(uint8_t)sizeof(HidReportDescriptor),
		0x00,

		/* HID EP IN */
		0x07,
		USB_ENDPOINT_DESCRIPTOR_TYPE,
		(HID_EP | 0x80),
		0x03,
		0x40,
		0x00,
		0x01,
		
		/* HID EP OUT */
		0x07,
		USB_ENDPOINT_DESCRIPTOR_TYPE,
		HID_EP,
		0x03,
		0x40,
		0x00,
		0x01,
#endif	// HID Function
)};

const uint8_t * const ConfigDescriptList[] = 
{
	ConfigDescriptor
};

const uint8_t BOSDescriptor[] =
{
  0x5,
  USB_BOS_DESCRIPTOR_TYPE,
  0xC,
  0x0,
  0x1,  /* 1 device capability*/
        /* device capability*/
  0x7,
  USB_DEVICE_CAPABITY_TYPE,
  0x2,
  0x2,  /* LPM capability bit set*/
  0x0,
  0x0,
  0x0
};

const uint8_t QualifierDescriptor[] = 
{
	BYTE_LEN_STREAM(1,
		USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE,
		LE_WORD(0x2000),
		0xEF,
		0x02,
		0x01,
		0x40,
		0x01,
		0x00
	)
};

const fusb_str_descriptor_t* const StringDescriptorList[] = 
{
	(const fusb_str_descriptor_t*)((const uint8_t[]){BYTE_LEN_STREAM(1, USB_STRING_DESCRIPTOR_TYPE, LE_WORD(0x0409))}),
	&DECL_USB_ANONYMOUS_STRING_DESCRIPTOR("Centerm Info"),
	&DECL_USB_ANONYMOUS_STRING_DESCRIPTOR("IR Camera"),
	&DECL_USB_ANONYMOUS_STRING_DESCRIPTOR("000001"),
	&DECL_USB_ANONYMOUS_STRING_DESCRIPTOR("AUTH Pipe")
};

const fusbd_descriptor_set_t FUsbDeviceDescriptors = 
{
	.pDeviceDescriptor = DeviceDescriptor,
	.pHSConfigDescriptorList = ConfigDescriptList,
	.nHSConfigCount = sizeof(ConfigDescriptList) / sizeof(ConfigDescriptList[0]),
	.pFSConfigDescriptorList = ConfigDescriptList,
	.nFSConfigCount = sizeof(ConfigDescriptList) / sizeof(ConfigDescriptList[0]),
	.pOtherSpeedConfigDescriptorList = ConfigDescriptList,
	.nOtherSpeedConfigCount = sizeof(ConfigDescriptList) / sizeof(ConfigDescriptList[0]),
	.pBOSDescriptor = BOSDescriptor,
	.pStringDescriptorList = StringDescriptorList,
	.nStringCount = sizeof(StringDescriptorList) / sizeof(StringDescriptorList[0]),
	.pDeviceQualifierDescriptor = QualifierDescriptor
};

uint16_t GetHIDReportDescriptor(const uint8_t** lppReport)
{
	if (lppReport)
	{
		*lppReport = HidReportDescriptor;
	}
	return sizeof(HidReportDescriptor);
}
