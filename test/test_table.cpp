#pragma once

#include "hash_table.h"
#include <gtest.h>
using namespace std;
TEST(HashTable, insert_hash_table) {
	HashTable<string, int> ht(10);
	int res1= ht.insert("Hello", 1)->second;
	int et1 = 1;
	EXPECT_EQ(et1, res1);
}
TEST(HashTable, copy_equal_tables) {
	HashTable<string, int> ht(10);
	int et1 = ht.insert("Hello", 1)->second;
	HashTable<string, int> eht(ht);
	int res = eht.find("Hello")->second;
	EXPECT_EQ(et1, res);
}
