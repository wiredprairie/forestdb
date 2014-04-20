/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 *     Copyright 2010 Couchbase, Inc
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef _JSAHN_BTREEBLOCK_H
#define _JSAHN_BTREEBLOCK_H

#include "filemgr.h"
#include "list.h"
#include "btree.h"

#ifdef __cplusplus
extern "C" {
#endif

struct btreeblk_block;

struct btreeblk_handle{
    uint32_t nodesize;
    uint16_t nnodeperblock;
    uint64_t nlivenodes;
    struct list alc_list;
    struct list read_list;
    struct filemgr *file;

#ifdef __BTREEBLK_BLOCKPOOL
    struct list blockpool;
#endif

#ifdef __BTREEBLK_CACHE
    uint16_t bin_size;
    struct list recycle_bin;
    struct btreeblk_block *cache[BTREEBLK_CACHE_LIMIT];
#endif
};

struct btree_blk_ops *btreeblk_get_ops();
void btreeblk_init(struct btreeblk_handle *handle, struct filemgr *file, int nodesize);
void btreeblk_free(struct btreeblk_handle *handle);
void btreeblk_end(struct btreeblk_handle *handle);

#ifdef __cplusplus
}
#endif

#endif
