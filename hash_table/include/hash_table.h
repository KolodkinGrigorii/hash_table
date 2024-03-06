#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
template <typename TypeKey, typename TypeData>
class HashTable {
private:
	vector<pair<TypeKey, TypeData>> *ar;
	int length;
public:
	HashTable(int n) {
		ar = new vector<pair<TypeKey, TypeData>>[n];
		length = n;
	}
	HashTable(const HashTable& ht) {
		length = ht.length;
		ar = ht.ar;
	}
	HashTable operator=(const HashTable& ht) {
		delete[] ar;
		length = ht.length;
		for (int i = 0; i < length; i++) {
			ar[i] = ht.ar[i];
		}
		return *this;
	}
	~HashTable(){
		delete[] ar;
	}
	int hash(string s) {
		char al[]= "abcdefghijklmnopqrstuvwxyz";
		int sum=0;
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			for (int j = 0; j < 26; j++) {
				if (c == al[j]) {
					sum += pow(j, i);
				}
			}
		}
		return sum%length;
	}
	int hash(int i) {
		return i%length;
	}
	auto insert(TypeKey key, const TypeData& data) {
		int pos = hash(key);
		ar[pos].push_back(make_pair(key, data));
		if (pos != length - 1) {
			ar[pos].end() = ar[pos + 1].begin();
		}
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				return it;
			}
		}
	}
	auto find(const TypeKey& key) {
		int pos = hash(key);
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				return it;
			}
		}
		return ar[length-1].end();
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
		for (auto it = ar[pos].begin(); it != ar[pos].end(); it++) {
			if (it->first == key) {
				return it->second;
			}
		}
		return ar[length - 1].end();
	}
	auto begin(){
		return ar[0].begin();
	}
	auto end() {
		return ar[length-1].end();
	}
	friend std::ostream& operator<<(std::ostream& out, const HashTable& v) {
		for (int i = 0; i < v.length; i++) {
			for (auto it = v.ar[i].begin(); it != v.ar[i].end(); it++) {
				cout << i << " "<< it->first << " " << it->second << endl;
			}
		}
		return out;
	}
};