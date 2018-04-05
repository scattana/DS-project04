// chained.cpp: Separate Chaining Map
#include "map.h"
#include <stdio.h>
#include <stdexcept>

// Methods --------------------------------------------------------------------

void        ChainedMap::insert(const std::string &key, const std::string &value) {
	StringHasher hfunc;
	table[hfunc(key)%size][key] = value;
	nEntries++;
	if((double) nEntries/size >= loadFactor)
    	resize(size*2);
}
const Entry ChainedMap::search(const std::string &key) {
	StringHasher hfunc;
	auto find = table[hfunc(key)%size].find(key);
	return find==table[hfunc(key)%size].end()?NONE:Entry(key,find->second);
}

void        ChainedMap::dump(std::ostream &os, DumpFlag flag) {
	for (size_t i = 0;i < size;i++) {
    	for(auto it = table[i].begin();it != table[i].end();it++){
        	switch (flag) {
          	  case DUMP_KEY:      os << it->first  << std::endl; break;
            	case DUMP_VALUE:    os << it->second << std::endl; break;
            	case DUMP_KEY_VALUE:os << it->first  << "\t" << it->second << std::endl; break;
            	case DUMP_VALUE_KEY:os << it->second << "\t" << it->first  << std::endl; break;
        	}
    	}
	}
}

void        ChainedMap::resize(const size_t new_size) {
	std::map<std::string,std::string> *new_table = new std::map<std::string,std::string> [new_size];
	std::map<std::string,std::string> *old_table = table;
	table = new_table;
	size_t old_size = size;
	size = new_size;
	if(old_size > 0){
    	for(size_t i = 0;i < old_size;i++)
        	for(auto it = old_table[i].begin();it != old_table[i].end();it++)
            	insert(it->first, it->second);
    	delete[] old_table;
	}
}
// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
