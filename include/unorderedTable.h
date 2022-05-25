#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "../include/Logger.h"


template<typename TKey, typename TValue>
class UnorderedTable
{
private:
	template<typename TKey, typename TValue>
	struct Pair
	{
		TKey key;
		TValue value;
		Pair(const TKey key) : key(key) {};
		Pair(const TKey key, const TValue value) : key(key), value(value) {};
		bool operator==(const Pair& other) const { return key == other.key; }
		bool operator!=(const Pair& other) const { return key != other.key; }
		friend std::ostream& operator<<(std::ostream& out, const Pair& pair)
		{
			out << pair.key << ": " << pair.value << std::endl;
			return out;
		}
	};
	Logger logger;
	std::vector<Pair<TKey, TValue>> data;
public:
	UnorderedTable() = default;

	int find(const TKey& key) 
	{
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].key == key) {
				logger.DebugLog("unorderedTable: Actions for finding a polynomial: " + std::to_string(i + 1));
				return i;
			}
		}
		return -1;
	}

	TValue getValue(const TKey& key)
	{
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].key == key) {
				return data[i].value;
			}
		}
		throw "Key missing";
	}

	void insert(const TKey& key, const TValue& value)
	{
		if (find(key) != -1)
		{
			std::cout << "Key is already there" << std::endl;
			return;
		}

		data.push_back(Pair<TKey, TValue>(key, value));
	}

	void erase(const TKey& key)
	{
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].key == key) {
				data.erase(data.cbegin() + i);
				break;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const UnorderedTable& table)
	{
		for (int i = 0; i < table.data.size(); ++i) {
			out << table.data[i];
		}
		return out;
	}


};