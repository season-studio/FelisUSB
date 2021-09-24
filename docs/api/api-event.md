# group `event funntions of the stack` {#group__event}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`on_fusbd_reset`](#group__event_1ga9df94df369128d288c6d956d9dfd087c)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | event callback for the reset signal appearing in the BUS
`public void `[`on_fusbd_setup_request`](#group__event_1ga45196e9a5922b2c45647db895261cbe9)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t * pReqBuf)`            | event callback for a setup request being received from the host
`public void `[`on_fusbd_data_in`](#group__event_1ga84bd962009db00bfcfbd75987b4c82f4)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)`            | event callback for a transmition being completed in an endpoint
`public void `[`on_fusbd_data_out`](#group__event_1ga10a7694207684904690c8a57d4f45999)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)`            | event callback for some data being received in an endpoint
`public void `[`on_fusbd_suspend`](#group__event_1ga4d560477089580e06418e266cf7b4cb6)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | event callback for a suspend signal being received from the host
`public void `[`on_fusbd_resume`](#group__event_1gafe71a273ceefc3af150b1cff4dbbf046)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | event callback for a resume signal being received from the host
`public void `[`on_fusbd_sof`](#group__event_1ga053ca600c4483048c2ce7b2772949baa)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | event callback for a sof signal being received from the host

## Members

#### `public void `[`on_fusbd_reset`](#group__event_1ga9df94df369128d288c6d956d9dfd087c)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group__event_1ga9df94df369128d288c6d956d9dfd087c}

event callback for the reset signal appearing in the BUS

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_setup_request`](#group__event_1ga45196e9a5922b2c45647db895261cbe9)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t * pReqBuf)` {#group__event_1ga45196e9a5922b2c45647db895261cbe9}

event callback for a setup request being received from the host

#### Parameters
* `pDev` the usb device 

* `pReqBuf` the buffer contains the request

#### `public void `[`on_fusbd_data_in`](#group__event_1ga84bd962009db00bfcfbd75987b4c82f4)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)` {#group__event_1ga84bd962009db00bfcfbd75987b4c82f4}

event callback for a transmition being completed in an endpoint

#### Parameters
* `pDev` the usb device 

* `nEpAddr` the address of the endpoint

#### `public void `[`on_fusbd_data_out`](#group__event_1ga10a7694207684904690c8a57d4f45999)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)` {#group__event_1ga10a7694207684904690c8a57d4f45999}

event callback for some data being received in an endpoint

#### Parameters
* `pDev` the usb device 

* `nEpAddr` the address of the endpoint

#### `public void `[`on_fusbd_suspend`](#group__event_1ga4d560477089580e06418e266cf7b4cb6)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group__event_1ga4d560477089580e06418e266cf7b4cb6}

event callback for a suspend signal being received from the host

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_resume`](#group__event_1gafe71a273ceefc3af150b1cff4dbbf046)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group__event_1gafe71a273ceefc3af150b1cff4dbbf046}

event callback for a resume signal being received from the host

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_sof`](#group__event_1ga053ca600c4483048c2ce7b2772949baa)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group__event_1ga053ca600c4483048c2ce7b2772949baa}

event callback for a sof signal being received from the host

#### Parameters
* `pDev` the usb device

