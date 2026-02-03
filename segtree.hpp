#pragma once

#include <cassert>
#include <functional>
#include <vector>

namespace ds {
    template <class type>
    struct segtree {
        using ftype = std::function<type(const type&, const type&)>;

        static int lnode(int x) {return x*2+1;}
        static int rnode(int x) {return x*2+2;}
        static int root(int x) {return (x-1)/2;}
        static int next_pow2(int x) {
            int val = 1;
            while (val < x) {val <<= 1;}
            return val;
        }

        private:
        ftype func;
        type* tree;
        int _size;
    
        public:
        segtree(int size, const ftype& func): _size(size), func(func) {
            int width = next_pow2(size);
            tree = new type[width*2-1]();
        }
        ~segtree() {
            delete[] tree;
        }

        private:
        void _build(const std::vector<type>& arr, int node, int l, int r) {
            if (l == r) {
                tree[node] = arr[l];
            } else {
                int mid = (l+r)/2;
                _build(arr, lnode(node), l, mid);
                _build(arr, rnode(node), mid+1, r);
                tree[node] = func(tree[lnode(node)], tree[rnode(node)]);
            }
        }
        type _query(int l, int r, int node, int nl, int nr) {
            if (nl == l and nr == r) {
                return tree[node];
            } else {
                int mid = (nl+nr)/2;
                int lr = min(r, mid);
                int rl = max(l, mid+1);
                if (l <= lr && rl <= r) {
                    return func(
                        _query(l, lr, lnode(node), nl, mid),
                        _query(rl, r, rnode(node), mid+1, nr)
                    );
                } else if (l <= lr) {
                    return _query(l, lr, lnode(node), nl, mid);
                } else {
                    // assert(rl <= r);
                    return _query(rl, r, rnode(node), mid+1, nr);
                }
            }
        }

        public:
        int size() {return size;}
        void build(const std::vector<type>& arr) {
            _build(arr, 0, 0, _size-1);
        }
        void update(int indx, const type& val) {
            int l = 0;
            int r = _size-1;
            int node = 0;
            while (l != r) {
                int mid = (l+r)/2;
                if (indx <= mid) {r = mid; node = lnode(node);}
                else {l = mid+1; node = rnode(node);}
            }
            // assert(l == indx);
            tree[node] = val;
            while (node != 0) {
                node = root(node);
                tree[node] = func(tree[lnode(node)], tree[rnode(node)]);
            }
        }
        type query(int l, int r) {
            assert(l <= r);
            return _query(l, r, 0, 0, _size-1);
        }
    };
}