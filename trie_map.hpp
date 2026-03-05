#pragma once

#include "trie_base.hpp"

namespace ds {
    template <class type>
    struct trie_map: trie_base<type> {
        trie_map<type>(): trie_base<type>() {}
    };
}