#include <array>

namespace ds {
    struct trie {
        static constexpr int BITS = 8;
        static constexpr int RANGE = 1<<BITS;

        struct node {
            std::array<node*,RANGE> children = {};
            node* parent;
            int8_t radix;
            bool leaf;
            node(node* parent, int8_t radix, bool leaf): parent(parent), radix(radix), leaf(leaf) {}
            ~node() {
                for (node* nd: children) {delete nd;}
            }
        };

        node* root;

        trie() {root = new node(NULL, 0, false);}
        ~trie() {delete root;}
    
        node* find(int8_t* begin, int size, node* _root = NULL) {
            int8_t* end = begin+size;
            node* curr = (_root? _root : root);
            while (begin < end) {
                int8_t radix = *begin;
                if (!(curr = curr->children[radix])) {return NULL;}
                begin++;
            }
            return curr;
        }
        node* insert(int8_t* begin, int size, node* _root = NULL) {
            int8_t* end = begin+size;
            node* curr = (_root? _root : root);
            while (begin < end) {
                int8_t radix = *begin;
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