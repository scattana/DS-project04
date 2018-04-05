// rbtree.cpp: RBTree Map

#include "map.h"

#include <algorithm>

// Methods --------------------------------------------------------------------

void            RBTreeMap::insert(const std::string &key, const std::string &value) {
    entries[key] = value;
}

const Entry     RBTreeMap::search(const std::string &key) {
    auto result = entries.find(key);
    if (result == entries.end())
        return NONE;
    else
        return *result;
}

void            RBTreeMap::dump(std::ostream &os, DumpFlag flag) {
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
