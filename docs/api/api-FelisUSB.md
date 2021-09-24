# group `FelisUSB` {#group___felis_u_s_b}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`INHERIT_FUSBD_CLASS_RUNTIME`](#group___felis_u_s_b_1gabb722211b02a756bf0a65dcf4e207641)            | toolkit for inheriting the basic members of the class's runtime
`define `[`fusbd_call_class_method`](#group___felis_u_s_b_1gab73ba5e7d6f407b43c3197b4ac8c550f)            | toolkit for invoke a method of a class
`define `[`BEGIN_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1gad1a28932a2761071d7f9844d1ff1cff8)            | toolkit for starting the declaration of a set of methods for a class
`define `[`FUSBD_CLASS_METHOD`](#group___felis_u_s_b_1ga9afc8bb718adc9b9e851e9bd7bed6d6b)            | toolkit for declaring a method of a class
`define `[`END_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1ga1a3538310b12b8712146ca322583c65e)            | toolkit for ending the declaration of a set of methods for a class
`define `[`EXTERN_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1ga167f423d3290ec0de6a6aad87b386c7e)            | toolkit for externalizing the set of the methods for a class
`define `[`INHERIT_FUSBD_CLASS`](#group___felis_u_s_b_1ga9c5185ead89affb031dfda29b5da82bf)            | toolkit fot inheriting the basic member of a usb class
`define `[`FUSBD_DEVICE_CONFIG`](#group___felis_u_s_b_1ga68af2eb438dac3abad5c13508df4a69e)            | toolkit for declaring the configuration of the usb device
`define `[`FUSBD_DEVICE`](#group___felis_u_s_b_1gaa0a9400dd8afe43f3158820dd2758b33)            | toolkit for declaring the usb device object
`define `[`fusbd_class_ep_open`](#group___felis_u_s_b_1ga0488bb2e02aa1607ef4aaf3b6d67a5ca)            | toolkit for opening an endpoint in a usb class
`define `[`fusbd_class_ep_close`](#group___felis_u_s_b_1ga50ad777e2e05fd2363ca565d006d75fd)            | toolkit for closing an endpoint in a usb class
`define `[`fusbd_class_ep_stall`](#group___felis_u_s_b_1gae183ec08ee5cea3c2480bd630514d8ac)            | toolkit for setting an endpoint to stall state in a usb class
`define `[`fusbd_class_ep_stall_clr`](#group___felis_u_s_b_1ga23a50d08e4e3bbe2352e99f1c43b6995)            | toolkit for clearing the stall state for an endpoint in a usb class
`define `[`fusbd_class_ep_isstall`](#group___felis_u_s_b_1gac74e20d39e5e4c75ae6b9dac43816db7)            | toolkit for checking if an endpoint is set to stall state in a usb class
`define `[`fusbd_class_ep_flush`](#group___felis_u_s_b_1gaf52b2df185b4375aedbecc4be14d696a)            | toolkit for flushing an endpoint in a usb class
`define `[`fusbd_class_send_data`](#group___felis_u_s_b_1ga43719f8deacf254f298a369b29d3cace)            | toolkit for sending data from an endpoint in a usb class
`define `[`fusbd_class_send_data_sync`](#group___felis_u_s_b_1ga41436df67e79226a8f4dded7ba23ea16)            | toolkit for sending data from an endpoint in a usb class until the transmition is completed
`define `[`fusbd_class_send_data_async`](#group___felis_u_s_b_1gafeb7e9dc25d0d25d5314a6fc267055d3)            | toolkit for sending data from an endpoint in a usb class without waiting
`define `[`fusbd_class_prepare_receive`](#group___felis_u_s_b_1gad2fb5950cbbd96102a6a6111e94ba22e)            | toolkit for preparing receiving data from an endpoint in a usb class
`define `[`fusbd_class_ctrl_send_data`](#group___felis_u_s_b_1ga3d9ad18e041ddf2ec077449e84ef07b7)            | toolkit for sending data by controlling transmition in a usb class
`define `[`fusbd_class_ctrl_receive`](#group___felis_u_s_b_1gaf277ab345ae54456911911d210aaee3b)            | toolkit for receiving data by controlling transmition in a usb class
`define `[`fusbd_class_ctrl_send_status`](#group___felis_u_s_b_1ga9875ff82e46570fed03e00bdf04d5f2c)            | toolkit for sending a zero length packet by controlling transmition in a usb class
`define `[`fusbd_class_ctrl_error`](#group___felis_u_s_b_1gaaf5f22e1b55d1ecac6f6de93a98df1e9)            | toolkit for sending an error signal by controlling transmition in a usb class
`define `[`fusbd_class_ctrl_send_resp`](#group___felis_u_s_b_1gaf2328dcfd6e8bd732b974a2e44a589f6)            | toolkit for sending a simple response by controlling transmition in a usb class
`define `[`DECL_USB_STRING_DESCRIPTOR`](#group___felis_u_s_b_1gae5d59109b69a65ed4c05ca7ba87f9b65)            | toolkit for declaring a string descriptor
`define `[`DECL_USB_ANONYMOUS_STRING_DESCRIPTOR`](#group___felis_u_s_b_1ga2f5916f6c0c6a3dd929eea7512f0682b)            | toolkit for declaring an anunymous string descriptor
`public int `[`fusbd_ep_open`](#group___felis_u_s_b_1ga2f2115b68356d3a6c3411529cbf0fe28)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | open an endpoint
`public int `[`fusbd_ep_close`](#group___felis_u_s_b_1ga4763cf35806b365c64da7de560165a48)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | close an endpoint
`public int `[`fusbd_ep_stall`](#group___felis_u_s_b_1gac353c39831d2ae4d42eac29fe9a5b9d7)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | set an endpoint to the stall state
`public int `[`fusbd_ep_stall_clr`](#group___felis_u_s_b_1ga2b14ad2baaea5a35ec4afa06e40c7275)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | clear the stall state for an endpoint
`public bool `[`fusbd_ep_is_stall`](#group___felis_u_s_b_1ga4d641357fc9da62ffe00dd5d6cc6d8ba)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | check if an endpoint is set to stall state
`public int `[`fusbd_ep_flush`](#group___felis_u_s_b_1ga7e4acb9f309f7857a26a0dcbc1cda85a)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | flush an endpoint
`public bool `[`fusbd_ep_is_busy`](#group___felis_u_s_b_1ga7fd603e3712ed8c412028f019a6d3a4b)`(`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | check if an endpoint is in transmition
`public bool `[`fusbd_ep_is_opened`](#group___felis_u_s_b_1gaf93946833fd7d31dcf35c06e8168dd89)`(`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | check if an endpoint is opened
`public int `[`fusbd_send_data`](#group___felis_u_s_b_1ga8cb4697e9d6ef04bc5127ca2c0d3a5ef)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize,uint32_t nTimeout)`            | send data in an endpoint
`public int `[`fusbd_send_data_sync`](#group___felis_u_s_b_1ga0c7ad7310fe08f68e6c7a0d0856ab2b8)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize)`            | send data in an endpoint until the transmition is completed
`public int `[`fusbd_send_data_async`](#group___felis_u_s_b_1gac39677b07e6b5cad8074b1e9bc52803f)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize)`            | send data in an endpoint without waiting the transmition completed
`public int `[`fusbd_prepare_receive`](#group___felis_u_s_b_1ga3a49a547151679bf7332fdd3c01f4057)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,void * pBuf,size_t nSize)`            | starting receiving data from an endpoint
`public int `[`fusbd_device_init`](#group___felis_u_s_b_1ga198e0e7beb02d55b37af275abced75eb)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | initialize a special usb device
`public int `[`fusbd_device_start`](#group___felis_u_s_b_1ga437689bbaaf5e53bba000b3d5affe0de)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | start a special usb device
`public uint8_t `[`fusbd_device_check_configed`](#group___felis_u_s_b_1gaa4fd6b72d4bc3a0a45d5c2ac5da80c0f)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint32_t nTimeout)`            | check if a configuration is selected by the host to the special usb device
`public __STATIC_FORCEINLINE int `[`fusbd_ctrl_error`](#group___felis_u_s_b_1ga7c34120bbc6694d9246165e396c56e55)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusb_setup_reuqest_t`](../api/api-FelisUSB.md#structfusb__setup__reuqest__t)` * pReq)`            | send an error signal for the controlling transmition
`public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_data`](#group___felis_u_s_b_1ga79af794d7fb1408324a198814c7918ca)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,const void * pBuf,size_t nSize)`            | send data by the controlling transmition
`public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_resp`](#group___felis_u_s_b_1gac7792e1e95ceb78d8d679f25507a6298)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint32_t nVal,size_t nSize)`            | send a simple response by the controlling transmition
`public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_status`](#group___felis_u_s_b_1gabdedbe325a9b75221a3cb5c9479b8469)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)`            | send a zere length packet by the controlling transmition
`public __STATIC_FORCEINLINE int `[`fusbd_ctrl_receive`](#group___felis_u_s_b_1gada07689cabab14ad96f8e79fb47a1365)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,void * pBuf,size_t nSize,`[`fusbd_ep0_out_callback_fn_t`](../api/api-undefined.md#group___felis_u_s_b_1ga7a88b45d62e796cabeff777a56b53051)` pfnCallback,const void * pUser)`            | start receiving data from the controlling transmition
`public bool `[`fusbd_ep_isstall`](#group___felis_u_s_b_1ga1da6172e71fe84dceda802f769a481ab)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)`            | 
`struct `[`fusbd_endpoint_t`](#struct__tag__fusbd__endpoint) | 
`struct `[`fusbd_class_runtime_t`](#structfusbd__class__runtime__t) | type of the class's runtime
`struct `[`fusbd_class_methods_t`](#structfusbd__class__methods__t) | type of the set of the callbacks of the class
`struct `[`fusbd_class_t`](#struct__tag__fusbd__class) | 
`struct `[`fusbd_device_config_t`](#structfusbd__device__config__t) | type of the configuration of the usb device
`struct `[`fusbd_device_t`](#struct__tag__fusbd__device) | 
`struct `[`fusb_setup_reuqest_t`](#structfusb__setup__reuqest__t) | type of the setup request
`struct `[`fusbd_endpoint_t`](#structfusbd__endpoint__t) | type of the endpoint of the usb device
`struct `[`fusbd_class_t`](#structfusbd__class__t) | type of the usb class
`struct `[`fusbd_device_t`](#structfusbd__device__t) | type of the usb device

## Members

#### `define `[`INHERIT_FUSBD_CLASS_RUNTIME`](#group___felis_u_s_b_1gabb722211b02a756bf0a65dcf4e207641) {#group___felis_u_s_b_1gabb722211b02a756bf0a65dcf4e207641}

toolkit for inheriting the basic members of the class's runtime

#### `define `[`fusbd_call_class_method`](#group___felis_u_s_b_1gab73ba5e7d6f407b43c3197b4ac8c550f) {#group___felis_u_s_b_1gab73ba5e7d6f407b43c3197b4ac8c550f}

toolkit for invoke a method of a class

#### Parameters
* `lpClass` pointer to the instance of the device interface class 

* `name` the name of the method 

* `...` arguments passed to the method

#### `define `[`BEGIN_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1gad1a28932a2761071d7f9844d1ff1cff8) {#group___felis_u_s_b_1gad1a28932a2761071d7f9844d1ff1cff8}

toolkit for starting the declaration of a set of methods for a class

#### Parameters
* `name` the name of the set of the methods

#### `define `[`FUSBD_CLASS_METHOD`](#group___felis_u_s_b_1ga9afc8bb718adc9b9e851e9bd7bed6d6b) {#group___felis_u_s_b_1ga9afc8bb718adc9b9e851e9bd7bed6d6b}

toolkit for declaring a method of a class

#### Parameters
* `name` the name of the method 

* `fn` the function assign to the method

#### `define `[`END_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1ga1a3538310b12b8712146ca322583c65e) {#group___felis_u_s_b_1ga1a3538310b12b8712146ca322583c65e}

toolkit for ending the declaration of a set of methods for a class

#### `define `[`EXTERN_FUSBD_CLASS_METHODS`](#group___felis_u_s_b_1ga167f423d3290ec0de6a6aad87b386c7e) {#group___felis_u_s_b_1ga167f423d3290ec0de6a6aad87b386c7e}

toolkit for externalizing the set of the methods for a class

#### Parameters
* `name` the name of the set of the methods

#### `define `[`INHERIT_FUSBD_CLASS`](#group___felis_u_s_b_1ga9c5185ead89affb031dfda29b5da82bf) {#group___felis_u_s_b_1ga9c5185ead89affb031dfda29b5da82bf}

toolkit fot inheriting the basic member of a usb class

#### `define `[`FUSBD_DEVICE_CONFIG`](#group___felis_u_s_b_1ga68af2eb438dac3abad5c13508df4a69e) {#group___felis_u_s_b_1ga68af2eb438dac3abad5c13508df4a69e}

toolkit for declaring the configuration of the usb device

#### Parameters
* `pDescs` pointer to the list of all descriptors 

* `...` list of the pointers to the instance of the device interface classes

#### `define `[`FUSBD_DEVICE`](#group___felis_u_s_b_1gaa0a9400dd8afe43f3158820dd2758b33) {#group___felis_u_s_b_1gaa0a9400dd8afe43f3158820dd2758b33}

toolkit for declaring the usb device object

#### Parameters
* `pCfg` the pointer to the configuration of the usb device

#### `define `[`fusbd_class_ep_open`](#group___felis_u_s_b_1ga0488bb2e02aa1607ef4aaf3b6d67a5ca) {#group___felis_u_s_b_1ga0488bb2e02aa1607ef4aaf3b6d67a5ca}

toolkit for opening an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_ep_close`](#group___felis_u_s_b_1ga50ad777e2e05fd2363ca565d006d75fd) {#group___felis_u_s_b_1ga50ad777e2e05fd2363ca565d006d75fd}

toolkit for closing an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_ep_stall`](#group___felis_u_s_b_1gae183ec08ee5cea3c2480bd630514d8ac) {#group___felis_u_s_b_1gae183ec08ee5cea3c2480bd630514d8ac}

toolkit for setting an endpoint to stall state in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_ep_stall_clr`](#group___felis_u_s_b_1ga23a50d08e4e3bbe2352e99f1c43b6995) {#group___felis_u_s_b_1ga23a50d08e4e3bbe2352e99f1c43b6995}

toolkit for clearing the stall state for an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_ep_isstall`](#group___felis_u_s_b_1gac74e20d39e5e4c75ae6b9dac43816db7) {#group___felis_u_s_b_1gac74e20d39e5e4c75ae6b9dac43816db7}

toolkit for checking if an endpoint is set to stall state in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_ep_flush`](#group___felis_u_s_b_1gaf52b2df185b4375aedbecc4be14d696a) {#group___felis_u_s_b_1gaf52b2df185b4375aedbecc4be14d696a}

toolkit for flushing an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint

#### `define `[`fusbd_class_send_data`](#group___felis_u_s_b_1ga43719f8deacf254f298a369b29d3cace) {#group___felis_u_s_b_1ga43719f8deacf254f298a369b29d3cace}

toolkit for sending data from an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint 

* `pBuf` the data to send 

* `nSize` the size of the data in the buffer 

* `nTimeout` time out for waiting the transmit complete

#### `define `[`fusbd_class_send_data_sync`](#group___felis_u_s_b_1ga41436df67e79226a8f4dded7ba23ea16) {#group___felis_u_s_b_1ga41436df67e79226a8f4dded7ba23ea16}

toolkit for sending data from an endpoint in a usb class until the transmition is completed

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint 

* `pBuf` the data to send 

* `nSize` the size of the data in the buffer

#### `define `[`fusbd_class_send_data_async`](#group___felis_u_s_b_1gafeb7e9dc25d0d25d5314a6fc267055d3) {#group___felis_u_s_b_1gafeb7e9dc25d0d25d5314a6fc267055d3}

toolkit for sending data from an endpoint in a usb class without waiting

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint 

* `pBuf` the data to send 

* `nSize` the size of the data

#### `define `[`fusbd_class_prepare_receive`](#group___felis_u_s_b_1gad2fb5950cbbd96102a6a6111e94ba22e) {#group___felis_u_s_b_1gad2fb5950cbbd96102a6a6111e94ba22e}

toolkit for preparing receiving data from an endpoint in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pUEP` pointer to the endpoint 

* `pBuf` the buffer to receive the data 

* `nSize` the size of the buffer

#### `define `[`fusbd_class_ctrl_send_data`](#group___felis_u_s_b_1ga3d9ad18e041ddf2ec077449e84ef07b7) {#group___felis_u_s_b_1ga3d9ad18e041ddf2ec077449e84ef07b7}

toolkit for sending data by controlling transmition in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pBuf` the data to send 

* `nSize` the size of the data

#### `define `[`fusbd_class_ctrl_receive`](#group___felis_u_s_b_1gaf277ab345ae54456911911d210aaee3b) {#group___felis_u_s_b_1gaf277ab345ae54456911911d210aaee3b}

toolkit for receiving data by controlling transmition in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pBuf` the buffer to receive the data 

* `nSize` the size of the buffer 

* `fn` the callback fucntion 

* `pUser` the argument pass to the callback function

#### `define `[`fusbd_class_ctrl_send_status`](#group___felis_u_s_b_1ga9875ff82e46570fed03e00bdf04d5f2c) {#group___felis_u_s_b_1ga9875ff82e46570fed03e00bdf04d5f2c}

toolkit for sending a zero length packet by controlling transmition in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class

#### `define `[`fusbd_class_ctrl_error`](#group___felis_u_s_b_1gaaf5f22e1b55d1ecac6f6de93a98df1e9) {#group___felis_u_s_b_1gaaf5f22e1b55d1ecac6f6de93a98df1e9}

toolkit for sending an error signal by controlling transmition in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `pReq` the content of the request

#### `define `[`fusbd_class_ctrl_send_resp`](#group___felis_u_s_b_1gaf2328dcfd6e8bd732b974a2e44a589f6) {#group___felis_u_s_b_1gaf2328dcfd6e8bd732b974a2e44a589f6}

toolkit for sending a simple response by controlling transmition in a usb class

#### Parameters
* `pClass` pointer to the instance of the device interface class 

* `val` the value of the simple response 

* `nSize` the size of the simple reponse, must no greater then 4byte

#### `define `[`INHERIT_FUSB_DESCRIPTOR`](#group___felis_u_s_b_1gafae5502a6d38142ac8a0e41d71102408) {#group___felis_u_s_b_1gafae5502a6d38142ac8a0e41d71102408}

#### `define `[`DECL_USB_STRING_DESCRIPTOR`](#group___felis_u_s_b_1gae5d59109b69a65ed4c05ca7ba87f9b65) {#group___felis_u_s_b_1gae5d59109b69a65ed4c05ca7ba87f9b65}

toolkit for declaring a string descriptor

#### Parameters
* `name` name of the descriptor 

* `text` content of the string

#### `define `[`DECL_USB_ANONYMOUS_STRING_DESCRIPTOR`](#group___felis_u_s_b_1ga2f5916f6c0c6a3dd929eea7512f0682b) {#group___felis_u_s_b_1ga2f5916f6c0c6a3dd929eea7512f0682b}

toolkit for declaring an anunymous string descriptor

#### Parameters
* `text` content of the string

#### `public int `[`fusbd_ep_open`](#group___felis_u_s_b_1ga2f2115b68356d3a6c3411529cbf0fe28)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga2f2115b68356d3a6c3411529cbf0fe28}

open an endpoint

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint to be opened 

#### Returns
int 0 for success

#### `public int `[`fusbd_ep_close`](#group___felis_u_s_b_1ga4763cf35806b365c64da7de560165a48)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga4763cf35806b365c64da7de560165a48}

close an endpoint

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint to be closed 

#### Returns
int 0 for success

#### `public int `[`fusbd_ep_stall`](#group___felis_u_s_b_1gac353c39831d2ae4d42eac29fe9a5b9d7)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1gac353c39831d2ae4d42eac29fe9a5b9d7}

set an endpoint to the stall state

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

#### Returns
int 0 for success

#### `public int `[`fusbd_ep_stall_clr`](#group___felis_u_s_b_1ga2b14ad2baaea5a35ec4afa06e40c7275)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga2b14ad2baaea5a35ec4afa06e40c7275}

clear the stall state for an endpoint

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

#### Returns
int 0 for success

#### `public bool `[`fusbd_ep_is_stall`](#group___felis_u_s_b_1ga4d641357fc9da62ffe00dd5d6cc6d8ba)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga4d641357fc9da62ffe00dd5d6cc6d8ba}

check if an endpoint is set to stall state

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

#### Returns
bool

#### `public int `[`fusbd_ep_flush`](#group___felis_u_s_b_1ga7e4acb9f309f7857a26a0dcbc1cda85a)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga7e4acb9f309f7857a26a0dcbc1cda85a}

flush an endpoint

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

#### Returns
int 0 for success

#### `public bool `[`fusbd_ep_is_busy`](#group___felis_u_s_b_1ga7fd603e3712ed8c412028f019a6d3a4b)`(`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga7fd603e3712ed8c412028f019a6d3a4b}

check if an endpoint is in transmition

#### Parameters
* `pUEP` the endpoint 

#### Returns
bool

#### `public bool `[`fusbd_ep_is_opened`](#group___felis_u_s_b_1gaf93946833fd7d31dcf35c06e8168dd89)`(`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1gaf93946833fd7d31dcf35c06e8168dd89}

check if an endpoint is opened

#### Parameters
* `pUEP` the endpoint 

#### Returns
bool

#### `public int `[`fusbd_send_data`](#group___felis_u_s_b_1ga8cb4697e9d6ef04bc5127ca2c0d3a5ef)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize,uint32_t nTimeout)` {#group___felis_u_s_b_1ga8cb4697e9d6ef04bc5127ca2c0d3a5ef}

send data in an endpoint

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

* `pBuf` the buffer contains the data to be sent 

* `nSize` the size of the data to be sent 

* `nTimeout` time for waiting the transmition completing in MS uint, 0 for no wait, -1 for no timeout 

#### Returns
int 0 for success

#### `public int `[`fusbd_send_data_sync`](#group___felis_u_s_b_1ga0c7ad7310fe08f68e6c7a0d0856ab2b8)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize)` {#group___felis_u_s_b_1ga0c7ad7310fe08f68e6c7a0d0856ab2b8}

send data in an endpoint until the transmition is completed

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

* `pBuf` the buffer contains the data to be sent 

* `nSize` the size of the data to be sent 

#### Returns
int 0 for success

#### `public int `[`fusbd_send_data_async`](#group___felis_u_s_b_1gac39677b07e6b5cad8074b1e9bc52803f)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,const void * pBuf,size_t nSize)` {#group___felis_u_s_b_1gac39677b07e6b5cad8074b1e9bc52803f}

send data in an endpoint without waiting the transmition completed

#### Parameters
* `pDev` the usb device 

* `pUEP` the endpoint 

* `pBuf` the buffer contains the data to be sent 

* `nSize` the size of the data to be sent 

#### Returns
int 0 for success

#### `public int `[`fusbd_prepare_receive`](#group___felis_u_s_b_1ga3a49a547151679bf7332fdd3c01f4057)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP,void * pBuf,size_t nSize)` {#group___felis_u_s_b_1ga3a49a547151679bf7332fdd3c01f4057}

starting receiving data from an endpoint

#### Parameters
* `pDev` the usd device 

* `pUEP` the endpoint 

* `pBuf` the buffer for receiving the data 

* `nSize` the size of the data would be received 

#### Returns
int 0 for success

#### `public int `[`fusbd_device_init`](#group___felis_u_s_b_1ga198e0e7beb02d55b37af275abced75eb)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1ga198e0e7beb02d55b37af275abced75eb}

initialize a special usb device

#### Parameters
* `pDev` pointer to an usb device 

#### Returns
int 0 for success

#### `public int `[`fusbd_device_start`](#group___felis_u_s_b_1ga437689bbaaf5e53bba000b3d5affe0de)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1ga437689bbaaf5e53bba000b3d5affe0de}

start a special usb device

#### Parameters
* `pDev` pointer to an usb device 

#### Returns
int 0 for success

#### `public uint8_t `[`fusbd_device_check_configed`](#group___felis_u_s_b_1gaa4fd6b72d4bc3a0a45d5c2ac5da80c0f)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint32_t nTimeout)` {#group___felis_u_s_b_1gaa4fd6b72d4bc3a0a45d5c2ac5da80c0f}

check if a configuration is selected by the host to the special usb device

#### Parameters
* `pDev` pointer to an usb device 

* `nTimeout` timeout for waiting the configaration selected, 0 for without waiting, -1 for without timeout 

#### Returns
uint8_t 0 for no configed, other is the index of the configuration selected by the host

#### `public __STATIC_FORCEINLINE int `[`fusbd_ctrl_error`](#group___felis_u_s_b_1ga7c34120bbc6694d9246165e396c56e55)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusb_setup_reuqest_t`](../api/api-FelisUSB.md#structfusb__setup__reuqest__t)` * pReq)` {#group___felis_u_s_b_1ga7c34120bbc6694d9246165e396c56e55}

send an error signal for the controlling transmition

#### Parameters
* `pDev` the usb device 

* `pReq` the request buffer 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_data`](#group___felis_u_s_b_1ga79af794d7fb1408324a198814c7918ca)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,const void * pBuf,size_t nSize)` {#group___felis_u_s_b_1ga79af794d7fb1408324a198814c7918ca}

send data by the controlling transmition

#### Parameters
* `pDev` the usb device 

* `pBuf` the buffer contains the data to be sent 

* `nSize` the size of the data to be sent 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_resp`](#group___felis_u_s_b_1gac7792e1e95ceb78d8d679f25507a6298)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint32_t nVal,size_t nSize)` {#group___felis_u_s_b_1gac7792e1e95ceb78d8d679f25507a6298}

send a simple response by the controlling transmition

#### Parameters
* `pDev` the usb device 

* `nVal` the value of the simple response 

* `nSize` the size of the simple response 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_ctrl_send_status`](#group___felis_u_s_b_1gabdedbe325a9b75221a3cb5c9479b8469)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1gabdedbe325a9b75221a3cb5c9479b8469}

send a zere length packet by the controlling transmition

#### Parameters
* `pDev` the usb device 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_ctrl_receive`](#group___felis_u_s_b_1gada07689cabab14ad96f8e79fb47a1365)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,void * pBuf,size_t nSize,`[`fusbd_ep0_out_callback_fn_t`](../api/api-undefined.md#group___felis_u_s_b_1ga7a88b45d62e796cabeff777a56b53051)` pfnCallback,const void * pUser)` {#group___felis_u_s_b_1gada07689cabab14ad96f8e79fb47a1365}

start receiving data from the controlling transmition

#### Parameters
* `pDev` the usb device 

* `pBuf` the buffer for receiveing the data 

* `nSize` the size of the data would be received 

* `pfnCallback` the callback function need being invoked when the data is received, can be NULL 

* `pUser` the user data will passed to the callback function 

#### Returns
int 0 for success

#### `public bool `[`fusbd_ep_isstall`](#group___felis_u_s_b_1ga1da6172e71fe84dceda802f769a481ab)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pUEP)` {#group___felis_u_s_b_1ga1da6172e71fe84dceda802f769a481ab}

#### `public void `[`on_fusbd_reset`](#group___felis_u_s_b_1ga9df94df369128d288c6d956d9dfd087c)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1ga9df94df369128d288c6d956d9dfd087c}

event callback for the reset signal appearing in the BUS

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_setup_request`](#group___felis_u_s_b_1ga45196e9a5922b2c45647db895261cbe9)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t * pReqBuf)` {#group___felis_u_s_b_1ga45196e9a5922b2c45647db895261cbe9}

event callback for a setup request being received from the host

#### Parameters
* `pDev` the usb device 

* `pReqBuf` the buffer contains the request

#### `public void `[`on_fusbd_data_in`](#group___felis_u_s_b_1ga84bd962009db00bfcfbd75987b4c82f4)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)` {#group___felis_u_s_b_1ga84bd962009db00bfcfbd75987b4c82f4}

event callback for a transmition being completed in an endpoint

#### Parameters
* `pDev` the usb device 

* `nEpAddr` the address of the endpoint

#### `public void `[`on_fusbd_data_out`](#group___felis_u_s_b_1ga10a7694207684904690c8a57d4f45999)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,uint8_t nEpAddr)` {#group___felis_u_s_b_1ga10a7694207684904690c8a57d4f45999}

event callback for some data being received in an endpoint

#### Parameters
* `pDev` the usb device 

* `nEpAddr` the address of the endpoint

#### `public void `[`on_fusbd_suspend`](#group___felis_u_s_b_1ga4d560477089580e06418e266cf7b4cb6)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1ga4d560477089580e06418e266cf7b4cb6}

event callback for a suspend signal being received from the host

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_resume`](#group___felis_u_s_b_1gafe71a273ceefc3af150b1cff4dbbf046)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1gafe71a273ceefc3af150b1cff4dbbf046}

event callback for a resume signal being received from the host

#### Parameters
* `pDev` the usb device

#### `public void `[`on_fusbd_sof`](#group___felis_u_s_b_1ga053ca600c4483048c2ce7b2772949baa)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1ga053ca600c4483048c2ce7b2772949baa}

event callback for a sof signal being received from the host

#### Parameters
* `pDev` the usb device

#### `public int `[`on_fusbd_adpt_init`](#group___felis_u_s_b_1gaa1d65b0efa7e558cd1ff77b7330027b2)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev)` {#group___felis_u_s_b_1gaa1d65b0efa7e558cd1ff77b7330027b2}

event callback when the usb device object is initializing

#### Parameters
* `pDev` the usb device object 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_start`](#group___felis_u_s_b_1ga7122378f974a8806e9cf7be0b50e0cb0)`(fusbd_adapter_t * pInst)` {#group___felis_u_s_b_1ga7122378f974a8806e9cf7be0b50e0cb0}

event callback for starting the usb device

#### Parameters
* `pInst` the instance of the adapter 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_set_address`](#group___felis_u_s_b_1gaff4f0e43115bed02d49386054206f2aa)`(fusbd_adapter_t * pInst,uint8_t nAddr)` {#group___felis_u_s_b_1gaff4f0e43115bed02d49386054206f2aa}

event callback for setting the address of the usb device

#### Parameters
* `pInst` the instance of the adapter 

* `nAddr` the address 

#### Returns
int 0 for success

#### `public int `[`on_fusbd_adpt_init_endpoints`](#group___felis_u_s_b_1gacf2dc41a15a3669e12db983f52e56f15)`(`[`fusbd_device_pt`](../api/api-undefined.md#group___felis_u_s_b_1gacace61d29ac4d7323c873f2f75f16124)` pDev,`[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` pFirstEP)` {#group___felis_u_s_b_1gacf2dc41a15a3669e12db983f52e56f15}

event callback for initializing the endpoints assigned to the usb device

#### Parameters
* `pDev` the usb device 

* `pFirstEP` the pointer to the first entry of the link list of the endpoints 

#### Returns
int 0 for success

# struct `fusbd_endpoint_t` {#struct__tag__fusbd__endpoint}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public struct _tag_fusbd_endpoint * `[`pNext`](#struct__tag__fusbd__endpoint_1a125a5c98a973d6ddfb81d6d48ee0eaba) | point to the next endpoint
`public const uint8_t * `[`pDesc`](#struct__tag__fusbd__endpoint_1ad5b43a4f0c761fbd92c0f1a7238ca5e2) | point to the descriptor of this endpoint
`public uint8_t `[`nIntf`](#struct__tag__fusbd__endpoint_1a369e6a9f64ac77c4cb428ee36bd2a834) | the index of the interface use this endpoint
`public volatile uint8_t `[`nFlag`](#struct__tag__fusbd__endpoint_1ab7b118ac59a1c34711639d1b2e1ada25) | the flag of this endpoint
`public uint16_t `[`nXferSize`](#struct__tag__fusbd__endpoint_1a324cb19dcfbe2006dbfe46c86896ce2e) | the size of the data being transmited by this endpoint
`public void * `[`pXferBuf`](#struct__tag__fusbd__endpoint_1aa4589d8ad003d5075dc62f2d80e8fb5c) | the buffer contains the data being transmited by this endpoint

## Members

#### `public struct _tag_fusbd_endpoint * `[`pNext`](#struct__tag__fusbd__endpoint_1a125a5c98a973d6ddfb81d6d48ee0eaba) {#struct__tag__fusbd__endpoint_1a125a5c98a973d6ddfb81d6d48ee0eaba}

point to the next endpoint

#### `public const uint8_t * `[`pDesc`](#struct__tag__fusbd__endpoint_1ad5b43a4f0c761fbd92c0f1a7238ca5e2) {#struct__tag__fusbd__endpoint_1ad5b43a4f0c761fbd92c0f1a7238ca5e2}

point to the descriptor of this endpoint

#### `public uint8_t `[`nIntf`](#struct__tag__fusbd__endpoint_1a369e6a9f64ac77c4cb428ee36bd2a834) {#struct__tag__fusbd__endpoint_1a369e6a9f64ac77c4cb428ee36bd2a834}

the index of the interface use this endpoint

#### `public volatile uint8_t `[`nFlag`](#struct__tag__fusbd__endpoint_1ab7b118ac59a1c34711639d1b2e1ada25) {#struct__tag__fusbd__endpoint_1ab7b118ac59a1c34711639d1b2e1ada25}

the flag of this endpoint

#### `public uint16_t `[`nXferSize`](#struct__tag__fusbd__endpoint_1a324cb19dcfbe2006dbfe46c86896ce2e) {#struct__tag__fusbd__endpoint_1a324cb19dcfbe2006dbfe46c86896ce2e}

the size of the data being transmited by this endpoint

#### `public void * `[`pXferBuf`](#struct__tag__fusbd__endpoint_1aa4589d8ad003d5075dc62f2d80e8fb5c) {#struct__tag__fusbd__endpoint_1aa4589d8ad003d5075dc62f2d80e8fb5c}

the buffer contains the data being transmited by this endpoint

# struct `fusbd_class_runtime_t` {#structfusbd__class__runtime__t}

type of the class's runtime

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`INHERIT_FUSBD_CLASS_RUNTIME`](#structfusbd__class__runtime__t_1a3fa034a3f81569277f390c3c96d3e039) | 

## Members

#### `public  `[`INHERIT_FUSBD_CLASS_RUNTIME`](#structfusbd__class__runtime__t_1a3fa034a3f81569277f390c3c96d3e039) {#structfusbd__class__runtime__t_1a3fa034a3f81569277f390c3c96d3e039}

# struct `fusbd_class_methods_t` {#structfusbd__class__methods__t}

type of the set of the callbacks of the class

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a31774ffc3fdef71468ea36f5db782532)`(Init)` | the callback function for initializing the class
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1ab0dab832d64ba97da1ca5fbd5dc74e16)`(Config)` | the callback function for configing the class when the usb device is configed by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a1a56ae5127bbc8bce08e8c3f5f93aba4)`(ConfigDone)` | the callback function for finishing configing the class when the usb device is configed by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1aa0f64e6e1d3a7376015c13392f10fe16)`(Unconfig)` | the callback function for unconfiging the class when the usb device is configed by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1af4598be4c55c5cd655936bf0305ca72b)`(AssignEndPoint)` | the callback function for assigning an endpoint to the class when the usb device is configed by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a0949280ab1f203b6fda4125ab6e46ede)`(SetupRequest)` | the callback function for processing the request when the usb device received setup request from ths host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a7d498bf5207cbe1ec0cf720c2f88c808)`(DataIn)` | the callback function when a transmiting is completed in an endpoint
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a07639f61a7e1a27471f1a0d075a017c2)`(DataOut)` | the callback function when some data is received from the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a23821db93a10ef90b06b51fa94606c0c)`(Suspend)` | the callback function for suspending the class when the usb device is suspended by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1ac186f59f74ee4ce01c114e9e938f0079)`(Resume)` | the callback function for resuming the class when the usb device is resumed by the host
`public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a1f5c71c7bde4ad14ea425f6b9f06e3e3)`(SOF)` | the callback function for processing the SOF signal

## Members

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a31774ffc3fdef71468ea36f5db782532)`(Init)` {#structfusbd__class__methods__t_1a31774ffc3fdef71468ea36f5db782532}

the callback function for initializing the class

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1ab0dab832d64ba97da1ca5fbd5dc74e16)`(Config)` {#structfusbd__class__methods__t_1ab0dab832d64ba97da1ca5fbd5dc74e16}

the callback function for configing the class when the usb device is configed by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a1a56ae5127bbc8bce08e8c3f5f93aba4)`(ConfigDone)` {#structfusbd__class__methods__t_1a1a56ae5127bbc8bce08e8c3f5f93aba4}

the callback function for finishing configing the class when the usb device is configed by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1aa0f64e6e1d3a7376015c13392f10fe16)`(Unconfig)` {#structfusbd__class__methods__t_1aa0f64e6e1d3a7376015c13392f10fe16}

the callback function for unconfiging the class when the usb device is configed by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1af4598be4c55c5cd655936bf0305ca72b)`(AssignEndPoint)` {#structfusbd__class__methods__t_1af4598be4c55c5cd655936bf0305ca72b}

the callback function for assigning an endpoint to the class when the usb device is configed by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a0949280ab1f203b6fda4125ab6e46ede)`(SetupRequest)` {#structfusbd__class__methods__t_1a0949280ab1f203b6fda4125ab6e46ede}

the callback function for processing the request when the usb device received setup request from ths host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a7d498bf5207cbe1ec0cf720c2f88c808)`(DataIn)` {#structfusbd__class__methods__t_1a7d498bf5207cbe1ec0cf720c2f88c808}

the callback function when a transmiting is completed in an endpoint

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a07639f61a7e1a27471f1a0d075a017c2)`(DataOut)` {#structfusbd__class__methods__t_1a07639f61a7e1a27471f1a0d075a017c2}

the callback function when some data is received from the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a23821db93a10ef90b06b51fa94606c0c)`(Suspend)` {#structfusbd__class__methods__t_1a23821db93a10ef90b06b51fa94606c0c}

the callback function for suspending the class when the usb device is suspended by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1ac186f59f74ee4ce01c114e9e938f0079)`(Resume)` {#structfusbd__class__methods__t_1ac186f59f74ee4ce01c114e9e938f0079}

the callback function for resuming the class when the usb device is resumed by the host

#### `public  `[`_FUSBD_CLASS_METHOD`](#structfusbd__class__methods__t_1a1f5c71c7bde4ad14ea425f6b9f06e3e3)`(SOF)` {#structfusbd__class__methods__t_1a1f5c71c7bde4ad14ea425f6b9f06e3e3}

the callback function for processing the SOF signal

# struct `fusbd_class_t` {#struct__tag__fusbd__class}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`INHERIT_FUSBD_CLASS`](#struct__tag__fusbd__class_1a8ff50364061702270d743a4c5e091963) | 

## Members

#### `public  `[`INHERIT_FUSBD_CLASS`](#struct__tag__fusbd__class_1a8ff50364061702270d743a4c5e091963) {#struct__tag__fusbd__class_1a8ff50364061702270d743a4c5e091963}

# struct `fusbd_device_config_t` {#structfusbd__device__config__t}

type of the configuration of the usb device

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const fusbd_descriptor_set_t * `[`pDescriptors`](#structfusbd__device__config__t_1ae6baa3a7fb5883f56b865657523daa96) | pointer to the descriptors for the device
`public `[`fusbd_class_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga56f1a1b1c4859e691c6ae5e1cc49d80e)` `[`zClassPtrs`](#structfusbd__device__config__t_1a3614857a4619ca93f95a3317234b5b24) | array of the classes assigned to the device, this array must be ended by NULL

## Members

#### `public const fusbd_descriptor_set_t * `[`pDescriptors`](#structfusbd__device__config__t_1ae6baa3a7fb5883f56b865657523daa96) {#structfusbd__device__config__t_1ae6baa3a7fb5883f56b865657523daa96}

pointer to the descriptors for the device

#### `public `[`fusbd_class_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga56f1a1b1c4859e691c6ae5e1cc49d80e)` `[`zClassPtrs`](#structfusbd__device__config__t_1a3614857a4619ca93f95a3317234b5b24) {#structfusbd__device__config__t_1a3614857a4619ca93f95a3317234b5b24}

array of the classes assigned to the device, this array must be ended by NULL

# struct `fusbd_device_t` {#struct__tag__fusbd__device}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const `[`fusbd_device_config_t`](../api/api-FelisUSB.md#structfusbd__device__config__t)` * `[`pConfig`](#struct__tag__fusbd__device_1a0372a80c6202aa99f4d2d4e7659646d2) | pointer to the configuration of the device
`public fusbd_adapter_t * `[`pAdapter`](#struct__tag__fusbd__device_1a2f8855dbdbd7f97d3faaa2daf92e8d78) | pointer to the instance of the adapter of the USB hardware
`public uint8_t `[`nRemoteWakeup`](#struct__tag__fusbd__device_1a85be9f47fa67b147d784574ae33c6f93) | record the state of the remote_wakeup
`public uint8_t `[`nSpeed`](#struct__tag__fusbd__device_1a64c0a4c5472f956c5883e3876f2dba2e) | record the speed of the usb device
`public uint8_t `[`nConfigIndex`](#struct__tag__fusbd__device_1afcc744676f5fa7cda5b1b6ecf6281fe3) | record the index of the configuration the host selected
`public volatile uint8_t `[`nState`](#struct__tag__fusbd__device_1afc3e5ec84a51931d59d014fb52a62b10) | record the state of the usb device
`public uint16_t `[`nEP0DataInRemain`](#struct__tag__fusbd__device_1ac2565f87e2ea69b8a49fac990331f9df) | record the size of the data remained for transmiting in endpoint 0
`public uint16_t `[`nEP0DataOutRemain`](#struct__tag__fusbd__device_1a275810634aa3dcb784f8440cbadc0dd6) | record the size of the data remained for receiving in endpoint 0
`public uint16_t `[`nEP0DataOutTotal`](#struct__tag__fusbd__device_1a79aa0200c6b9ab0e899f43599f19f3cb) | record the total size of the data needed receiving in endpoint 0
`public uint8_t `[`nEP0InFlag`](#struct__tag__fusbd__device_1a97189db50c18b306075ffd00c127f25e) | record the state of the transmiting in endpoint 0
`public uint8_t `[`nEP0OutFlag`](#struct__tag__fusbd__device_1a756ac9b3fa1c83f9565f112b2287804e) | record the state of the receiving in endpoint 0
`public void * `[`pEP0OutBuf`](#struct__tag__fusbd__device_1aa32e2e28b505812eaacc0b18e071ea3d) | record the buffer of for receiving the data in endpoint 0
`public const void * `[`pEP0CallbackUser`](#struct__tag__fusbd__device_1ad998f4cc1ff4c8f2778dbce642156e5b) | the user data passed to the callback function when some data is received in the endpoint 0
`public `[`fusbd_ep0_out_callback_fn_t`](../api/api-undefined.md#group___felis_u_s_b_1ga7a88b45d62e796cabeff777a56b53051)` `[`fnEP0OutCallback`](#struct__tag__fusbd__device_1af516240fc1f0f5d74c8c2f8758ba960a) | < the callback function when some data is received in the endpoint 0
`public `[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` `[`pEndPoints`](#struct__tag__fusbd__device_1abc0b75c7b1d4b858e6fc7116d6505d1c) | record the first pointer of the endpoint of the link list of all endpoints assigned to the classes in the usb device
`public uint32_t `[`gCtrlResp`](#struct__tag__fusbd__device_1a5a58d2c247fda75a68ae8723373e22af) | a temporary buffer for storing the simple response sent from the controlling transmition

## Members

#### `public const `[`fusbd_device_config_t`](../api/api-FelisUSB.md#structfusbd__device__config__t)` * `[`pConfig`](#struct__tag__fusbd__device_1a0372a80c6202aa99f4d2d4e7659646d2) {#struct__tag__fusbd__device_1a0372a80c6202aa99f4d2d4e7659646d2}

pointer to the configuration of the device

#### `public fusbd_adapter_t * `[`pAdapter`](#struct__tag__fusbd__device_1a2f8855dbdbd7f97d3faaa2daf92e8d78) {#struct__tag__fusbd__device_1a2f8855dbdbd7f97d3faaa2daf92e8d78}

pointer to the instance of the adapter of the USB hardware

#### `public uint8_t `[`nRemoteWakeup`](#struct__tag__fusbd__device_1a85be9f47fa67b147d784574ae33c6f93) {#struct__tag__fusbd__device_1a85be9f47fa67b147d784574ae33c6f93}

record the state of the remote_wakeup

#### `public uint8_t `[`nSpeed`](#struct__tag__fusbd__device_1a64c0a4c5472f956c5883e3876f2dba2e) {#struct__tag__fusbd__device_1a64c0a4c5472f956c5883e3876f2dba2e}

record the speed of the usb device

#### `public uint8_t `[`nConfigIndex`](#struct__tag__fusbd__device_1afcc744676f5fa7cda5b1b6ecf6281fe3) {#struct__tag__fusbd__device_1afcc744676f5fa7cda5b1b6ecf6281fe3}

record the index of the configuration the host selected

#### `public volatile uint8_t `[`nState`](#struct__tag__fusbd__device_1afc3e5ec84a51931d59d014fb52a62b10) {#struct__tag__fusbd__device_1afc3e5ec84a51931d59d014fb52a62b10}

record the state of the usb device

#### `public uint16_t `[`nEP0DataInRemain`](#struct__tag__fusbd__device_1ac2565f87e2ea69b8a49fac990331f9df) {#struct__tag__fusbd__device_1ac2565f87e2ea69b8a49fac990331f9df}

record the size of the data remained for transmiting in endpoint 0

#### `public uint16_t `[`nEP0DataOutRemain`](#struct__tag__fusbd__device_1a275810634aa3dcb784f8440cbadc0dd6) {#struct__tag__fusbd__device_1a275810634aa3dcb784f8440cbadc0dd6}

record the size of the data remained for receiving in endpoint 0

#### `public uint16_t `[`nEP0DataOutTotal`](#struct__tag__fusbd__device_1a79aa0200c6b9ab0e899f43599f19f3cb) {#struct__tag__fusbd__device_1a79aa0200c6b9ab0e899f43599f19f3cb}

record the total size of the data needed receiving in endpoint 0

#### `public uint8_t `[`nEP0InFlag`](#struct__tag__fusbd__device_1a97189db50c18b306075ffd00c127f25e) {#struct__tag__fusbd__device_1a97189db50c18b306075ffd00c127f25e}

record the state of the transmiting in endpoint 0

#### `public uint8_t `[`nEP0OutFlag`](#struct__tag__fusbd__device_1a756ac9b3fa1c83f9565f112b2287804e) {#struct__tag__fusbd__device_1a756ac9b3fa1c83f9565f112b2287804e}

record the state of the receiving in endpoint 0

#### `public void * `[`pEP0OutBuf`](#struct__tag__fusbd__device_1aa32e2e28b505812eaacc0b18e071ea3d) {#struct__tag__fusbd__device_1aa32e2e28b505812eaacc0b18e071ea3d}

record the buffer of for receiving the data in endpoint 0

#### `public const void * `[`pEP0CallbackUser`](#struct__tag__fusbd__device_1ad998f4cc1ff4c8f2778dbce642156e5b) {#struct__tag__fusbd__device_1ad998f4cc1ff4c8f2778dbce642156e5b}

the user data passed to the callback function when some data is received in the endpoint 0

#### `public `[`fusbd_ep0_out_callback_fn_t`](../api/api-undefined.md#group___felis_u_s_b_1ga7a88b45d62e796cabeff777a56b53051)` `[`fnEP0OutCallback`](#struct__tag__fusbd__device_1af516240fc1f0f5d74c8c2f8758ba960a) {#struct__tag__fusbd__device_1af516240fc1f0f5d74c8c2f8758ba960a}

< the callback function when some data is received in the endpoint 0

#### `public `[`fusbd_endpoint_pt`](../api/api-undefined.md#group___felis_u_s_b_1ga62fd52a332bd22098b0a6e183bb3274c)` `[`pEndPoints`](#struct__tag__fusbd__device_1abc0b75c7b1d4b858e6fc7116d6505d1c) {#struct__tag__fusbd__device_1abc0b75c7b1d4b858e6fc7116d6505d1c}

record the first pointer of the endpoint of the link list of all endpoints assigned to the classes in the usb device

#### `public uint32_t `[`gCtrlResp`](#struct__tag__fusbd__device_1a5a58d2c247fda75a68ae8723373e22af) {#struct__tag__fusbd__device_1a5a58d2c247fda75a68ae8723373e22af}

a temporary buffer for storing the simple response sent from the controlling transmition

# struct `fusb_setup_reuqest_t` {#structfusb__setup__reuqest__t}

type of the setup request

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bmRequest`](#structfusb__setup__reuqest__t_1ae9d47c1f5d3b81fa2f00e3177c02f8ba) | 
`public uint8_t `[`bRequest`](#structfusb__setup__reuqest__t_1a1e7be110861bd4ff75c86d5214f31543) | 
`public uint8_t `[`ucValue`](#structfusb__setup__reuqest__t_1ab0f64bc1fc85327e82697007d93c48ad) | 
`public uint16_t `[`wValue`](#structfusb__setup__reuqest__t_1a7383d0165ad8eab48aa239c005199121) | 
`public union fusb_setup_reuqest_t::@0 `[`@1`](#structfusb__setup__reuqest__t_1aa10dc773eb2f8ef3c691aeb6695877ef) | 
`public uint8_t `[`ucIndex`](#structfusb__setup__reuqest__t_1a091e92d4059bb3ef26e3cf12fbc3e7af) | 
`public uint16_t `[`wIndex`](#structfusb__setup__reuqest__t_1adc578ce35d89d52deba61ee6f312f177) | 
`public union fusb_setup_reuqest_t::@2 `[`@3`](#structfusb__setup__reuqest__t_1a2cd257cae6ec4d831504494722b00935) | 
`public uint16_t `[`wLength`](#structfusb__setup__reuqest__t_1a496c03443b177fd2e6c93616064d2934) | 

## Members

#### `public uint8_t `[`bmRequest`](#structfusb__setup__reuqest__t_1ae9d47c1f5d3b81fa2f00e3177c02f8ba) {#structfusb__setup__reuqest__t_1ae9d47c1f5d3b81fa2f00e3177c02f8ba}

#### `public uint8_t `[`bRequest`](#structfusb__setup__reuqest__t_1a1e7be110861bd4ff75c86d5214f31543) {#structfusb__setup__reuqest__t_1a1e7be110861bd4ff75c86d5214f31543}

#### `public uint8_t `[`ucValue`](#structfusb__setup__reuqest__t_1ab0f64bc1fc85327e82697007d93c48ad) {#structfusb__setup__reuqest__t_1ab0f64bc1fc85327e82697007d93c48ad}

#### `public uint16_t `[`wValue`](#structfusb__setup__reuqest__t_1a7383d0165ad8eab48aa239c005199121) {#structfusb__setup__reuqest__t_1a7383d0165ad8eab48aa239c005199121}

#### `public union fusb_setup_reuqest_t::@0 `[`@1`](#structfusb__setup__reuqest__t_1aa10dc773eb2f8ef3c691aeb6695877ef) {#structfusb__setup__reuqest__t_1aa10dc773eb2f8ef3c691aeb6695877ef}

#### `public uint8_t `[`ucIndex`](#structfusb__setup__reuqest__t_1a091e92d4059bb3ef26e3cf12fbc3e7af) {#structfusb__setup__reuqest__t_1a091e92d4059bb3ef26e3cf12fbc3e7af}

#### `public uint16_t `[`wIndex`](#structfusb__setup__reuqest__t_1adc578ce35d89d52deba61ee6f312f177) {#structfusb__setup__reuqest__t_1adc578ce35d89d52deba61ee6f312f177}

#### `public union fusb_setup_reuqest_t::@2 `[`@3`](#structfusb__setup__reuqest__t_1a2cd257cae6ec4d831504494722b00935) {#structfusb__setup__reuqest__t_1a2cd257cae6ec4d831504494722b00935}

#### `public uint16_t `[`wLength`](#structfusb__setup__reuqest__t_1a496c03443b177fd2e6c93616064d2934) {#structfusb__setup__reuqest__t_1a496c03443b177fd2e6c93616064d2934}

# struct `fusbd_endpoint_t` {#structfusbd__endpoint__t}

type of the endpoint of the usb device

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `fusbd_class_t` {#structfusbd__class__t}

type of the usb class

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `fusbd_device_t` {#structfusbd__device__t}

type of the usb device

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

