// Copyright (c) 2014, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.
//
// This file implements the "bridge" between Java and C++ for rocksdb::Options.

#include <jni.h>
#include "include/org_rocksdb_PlainTableConfig.h"
#include "include/org_rocksdb_BlockBasedTableConfig.h"
#include "rocksdb/table.h"
#include "rocksdb/cache.h"
#include "rocksdb/filter_policy.h"

/*
 * Class:     org_rocksdb_PlainTableConfig
 * Method:    newTableFactoryHandle
 * Signature: (IIDI)J
 */
jlong Java_org_rocksdb_PlainTableConfig_newTableFactoryHandle(
    JNIEnv* env, jobject jobj, jint jkey_size, jint jbloom_bits_per_key,
    jdouble jhash_table_ratio, jint jindex_sparseness) {
  rocksdb::PlainTableOptions options = rocksdb::PlainTableOptions();
  options.user_key_len = jkey_size;
  options.bloom_bits_per_key = jbloom_bits_per_key;
  options.hash_table_ratio = jhash_table_ratio;
  options.index_sparseness = jindex_sparseness;
  return reinterpret_cast<jlong>(rocksdb::NewPlainTableFactory(options));
}

/*
 * Class:     org_rocksdb_BlockBasedTableConfig
 * Method:    newTableFactoryHandle
 * Signature: (ZJIJIIZIZZJI)J
 */
jlong Java_org_rocksdb_BlockBasedTableConfig_newTableFactoryHandle(
    JNIEnv* env, jobject jobj, jboolean no_block_cache, jlong block_cache_size,
    jint block_cache_num_shardbits, jlong block_size, jint block_size_deviation,
    jint block_restart_interval, jboolean whole_key_filtering,
    jint bits_per_key, jboolean cache_index_and_filter_blocks,
    jboolean hash_index_allow_collision, jlong block_cache_compressed_size,
    jint block_cache_compressd_num_shard_bits) {
  rocksdb::BlockBasedTableOptions options;
  options.no_block_cache = no_block_cache;

  if (!no_block_cache && block_cache_size > 0) {
    if (block_cache_num_shardbits > 0) {
      options.block_cache =
          rocksdb::NewLRUCache(block_cache_size, block_cache_num_shardbits);
    } else {
      options.block_cache = rocksdb::NewLRUCache(block_cache_size);
    }
  }
  options.block_size = block_size;
  options.block_size_deviation = block_size_deviation;
  options.block_restart_interval = block_restart_interval;
  options.whole_key_filtering = whole_key_filtering;
  if (bits_per_key > 0) {
    options.filter_policy.reset(rocksdb::NewBloomFilterPolicy(bits_per_key));
  }
  options.cache_index_and_filter_blocks = cache_index_and_filter_blocks;
  options.hash_index_allow_collision = hash_index_allow_collision;
  if (block_cache_compressed_size > 0) {
    if (block_cache_compressd_num_shard_bits > 0) {
      options.block_cache =
          rocksdb::NewLRUCache(block_cache_compressed_size,
              block_cache_compressd_num_shard_bits);
    } else {
      options.block_cache = rocksdb::NewLRUCache(block_cache_compressed_size);
    }
  }
  
  return reinterpret_cast<jlong>(rocksdb::NewBlockBasedTableFactory(options));
}
