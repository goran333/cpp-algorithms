
#include "number_trie.h"

#include <iostream>
#include <map>

struct CUintTrie::CUintTrieNode
{ //todo
};


CUintTrie::CUintTrie()
    : m_root(new CUintTrieNode())
{
}

CUintTrie::~CUintTrie()
{
    if (m_root)
        delete m_root;
}

void CUintTrie::Add(const uint32_t a_val)
{// todo
}

int CUintTrie::FindCountsNumericRange(const uint32_t a_start,
                                      const uint32_t a_end,
                                      const bool a_inclusive)
{// todo
    return 0;
}
