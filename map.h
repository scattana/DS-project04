// map.h

#pragma once

// Includes --------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

// Type definitions ------------------------------------------------------------

typedef enum {
    DUMP_KEY,
    DUMP_VALUE,
    DUMP_KEY_VALUE,
    DUMP_VALUE_KEY,
} DumpFlag;

typedef std::pair<std::string, std::string> Entry;
typedef std::hash<std::string>              StringHasher;

// Constants -------------------------------------------------------------------

extern const Entry  NONE;
extern const double DEFAULT_LOAD_FACTOR;
extern const size_t DEFAULT_TABLE_SIZE;

// Structures ------------------------------------------------------------------

struct Node {
    Entry entry;
    int   priority;
    Node *left;
    Node *right;

    ~Node() {
        delete left;
        delete right;
    }
};

// Classes ---------------------------------------------------------------------

class Map {
public:
    virtual void            insert(const std::string &key, const std::string &value) {}
    virtual const Entry     search(const std::string &key) { return NONE; }
    virtual void            dump(std::ostream &os, DumpFlag flag) {}
    virtual                ~Map() {}
};

class UnsortedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::vector<Entry>    entries;
};

class SortedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::vector<Entry>    entries;
};

class BSTMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
                           ~BSTMap() { delete root; }
private:
            Node    *root = nullptr;
};

class RBTreeMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::map<std::string, std::string> entries;
};

class TreapMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
                           ~TreapMap() { delete root; }
private:
            Node    *root = nullptr;
};

class UnorderedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
			std::unordered_map<std::string, std::string> entries;
};

class ChainedMap : public Map {
public:
							ChainedMap(size_t tableSize, double ldFactor){
								size = 0;
								nEntries = 0;
								loadFactor = ldFactor;
								resize(tableSize);
							}
							ChainedMap(){
								size = 0;
								nEntries = 0;
								loadFactor = DEFAULT_LOAD_FACTOR;
								resize(DEFAULT_TABLE_SIZE);
							}
							~ChainedMap(){
								delete[] table;
							}
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);

private:
            void            resize(const size_t new_size);
            size_t			size;
            size_t			nEntries;
            double			loadFactor;
            std::map<std::string, std::string> *table;
};

class OpenMap : public Map {
public:
							OpenMap();					// default constructor
							OpenMap(size_t, double);	// constructor
							~OpenMap();					// destructor
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);

private:
            size_t          locate(const std::string &key);
            void            resize(const size_t new_size);
            size_t			table_size;
            size_t			num_items;
            Entry*			table;
            double			max_load_factor;
};

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
