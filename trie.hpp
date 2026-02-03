#pragma once

#include <array>
#include <string>

namespace ds {
    struct trie {
        static constexpr int BITS = 8;
        static constexpr int RANGE = 1<<BITS;

        struct node {
            std::array<node*,RANGE> children = {};
            node* parent;
            uint8_t radix;
            bool leaf;
            node(node* parent, uint8_t radix, bool leaf): parent(parent), radix(radix), leaf(leaf) {}
            ~node() {
                for (node* nd: children) {delete nd;}
            }
        };

        node* root;

        trie() {root = new node(NULL, 0, false);}
        ~trie() {delete root;}
    
        node* find(const char* begin, int size, node* _root = NULL) {
            const char* end = begin+size;
            node* curr = (_root? _root : root);
            while (begin < end) {
                uint8_t radix = *begin;
                if (!(curr = curr->children[radix])) {return NULL;}
                begin++;
            }
            return curr;
        }
        node* insert(const char* begin, int size, node* _root = NULL) {
            const char* end = begin+size;
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
        node* find(const std::string& str) {return find(str.c_str(), str.size());}
        node* insert(const std::string& str) {return insert(str.c_str(), str.size());}
    };
}