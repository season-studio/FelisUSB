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
#if !defined(__FELIS_USB_UTILITY__)
#define __FELIS_USB_UTILITY__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "compiler.h"

#define HIBYTE(w)										(uint8_t)(((w) >> 8) & 0x00FF)
#define	LOBYTE(w)										(uint8_t)((w) & 0x00FF)
#define	HIWORD(dw)									(uint16_t)(((dw) >> 16) & 0x00FFFF)
#define	LOWORD(dw)									(uint16_t)((dw) & 0x00FFFF)

#define	MAKEDWORD(lo, hi)						(((uint32_t)(lo) & 0x00FFFF) | ((((uint32_t)(hi)) << 16) & 0xFFFF0000))
#define	MAKEWORD(lo, hi)						(((uint16_t)(lo) & 0x00FF) | ((((uint16_t)(hi)) << 8) & 0xFF00))

#define	LE_WORD(w)									LOBYTE(w), HIBYTE(w)
#define	LE_DWORD(dw)								(uint8_t)((dw) & 0x00FF), (uint8_t)((((unsigned)(dw)) >> 8) & 0x00FF), (uint8_t)((((unsigned)(dw)) >> 16) & 0x00FF), (uint8_t)((((unsigned)(dw)) >> 24) & 0x00FF)

#define BYTE_LEN_STREAM(delta, ...)			\
	(uint8_t)(sizeof((const uint8_t[]){__VA_ARGS__})+(delta)),  __VA_ARGS__

#define WORD_LEN_STREAM(delta, ...)			\
	LOBYTE(sizeof((const uint8_t[]){__VA_ARGS__})+(delta)), HIBYTE(sizeof((const uint8_t[]){__VA_ARGS__})+(delta)), __VA_ARGS__


#ifndef MIN
	#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
	#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#define	ASSERT(nCond, fAction)			do { if(!(nCond)) { fAction; } } while (0)

#endif  // __FELIS_USB_UTILITY__
