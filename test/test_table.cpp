#pragma once
#include "hash_table.h"
#include <gtest.h>
using namespace std;

TEST(HashTableTest, insert_hash_table) {
	HashTable<string, int> ht(10);
	int res1 = ht.insert("Hello", 1)->second;
	int et1 = 1;
	EXPECT_EQ(et1, res1);
}

TEST(HashTableTest, copy_equal_tables) {
	HashTable<string, int> ht(10);
	int et1 = ht.insert("Hello", 1)->second;
	HashTable<string, int> eht(ht);
	int res = eht.find("Hello")->second;
	EXPECT_EQ(et1, res);
}

TEST(HashTableTest, InsertAndFind) {
	HashTable<string, int> ht(5);
	ht.insert("apple", 10);
	ht.insert("banana", 20);
	ht.insert("orange", 30);
	EXPECT_EQ(ht.find("apple")->second, 10);
	EXPECT_EQ(ht.find("banana")->second, 20);
	EXPECT_EQ(ht.find("orange")->second, 30);
}

TEST(HashTableTest, Remove) {
	HashTable<string, int> ht(5);
	ht.insert("apple", 10);
	ht.insert("banana", 20);
	EXPECT_TRUE(ht.remove("apple"));
	EXPECT_FALSE(ht.remove("orange"));
}

TEST(HashTableTest, BracketOperator) { 
	HashTable<string, int> ht(5);
	ht.insert("apple", 10);
	ht.insert("banana", 20);
	EXPECT_EQ(ht["apple"], 10);
	EXPECT_EQ(ht["banana"], 20);
}

TEST(HashTableTest, Iterator) { 
	HashTable<string, int> ht(5);
	ht.insert("apple", 10);
	ht.insert("banana", 20);
	ht.insert("orange", 30);
	int sum = 0;
	for (auto it = ht.begin(); it != ht.end(); ++it)
	{
		sum += it->second;
	}
	EXPECT_EQ(sum, 60);
}

TEST(HashTable, Insert) { 
	HashTable<string, int> ht(10);
	ht.insert("apple", 1);
	ht.insert("banana", 2);
	ht.insert("cherry", 3);

	EXPECT_EQ(ht["apple"], 1);
	EXPECT_EQ(ht["banana"], 2);
	EXPECT_EQ(ht["cherry"], 3);
}

TEST(HashTable, Find) { 
	HashTable<string, int> ht(10);
	ht.insert("apple", 1);
	ht.insert("banana", 2);
	ht.insert("cherry", 3);

	EXPECT_EQ(ht.find("apple")->second, 1);
	EXPECT_EQ(ht.find("banana")->second, 2);
	EXPECT_EQ(ht.find("cherry")->second, 3);
}

TEST(HashTable, Remove) {
	HashTable<string, int> ht(10);
	ht.insert("apple", 1);
	ht.insert("banana", 2);
	ht.insert("cherry", 3);

	EXPECT_TRUE(ht.remove("apple"));
	EXPECT_EQ(ht["banana"], 2);
	EXPECT_EQ(ht["cherry"], 3);
}

TEST(HashTable, Iterator) {
	HashTable<string, int> ht(10);
	ht.insert("apple", 1);
	ht.insert("banana", 2);
	ht.insert("cherry", 3);

	auto it = ht.begin();
	EXPECT_EQ(it->first, "banana");
	EXPECT_EQ(it->second, 2);

	++it;
	EXPECT_EQ(it->first, "cherry");
	EXPECT_EQ(it->second, 3);

	++it;
	EXPECT_EQ(it->first, "apple");
	EXPECT_EQ(it->second, 1);
}
TEST(HashTableTest, equal_assign) {
	HashTable<int, int> ht(10);
	ht.insert(1, 1);
	ht.insert(2, 2);
	ht = ht;
	EXPECT_EQ(1, ht.find(1)->second);
	EXPECT_EQ(2, ht.find(2)->second);
}
TEST(HashTableTest, non_equal_assign) {
	HashTable<int, int> ht(10);
	ht.insert(1, 1);
	ht.insert(2, 2);
	HashTable<int, int> aht(9);
	aht.insert(3, 3);
	aht = ht;
	EXPECT_EQ(1, aht.find(1)->second);
}
TEST(HashTableTest, double_table) {
	HashTable<double, int> ht(10);
	ht.insert(1.5, 1);
	ht.insert(2.4, 2);
	ht.insert(3.14, 4);
	EXPECT_EQ(1, ht.find(1.5)->second);
}
TEST(HashTableTest, float_table) {
	HashTable<float, int> ht(10);
	ht.insert(1.5, 1);
	ht.insert(2.4, 2);
	ht.insert(3.14, 4);
	EXPECT_EQ(2, ht.find(2.4)->second);
}