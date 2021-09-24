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
#include "FelisUsbDClassHID.h"

#include "FelisUsbDebug.h"

static size_t on_hid_config(fusbd_hid_pt pHid, const uint8_t *pDesc)
{
	size_t nSize = 0;
	
	if ((USB_CLASS_HID == fusb_intf_desc_class(pDesc)) && !fusbd_class_intf_marked(pHid))
	{
		fusbd_hid_runtime_pt pRT = fusbd_hid_rt(pHid);
		
		nSize = fusb_desc_len(pDesc);
		pRT->pIntfDesc = pDesc;
		pDesc = fusb_next_desc_ptr(pDesc);
		if (USB_HID_DESCRIPTOR_TYPE == fusb_desc_type(pDesc))
		{
			nSize += fusb_desc_len(pDesc);
			fusbd_hid_rt(pHid)->pHidDesc = pDesc;
		}
	}
	
	return nSize;
}

static fusbd_endpoint_pt on_hid_assign_endpoint(fusbd_hid_pt pHid, const uint8_t *pDesc, const uint8_t * pIntfDesc)
{
	fusbd_hid_runtime_pt pRT = fusbd_hid_rt(pHid);
	
	return fusb_ep_desc_is_in(pDesc) ? &pRT->vEpIn : &pRT->vEpOut;
}

static int on_hid_config_done(fusbd_hid_pt pHid)
{
	fusbd_hid_runtime_pt pRT = fusbd_hid_rt(pHid);
	int iRet;
	
	iRet = fusbd_class_ep_open(pHid, &pRT->vEpIn);
	iRet = ((0 == iRet) ? fusbd_class_ep_open(pHid, &pRT->vEpOut) : 0);
	if ((NULL != pRT->pRecvBuf) && (0 == iRet))
	{
		fusbd_class_prepare_receive(pHid, &pRT->vEpOut, pRT->pRecvBuf, fusb_ep_mps_from_desc(pRT->vEpOut.pDesc));
	}
	
	return 0;
}

static void on_hid_ep0_report_callback(fusbd_hid_pt pHid, void * pBuf, size_t nSize)
{
	if (NULL != pHid)
	{
		fusbd_hid_callback(pHid, OnReceived, pBuf);
		fusbd_class_ctrl_send_status(pHid);
	}
}	

static int on_hid_setup_request(fusbd_hid_pt pHid, fusb_setup_reuqest_pt pReq)
{
	fusbd_hid_runtime_pt pRT = fusbd_hid_rt(pHid);
	
	if (USB_REQ_RECIPIENT_INTERFACE == (pReq->bmRequest & USB_REQ_RECIPIENT_MASK))
	{
		if (USB_REQ_GET_DESCRIPTOR == pReq->bRequest)
		{
			if (USB_DESC_TYPE_REPORT == pReq->ucValue[1])
			{
				size_t nReportSize = pRT->pHidDesc[7];
				const uint8_t * pReportDesc = pHid->pReportDesc;
				if ((NULL != pReportDesc) && (0 != nReportSize))
				{
					fusbd_class_ctrl_send_data(pHid, pReportDesc, MIN(pReq->wLength, nReportSize));
					return 0;
				}
				else
				{
					return -1;
				}
			}
		}
	}
	
	if (USB_REQ_TYPE_CLASS == (pReq->bmRequest & USB_REQ_TYPE_MASK))
	{
		switch (pReq->bRequest)
		{
			case HID_REQ_SET_IDLE:
				pRT->nIdle = pReq->ucValue[1];
				fusbd_hid_callback(pHid, OnStateChange);
				return 0;
			
			case HID_REQ_GET_IDLE:
				fusbd_class_ctrl_send_resp(pHid, pRT->nIdle, 1);
				return 0;
				
			case HID_REQ_SET_PROTOCOL:
				pRT->nProtocol = pReq->ucValue[1];
				fusbd_hid_callback(pHid, OnStateChange);
				return 0;
			
			case HID_REQ_GET_PROTOCOL:
				fusbd_class_ctrl_send_resp(pHid, pRT->nProtocol, 1);
				return 0;
				
			case HID_REQ_SET_REPORT:
				return (fusb_ep_mps_from_desc(pRT->vEpOut.pDesc) < pReq->wLength)
									? -1
									: fusbd_class_ctrl_receive(pHid, pRT->pRecvBuf, pReq->wLength, on_hid_ep0_report_callback, pHid);
			
			case HID_REQ_GET_REPORT:
				if (0 != pReq->wLength)
				{
					const void * pData = NULL;
					size_t nSize = fusbd_hid_callback(pHid, OnGetReport, pReq->ucValue[0], pReq->ucValue[1], pReq->wLength, &pData);
					if ((0 != nSize) && (NULL != pData))
					{
						fusbd_class_ctrl_send_data(pHid, pData, nSize);
					}
				}
				return 0;
				
			default:
				return 0;
		}
	}
	
  return 0;
}

static int on_hid_data_out(fusbd_hid_pt pHid, fusbd_endpoint_pt pEndPoint)
{
	fusbd_hid_callback(pHid, OnReceived, fusbd_hid_rt(pHid)->pRecvBuf);
	fusbd_class_prepare_receive(pHid, pEndPoint, pEndPoint->pXferBuf, pEndPoint->nXferSize);
	return 0;
}

static int on_hid_data_in(fusbd_hid_pt pHid, fusbd_endpoint_pt pEndPoint)
{
	fusbd_hid_callback(pHid, OnSent);
	return 0;
}

BEGIN_FUSBD_CLASS_METHODS(fusbd_hid_methods)
	FUSBD_CLASS_METHOD(Config, on_hid_config),
	FUSBD_CLASS_METHOD(ConfigDone, on_hid_config_done),
	FUSBD_CLASS_METHOD(AssignEndPoint, on_hid_assign_endpoint),
	FUSBD_CLASS_METHOD(SetupRequest, on_hid_setup_request),
	FUSBD_CLASS_METHOD(DataIn, on_hid_data_in),
	FUSBD_CLASS_METHOD(DataOut, on_hid_data_out),
END_FUSBD_CLASS_METHODS();
