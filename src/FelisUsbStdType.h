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
#if	!defined(__FELIS_USB_STD_TYPE_H__)
#define	__FELIS_USB_STD_TYPE_H__

#include "utility.h"
#include "FelisUsbBoard.h"

/**
 * @defgroup FelisUSB
 * @{
 */

#define	INHERIT_FUSB_DESCRIPTOR	\
	uint8_t			bLength;	\
	uint8_t			bDescriptorType

typedef struct
{
	INHERIT_FUSB_DESCRIPTOR;
	
	uint8_t			zData[];
} FUSB_PACKED fusb_descriptor_t;

/**
 * @defgroup toolkits for processing the basic descriptor
 * @{
 */

/**
 * @brief toolkit for locating the next descriptor of the special descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_next_desc_ptr(pDesc)					(((const uint8_t *)pDesc) + ((const uint8_t *)pDesc)[0])
/**
 * @brief toolkit for getting the length of the special descriptor 
 * @param pDesc pointer to the descriptor
 */
#define	fusb_desc_len(pDesc)							(((const uint8_t *)pDesc)[0])
/**
 * @brief toolkit for getting the length of the special descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_desc_type(pDesc)							(((const uint8_t *)pDesc)[1])
/** @} */

typedef struct
{
	INHERIT_FUSB_DESCRIPTOR;
	
	uint8_t			bInterfaceNumber;
	uint8_t			bAlternateSetting;
	uint8_t			bNumEndpoints;
	uint8_t			bInterfaceClass;
	uint8_t			bInterfaceSubClass;
	uint8_t			bInterfaceProtocol;
	uint8_t			iInterfaceStr;
} FUSB_PACKED fusb_intf_descriptor_t;

/**
 * @defgroup toolkits for processing the interface descriptor
 * @{
 */

/**
 * @brief toolkit for getting the index of the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_idx(pDesc)					(((const uint8_t *)pDesc)[2])
/**
 * @brief toolkit for getting the alt index of the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_alt(pDesc)					(((const uint8_t *)pDesc)[3])
/**
 * @brief toolkit for getting the count of the endpoints assigned to the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_ep_count(pDesc)		(((const uint8_t *)pDesc)[4])
/**
 * @brief toolkit for getting the class code of the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_class(pDesc)				(((const uint8_t *)pDesc)[5])
/**
 * @brief toolkit for getting the sub-class code of the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_subclass(pDesc)		(((const uint8_t *)pDesc)[6])
/**
 * @brief toolkit for getting the protocol code of the interface in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_intf_desc_protocol(pDesc)		(((const uint8_t *)pDesc)[7])
/** @} */

typedef struct
{
	INHERIT_FUSB_DESCRIPTOR;
	
	uint8_t			bEndpointAddress;
	uint8_t			bmAttributes;
	uint16_t		wMaxPacketSize;
	uint8_t			bInterval;
} FUSB_PACKED fusb_ep_descriptor_t;

/**
 * @defgroup toolkits for processing the interface descriptor
 * @{
 */

/**
 * @brief toolkit for getting the address of the endpoint in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_ep_addr_from_desc(pDesc)			((pDesc)[2])
/**
 * @brief toolkit for getting the max_packet_size of the endpoint in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_ep_mps_from_desc(pDesc)			(MAKEWORD(pDesc[4], pDesc[5]) & 2047)
/**
 * @brief toolkit for getting the transmition type of the endpoint in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_ep_type_from_desc(pDesc)			((pDesc)[3] & 3)
/**
 * @brief toolkit for check if the endpoint is an in-endpoint in the descriptor
 * @param pDesc pointer to the descriptor
 */
#define	fusb_ep_desc_is_in(pDesc)					(0 != ((pDesc)[2] & 0x80))
/** @} */

typedef struct
{
	INHERIT_FUSB_DESCRIPTOR;
	
	wchar_t	wstrText[];
} FUSB_PACKED fusb_str_descriptor_t;

/**
 * @brief toolkit for declaring a string descriptor
 * @param name name of the descriptor
 * @param text content of the string
 */
#define	DECL_USB_STRING_DESCRIPTOR(name, text)	\
	const fusb_str_descriptor_t name = {	\
		.bLength = sizeof(L""text),	\
		.bDescriptorType = USB_STRING_DESCRIPTOR_TYPE,	\
		.wstrText = L""text	\
	}
	
/**
 * @brief toolkit for declaring an anunymous string descriptor
 * @param text content of the string
 */
#define	DECL_USB_ANONYMOUS_STRING_DESCRIPTOR(text)	\
	((const fusb_str_descriptor_t) {	\
		.bLength = sizeof(L""text),	\
		.bDescriptorType = USB_STRING_DESCRIPTOR_TYPE,	\
		.wstrText = L""text	\
	})
	

/**
 * @struct fusb_setup_reuqest_t
 * @brief type of the setup request
 */
typedef struct
{
	uint8_t			bmRequest;
	uint8_t			bRequest;
	union
	{
		uint8_t		ucValue[2];
		uint16_t	wValue;
	};
	union
	{
		uint8_t		ucIndex[2];
		uint16_t	wIndex;
	};
	uint16_t		wLength;
} fusb_setup_reuqest_t, * fusb_setup_reuqest_pt;

/** @} */

#endif	// __FELIS_USB_STD_TYPE_H__
