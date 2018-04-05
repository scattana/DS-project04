// treap.cpp: Treap Map

#include "map.h"

#include <climits>
#include <random>

// Prototypes ------------------------------------------------------------------

static Node *insert_r(Node *node, const std::string &key, const std::string &value);
extern Node *search_r(Node *node, const std::string &key);
extern void    dump_r(Node *node, std::ostream &os, DumpFlag flag);
static Node *rotate_right(Node *p);
static Node *rotate_left(Node *p);
static int get_random();

// Methods ---------------------------------------------------------------------

void            TreapMap::insert(const std::string &key, const std::string &value) {
    root = insert_r(root, key, value);
}

const Entry     TreapMap::search(const std::string &key) {
    auto result = search_r(root, key);
    return (result == nullptr ? NONE : result->entry);
}

void            TreapMap::dump(std::ostream &os, DumpFlag flag) {
    dump_r(root, os, flag);
}

// Internal Functions ----------------------------------------------------------

Node *insert_r(Node *node, const std::string &key, const std::string &value) {
    if (node == nullptr) {
        return new Node{Entry(key, value), get_random(), nullptr, nullptr};
    }

    if (node->entry.first == key) {
        node->entry.second = value;
        return node;
    }

    if (node->entry.first > key) {
        node->left = insert_r(node->left, key, value);
        if (node->left->priority > node->priority)
            node = rotate_right(node);
    } else {
        node->right = insert_r(node->right, key, value);
        if (node->right->priority > node->priority)
            node = rotate_left(node);
    }

    return node;
}

Node *rotate_right(Node *p) {
    Node *c  = p->left;
    Node *T2 = c->right;

    c->right = p;
    p->left  = T2;

    return c;
}

Node *rotate_left(Node *p) {
    Node *c  = p->right;
    Node *T2 = c->left;

    c->left  = p;
    p->right = T2;

    return c;
}

int get_random() {
    static std::random_device		    rd;
    static std::default_random_engine	    g(rd());
    static std::uniform_int_distribution<>  d(1, INT_MAX);
    return d(g);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
