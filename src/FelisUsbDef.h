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
#if	!defined(__FELIS_USB_DEF_CONSTANT_H__)
#define	__FELIS_USB_DEF_CONSTANT_H__

// constants of the type of the usb request
#define	USB_REQ_TYPE_STANDARD                         0x00U
#define	USB_REQ_TYPE_CLASS                            0x20U
#define	USB_REQ_TYPE_VENDOR                           0x40U
#define	USB_REQ_TYPE_MASK                             0x60U

// constants of the recipient of the usb request
#define	USB_REQ_RECIPIENT_DEVICE                      0x00U
#define	USB_REQ_RECIPIENT_INTERFACE                   0x01U
#define	USB_REQ_RECIPIENT_ENDPOINT                    0x02U
#define	USB_REQ_RECIPIENT_MASK                        0x03U

// constant of the code of the usb request
#define	USB_REQ_GET_STATUS                            0x00U
#define	USB_REQ_CLEAR_FEATURE                         0x01U
#define	USB_REQ_SET_FEATURE                           0x03U
#define	USB_REQ_SET_ADDRESS                           0x05U
#define	USB_REQ_GET_DESCRIPTOR                        0x06U
#define	USB_REQ_SET_DESCRIPTOR                        0x07U
#define	USB_REQ_GET_CONFIGURATION                     0x08U
#define	USB_REQ_SET_CONFIGURATION                     0x09U
#define	USB_REQ_GET_INTERFACE                         0x0AU
#define	USB_REQ_SET_INTERFACE                         0x0BU
#define	USB_REQ_SYNCH_FRAME                           0x0CU

// constant of the type of the descriptor
#define USB_DEVICE_DESCRIPTOR_TYPE										0x01U
#define USB_CONFIGURATION_DESCRIPTOR_TYPE							0x02U
#define USB_STRING_DESCRIPTOR_TYPE										0x03U
#define USB_INTERFACE_DESCRIPTOR_TYPE									0x04U
#define USB_ENDPOINT_DESCRIPTOR_TYPE									0x05U
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE					0x06U
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE	0x07U
#define USB_IAD_DESCRIPTOR_TYPE												0x0BU
#define USB_BOS_DESCRIPTOR_TYPE												0x0FU
#define USB_HUB_DESCRIPTOR_TYPE												0x29U
#define USB_HID_DESCRIPTOR_TYPE												0x21U
#define USB_REPORT_DESCRIPTOR_TYPE										0x22U
#define USB_DESC_TYPE_REPORT													0x22U
#define USB_FUCNTION_DESCRIPTOR_TYPE									0x24U
#define USB_SS_ENDPOINT_COMPANION_TYPE								0x30U

// constant of the state of the usb
#define	USB_CONFIG_REMOTE_WAKEUP											0x02U
#define	USB_CONFIG_SELF_POWERED												0x01U

// constant of the feature of the usb
#define USB_FEATURE_EP_HALT														0x00U
#define USB_FEATURE_REMOTE_WAKEUP											0x01U
#define USB_FEATURE_TEST_MODE													0x02U

#define	USB_DEVICE_CAPABITY_TYPE											0x10U

// constant of the class of the usb interface
#define USB_CLASS_DEVICE															0x00U
#define USB_CLASS_AUDIO																0x01U
#define USB_CLASS_CDC																	0x02U
#define USB_CLASS_HID																	0x03U
#define USB_CLASS_PHYSICAL														0x05U
#define USB_CLASS_IMAGE																0x06U
#define USB_CLASS_PRINTER															0x07U
#define USB_CLASS_MASS_STORAGE												0x08U
#define USB_CLASS_HUB																	0x09U
#define USB_CLASS_CDC_DATA														0x0aU
#define USB_CLASS_SMART_CARD													0x0bU
#define USB_CLASS_SECURITY														0x0dU
#define USB_CLASS_VIDEO																0x0eU
#define USB_CLASS_HEALTHCARE													0x0fU
#define USB_CLASS_DIAG_DEVICE													0xdcU
#define USB_CLASS_WIRELESS														0xe0U
#define USB_CLASS_MISC																0xefU
#define USB_CLASS_APP_SPECIFIC												0xfeU
#define USB_CLASS_VEND_SPECIFIC												0xffU

// constant of the type of the endpoint
#define USBD_EP_TYPE_CTRL															0x00U
#define USBD_EP_TYPE_ISOC															0x01U
#define USBD_EP_TYPE_BULK															0x02U
#define USBD_EP_TYPE_INTERRUPT												0x03U

#endif	// __FELIS_USB_DEF_CONSTANT_H__
