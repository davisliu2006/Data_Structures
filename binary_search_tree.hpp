#include <cassert>

template <class type>
struct binary_search_tree {
    struct node {
        node* parent = NULL;
        node* left = NULL;
        node* right = NULL;
        type val;
        node(node* parent, const type& val): parent(parent), val(val) {}
        ~node() {
            delete left;
            delete right;
        }
    };

    node* root = NULL;
    binary_search_tree() {}
    ~binary_search_tree() {
        delete root;
    }

    node* find(const type& val) {
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
                else {return curr->left = new node(curr, val);}
            } else if (val > curr->val) {
                if (curr->right) {curr = curr->right;}
                else {return curr->right = new node(curr, val);}
            } else if (val == curr->val) {
                return curr;
            }
        }
        return NULL;
    }
    void erase(node* nd) {
        assert(nd); assert(root);
        node* par = nd->parent;
        node*& _root = (!par? root : (nd == par->left? par->left : par->right));
        node* left = nd->left;
        node* right = nd->right;
        if (!right) {
            _root = left; if (left) {left->parent = par;}
        } else if (!left) {
            _root = right; if (right) {right->parent = par;}
        } else {
            if (!left->right) {
                _root = left; left->parent = par;
                left->right = right; right->parent = left;
            } else {
                node* mid = left->right;
                while (mid->right) {mid = mid->right;}
                node* mid_left = mid->left;
                node* mid_par = mid->parent;
                _root = mid; mid->parent = par;
                mid->left = left; left->parent = mid;
                mid->right = right; right->parent = mid;
                mid_par->right = mid_left; if (mid_left) {mid_left->parent = mid_par;}
            }
        }
        nd->left = nd->right = NULL;
        delete nd;
    }
};