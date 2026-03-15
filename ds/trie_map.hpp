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
    };

    /**
     * Variant of ds::trie_map that allows custom configuration
     * of the radix and character mappings.
     */
    template <class type, class trie_config>
    struct sp_trie_map: trie_base<type, trie_config> {
        sp_trie_map(): trie_base<type, trie_config>() {}
    };
}