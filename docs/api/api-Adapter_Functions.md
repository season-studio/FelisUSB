# group `Adapter_Functions` {#group___adapter___functions}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_open`](#group___adapter___functions_1gad05ca1db37c0034fde663a1cf45d64df)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,size_t nMps,uint8_t nType)`            | open an endpoint
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_close`](#group___adapter___functions_1gae08d474d7ce89805cfce18274cbd4c99)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)`            | close an endpoint
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_stall`](#group___adapter___functions_1ga66093235c1188e562267b164f3e59dae)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)`            | set an endpoint to stall
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_stall_clr`](#group___adapter___functions_1ga337708faac43573b643e7edfdb11a5f4)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)`            | clear stall state for an endpoint
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_isstall`](#group___adapter___functions_1ga8c89548efa9cc05b228401a44e6c93d0)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)`            | check if an endpoint is in stall state
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_flush`](#group___adapter___functions_1gacf4283562619ebc921664582cd89ff6c)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)`            | flush an endpoint
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_transmit`](#group___adapter___functions_1gaf228d183c74588780303f8afcb15a574)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,uint8_t * pBuf,size_t nSize)`            | transmit data by an endpoint
`public __STATIC_FORCEINLINE int `[`fusbd_adpt_prepare_receive`](#group___adapter___functions_1ga8fcc122d9fb102b5604fb145cd768a8a)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,void * pBuf,size_t nSize)`            | receive data from an endpoint
`public __STATIC_FORCEINLINE uint32_t `[`fusbd_adpt_get_tickcount`](#group___adapter___functions_1gad6ffb995d68acebdc26708dd395eeda0)`(fusbd_adapter_t * pInst)`            | get the tick count

## Members

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_open`](#group___adapter___functions_1gad05ca1db37c0034fde663a1cf45d64df)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,size_t nMps,uint8_t nType)` {#group___adapter___functions_1gad05ca1db37c0034fde663a1cf45d64df}

open an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

* `nMps` the max_packet_size of the endpoint 

* `nType` the type of the transmition of the endpoint 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_close`](#group___adapter___functions_1gae08d474d7ce89805cfce18274cbd4c99)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)` {#group___adapter___functions_1gae08d474d7ce89805cfce18274cbd4c99}

close an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

#### Returns
int 0 for address

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_stall`](#group___adapter___functions_1ga66093235c1188e562267b164f3e59dae)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)` {#group___adapter___functions_1ga66093235c1188e562267b164f3e59dae}

set an endpoint to stall

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

#### Returns
int 0 for address

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_stall_clr`](#group___adapter___functions_1ga337708faac43573b643e7edfdb11a5f4)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)` {#group___adapter___functions_1ga337708faac43573b643e7edfdb11a5f4}

clear stall state for an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

#### Returns
int 0 for address

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_isstall`](#group___adapter___functions_1ga8c89548efa9cc05b228401a44e6c93d0)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)` {#group___adapter___functions_1ga8c89548efa9cc05b228401a44e6c93d0}

check if an endpoint is in stall state

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

#### Returns
int 0 for address

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_ep_flush`](#group___adapter___functions_1gacf4283562619ebc921664582cd89ff6c)`(fusbd_adapter_t * pInst,uint8_t nEpAddr)` {#group___adapter___functions_1gacf4283562619ebc921664582cd89ff6c}

flush an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_transmit`](#group___adapter___functions_1gaf228d183c74588780303f8afcb15a574)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,uint8_t * pBuf,size_t nSize)` {#group___adapter___functions_1gaf228d183c74588780303f8afcb15a574}

transmit data by an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

* `pBuf` the buffer contains the data to be sent 

* `nSize` the size of the data to be sent 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE int `[`fusbd_adpt_prepare_receive`](#group___adapter___functions_1ga8fcc122d9fb102b5604fb145cd768a8a)`(fusbd_adapter_t * pInst,uint8_t nEpAddr,void * pBuf,size_t nSize)` {#group___adapter___functions_1ga8fcc122d9fb102b5604fb145cd768a8a}

receive data from an endpoint

#### Parameters
* `pInst` the instance of the adapter 

* `nEpAddr` the address of the endpoint 

* `pBuf` the buffer for receiving the data 

* `nSize` the size of the data would be received 

#### Returns
int 0 for success

#### `public __STATIC_FORCEINLINE uint32_t `[`fusbd_adpt_get_tickcount`](#group___adapter___functions_1gad6ffb995d68acebdc26708dd395eeda0)`(fusbd_adapter_t * pInst)` {#group___adapter___functions_1gad6ffb995d68acebdc26708dd395eeda0}

get the tick count

#### Parameters
* `pInst` the instance of the adapter 

#### Returns
uint32_t the tick count

