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
#include "FelisUsbDClassUVC.h"

#include "FelisUsbDebug.h"

static const uint8_t * uvc_get_format_desc(fusbd_uvc_pt pInst, uint8_t nIdx)
{
	const uint8_t * pDesc = fusbd_uvc_rt(pInst)->pVsIntfDesc;
	uint8_t nFormatCount = pDesc[3];
	
	if (nIdx > nFormatCount)
	{
		pDesc = NULL;
	}
	else
	{
		pDesc += fusb_desc_len(pDesc);
		while ((nFormatCount > 0) && (nIdx != pDesc[3]))
		{
			for (uint8_t nFrameCount = pDesc[4]; nFrameCount > 0; nFrameCount --)
			{
				pDesc += fusb_desc_len(pDesc);
			}
			pDesc += fusb_desc_len(pDesc);
			nFormatCount--;
		}
		if (0 == nFormatCount)
		{
			pDesc = NULL;
		}
	}
	return pDesc;
}

static const uint8_t * uvc_get_frame_desc(const uint8_t * pDesc, uint8_t nIdx)
{
	uint8_t nFrameCount = pDesc[4];
	
	if (nIdx > nFrameCount)
	{
		pDesc = NULL;
	}
	else
	{
		pDesc += fusb_desc_len(pDesc);
		for (; (nFrameCount > 0) && (nIdx != pDesc[3]); nFrameCount--)
		{
			pDesc += fusb_desc_len(pDesc);
		}
		if (0 == nFrameCount)
		{
			pDesc = NULL;
		}
	}
	
	return pDesc;
}

static void uvc_adjust_probe(fusbd_uvc_pt pInst, uvc_probe_pt pProbe, uint8_t nFormatIdx, uint8_t nFrameIdx)
{
	fusbd_uvc_runtime_pt pRT = fusbd_uvc_rt(pInst);
	
	const uint8_t * pFormatDesc = uvc_get_format_desc(pInst, nFormatIdx);
	if (NULL == pFormatDesc)
	{
		nFormatIdx = 1;
		pFormatDesc = uvc_get_format_desc(pInst, nFormatIdx);
	}
	if (NULL != pFormatDesc)
	{
		const uint8_t * pFrameDesc = uvc_get_frame_desc(pFormatDesc, nFrameIdx);
		if (NULL == pFrameDesc)
		{
			nFrameIdx = 1;
			pFrameDesc = uvc_get_frame_desc(pFormatDesc, nFrameIdx);
		}
		if (NULL != pFrameDesc)
		{
			pProbe->bmHint = 0;
			pProbe->bFormatIndex = nFormatIdx;
			pProbe->bFrameIndex = nFrameIdx;
			if (UVC_VS_FRAME_UNCOMPRESSED == pFrameDesc[2])
			{
				pProbe->dwMaxVideoFrameSize = MAKEDWORD(MAKEWORD(pFrameDesc[17], pFrameDesc[18]), MAKEWORD(pFrameDesc[19], pFrameDesc[20]));
				pProbe->dwFrameInterval = MAKEDWORD(MAKEWORD(pFrameDesc[21], pFrameDesc[22]), MAKEWORD(pFrameDesc[23], pFrameDesc[24]));
			}
			pProbe->dwClockFrequency = MAKEWORD(pRT->pVcIntfDesc[7], pRT->pVcIntfDesc[8]);
			pProbe->dwMaxPayloadTransferSize = fusb_ep_mps_from_desc(pRT->vEpVS.pDesc);
			pProbe->bmFramingInfo = 3;
			pProbe->wDelay = 10;
			pProbe->wKeyFrameRate = 0;
			pProbe->wPFrameRate = 0;
			pProbe->wCompQuality = 0;
			pProbe->wCompWindowSize = 0;
			pProbe->bPreferedVersion = 0;
			pProbe->bMinVersion = 0;
			pProbe->bMaxVersion = 0;
			fusbd_uvc_callback(pInst, OnAdjustProbe, pProbe, nFormatIdx, nFrameIdx);
		}
	}
}

static size_t on_uvc_config(fusbd_uvc_pt pInst, const uint8_t * pDesc)
{
	fusbd_uvc_runtime_pt pRT = fusbd_uvc_rt(pInst);
	size_t nSize = 0;
	uint8_t nIntfIdx;
	
	if (USB_CLASS_VIDEO == fusb_intf_desc_class(pDesc))
	{
		nSize = fusb_desc_len(pDesc);
		nIntfIdx = fusb_intf_desc_idx(pDesc);
		switch (fusb_intf_desc_subclass(pDesc))
		{
			case UVC_SC_VIDEOCONTROL:
				pDesc = fusb_next_desc_ptr(pDesc);
				if (USB_FUCNTION_DESCRIPTOR_TYPE == fusb_desc_type(pDesc))
				{
					nSize += MAKEWORD(pDesc[5], pDesc[6]);
					pRT->pVcIntfDesc = pDesc;
				}
				break;
			
			case UVC_SC_VIDEOSTREAMING:
				pDesc = fusb_next_desc_ptr(pDesc);
				if (USB_FUCNTION_DESCRIPTOR_TYPE == fusb_desc_type(pDesc))
				{
					nSize += MAKEWORD(pDesc[4], pDesc[5]);
					pRT->pVsIntfDesc = pDesc;
					pRT->nVSIntfIdx = nIntfIdx;
					pRT->nVSIntfSelect = 0;
				}
				break;
			
			default:
				break;
		}
	}
	
	return nSize;
}

static int on_uvc_config_done(fusbd_uvc_pt pInst)
{
	uvc_adjust_probe(pInst, &fusbd_uvc_rt(pInst)->vProbe, 1, 1);
	//fusbd_class_ep_open(pInst, &fusbd_uvc_rt(pInst)->vEpVS);
	return 0;
}

static fusbd_endpoint_pt on_uvc_assign_endpoint(fusbd_uvc_pt pInst, const uint8_t * pEpDesc, const uint8_t * pIntfDesc)
{
	fusbd_uvc_runtime_pt pRT = fusbd_uvc_rt(pInst);
	return ((USB_CLASS_VIDEO == fusb_intf_desc_class(pIntfDesc)) 
							&& (UVC_SC_VIDEOSTREAMING == fusb_intf_desc_subclass(pIntfDesc))
							&& fusb_ep_desc_is_in(pEpDesc)) 
					? &pRT->vEpVS : NULL;
}

static void on_uvc_probe_set(fusbd_uvc_pt pInst, void * pBuf, size_t nSize)
{
	fusbd_uvc_runtime_pt pRT = fusbd_uvc_rt(pInst);
	uvc_adjust_probe(pInst, &pRT->vProbe, pRT->vProbe.bFormatIndex, pRT->vProbe.bFrameIndex);
	fusbd_class_ctrl_send_status(pInst);
}

static int on_uvc_setup_request(fusbd_uvc_pt pInst, fusb_setup_reuqest_pt pReq)
{
	fusbd_uvc_runtime_pt pRT = fusbd_uvc_rt(pInst);
	
	switch (pReq->bmRequest & USB_REQ_TYPE_MASK)
	{
		case USB_REQ_TYPE_CLASS :
			switch (pReq->bRequest)
			{
				case UVC_REQ_GET_CUR:
				case UVC_REQ_GET_MIN:
				case UVC_REQ_GET_MAX:
					fusbd_class_ctrl_send_data(pInst, &pRT->vProbe, pReq->wLength);
					return 0;

				case UVC_REQ_SET_CUR:
					fusbd_class_ctrl_receive(pInst, &pRT->vProbe, sizeof(uvc_probe_t), on_uvc_probe_set, pInst);
          return 0;

        default:
          break;
      }
      break;

		case USB_REQ_TYPE_STANDARD:
			switch (pReq->bRequest)
			{
				case USB_REQ_GET_INTERFACE:
					fusbd_class_ctrl_send_data(pInst, &pRT->nVSIntfSelect, 1);
					return 0;
        
				case USB_REQ_SET_INTERFACE:
					if (pReq->ucIndex[0] == pRT->nVSIntfIdx)
					{
						pRT->nVSIntfSelect = pReq->ucValue[0];
						if (0 != pReq->ucValue[0])
						{
							fusbd_class_ep_open(pInst, &pRT->vEpVS);
						}
						else
						{
							fusbd_class_ep_close(pInst, &pRT->vEpVS);
						}
						fusbd_uvc_callback(pInst, OnSelect, pReq->ucValue[0]);
					}
          return 0;

        default:
          break;
      }
      break;
      
    default:
      break;
  }
  
  return 0;
}

static int on_uvc_data_in(fusbd_uvc_pt pInst, fusbd_endpoint_pt pEndPoint)
{
	if (0 != fusbd_uvc_rt(pInst)->nVSIntfSelect)
	{
		fusbd_class_ep_flush(pInst, pEndPoint);
		fusbd_uvc_callback(pInst, OnSent);
	}
	return 0;
}

BEGIN_FUSBD_CLASS_METHODS(fusbd_uvc_methods)
	FUSBD_CLASS_METHOD(Config, on_uvc_config),
	FUSBD_CLASS_METHOD(ConfigDone, on_uvc_config_done),
	FUSBD_CLASS_METHOD(AssignEndPoint, on_uvc_assign_endpoint),
	FUSBD_CLASS_METHOD(SetupRequest, on_uvc_setup_request),
	FUSBD_CLASS_METHOD(DataIn, on_uvc_data_in)
END_FUSBD_CLASS_METHODS();
