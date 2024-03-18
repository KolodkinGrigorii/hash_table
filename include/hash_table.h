#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
template <typename TypeKey, typename TypeData>
class HashTable {
private:
	vector < pair < TypeKey, TypeData>>* ar;
	int length;
public:
	class Iterator
	{
	private:
		vector < pair < TypeKey, TypeData>>* ar_;
		size_t counter_;
		size_t number_;
		size_t length_;
	public:
		Iterator(vector < pair < TypeKey, TypeData>>* ar, size_t counter, size_t number, size_t length) : ar_(ar), counter_(counter), number_(number), length_(length) {}
		Iterator& operator++()
		{
			if (ar_[counter_].size() == number_ + 1)
			{
				counter_++;
				while (ar_[counter_].size() == 0)
				{
					if (counter_ == length_)
						return *this;
					number_ = 0;
					counter_++;
				}
			}
			else
			{
				number_++;
			}
			return *this;
		}
		static Iterator begin(vector < pair < TypeKey, TypeData>>* ar, size_t length)
		{
			for (size_t i = 0; i < length; i++)
			{
				if (ar[i].size() != 0)
					return Iterator(ar, i, 0, length);
			}
			return Iterator(ar, length, 0, length);
		}
		pair<TypeKey, TypeData>& operator*()
		{
			return ar_[counter_][number_];
		}
		bool operator ==(const Iterator& other)
		{
			return (ar_ == other.ar_ && counter_ == other.counter_ && number_ == other.number_);
		}
		bool operator !=(const Iterator& other)
		{
			return !(*this == other);
		}
		pair<TypeKey, TypeData>* operator->()
		{
			return &**this;
		}
	};
	HashTable(int n) {
		ar = new vector < pair < TypeKey, TypeData>>[n];
		length = n;
	}
	HashTable(const HashTable& ht) {
		length = ht.length;
		ar = new vector < pair < TypeKey, TypeData>>[length];
		for (int i = 0; i < length; i++) {
			ar[i] = ht.ar[i];
		}
	}
	HashTable operator=(const HashTable& ht) {
		if (length == ht.length) {
			for (int i = 0; i < length; i++) {
				ar[i] = ht.ar[i];
			}
		}
		else {
			length = ht.length;
			delete[] ar;
			ar = new vector < pair < TypeKey , TypeData>>[length];
			for (int i = 0; i < ht.length; i++) {
				for (auto it = ht.ar[i].begin(); it != ht.ar[i].end(); it++) {
					this->insert(it->first, it->second);
				}
			}
		}
		return *this;
	}
	~HashTable() {
		length = 0;
		delete[] ar;
	}
	int hash(string s) {
		char al[] = "abcdefghijklmnopqrstuvwxyz";
		int sum = 0;
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			for (int j = 0; j < 26; j++) {
				if (c == al[j]) {
					sum += pow(j, i);
				}
			}
		}
		return sum % length;
	}
	int hash(char c) {
		char al[] = "abcdefghijklmnopqrstuvwxyz";
		int sum = 0;
		for (int j = 0; j < 26; j++) {
			if (c == al[j]) {
				sum += pow(j, i);
			}
		}
		return sum % length;
	}
	int hash(long long i) {
		return i % length;
	}
	int hash(int i) {
		return i % length;
	}
	int hash(double i) {
		i = abs(i);
		int n;
		int man=frexp(i, &n);
		int ord = trunc(i);
		int res = man + pow(2,ord);
		return res%length;
	}
	int hash(float i) {
		i = abs(i);
		int n;
		int man = frexp(i, &n);
		int ord = trunc(i);
		int res = man + pow(2, ord);
		return res % length;
	}
	int hash(vector<int> v) {
		int sum = 0;
		for (int i = 0; i < v.size(); i++) {
			sum += v[i];
		}
		return sum % length;
	}
	auto insert(TypeKey key, const TypeData& data) {
		int pos = hash(key);
		ar[pos].push_back(make_pair(key, data));
		//checkcap();
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				return it;
			}
		}
	}
	Iterator find(const TypeKey& key) {
		int pos = hash(key);
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				return Iterator(ar, pos, it - ar[pos].begin(), length);
			}
		}
		return Iterator(ar, length, 0, length);
	}
	bool remove(const TypeKey& key) {
		int pos = hash(key);
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				ar[pos].erase(it);
				return true;
			}
		}
		return false;
	}
	TypeData& operator[](const TypeKey& key) {
		int pos = hash(key);
		for (auto it = ar[pos].begin(); it != ar[pos].end(); ++it) {
			if (it->first == key) {
				return it->second;
			}
		}
		throw std::runtime_error("Invalid key!");
	}

	Iterator begin() {
		return Iterator::begin(ar, length);
	}
	Iterator end() {
		return Iterator(ar, length, 0, length);
	}
	void checkcap() {
		int sum = 0;
		for (int i = 0; i < length; i++) {
			sum += ar[i].size();
		}
		double cap = sum / length;
		if (cap > 1) {
			cout<<balancecap(sum);
		}
	}
	HashTable balancecap(int newLength) {
	}
	friend std::ostream& operator<<(std::ostream& out, const HashTable& v) {
		for (int i = 0; i < v.length; i++) {
			for (auto it = v.ar[i].begin(); it != v.ar[i].end(); it++) {
				cout << i << " " << it->first << " " << it->second << endl;
			}
		}
		return out;
	}
};