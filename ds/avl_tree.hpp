#pragma once

#include "binary_search_tree.hpp"

namespace ds {
    struct avl_tree_flags {
        short l_height = 0;
        short r_height = 0;
        short height() {
            return std::max(l_height, r_height);
        }
        short balance() {
            return r_height-l_height;
        }
    };

    /**
     * Extension of ds::binary_search_tree using AVL tree balancing.
     */
    template <class type>
    struct avl_tree: binary_search_tree<type, avl_tree_flags> {
        using base_tree = binary_search_tree<type, avl_tree_flags>;
        using node = typename base_tree::node;

        avl_tree(): base_tree() {}
        ~avl_tree() {}

        protected:
        void rotate_right(node* nd) {
            auto [root, right_left] = base_tree::rotate_right(nd);
            nd->flags.l_height = (right_left? 1+right_left->flags.height() : 0);
            root->flags.r_height = 1 + nd->flags.height();
        }
        void rotate_left(node* nd) {
            auto [root, left_right] = base_tree::rotate_left(nd);
            nd->flags.r_height = (left_right? 1+left_right->flags.height() : 0);
            root->flags.l_height = 1 + nd->flags.height();
        }

        public:
        node* insert(const type& val) {
            node* nd = base_tree::insert(val);
            node* curr = nd->parent;
            while (curr) {
                curr->flags.l_height = (curr->left? 1+curr->left->flags.height() : 0);
                curr->flags.r_height = (curr->right? 1+curr->right->flags.height() : 0);
                if (curr->flags.balance() < -1) {
                    if (curr->left->flags.balance() > 0) {
                        rotate_left(curr->left);
                    }
                    rotate_right(curr);
                } else if (curr->flags.balance() > 1) {
                    if (curr->right->flags.balance() < 0) {
                        rotate_right(curr->right);
                    }
                    rotate_left(curr);
                }
                curr = curr->parent;
            }
            return nd;
        }
        void erase(node* nd) {
            auto [upd] = base_tree::erase(nd);
            node* curr = upd;
            while (curr) {
                curr->flags.l_height = (curr->left? 1+curr->left->flags.height() : 0);
                curr->flags.r_height = (curr->right? 1+curr->right->flags.height() : 0);
                if (curr->flags.balance() < -1) {
                    if (curr->left->flags.balance() > 0) {
                        rotate_left(curr->left);
                    }
                    rotate_right(curr);
                } else if (curr->flags.balance() > 1) {
                    if (curr->right->flags.balance() < 0) {
                        rotate_right(curr->right);
                    }
                    rotate_left(curr);
                }
                curr = curr->parent;
            }
        }

        avl_tree(const avl_tree& bst) {
            copy_subtree(NULL, base_tree::root, bst.root);
        };
        avl_tree& operator =(const avl_tree& bst) {
            delete base_tree::root;
            copy_subtree(NULL, base_tree::root, bst.root);
            return *this;
        };
        avl_tree(avl_tree&& bst) noexcept {
            base_tree::root = bst.root;
            bst.root = NULL;
        };
        avl_tree& operator =(avl_tree&& bst) noexcept {
            delete base_tree::root;
            base_tree::root = bst.root;
            bst.root = NULL;
            return *this;
        };
    };
}