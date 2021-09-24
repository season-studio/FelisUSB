#if	!defined(__USB_DESC_H__)
#define	__USB_DESC_H__

#include "FelisUSB.h"
#include "classes/FelisUsbDClassUVC.h"

#define	UVC_USED									(2) //0	//2
#define	FORMAT_YUV422							(1)
#define	UVC_FRAME_SELECT					(256)

#define	HID_USED									(1) //0 //1

#define	USBD_VID									(0x2B46)
#define	USBD_PID									(0xBD0A)

#if	HID_USED
	#define	HID_EP									(1)
#endif

#if	UVC_USED
	#define USBD_UVC_IMAGE_WIDTH    (256)
  #define USBD_UVC_IMAGE_HEIGHT   (192)
	#define	MAX_FRAME_COUNT_PER_SEC	(10)
	
  #define USBD_UVC_FRAME_INTERVAL (10000000/MAX_FRAME_COUNT_PER_SEC)
                            
  #define UVC_CLOCK_FREQ    			(48000000)  // (72000000)  // 0x280DE80
  #define UVC_EP         					(2)

  #if	FORMAT_YUV422
    #define UVC_IMAGEFRAME_SIZE		(USBD_UVC_IMAGE_WIDTH*USBD_UVC_IMAGE_HEIGHT*2)
		#define	UVC_FORMAT_GUID				UVC_FORMAT_YUV422
		#define	UVC_BITS_PER_PIX			UVC_YUV422_BITS_PER_PIXEL
  #else
    #define	UVC_IMAGEFRAME_SIZE		(USBD_UVC_IMAGE_WIDTH*USBD_UVC_IMAGE_HEIGHT + USBD_UVC_IMAGE_WIDTH*USBD_UVC_IMAGE_HEIGHT/2)
		#define	UVC_FORMAT_GUID				UVC_FORMAT_I420
		#define	UVC_BITS_PER_PIX			UVC_I420_BITS_PER_PIXEL
  #endif
	
	#define	UVC_BITRATE_PER_SEC			(UVC_IMAGEFRAME_SIZE*8*MAX_FRAME_COUNT_PER_SEC)

  #define USBD_UVC_PACKET_SIZE    (514) // (130)  //(0x102)
#endif	// UVC_USED`

extern const fusbd_descriptor_set_t FUsbDeviceDescriptors;
extern const uint8_t HidReportDescriptor[];

#endif	// __USB_DESC_H__
