#pragma once

#include "empty.hpp"
#include "trie_base.hpp"

namespace ds {
    struct trie: trie_base<empty_t> {
        trie(): trie_base<empty_t>() {}
    };

    template <class trie_config>
    struct sp_trie: trie_base<empty_t, trie_config> {
        sp_trie(): trie_base<empty_t, trie_config>() {}
    };
}