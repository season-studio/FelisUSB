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
#if	!defined(__FELIS_USBD_CLASS_SAMPLE_H__)
#define	__FELIS_USBD_CLASS_SAMPLE_H__

#include "FelisUsbDevice.h"

typedef const struct _tag_fusbd_sample * fusbd_sample_pt;

#define	INHERIT_FUSBD_CLASS_SAMPLE	\
	INHERIT_FUSBD_CLASS;	\
	int (*OnReceived)(fusbd_sample_pt pUVC, void * pBuf);	\
	int (*OnSent)(fusbd_sample_pt pUVC)

typedef struct _tag_fusbd_sample
{
	INHERIT_FUSBD_CLASS_SAMPLE;
	
} fusbd_sample_t;

#define	fusbd_sample_rt(pUVC)							((fusbd_sample_runtime_pt)((pUVC)->pRuntime))
#define	fusbd_sample_callback(pUVC, name, ...)	\
	((NULL != (pUVC)->name) ? (pUVC)->name(pUVC, ##__VA_ARGS__) : 0)

#define	INHERIT_FUSBD_CLASS_SAMPLE_RUNTIME	\
	INHERIT_FUSBD_CLASS_RUNTIME;	\
	fusbd_endpoint_t	vEpIn;			\
	fusbd_endpoint_t	vEpOut;			\
	const uint8_t *		pIntfDesc

typedef struct
{
	INHERIT_FUSBD_CLASS_SAMPLE_RUNTIME;
	
} fusbd_sample_runtime_t, *fusbd_sample_runtime_pt;

EXTERN_FUSBD_CLASS_METHODS(fusbd_sample_methods);

#define	FUSBD_SAMPLE_CLASS_RUNTIME(...)		(fusbd_sample_runtime_t){ ##__VA_ARGS__ }	

#define	FUSBD_SAMPLE_CLASS(dev, rt, ...)	(const fusbd_hid_t){ .pDev = dev, .pMethods = &fusbd_sample_methods, .pRuntime = (fusbd_class_runtime_pt)&rt, ##__VA_ARGS__ }

#endif	// __FELIS_USBD_CLASS_SAMPLE_H__
