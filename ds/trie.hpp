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
    };

    /**
     * Variant of ds::trie that allows custom configuration
     * of the radix and character mappings.
     */
    template <class trie_config>
    struct sp_trie: trie_base<empty_t, trie_config> {
        sp_trie(): trie_base<empty_t, trie_config>() {}
    };
}