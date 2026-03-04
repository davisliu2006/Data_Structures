#pragma once

#include "empty.hpp"
#include "trie_base.hpp"

namespace ds {
    struct trie: trie_base<empty_t> {
        trie(): trie_base<empty_t>() {}
    };
}