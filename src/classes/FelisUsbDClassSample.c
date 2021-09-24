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
#include "FelisUsbDClassSample.h"

static int on_sample_init(fusbd_sample_pt pInst)
{
	return 0;
}

static size_t on_sample_config(fusbd_sample_pt pInst, const uint8_t * pDesc)
{
	return 0;
}

static int on_sample_config_done(fusbd_sample_pt pInst)
{
	return 0;
}

static int on_sample_unconfig(fusbd_sample_pt pInst)
{
	return 0;
}

static fusbd_endpoint_pt on_sample_assign_endpoint(fusbd_sample_pt pInst, const uint8_t * pEpDesc, const uint8_t * pIntfDesc)
{
	fusbd_sample_runtime_pt pRT = fusbd_sample_rt(pInst);
	
	return fusb_ep_desc_is_in(pEpDesc) ? &pRT->vEpIn : &pRT->vEpOut;
}

static int on_sample_setup_request(fusbd_sample_pt pInst, fusb_setup_reuqest_pt pReq)
{
	return 0;
}

static int on_sample_data_in(fusbd_sample_pt pInst, fusbd_endpoint_pt pEndPoint)
{
	return 0;
}

static int on_sample_data_out(fusbd_sample_pt pInst, fusbd_endpoint_pt pEndPoint)
{
	return 0;
}

static int on_sample_suspend(fusbd_sample_pt pInst)
{
	return 0;
}

static int on_sample_resume(fusbd_sample_pt pInst)
{
	return 0;
}

static int on_sample_sof(fusbd_sample_pt pInst)
{
	return 0;
}

BEGIN_FUSBD_CLASS_METHODS(fusbd_sample_methods)
	FUSBD_CLASS_METHOD(Init, on_sample_init),
	FUSBD_CLASS_METHOD(Config, on_sample_config),
	FUSBD_CLASS_METHOD(ConfigDone, on_sample_config_done),
	FUSBD_CLASS_METHOD(Unconfig, on_sample_unconfig),
	FUSBD_CLASS_METHOD(AssignEndPoint, on_sample_assign_endpoint),
	FUSBD_CLASS_METHOD(SetupRequest, on_sample_setup_request),
	FUSBD_CLASS_METHOD(DataIn, on_sample_data_in),
	FUSBD_CLASS_METHOD(DataOut, on_sample_data_out),
	FUSBD_CLASS_METHOD(Suspend, on_sample_suspend),
	FUSBD_CLASS_METHOD(Resume, on_sample_resume),
	FUSBD_CLASS_METHOD(SOF, on_sample_sof)
END_FUSBD_CLASS_METHODS();
