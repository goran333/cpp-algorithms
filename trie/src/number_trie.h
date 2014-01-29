#pragma once

#include <stdint.h>

class CUintTrie
{
public:
    CUintTrie();
    ~CUintTrie();

    void Add(const uint32_t a_val);
    int FindCountsNumericRange(const uint32_t a_start,
                               const uint32_t a_end,
                               const bool a_inclusive = true);

private:
    class CUintTrieNode;
    CUintTrieNode* m_root;
};
