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
#if	!defined(__FELIS_USBD_CLASS_UVC_H__)
#define	__FELIS_USBD_CLASS_UVC_H__

#include "FelisUsbDevice.h"

#if	1		// constants of the UVC stander
	// Video Class-Specific Interface SubClass
	#define	UVC_SC_VIDEOCONTROL					(1)
	#define	UVC_SC_VIDEOSTREAMING				(2)

	// Video Class-Specific VS Interface Descriptor Subtypes
	#define UVC_VS_FORMAT_UNCOMPRESSED	(0x04)
	#define UVC_VS_FRAME_UNCOMPRESSED		(0x05)
  #define UVC_VS_FORMAT_MJPEG					(0x06)

	// request code of the uvc class
	#define UVC_REQ_GET_CUR							(0x81)
	#define UVC_REQ_GET_MIN							(0x82)
	#define UVC_REQ_GET_MAX							(0x83)
	#define UVC_REQ_SET_CUR							(0x01)

  // YUV Format(GUID used to identify stream-encoding format, 16 Bytes)
	#define UVC_FORMAT_YUV422						0x59,0x55,0x59,0x32,\
																			0x00,0x00,\
																			0x10,0x00,\
																			0x80, 0x00,\
																			0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71
	#define UVC_FORMAT_YUY2							YUV422		/* GUID: 32595559-0000-0010-8000-00AA00389B71 */
	#define UVC_FORMAT_YUV420						0x4e, 0x56, 0x31, 0x32,\
																			0x00,0x00,\
																			0x10, 0x00,\
																			0x80,0x00,\
																			0x00,0xaa,0x00,0x38,0x9b,0x71
	#define UVC_FORMAT_NV12							YUV420		/* GUID:3231564E-0000-0010-8000-00AA00389B71 */
	#define	UVC_FORMAT_I420							0x49,0x34,0x32,0x30, \
																			0x00,0x00,\
																			0x10,0x00,\
																			0x80, 0x00,\
																			0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71	/* 30323449-0000-0010-8000-00AA00389B71 */
              
	#define	UVC_YUV422_BITS_PER_PIXEL		(16)
	#define	UVC_I420_BITS_PER_PIXEL			(12)
	
#endif	// constants of the UVC stander

typedef struct _tag_uvc_probe
{
	uint16_t	bmHint;
	uint8_t		bFormatIndex;
	uint8_t		bFrameIndex;
	uint32_t	dwFrameInterval;
	uint16_t	wKeyFrameRate;
	uint16_t	wPFrameRate;
	uint16_t	wCompQuality;
	uint16_t	wCompWindowSize;
	uint16_t	wDelay;
	uint32_t	dwMaxVideoFrameSize;
	uint32_t	dwMaxPayloadTransferSize;
	uint32_t	dwClockFrequency;
	uint8_t		bmFramingInfo;
	uint8_t		bPreferedVersion;
	uint8_t		bMinVersion;
	uint8_t		bMaxVersion;
} FUSB_PACKED uvc_probe_t;

typedef uvc_probe_t * uvc_probe_pt;

typedef const struct _tag_fusbd_uvc * fusbd_uvc_pt;

#define	INHERIT_FUSBD_CLASS_UVC	\
	INHERIT_FUSBD_CLASS;	\
	int (*OnSelect)(fusbd_uvc_pt pUVC, uint8_t nSelect);	\
	int (*OnSent)(fusbd_uvc_pt pUVC);	\
	int (*OnAdjustProbe)(fusbd_uvc_pt pUVC, uvc_probe_pt pProbe, uint8_t nFormatIdx, uint8_t nFrameIdx)

typedef struct _tag_fusbd_uvc
{
	INHERIT_FUSBD_CLASS_UVC;
	
} fusbd_uvc_t;

#define	fusbd_uvc_rt(pUVC)							((fusbd_uvc_runtime_pt)((pUVC)->pRuntime))
#define	fusbd_uvc_callback(pUVC, name, ...)	\
	((NULL != (pUVC)->name) ? (pUVC)->name(pUVC, ##__VA_ARGS__) : 0)

#define	INHERIT_FUSBD_CLASS_UVC_RUNTIME	\
	INHERIT_FUSBD_CLASS_RUNTIME;	\
	fusbd_endpoint_t	vEpVS;			\
	const uint8_t *		pVcIntfDesc;\
	const uint8_t *		pVsIntfDesc;\
	uvc_probe_t				vProbe;			\
	uint8_t						nVSIntfIdx;	\
	uint8_t						nVSIntfSelect
	

typedef struct
{
	INHERIT_FUSBD_CLASS_UVC_RUNTIME;
	
} fusbd_uvc_runtime_t, *fusbd_uvc_runtime_pt;

EXTERN_FUSBD_CLASS_METHODS(fusbd_uvc_methods);

#define	FUSBD_UVC_CLASS_RUNTIME(...)		(fusbd_uvc_runtime_t){ ##__VA_ARGS__ }	

#define	FUSBD_UVC_CLASS(dev, rt, ...)	(const fusbd_uvc_t){ .pDev = dev, .pMethods = &fusbd_uvc_methods, .pRuntime = (fusbd_class_runtime_pt)&rt, ##__VA_ARGS__ }

#endif	// __FELIS_USBD_CLASS_UVC_H__
