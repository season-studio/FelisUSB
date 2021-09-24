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
#if	!defined(__FELIS_USB_DEBUG_H__)
#define	__FELIS_USB_DEBUG_H__

#include "FelisUsbBoard.h"

#include <stdio.h>

#if	!defined(FUSB_DEBUG_OUT)
	#define	FUSB_DEBUG_OUT													(0xFF)
#endif

#define	FUsbLog(level, fmt, ...)	\
	do {	\
		if (level <= FUSB_DEBUG_OUT)	\
			if (level >= 0xFF)	\
				printf("[FU#X] " fmt, ##__VA_ARGS__);	\
			else	\
				printf("[FU"#level "] " fmt, ##__VA_ARGS__);	\
	} while (0)

#define	FUsbLogL1(fmt, ...)												FUsbLog(1, fmt, ##__VA_ARGS__)
#define	FUsbLogL2(fmt, ...)												FUsbLog(2, fmt, ##__VA_ARGS__)
#define	FUsbLogL3(fmt, ...)												FUsbLog(3, fmt, ##__VA_ARGS__)
#define	FUsbLogL4(fmt, ...)												FUsbLog(4, fmt, ##__VA_ARGS__)
#define	FUsbLogX(fmt, ...)												FUsbLog(0xFF, fmt, ##__VA_ARGS__)

#endif	// __FELIS_USB_DEBUG_H__
