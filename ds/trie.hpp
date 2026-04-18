#pragma once

#include "empty.hpp"
#include "trie_base.hpp"

namespace ds {
    /**
     * Standard prefix tree data structure.
     * Defaults to a 256 bit radix.
     */
    struct trie: trie_base<empty_t> {
        trie(): trie_base<empty_t>() {}
        trie(const trie& tr): trie_base<empty_t>(tr) {}
        trie& operator =(const trie& tr) {
            trie_base<empty_t>::operator =(tr);
            return *this;
        }
    };

    /**
     * Variant of ds::trie that allows custom configuration
     * of the radix and character mappings.
     */
    template <class trie_config>
    struct sp_trie: trie_base<empty_t, trie_config> {
        sp_trie(): trie_base<empty_t, trie_config>() {}
        sp_trie(const sp_trie& tr): trie_base<empty_t, trie_config>(tr) {}
        sp_trie& operator =(const sp_trie& tr) {
            trie_base<empty_t, trie_config>::operator =(tr);
            return *this;
        }
    };
}