#pragma once

#include "trie_base.hpp"

namespace ds {
    template <class type>
    struct trie_map: trie_base<type> {
        trie_map<type>(): trie_base<type>() {}
    };

    template <class type, class trie_config>
    struct sp_trie_map: trie_base<type, trie_config> {
        sp_trie_map(): trie_base<type, trie_config>() {}
    };
}