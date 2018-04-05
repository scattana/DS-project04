// unsorted.cpp: Unsorted Map

#include "map.h"

// Methods --------------------------------------------------------------------

void            UnsortedMap::insert(const std::string &key, const std::string &value) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        if (it->first == key) {
            it->second = value;
            return;
        }
    }

    entries.push_back(Entry(key, value));
}

const Entry     UnsortedMap::search(const std::string &key) {
    for (auto it = entries.begin(); it != entries.end(); it++)
        if (it->first == key)
            return *it;

    return NONE;
}

void            UnsortedMap::dump(std::ostream &os, DumpFlag flag) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        switch (flag) {
            case DUMP_KEY:          os << it->first  << std::endl; break;
            case DUMP_VALUE:        os << it->second << std::endl; break;
            case DUMP_KEY_VALUE:    os << it->first  << "\t" << it->second << std::endl; break;
            case DUMP_VALUE_KEY:    os << it->second << "\t" << it->first  << std::endl; break;
        }
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
