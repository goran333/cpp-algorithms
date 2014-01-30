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

    int FindCountsRange(const uint32_t a_start,
                        const uint32_t a_end,
                        const bool a_startInclusive = true,
                        const bool a_endInclusive = true);

private:
    class CUintTrieNode;
    CUintTrieNode* m_root;
};
