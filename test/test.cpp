#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

#include "test.hpp"
#include "rng.hpp"
#include "../binary_search_tree.hpp"
#include "../deque.hpp"
#include "../fenwick.hpp"
#include "../segtree.hpp"
#include "../trie.hpp"

using namespace std;

vector<Test> tests = {
    {"fenwick_test", []() {
        int n = 100;
        int q = 50;
        vector<int64_t> arr(n+1);
        ds::fenwick<int64_t> fw(n);
        for (int i = 1; i <= n; i++) {
            arr[i] = randint(-100, 100);
            fw.update(i, arr[i]);
        }
        while (q--) {
            int upd = randint(0, 1);
            if (upd) {
                int i = randint(1, n);
                int v = randint(-100, 100);
                arr[i] += v;
                fw.update(i, v);
            } else {
                int r = randint(1, n);
                int64_t expected = 0;
                for (int i = 1; i <= r; i++) {expected += arr[i];}
                assert(expected == fw.query(r));
            }
        }
    }},
    {"segtree_test", []() {
        int n = 100;
        int q = 50;
        vector<int64_t> arr(n);
        for (int64_t& x: arr) {
            x = randlong(-100, 100);
        }
        ds::segtree<int64_t> st(n, [](int x, int y) {return x+y;});
        st.build(arr);
        while (q--) {
            int upd = randint(0, 1);
            if (upd) {
                int i = randint(0, n-1);
                int64_t v = randint(0, 100);
                arr[i] = v;
                st.update(i, v);
            } else {
                int l = randint(0, n-1);
                int r = randint(0, n-1);
                if (l > r) {swap(l, r);}
                int64_t expected = 0;
                for (int i = l; i <= r; i++) {expected += arr[i];}
                assert(expected == st.query(l, r));
            }
        }
    }},
    {"trie_test", []() {
        ds::trie tr;
        ds::trie::node* nd1;
        ds::trie::node* nd2;
        assert(!tr.find("abcd"));
        tr.insert("abd");
        nd1 = tr.insert("abcd");
        tr.insert("abcde");
        assert((nd2 = tr.find("abcd")) && nd2->leaf && nd2 == nd1);
        assert((nd1 = tr.find("abc")) && !nd1->leaf);
        assert(!tr.find("abcdf"));
        assert(tr.find("d", 1, nd1) == nd2);
        tr.erase(nd2);
        assert((nd1 = tr.find("abcd")) && !nd1->leaf);
        assert((nd2 = tr.find("abcde")) && nd2->leaf);
        tr.prune(nd1);
        assert(!tr.find("abcde") && !tr.find("abcd"));
        assert(tr.find("abc") && tr.find("abd"));
    }},
    {"bst_test", []() {
        ds::binary_search_tree<int> bst;
        decltype(bst)::node* nd;
        assert(!bst.find(0));
        bst.insert(0);
        bst.insert(-2);
        bst.insert(2);
        bst.insert(-1);
        bst.insert(1);
        bst.insert(-3);
        assert((nd = bst.find(-2)) && nd->size == 3 && nd == bst.index(1));
        assert((nd = bst.find(2)) && nd->size == 2 && nd == bst.index(5));
        assert((nd = bst.find(-1)) && nd->size == 1 && nd == bst.index(2));
        assert((nd = bst.find(1)) && nd->size == 1 && nd == bst.index(4));
        assert((nd = bst.find(-3)) && nd->size == 1 && nd == bst.index(0));
        assert((nd = bst.find(0)) && nd->size == 6 && nd == bst.index(3));
        bst.erase(nd);
        assert(!bst.find(0));
        assert((nd = bst.find(-2)) && nd->size == 2 && nd == bst.index(1));
        assert((nd = bst.find(2)) && nd->size == 2 && nd == bst.index(4));
        assert((nd = bst.find(1)) && nd->size == 1 && nd == bst.index(3));
        assert((nd = bst.find(-3)) && nd->size == 1 && nd == bst.index(0));
        assert((nd = bst.find(-1)) && nd->size == 5 && nd == bst.index(2));
        bst.insert(-1);
        assert(nd->size == 5);
    }},
    {"bst_iterator_test", []() {
        ds::binary_search_tree<int> bst;
        decltype(bst)::node* nd;
        bst.insert(0);
        bst.insert(-2);
        bst.insert(2);
        bst.insert(-1);
        bst.insert(1);
        bst.insert(-3);
        nd = bst.first_node();
        assert(nd->val == -3);
        assert((nd = nd->next())->val == -2);
        assert((nd = nd->next())->val == -1);
        assert((nd = nd->next())->val == 0);
        assert((nd = nd->next())->val == 1);
        assert((nd = nd->next())->val == 2 && nd == bst.last_node());
    }},
    {"deque_test", []() {
        ds::circular_deque<int> d(2);
        d.push_back(1); d.push_back(2);
        assert(d.front() == 1 && d.back() == 2 && d.size() == 2 && d.capacity() == 2);
        d.push_front(-1); d.push_front(-2);
        assert(d.front() == -2 && d.back() == 2 && d.size() == 4 && d.capacity() == 4);
        d.push_front(0); d.push_back(0);
        assert(d.front() == 0 && d.back() == 0 && d.size() == 6 && d.capacity() == 8);
        d.pop_back(); d.pop_front();
        assert(d.front() == -2 && d.back() == 2 && d.size() == 4 && d.capacity() == 8);
        d.push_front(-3); d.push_back(3);
        assert(d.front() == -3 && d.back() == 3 && d.size() == 6 && d.capacity() == 8);
        assert(d[0] == -3 && d[1] == -2 && d[2] == -1 && d[3] == 1 && d[4] == 2 && d[5] == 3);
    }}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(15);

    for (const Test& test: tests) {
        test.run();
    }

    return 0;
}