/**
  *
  * Assignment 2 for ECE430.217 Data Structures
  *
 **/
#include <iostream>

#define INIT_TABLE_SIZE 64
#define MAX_CHAIN_LENGTH 4

 //
 // HashTable data structure using chaining to handle collision
 //
template <typename K, typename V>
class HashChain
{
public:
	// Constructor
	HashChain(unsigned int s = INIT_TABLE_SIZE) {
		table_size = s;
		num_elem = 0;
		ht = new TableElem<K, V>*[table_size];
		for (int i = 0; i < table_size; i++) ht[i] = nullptr;
	};
	// Destructor
	~HashChain() { removeall(); };

	unsigned int get_table_size() { return table_size; };
	unsigned int get_num_elem() { return num_elem; };
	bool isEmpty() { return (num_elem == 0); };
	TableElem<K, V>** hash_table() { return ht; };

	void print() {
		for (int i = 0; i < table_size; i++) {
			if (ht[i] != nullptr) {
				std::cout << "Table index: " << i << std::endl;
				std::cout << "-------------------------" << std::endl;
				TableElem<K, V>* temp = ht[i];
				std::cout << temp->key << ":" << temp->val;
				while (temp->link != nullptr) {
					temp = temp->link;
					std::cout << "   --->   " << temp->key << ":" << temp->val;
				}
				std::cout << std::endl;
			}
		}
	};

	// TODO

	//Find the element with the key
	TableElem<K, V>* find(const K& key);

	//Insert the element with the key and val
	//If the key already exists in the table, only replace the value with the val
	//Return a length of the chain with the key
	int insert(const K& key, const V& val);

	//Remove the element with the key
	//Return true if it is successfully removed, return false if there is no elem with the key in the table
	bool remove(const K& key);

	// Return average chain length of the entire table excluding the empty chain
	double avg_chain_len();


private:
	TableElem<K, V>** ht;
	unsigned int table_size, num_elem;

	// Hash function for string
	unsigned int hashfunction(const K& key) {
		unsigned int hash = 0;
		for (int i = 0; i < key.length(); ++i) hash = 12347 * hash + key[i];
		return hash % table_size;
	};
	const HashChain& operator=(const HashChain& other);

	// TODO

	// Enlarging the table when a length of chain > MAX_CHAIN_LENGTH
	void enlarge_table();

	// For destructor
	void removeall();
};

template <typename K, typename V>
TableElem<K, V>* HashChain<K, V>::find(const K& key)
{
	// TODO
	unsigned int index = hashfunction(key);
	TableElem<K, V>* currElem = ht[index];
	if (currElem != nullptr) {
		while (currElem != nullptr) {
			if (currElem->key == key) {
				return currElem;
			}

			currElem = currElem->link;
		}
		return nullptr;
	}

	return nullptr;
}

template <typename K, typename V>
int HashChain<K, V>::insert(const K& key, const V& val)
{
	// TODO

	unsigned int index = hashfunction(key);
	TableElem<K, V>* currElem = ht[index];
	unsigned int chain = 0;
	TableElem<K, V>* temp = nullptr;
	while (currElem != nullptr && currElem->key !=key) {
		temp = currElem;
		currElem = currElem->link;
		chain++;
	}
	if (currElem == nullptr) {
		num_elem += 1;
		if (temp == nullptr) { //1번도 이동 안함
			ht[index] = new TableElem<K, V>(key, val);


		}
		else {
			temp->link = new TableElem<K, V>(key, val);
		}

	}
	else {
		currElem->val = val;

	}

	if (chain >= MAX_CHAIN_LENGTH) {
		enlarge_table();
	}


	return chain;



}

template <typename K, typename V>
bool HashChain<K, V>::remove(const K& key)
{
	unsigned int index = hashfunction(key);
	if (find(key) == nullptr) {
		return false;
	}

	TableElem<K, V>* nextElem = ht[index];
	TableElem<K, V>* temp = nullptr;

	while (nextElem->key != key) {
		temp = nextElem;
		nextElem = nextElem->link;

	}

	if (temp != nullptr) {
		temp->link = nextElem->link;
		delete nextElem;
		nextElem = nullptr;
	}
	else {

		ht[index] = nextElem->link;
		delete nextElem;
		nextElem = nullptr;


	}
	num_elem -= 1;
	//std::cout << "removed " << nextElem->key << " at " << index << std::endl;
	//print();
	return true;




}

template <typename K, typename V>
void HashChain<K, V>::enlarge_table()
{
	unsigned int oldSize = table_size;
	table_size *= 2;
	TableElem<K, V>** newHT = new TableElem<K, V>*[table_size];
	for (unsigned int i = 0; i < table_size; i++) {
		newHT[i] = nullptr;
	}

	for (int i = 0; i < oldSize; i++) {

		while (ht[i] != nullptr) {

			TableElem<K, V>* temp = ht[i];
			unsigned int index = hashfunction(ht[i]->key);
			TableElem<K, V>* chainSearch = newHT[index];
			TableElem<K, V>* reHash = nullptr;

			while (chainSearch != nullptr) {
				reHash = chainSearch;
				chainSearch = chainSearch->link;
			}

			if (reHash == nullptr) {
				newHT[index] = temp;
			}
			else {
				reHash->link = temp;
			}

			ht[i] = temp->link;
			temp->link = nullptr;


			//std::cout << "{Key: " << temp->key << ", Value: " << temp->val << " has inserted in index " << index << std::endl; 
			

		}
		

	}
	

	delete[] ht;
	ht = newHT;
	

}



template <typename K, typename V>
void HashChain<K, V>::removeall()
{
	// TODO

	for (unsigned int i = 0; i < table_size; i++) {
		while (ht[i] != nullptr) {
			TableElem<K, V>* temp = ht[i];
			ht[i] = temp->link;
			delete temp;
			temp = nullptr;
		}
	}
	delete[] ht;
	ht = nullptr;

}

template <typename K, typename V>
double HashChain<K, V>::avg_chain_len() {
	// TODO
	unsigned int chain = 0;
	unsigned int chained_table = 0;
	for (int i = 0; i < get_table_size(); i++) {
		if (ht[i] != nullptr) {
			chained_table++;
			TableElem<K, V>* chainedElem = ht[i];
			while (chainedElem != nullptr) {
				chainedElem = chainedElem->link;
				chain++;
			}
		}
	}

	return (double)chain / chained_table;

}


