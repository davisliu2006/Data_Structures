#include "trie.hpp"
#include <string>

namespace ds {
    template <class type>
    struct trie_map {
        static constexpr int BITS = 8;
        static constexpr int RANGE = 1<<BITS;

        struct node: trie::node {
            type val = type();
            node(node* parent, int8_t radix, bool leaf): trie::node(parent, radix, leaf) {}
        };

        node* root;

        trie_map() {root = new node(NULL, 0, false);}
        ~trie_map() {delete root;}
    
        node* find(const int8_t* begin, int size, node* _root = NULL) {
            const int8_t* end = begin+size;
            node* curr = (_root? _root : root);
            while (begin < end) {
                uint8_t radix = *begin;
                if (!(curr = curr->children[radix])) {return NULL;}
                begin++;
            }
            return curr;
        }
        node* insert(const int8_t* begin, int size, node* _root = NULL) {
            const int8_t* end = begin+size;
            node* curr = (_root? _root : root);
            while (begin < end) {
                uint8_t radix = *begin;
                node*& trg = curr->children[radix];
                if (!trg) {trg = new node(curr, radix, false);}
                curr = trg;
                begin++;
            }
            curr->leaf = true;
            return curr;
        }
        void prune(node* nd) {
            node* parent = nd->parent;
            parent->children[nd->radix] = NULL;
            delete nd;
        }
        void erase(node* nd) {
            nd->leaf = false;
        }
    };
}