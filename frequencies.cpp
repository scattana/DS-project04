// freqencies.cpp

#include "map.h"

#include <iostream>
#include <string>

#include <strings.h>
#include <unistd.h>

// Utility functions -----------------------------------------------------------

void usage(int status) {
    std::cout << "usage: frequencies" << std::endl
              << "    -b BACKEND    Which Map backend (unsorted, sorted, bst, rbtree, treap, unordered, chained, open)" << std::endl
              << "    -d DUMPFLAG   Which dump flag (key, value, key_value, value_key)" << std::endl;

    exit(status);
}

void parse_command_line_options(int argc, char *argv[], Map *&map, DumpFlag &flag) {
    int c;

    while ((c = getopt(argc, argv, "hb:d:")) != -1) {
        switch (c) {
            case 'b':
                if (strcasecmp(optarg, "unsorted") == 0) {
                    map = new UnsortedMap();
                } else if (strcasecmp(optarg, "sorted") == 0) {
                    map = new SortedMap();
                } else if (strcasecmp(optarg, "bst") == 0) {
                    map = new BSTMap();
                } else if (strcasecmp(optarg, "rbtree") == 0) {
                    map = new RBTreeMap();
                } else if (strcasecmp(optarg, "treap") == 0) {
                    map = new TreapMap();
                } else if (strcasecmp(optarg, "unordered") == 0) {
                    map = new UnorderedMap();
                } else if (strcasecmp(optarg, "chained") == 0) {
                    map = new ChainedMap(DEFAULT_TABLE_SIZE, DEFAULT_LOAD_FACTOR);
                } else if (strcasecmp(optarg, "open") == 0) {
                    map = new OpenMap(DEFAULT_TABLE_SIZE, DEFAULT_LOAD_FACTOR);
                } else {
                    usage(1);
                }
                break;
            case 'd':
                if (strcasecmp(optarg, "key") == 0) {
                    flag = DUMP_KEY;
                } else if (strcasecmp(optarg, "value") == 0) {
                    flag = DUMP_VALUE;
                } else if (strcasecmp(optarg, "key_value") == 0) {
                    flag = DUMP_KEY_VALUE;
                } else if (strcasecmp(optarg, "value_key") == 0) {
                    flag = DUMP_VALUE_KEY;
                } else {
                    usage(1);
                }
                break;
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    if (map == nullptr) {
    map = new UnsortedMap();
    }
}

std::string increment(const std::string &s) {
    return std::to_string(std::stoi(s) + 1);
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    Map *map = nullptr;
    DumpFlag flag = DUMP_VALUE_KEY;
    std::string word;

    parse_command_line_options(argc, argv, map, flag);

    // Read input from STDIN
    while (std::cin >> word) {
        auto result = map->search(word);
        auto value  = std::string("0");

        if (result != NONE) {
            value = result.second;
        }
        map->insert(word, increment(value));
    }

    // Output words and frequencies
    map->dump(std::cout, flag);

    delete map;
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:

