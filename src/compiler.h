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
#if	!defined(__FELIS_USB_COMPILER_H__)
#define	__FELIS_USB_COMPILER_H__

#if	defined(__GNUC__)

	#define FUSB_PACKED					__attribute__((packed))
	#define	FUSB_ALIGN_BEGIN		
	#define	FUSB_ALIGN_END			__attribute__((aligned(4)))
	#define	FUSB_INLINE					static inline
	#define	FUSB_WEAK						__attribute__((weak))
	#define	FUSB_USED						__attribute__((used))

#elif	defined(__CC_ARM)

	#define FUSB_PACKED					__attribute__((packed))
	#define	FUSB_ALIGN_BEGIN		
	#define	FUSB_ALIGN_END			__attribute__((aligned(4)))
	#define	FUSB_INLINE					static __forceinline
	#define	FUSB_WEAK						__attribute__((weak))
	#define	FUSB_USED						__attribute__((used))

#elif	defined(__ICCARM__)

#endif

#endif	// __FELIS_USB_COMPILER_H__
