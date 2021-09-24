# group `toolkits for the descriptors` {#group__toolkits}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`fusb_next_desc_ptr`](#group__toolkits_1gaa366c2348007675bd204205b3c04af99)            | toolkit for locating the next descriptor of the special descriptor
`define `[`fusb_desc_len`](#group__toolkits_1ga7bb028cc115686f80a5a69470374e46d)            | toolkit for getting the length of the special descriptor
`define `[`fusb_desc_type`](#group__toolkits_1gada3587d91c7101b1cf0944a9aaa1522c)            | toolkit for getting the length of the special descriptor
`define `[`fusb_intf_desc_idx`](#group__toolkits_1ga2d40ed76a44803007ceec5be4b08a54f)            | toolkit for getting the index of the interface in the descriptor
`define `[`fusb_intf_desc_alt`](#group__toolkits_1gabbed136f479f07fd97237e0f02f84a06)            | toolkit for getting the alt index of the interface in the descriptor
`define `[`fusb_intf_desc_ep_count`](#group__toolkits_1ga91366514261a1906b949ad6d35ce0e75)            | toolkit for getting the count of the endpoints assigned to the interface in the descriptor
`define `[`fusb_intf_desc_class`](#group__toolkits_1ga3232a545fc61c4cf56e99ec1f7cf8306)            | toolkit for getting the class code of the interface in the descriptor
`define `[`fusb_intf_desc_subclass`](#group__toolkits_1gaa0d554f96103ebb3b78cfab39d8b09e6)            | toolkit for getting the sub-class code of the interface in the descriptor
`define `[`fusb_intf_desc_protocol`](#group__toolkits_1ga9bf2315e468672fbbce326eba98c3963)            | toolkit for getting the protocol code of the interface in the descriptor
`define `[`fusb_ep_addr_from_desc`](#group__toolkits_1ga123acd20e95f20381cdcb62303bb192a)            | toolkit for getting the address of the endpoint in the descriptor
`define `[`fusb_ep_mps_from_desc`](#group__toolkits_1gafc3430ac4c6d1eb6dbb7673c808b3236)            | toolkit for getting the max_packet_size of the endpoint in the descriptor
`define `[`fusb_ep_type_from_desc`](#group__toolkits_1gaf2a4161247889706596f2b43c4c6c89c)            | toolkit for getting the transmition type of the endpoint in the descriptor
`define `[`fusb_ep_desc_is_in`](#group__toolkits_1gaabcab2422abccf1ec173b76395a783a0)            | toolkit for check if the endpoint is an in-endpoint in the descriptor

## Members

#### `define `[`fusb_next_desc_ptr`](#group__toolkits_1gaa366c2348007675bd204205b3c04af99) {#group__toolkits_1gaa366c2348007675bd204205b3c04af99}

toolkit for locating the next descriptor of the special descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_desc_len`](#group__toolkits_1ga7bb028cc115686f80a5a69470374e46d) {#group__toolkits_1ga7bb028cc115686f80a5a69470374e46d}

toolkit for getting the length of the special descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_desc_type`](#group__toolkits_1gada3587d91c7101b1cf0944a9aaa1522c) {#group__toolkits_1gada3587d91c7101b1cf0944a9aaa1522c}

toolkit for getting the length of the special descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_idx`](#group__toolkits_1ga2d40ed76a44803007ceec5be4b08a54f) {#group__toolkits_1ga2d40ed76a44803007ceec5be4b08a54f}

toolkit for getting the index of the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_alt`](#group__toolkits_1gabbed136f479f07fd97237e0f02f84a06) {#group__toolkits_1gabbed136f479f07fd97237e0f02f84a06}

toolkit for getting the alt index of the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_ep_count`](#group__toolkits_1ga91366514261a1906b949ad6d35ce0e75) {#group__toolkits_1ga91366514261a1906b949ad6d35ce0e75}

toolkit for getting the count of the endpoints assigned to the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_class`](#group__toolkits_1ga3232a545fc61c4cf56e99ec1f7cf8306) {#group__toolkits_1ga3232a545fc61c4cf56e99ec1f7cf8306}

toolkit for getting the class code of the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_subclass`](#group__toolkits_1gaa0d554f96103ebb3b78cfab39d8b09e6) {#group__toolkits_1gaa0d554f96103ebb3b78cfab39d8b09e6}

toolkit for getting the sub-class code of the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_intf_desc_protocol`](#group__toolkits_1ga9bf2315e468672fbbce326eba98c3963) {#group__toolkits_1ga9bf2315e468672fbbce326eba98c3963}

toolkit for getting the protocol code of the interface in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_ep_addr_from_desc`](#group__toolkits_1ga123acd20e95f20381cdcb62303bb192a) {#group__toolkits_1ga123acd20e95f20381cdcb62303bb192a}

toolkit for getting the address of the endpoint in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_ep_mps_from_desc`](#group__toolkits_1gafc3430ac4c6d1eb6dbb7673c808b3236) {#group__toolkits_1gafc3430ac4c6d1eb6dbb7673c808b3236}

toolkit for getting the max_packet_size of the endpoint in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_ep_type_from_desc`](#group__toolkits_1gaf2a4161247889706596f2b43c4c6c89c) {#group__toolkits_1gaf2a4161247889706596f2b43c4c6c89c}

toolkit for getting the transmition type of the endpoint in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

#### `define `[`fusb_ep_desc_is_in`](#group__toolkits_1gaabcab2422abccf1ec173b76395a783a0) {#group__toolkits_1gaabcab2422abccf1ec173b76395a783a0}

toolkit for check if the endpoint is an in-endpoint in the descriptor

#### Parameters
* `pDesc` pointer to the descriptor

