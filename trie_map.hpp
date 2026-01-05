#include "trie.hpp"
#include <string>

namespace ds {
    template <class type>
    struct trie_map {
        struct node: trie::node {
            type val = type();
            node(node* parent, int8_t radix, bool leaf): trie::node(parent, radix, leaf) {}
        };

        node* root;

        trie_map() {root = new node(NULL, 0, false);}
        ~trie_map() {delete root;}
    };
}