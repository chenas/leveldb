#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"
#include "leveldb/env.h"
#include "leveldb/write_batch.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/table.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/table_builder.h"

#include <iostream>

using namespace leveldb;

int main()
{
	DB* db_;
	Options options;
	options.create_if_missing = true;
	options.block_cache = nullptr;
	options.write_buffer_size = 100;
	Status s = DB::Open(options, "Debug/testdbdata", &db_);
	if (!s.ok()) {
		fprintf(stderr, "open error: %s\n", s.ToString().c_str());
		exit(1);
	}
	std::string value;
	for (int i = 0; i < 10000; i++)
	{
		value = "test_" + std::to_string(i);
		s = db_->Put(leveldb::WriteOptions(), std::to_string(i), value);
	}
	for (int i = 0; i < 10000; i++)
	{
		db_->Get(leveldb::ReadOptions(), std::to_string(i), &value);
		std::cout << value << std::endl;
	}
	
	getchar();

	return 0;
}