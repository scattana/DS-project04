// bst.cpp: BST Map

#include "map.h"

#include <stdexcept>

// Prototypes ------------------------------------------------------------------

Node *insert_r(Node *node, const std::string &key, const std::string &value);
Node *search_r(Node *node, const std::string &key);
void    dump_r(Node *node, std::ostream &os, DumpFlag flag);

// Methods ---------------------------------------------------------------------

void            BSTMap::insert(const std::string &key, const std::string &value) {
    root = insert_r(root, key, value);
}

const Entry     BSTMap::search(const std::string &key) {
    auto result = search_r(root, key);
    return (result == nullptr ? NONE : result->entry);
}

void            BSTMap::dump(std::ostream &os, DumpFlag flag) {
    dump_r(root, os, flag);
}

// Internal Functions ----------------------------------------------------------

Node *insert_r(Node *node, const std::string &key, const std::string &value) {
    if (node == nullptr) {
        return new Node{Entry(key, value), 0, nullptr, nullptr};
    }

    if (node->entry.first == key) {
        node->entry.second = value;
        return node;
    }

    if (node->entry.first > key) {
        node->left = insert_r(node->left, key, value);
    } else {
        node->right = insert_r(node->right, key, value);
    }

    return node;
}

Node *search_r(Node *node, const std::string &key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->entry.first == key) {
        return node;
    }

    if (node->entry.first > key) {
        return search_r(node->left, key);
    } else {
        return search_r(node->right, key);
    }
}

void dump_r(Node *node, std::ostream &os, DumpFlag flag) {
    if (node == nullptr) {
        return;
    }

    dump_r(node->right, os, flag);
    switch (flag) {
        case DUMP_KEY:          os << node->entry.first  << std::endl; break;
        case DUMP_VALUE:        os << node->entry.second << std::endl; break;
        case DUMP_KEY_VALUE:    os << node->entry.first  << "\t" << node->entry.second << std::endl; break;
        case DUMP_VALUE_KEY:    os << node->entry.second << "\t" << node->entry.first  << std::endl; break;
    }
    dump_r(node->left, os, flag);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
