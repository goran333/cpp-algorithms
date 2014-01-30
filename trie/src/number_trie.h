#pragma once

#include <stdint.h>
#include "number_operators.h"

class CUintTrie
{
public:
    CUintTrie();
    ~CUintTrie();

    void Add(const uint32_t a_val);
    int FindCounts(const uint32_t a_val,
                   const NumberOperator a_oper);

    int FindCountsNumericRange(const uint32_t a_start,
                               const uint32_t a_end,
                               const bool a_inclusive = false);

private:
    class CUintTrieNode;
    CUintTrieNode* m_root;
};
