
/**
  *
  * Assignment 2 for ECE430.217 Data Structures
  *
 **/
#include <iostream>

#define INIT_TABLE_SIZE 64
#define MAX_LOAD 0.5

 //
 // HashTable data structure using linear/quad probing to handle collision
 //
template <typename K, typename V>
class HashProbe
{
public:
	// Constructor
	HashProbe(unsigned int s = INIT_TABLE_SIZE) {
		table_size = s;
		num_elem = 0;
		ht = new TableElem<K, V>[table_size];
	};

	// Destructor
	~HashProbe() { removeall(); };

	unsigned int get_table_size() { return table_size; };
	unsigned int get_num_elem() { return num_elem; };
	bool isEmpty() { return (num_elem == 0); };
	double get_load_factor() { return (double)num_elem / table_size; };
	TableElem<K, V>* hash_table() { return ht; };

	void print() {
		for (int i = 0; i < table_size; i++) {
			
			if (!ht[i].empty) {
				std::cout << "*************************" << std::endl;
				std::cout << "Table index: " << i << std::endl;
				std::cout << ht[i].key << ":" << ht[i].val << std::endl;
			}
		}
	};

	// TODO

	// Find the element with the key
	TableElem<K, V>* find(const K& key);

	// Insert the element with the key and val
	// If the key already exists in the table, only replace the value with the val
	// Return the number of probing step
	int insert(const K& key, const V& val);

	// Remove the element with the key
	// Return true if it is successfully removed
	// return false if there is no elem with the key in the table
	bool remove(const K& key);

private:
	TableElem<K, V>* ht;
	unsigned int table_size, num_elem;

	// Hash function for string
	unsigned int hashfunction(const K& key) {
		unsigned int hash = 0;
		for (int i = 0; i < key.length(); ++i) hash = 12347 * hash + key[i];
		
		return hash % table_size;
	}
	const HashProbe& operator=(const HashProbe& other);

	// TODO

	virtual unsigned int get_pos(unsigned int pos, unsigned int step) = 0;

	// Enlarging the table when a load factor > MAX_LOAD
	void enlarge_table();

	// For destructor
	void removeall();
};

template <typename K, typename V>
class LinearHashProbe : public HashProbe<K, V> {
private:
	// Get a position from first position (hash) after step-th linear probing 
	virtual unsigned int get_pos(unsigned int pos, unsigned int step) {
		// TODO
		pos = pos + step;
		pos = pos % HashProbe<K,V>::get_table_size();
		return pos;
		
	}
};

template <typename K, typename V>
class QuadHashProbe : public HashProbe<K, V> {
private:
	// Get a position from first position (hash) after step-th quad probing
	virtual unsigned int get_pos(unsigned int pos, unsigned int step) {
		// TODO

		pos = (pos + (step + step * step) / 2);
		pos = pos % HashProbe<K, V>::get_table_size();
		return pos;
		
	}
};


template <typename K, typename V>
TableElem<K, V>* HashProbe<K, V>::find(const K& key)
{
	// TODO
	
	for (int i = 0; i < get_table_size(); i++) {
		if (ht[i].key == key && !ht[i].empty && !ht[i].removed) {
			return &ht[i];
		}

	}
	/*
	std::cout << "finding " << key << std::endl;

	unsigned int count = 0;
	unsigned int index = hashfunction(key);
	TableElem<K, V>* currElem = &ht[index];

	while (count < get_table_size() ) {
		std::cout << currElem->key << "is match with target " << key << "?" << std::endl;

		if (currElem->key == key && !currElem->empty && !currElem->removed) {
			std::cout << "found key! " << index << " " << key << std::endl;
			return currElem;
		}

		else if (currElem->key != key && currElem->empty && !currElem->removed) {
			std::cout << "no such key! " << index << " " << key << std::endl;
			return nullptr;
		}

		else {
			std::cout << "search more! " << index << " " << key << std::endl;
			count++;
			index = get_pos(index,1);
			currElem = &ht[index];
		}
	}*/
	return nullptr;



};

template <typename K, typename V>
int HashProbe<K, V>::insert(const K& key, const V& val)
{
	

	// TODO
	unsigned int index = hashfunction(key);
	TableElem<K,V>* currentElem = &ht[index];
	unsigned int collision = 0;
	unsigned int finalPos = index;

	//std::cout << index << std::endl;

	while (!currentElem->empty) {
		if (ht[finalPos].key == key) {
			ht[finalPos].val = val;
			ht[finalPos].empty = false;
			ht[finalPos].removed = false;

			return 0;
		}
		finalPos = get_pos(index, ++collision);
		currentElem = &ht[finalPos];

	}


		ht[finalPos].key = key;
		ht[finalPos].val = val;
		ht[finalPos].empty = false;
		ht[finalPos].removed = false;
		//std::cout << find("192") << std::endl;
		//std::cout << "{Key: " << ht[finalPos].key << ", Value: " << ht[finalPos].val << " has inserted in index " << finalPos << std::endl;

		num_elem += 1;


		if (get_load_factor() > MAX_LOAD) {
			enlarge_table();
		} //load factor가 크다면 증가

		return collision;
	

	

	
}

template <typename K, typename V>
bool HashProbe<K, V>::remove(const K& key)
{
	// TODO

	TableElem<K,V>* target = find(key);

	if (target == nullptr) {
		return false;
	}
	
	target->empty = true;
	target->removed = true;
	num_elem -= 1;
	


	return true;

}

template <typename K, typename V>
void HashProbe<K, V>::enlarge_table()
{
	// TODO
	/*
	int newSize = 2 * table_size;
	table_size *= 2;
	TableElem<K, V>* newTable = new TableElem<K, V>[newSize];
	for (int i = 0; i <table_size/2; i++) {
		if (!ht[i].empty) {
			int index = hashfunction(ht[i].key);
			while (!newTable[index].empty) {
				index = get_pos(index, 1);
			}
			newTable[index].key = ht[i].key;
			newTable[index].val = ht[i].val;
			newTable[index].empty = ht[i].empty;
			newTable[index].removed = ht[i].removed;
		}
	}
	
	delete[] ht;
	ht = newTable;
	delete newTable;
	newTable = nullptr; */
	
	
	TableElem<K, V>* oldTable = ht;
	unsigned int oldSize = get_table_size();
	table_size *= 2;
	ht = new TableElem<K, V> [table_size];

	for (unsigned int i = 0; i < oldSize; i++) {
		if (!oldTable[i].empty) {
			TableElem<K, V> newElem = oldTable[i];
			unsigned int index = hashfunction(oldTable[i].key);
			unsigned int finalPos = index;
			int step = 1;
			while (!ht[finalPos].empty) {
				finalPos = get_pos(index, step);
				step++;
			}

			
			ht[finalPos].key = newElem.key;
			ht[finalPos].val = newElem.val;
			ht[finalPos].empty = false;
			ht[finalPos].removed = false;
		}
	} 
	

	delete[] oldTable;
	oldTable = nullptr; 

}

template <typename K, typename V>
void HashProbe<K, V>::removeall()
{	

	delete[] ht;
	ht = nullptr;
	// TODO
}
