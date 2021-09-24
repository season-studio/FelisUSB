# group `Adapter_Event_Callbacks` {#group___adapter___event___callbacks}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`on_fusbd_adpt_init`](#group___adapter___event___callbacks_1gaa1d65b0efa7e558cd1ff77b7330027b2)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | event callback when the usb device object is initializing
`public int `[`on_fusbd_adpt_start`](#group___adapter___event___callbacks_1ga7122378f974a8806e9cf7be0b50e0cb0)`(fusbd_adapter_t * pInst)`            | event callback for starting the usb device
`public int `[`on_fusbd_adpt_set_address`](#group___adapter___event___callbacks_1gaff4f0e43115bed02d49386054206f2aa)`(fusbd_adapter_t * pInst,uint8_t nAddr)`            | event callback for setting the address of the usb device
`public int `[`on_fusbd_adpt_init_endpoints`](#group___adapter___event___callbacks_1gacf2dc41a15a3669e12db983f52e56f15)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pFirstEP)`            | event callback for initializing the endpoints assigned to the usb device

## Members

#### `public int `[`on_fusbd_adpt_init`](#group___adapter___event___callbacks_1gaa1d65b0efa7e558cd1ff77b7330027b2)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___adapter___event___callbacks_1gaa1d65b0efa7e558cd1ff77b7330027b2}

event callback when the usb device object is initializing

#### Parameters
* `pDev` the usb device object 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_start`](#group___adapter___event___callbacks_1ga7122378f974a8806e9cf7be0b50e0cb0)`(fusbd_adapter_t * pInst)` {#group___adapter___event___callbacks_1ga7122378f974a8806e9cf7be0b50e0cb0}

event callback for starting the usb device

#### Parameters
* `pInst` the instance of the adapter 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_set_address`](#group___adapter___event___callbacks_1gaff4f0e43115bed02d49386054206f2aa)`(fusbd_adapter_t * pInst,uint8_t nAddr)` {#group___adapter___event___callbacks_1gaff4f0e43115bed02d49386054206f2aa}

event callback for setting the address of the usb device

#### Parameters
* `pInst` the instance of the adapter 

* `nAddr` the address 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_init_endpoints`](#group___adapter___event___callbacks_1gacf2dc41a15a3669e12db983f52e56f15)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pFirstEP)` {#group___adapter___event___callbacks_1gacf2dc41a15a3669e12db983f52e56f15}

event callback for initializing the endpoints assigned to the usb device

#### Parameters
* `pDev` the usb device 

* `pFirstEP` the pointer to the first entry of the link list of the endpoints 

#### Returns
int 0 for success

