#pragma once

#include <array>
#include <cassert>
#include <cstddef>

namespace ds {
    /*
    Because std::set already provides a binary search tree,
    this implementation will also support indecies to make it more versatile.
    */
    template <class type, class flags_t = int>
    struct binary_search_tree {
        struct node {
            node* parent = NULL;
            node* left = NULL;
            node* right = NULL;
            int size = 1;
            flags_t flags = flags_t();
            type val;

            node(node* parent, const type& val): parent(parent), val(val) {}
            ~node() {
                delete left;
                delete right;
            }

            node* prev() {
                node* val = this;
                if (val->left) {
                    val = val->left;
                    while (val->right) {val = val->right;}
                } else {
                    val = val->parent;
                    while (val->left == this) {val = val->parent;}
                }
                return val;
            }
            node* next() {
                node* val = this;
                if (val->right) {
                    val = val->right;
                    while (val->left) {val = val->left;}
                } else {
                    val = val->parent;
                    while (val->right == this) {val = val->parent;}
                }
                return val;
            }
        };

        template <int n>
        using context_t = std::array<node*,n>;

        node* root = NULL;
        binary_search_tree() {}
        ~binary_search_tree() {
            delete root;
        }

        node* first_node() const {
            node* val = root;
            while (val->left) {val = val->left;}
            return val;
        }
        node* last_node() const {
            node* val = root;
            while (val->right) {val = val->right;}
            return val;
        }

        protected:
        void update_ancestors(node* nd) {
            while (nd) {
                nd->size = 1 + (nd->left? nd->left->size : 0) + (nd->right? nd->right->size : 0);
                nd = nd->parent;
            }
        }

        public:
        node* find(const type& val) const {
            node* curr = root;
            while (curr) {
                if (val < curr->val) {curr = curr->left;}
                else if (val > curr->val) {curr = curr->right;}
                else {return curr;}
            }
            return NULL;
        }
        node* insert(const type& val) {
            if (!root) {return root = new node(NULL, val);}
            node* curr = root;
            while (curr) {
                if (val < curr->val) {
                    if (curr->left) {curr = curr->left;}
                    else {
                        curr->left = new node(curr, val);
                        update_ancestors(curr);
                        return curr->left;
                    }
                } else if (val > curr->val) {
                    if (curr->right) {curr = curr->right;}
                    else {
                        curr->right = new node(curr, val);
                        update_ancestors(curr);
                        return curr->right;
                    }
                } else if (val == curr->val) {
                    return curr;
                }
            }
            assert(false);
            return NULL;
        }
        context_t<1> erase(node* nd) {
            assert(nd);
            assert(root && "Cannot erase from an empty tree");
            node* par = nd->parent;
            node*& _root = (!par? root : (nd == par->left? par->left : par->right));
            node* left = nd->left;
            node* right = nd->right;
            context_t<1> val;
            if (!right) {
                _root = left; if (left) {left->parent = par;}
                update_ancestors(par);
                val = {par};
            } else if (!left) {
                _root = right; if (right) {right->parent = par;}
                update_ancestors(par);
                val = {par};
            } else {
                if (!left->right) {
                    _root = left; left->parent = par;
                    left->right = right; right->parent = left;
                    update_ancestors(left);
                    val = {left};
                } else {
                    node* mid = left->right;
                    while (mid->right) {mid = mid->right;}
                    node* mid_left = mid->left;
                    node* mid_par = mid->parent;
                    _root = mid; mid->parent = par;
                    mid->left = left; left->parent = mid;
                    mid->right = right; right->parent = mid;
                    mid_par->right = mid_left; if (mid_left) {mid_left->parent = mid_par;}
                    update_ancestors(mid_par);
                    val = {mid_par};
                }
            }
            nd->left = nd->right = NULL;
            delete nd;
            return val;
        }
        node* index(int x) const {
            assert(0 <= x && x < root->size);
            node* nd = root;
            while (nd) {
                if (nd->left) {
                    if (x < nd->left->size) {nd = nd->left;}
                    else if (x == nd->left->size) {return nd;}
                    else {x -= nd->left->size+1; nd = nd->right;}
                } else if (x == 0) {
                    return nd;
                } else {
                    x -= 1;
                    nd = nd->right;
                }
            }
            assert(false);
            return NULL;
        }

        protected:
        context_t<2> rotate_right(node* nd) {
            assert(nd);
            assert(nd->left && "Cannot rotate right if left side is empty");

            node* left = nd->left;
            node* left_right = left->right;
            node* par = nd->parent;
        
            nd->left = left_right; if (left_right) {left_right->parent = nd;}
            left->right = nd; nd->parent = left;
        
            left->parent = par;
            if (!par) {
                root = left;
            } else if (nd == par->left) {
                par->left = left;
            } else {
                par->right = left;
            }

            nd->size = 1 + (nd->left? nd->left->size : 0) + (nd->right? nd->right->size : 0);
            left->size = 1 + (left->left? left->left->size : 0) + (left->right? left->right->size : 0);

            return {left, left_right};
        }
        context_t<2> rotate_left(node* nd) {
            assert(nd);
            assert(nd->right && "Cannot rotate left if right side is empty");

            node* right = nd->right;
            node* right_left = right->left;
            node* par = nd->parent;

            nd->right = right_left; if (right_left) {right_left->parent = nd;}
            right->left = nd; nd->parent = right;
        
            right->parent = par;
            if (!par) {
                root = right;
            } else if (nd == par->left) {
                par->left = right;
            } else {
                par->right = right;
            }

            nd->size = 1 + (nd->left? nd->left->size : 0) + (nd->right? nd->right->size : 0);
            right->size = 1 + (right->left? right->left->size : 0) + (right->right? right->right->size : 0);

            return {right, right_left};
        }

        protected:
        static void copy_subtree(node* dst_par, node*& dst, node* src) {
            if (!src) {return;}
            dst = new node(dst_par, src->val);
            copy_subtree(dst, dst->left, src->left);
            copy_subtree(dst, dst->right, src->right);
        }
        public:
        binary_search_tree(const binary_search_tree& bst) {
            copy_subtree(NULL, root, bst.root);
        };
        binary_search_tree& operator =(const binary_search_tree& bst) {
            delete root;
            copy_subtree(NULL, root, bst.root);
            return *this;
        };
        binary_search_tree(binary_search_tree&& bst) noexcept {
            root = bst.root;
            bst.root = NULL;
        };
        binary_search_tree& operator =(binary_search_tree&& bst) noexcept {
            delete root;
            root = bst.root;
            bst.root = NULL;
            return *this;
        };
    };
}