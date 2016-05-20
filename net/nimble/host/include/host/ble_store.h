/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef H_BLE_STORE_
#define H_BLE_STORE_

#include <inttypes.h>

#define BLE_STORE_OBJ_TYPE_OUR_LTK      1
#define BLE_STORE_OBJ_TYPE_PEER_LTK     2
#define BLE_STORE_OBJ_TYPE_CCCD         3

union ble_store_key {
    struct {
        uint16_t ediv;
        uint64_t rand_num;
    } ltk;

    struct {
        uint8_t peer_addr[6];
        /* XXX: Peer addr type? */
    } cccd;
};

union ble_store_value {
    struct {
        uint8_t key[16];
        unsigned authenticated:1;
    } ltk;

    struct {
        uint16_t flags;
        unsigned value_changed:1;
    } cccd;
};

typedef int ble_store_read_fn(int obj_type, union ble_store_key *key,
                              union ble_store_value *dst);

typedef int ble_store_write_fn(int obj_type, union ble_store_key *key,
                               union ble_store_value *val);

typedef int ble_store_delete_fn(int obj_type, union ble_store_key *key);

int ble_store_read(int obj_type, union ble_store_key *key,
                   union ble_store_value *val);
int ble_store_write(int obj_type, union ble_store_key *key,
                    union ble_store_value *val);
int ble_store_delete(int obj_type, union ble_store_key *key);

#endif
