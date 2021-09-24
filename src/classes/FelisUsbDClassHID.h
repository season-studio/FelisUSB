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
#if	!defined(__FELIS_USBD_CLASS_HID_H__)
#define	__FELIS_USBD_CLASS_HID_H__

#include "FelisUsbDevice.h"

#define HID_REQ_SET_PROTOCOL					0x0B
#define HID_REQ_GET_PROTOCOL					0x03

#define HID_REQ_SET_IDLE							0x0A
#define HID_REQ_GET_IDLE							0x02

#define HID_REQ_SET_REPORT						0x09
#define HID_REQ_GET_REPORT						0x01

typedef const struct _tag_fusbd_hid * fusbd_hid_pt;

#define	INHERIT_FUSBD_CLASS_HID	\
	INHERIT_FUSBD_CLASS;					\
	const uint8_t * pReportDesc;	\
	int (*OnReceived)(fusbd_hid_pt pHid, void * pBuf);	\
	int (*OnSent)(fusbd_hid_pt pHid);	\
	int (*OnStateChange)(fusbd_hid_pt pHid);	\
	size_t (*OnGetReport)(fusbd_hid_pt pHid, uint8_t nType, uint8_t nID, size_t nNeedSize, const void** ppData)

typedef struct _tag_fusbd_hid
{
	INHERIT_FUSBD_CLASS_HID;
	
} fusbd_hid_t;

#define	fusbd_hid_rt(pHid)							((fusbd_hid_runtime_pt)((pHid)->pRuntime))
#define	fusbd_hid_callback(pHid, name, ...)	\
	((NULL != (pHid)->name) ? (pHid)->name(pHid, ##__VA_ARGS__) : 0)

#define	INHERIT_FUSBD_CLASS_HID_RUNTIME	\
	INHERIT_FUSBD_CLASS_RUNTIME;	\
	fusbd_endpoint_t	vEpIn;			\
	fusbd_endpoint_t	vEpOut;			\
	const uint8_t *		pIntfDesc;	\
	const uint8_t *		pHidDesc;		\
	void *						pRecvBuf;		\
	uint8_t						nIdle;			\
	uint8_t						nProtocol

typedef struct
{
	INHERIT_FUSBD_CLASS_HID_RUNTIME;
	
} fusbd_hid_runtime_t, *fusbd_hid_runtime_pt;

EXTERN_FUSBD_CLASS_METHODS(fusbd_hid_methods);

#define	FUSBD_HID_CLASS_RUNTIME(pBuf, ...)		(fusbd_hid_runtime_t){ .pRecvBuf = pBuf, ##__VA_ARGS__}	

#define	FUSBD_HID_CLASS(dev, reportDesc, rt, ...)	(const fusbd_hid_t){ .pDev = dev, .pMethods = &fusbd_hid_methods, .pReportDesc = reportDesc, .pRuntime = (fusbd_class_runtime_pt)&rt, ##__VA_ARGS__ }

#endif	// __FELIS_USBD_CLASS_HID_H__
