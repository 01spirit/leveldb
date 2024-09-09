//
// Created by DELL on 2024/9/6.
//

#include <iostream>
#include "leveldb/db.h"
#include "leveldb/comparator.h"
#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

int main(){
  // 开启数据库
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  // 读写数据（把 key1 -> value 修改为 key2 -> value）
  std::string value;
  std::string key1, key2;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key1, &value);
  if(s.ok()) {
    s= db->Put(leveldb::WriteOptions(), key2, value);
  }
  if(s.ok()) {
    s= db->Delete(leveldb::WriteOptions(), key1);
  }

  // 原子性更新  也可以加速批量操作
  status = db->Get(leveldb::ReadOptions(), key1, &value);
  if(s.ok()) {
    leveldb::WriteBatch batch;
    batch.Delete(key1);
    batch.Put(key2, value); // 先删除 key1 再写入 key2，因为若 key1 == key2 且在写入后删除，会把 key1/key2 -> value 全部删除掉
    status = db->Write(leveldb::WriteOptions(), &batch);
  }

  // 同步写入
  leveldb::WriteOptions write_options;
  write_options.sync = true;
  db->Put(write_options, key1, value);

  // 迭代   遍历数据库中的所有 key -> value
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for(it->SeekToFirst(); it->Valid(); it->Next()){
    std::cout<< it->key().ToString() << ":" << it->value().ToString() << std::endl;
  }
  assert(it->status().ok());
  delete it;

  // 迭代  找到 [start, limit) 范围内的所有 key -> value
  std::string start, limit;
  leveldb::Iterator* it2 = db->NewIterator(leveldb::ReadOptions());
  for(it2->Seek(start); it2->Valid() && it2->key().ToString() < limit; it2->Next()){
    std::cout<< it2->key().ToString() << ":" << it2->value().ToString() << std::endl;
  }
  delete it2;

  // 逆序迭代
  leveldb::Iterator* it3 = db->NewIterator(leveldb::ReadOptions());
  for(it3->SeekToLast(); it3->Valid(); it3->Prev()){
    std::cout<< it3->key().ToString() << ":" << it3->value().ToString() << std::endl;
  }
  delete it3;

  // leveldb::Slice 和 std::string 相互转换
  std::string str = "Hello";
  leveldb::Slice s2 = str;
  std::string str2 = s2.ToString();
  assert(str == str2);

  // 开启常用的未压缩数据的缓存
  options.block_cache = leveldb::NewLRUCache(100 * 1048576); // 100MB cache
  leveldb::DB* db3;
  leveldb::DB::Open(options, "tmp/testdb", &db3);
  delete db3;
  delete options.block_cache;

  // 估算 key range 存储的字节数
  leveldb::Range ranges[2];
  ranges[0] = leveldb::Range("a", "C");
  ranges[1] = leveldb::Range("x", "Z");
  uint64_t sizes[2];
  db->GetApproximateSizes(ranges, 2, sizes);

  // 关闭数据库（删除）
  delete db;
}