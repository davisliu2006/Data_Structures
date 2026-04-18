#pragma once

#include "trie_base.hpp"

namespace ds {
    /**
     * A map structure that uses a prefix tree implementation.
     * Defaults to a 256 bit radix.
     */
    template <class type>
    struct trie_map: trie_base<type> {
        trie_map<type>(): trie_base<type>() {}
        trie_map<type>(const trie_map<type>& tr): trie_base<type>(tr) {}
        trie_map<type>& operator =(const trie_map<type>& tr) {
            trie_base<type>::operator =(tr);
            return *this;
        }
    };

    /**
     * Variant of ds::trie_map that allows custom configuration
     * of the radix and character mappings.
     */
    template <class type, class trie_config>
    struct sp_trie_map: trie_base<type, trie_config> {
        sp_trie_map(): trie_base<type, trie_config>() {}
        sp_trie_map(const sp_trie_map<type, trie_config>& tr): trie_base<type, trie_config>(tr) {}
        sp_trie_map<type, trie_config>& operator =(const sp_trie_map<type, trie_config>& tr) {
            trie_base<type, trie_config>::operator =(tr);
            return *this;
        }
    };
}