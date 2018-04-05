// open.cpp: Open Addressing Map

#include "map.h"

#include <stdexcept>

// Methods --------------------------------------------------------------------

// default constructor (use DEFAULT values)
OpenMap::OpenMap(){
	table_size = 0;
	max_load_factor = DEFAULT_LOAD_FACTOR;
	num_items = 0;
        table = nullptr;
	resize(DEFAULT_TABLE_SIZE);
}

// parameter-based constructor
OpenMap::OpenMap(size_t t_size, double l_factor){
	table_size = 0;
	max_load_factor = l_factor;
	num_items = 0;
        table = nullptr;
	resize(t_size);
}


// deconstructor
OpenMap::~OpenMap(){
	delete[] table;
}

void            OpenMap::insert(const std::string &key, const std::string &value) {
	double curr_load_factor = (double)num_items/(double)table_size;

	if(curr_load_factor >= max_load_factor){
		resize(table_size*2);
	}
	size_t bucket = locate(key);
	if(bucket == table_size){
		resize(table_size*2); // if no empty buckets found
	}
	else if (table[bucket].first != key){
		num_items++; // increment the number of UNIQUE items in the table
	}
	table[bucket].first = key;
	table[bucket].second = value;
}

// call "locate" to find the value in a bucket for a specified key
const Entry     OpenMap::search(const std::string &key) {
    size_t bucket = locate(key);
    if (table[bucket].first == key)
    	return table[bucket];
    else
    	return NONE;
}

// dump in appropriate format to stream
void            OpenMap::dump(std::ostream &os, DumpFlag flag) {
	//return;
	for(size_t i=0; i<table_size; i++){
		if(table[i] != NONE){
		switch(flag){
			case DUMP_KEY:			os << table[i].first << std::endl; break;
			case DUMP_VALUE:		os << table[i].second << std::endl; break;
			case DUMP_KEY_VALUE:	os << table[i].first << "\t" << table[i].second << std::endl; break;
			case DUMP_VALUE_KEY:	os << table[i].second << "\t" << table[i].first << std::endl; break;
		}
		}
	}
}

size_t          OpenMap::locate(const std::string &key) {
	// hashing should take place here. If the given key has a non-empty
	// bucket, return that bucket. If the given key does not exist, return
	// the next empty bucket.
	StringHasher hash;		// define hashing type function
	size_t bucket = hash(key) % table_size;
	if(table[bucket].first == key) return bucket;
	else{
		size_t count = 0;
		while(count < table_size){
			if(table[bucket] == NONE) return bucket; // return next empty bucket
			if(table[bucket].first == key) return bucket;
			count++;
			bucket = (bucket+1)%table_size;
		}
		return table_size;	// sentinel to indicate 'locate' could not find
		// an empty bucket, so 'insert' should call 'resize'
	}
}

// called by "insert" when (1) no empty entries in the table, or (2) when
// current load factor exceeds max load factor
void            OpenMap::resize(const size_t new_size) {
//	std::cout << "\n\n\n\ntable size is: " << table_size << "\n\n\n\n" << std::endl;
//	dump(std::cout, DUMP_KEY_VALUE);
	auto old_table = table;
	auto old_size = table_size;
	table = new Entry[new_size];
	table_size = new_size;
	// copy old values from table to new table
	for(size_t i=0; i<old_size; i++){
		if(old_table[i] != NONE) insert(old_table->first, old_table->second);
	}
	delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
