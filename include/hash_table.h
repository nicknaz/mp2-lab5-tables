#pragma once
#include "../include/Logger.h"


using namespace std;

template<typename TKey, typename TValue>
class HashNode
{
public:
	TValue *value;
	TKey key;

	HashNode(TKey key, TValue *value)
	{
		this->value = value;
		this->key = key;
	}
};

template<typename TKey, typename TValue>
class HashQuadroTable
{

	HashNode<TKey, TValue> **arr;
	int capacity;
	int size;
	Logger logger;

public:

	HashQuadroTable()
	{
		capacity = 50;
		size = 0;
		arr = new HashNode<TKey, TValue>*[capacity];
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

	}

	int hashCode(TKey key)
	{
		std::hash<TKey> hasher;
		return hasher(key) % capacity;
	}

	void insertNode(TKey key, TValue *value)
	{
		HashNode<TKey, TValue> *temp = new HashNode<TKey, TValue>(key, value);
		int hashIndex = hashCode(key);
		//cout << "DEBUG: " << hashIndex << endl;
		int i = 0;
		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key)
		{
			hashIndex+= i + i*i;
			hashIndex %= capacity;
			i++;
		}

		if (arr[hashIndex] == NULL)
			size++;

		arr[hashIndex] = temp;

	}

	TValue deleteNode(TKey key)
	{

		int hashIndex = hashCode(key);
		int i = 0;
		while (arr[hashIndex] != NULL)
		{
			if (arr[hashIndex]->key == key)
			{
				HashNode<TKey, TValue> *temp = arr[hashIndex];
				arr[hashIndex] = NULL;
				size--;
				return temp->value;
			}
			if ((hashIndex + i + i * i) % capacity > capacity)
				return NULL;
			hashIndex += i + i * i;
			hashIndex %= capacity;
			i++;
		}
		return NULL;
	}

	TValue* getValue(TKey key)
	{
		int hashIndex = hashCode(key);
		int i = 0;
		while (arr[hashIndex] != NULL)
		{
			//cout << "DEBUG: " << hashIndex << endl;
			if (arr[hashIndex]->key == key) {
				logger.DebugLog("HashTable: Actions for finding a polynomial: " + std::to_string(i+1));
				return arr[hashIndex]->value;
			}
			if ((hashIndex + i + i * i) % capacity > capacity)
				return NULL;
			hashIndex += i + i * i;
			hashIndex %= capacity;
			i++;
		}
		return NULL;
	}

	int getSize()
	{
		return size;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const HashQuadroTable& table)
	{
		for (int i = 0; i < table.capacity; i++)
		{
			if (table.arr[i] != NULL)
				out << i << ":" << table.arr[i]->key << ":  value = " << table.arr[i]->value << endl;
		}
		return out;
	}

};
