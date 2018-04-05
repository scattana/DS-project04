// sorted.cpp: Sorted Map

#include "map.h"

#include <algorithm>

// Type Definitions ------------------------------------------------------------

typedef std::vector<Entry>::iterator IT;

// Prototypes ------------------------------------------------------------------

const Entry     binary_search(const IT &start, const IT &end, const std::string &key);

// Methods ---------------------------------------------------------------------

void            SortedMap::insert(const std::string &key, const std::string &value) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        if (it->first == key) {
            it->second = value;
            return;
        }

        if (it->first > key) {
            entries.insert(it, Entry(key, value));
            return;
        }
    }

    entries.push_back(Entry(key, value));
}

const Entry     SortedMap::search(const std::string &key) {
    return binary_search(entries.begin(), entries.end(), key);
}

void            SortedMap::dump(std::ostream &os, DumpFlag flag) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        switch (flag) {
            case DUMP_KEY:          os << it->first  << std::endl; break;
            case DUMP_VALUE:        os << it->second << std::endl; break;
            case DUMP_KEY_VALUE:    os << it->first  << "\t" << it->second << std::endl; break;
            case DUMP_VALUE_KEY:    os << it->second << "\t" << it->first  << std::endl; break;
        }
    }
}

// Internal Functions ----------------------------------------------------------

const Entry   binary_search(const IT &start, const IT &end, const std::string &target) {
    auto length   = end - start;
    auto middle   = length / 2;
    auto midpoint = start + middle;

    if (start == end) {
        return NONE;
    }

    if (midpoint->first == target) {
        return *midpoint;
    }

    if (midpoint->first > target) {
        return binary_search(start, midpoint, target);
    } else {
        return binary_search(midpoint + 1, end, target);
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
