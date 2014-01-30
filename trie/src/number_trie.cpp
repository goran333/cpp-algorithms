
#include "number_trie.h"

#include <iostream>
#include <iomanip>
#include <map>

struct CUintTrie::CUintTrieNode
{
    CUintTrieNode(): m_count(0), m_zeroCount(0) {}
    ~CUintTrieNode();

    void Insert(const uint32_t a_val);
    int GetCount() { return m_count; }
    int FindCountsEq(const uint32_t a_val);
    int FindCountsNotEq(const uint32_t a_val);
    int FindCountsLessThan(const uint32_t a_val,
                           const bool a_inclusive);
    int FindCountsGreaterThan(const uint32_t a_val,
                              const bool a_inclusive);

    typedef std::map<uint8_t, CUintTrieNode*> TNodes;

    TNodes m_children;
    size_t m_count, m_zeroCount;
};

CUintTrie::CUintTrieNode::~CUintTrieNode()
{
    TNodes::iterator l_it(m_children.begin());
    for (; m_children.end() != l_it; ++l_it)
    {
        std::cout << "Deleting node for key = "
                  << std::setw(2) << std::hex 
                  << (uint32_t)l_it->first << '\n';
        delete l_it->second;
        l_it->second = NULL;
    }
    m_children.clear();
}

void CUintTrie::CUintTrieNode::Insert(const uint32_t a_val)
{
    std::cout << "Inserting Uint = " << std::setfill('0')
              << std::setw(8) << std::hex << a_val << '\n';

    ++m_count; // cumulative count of all records under this node

    if (0 == a_val)
    {
        ++m_zeroCount;
        return;
    }

    uint8_t l_byte = (a_val & 0xFF000000) >> 24;

    CUintTrieNode* l_child(NULL);

    TNodes::iterator l_it(m_children.find(l_byte));
    if (m_children.end() == l_it)
    {
        l_child = new CUintTrieNode();
        m_children[l_byte] = l_child;
    }
    else
    {
        l_child = l_it->second;
    }
    std::cout << "New Count = " << m_count << '\n'
              << "No of Children = " << m_children.size() << '\n'
              << "Byte = " << std::setw(2) << std::hex << (unsigned int)l_byte << '\n';

    l_child->Insert((a_val << 8));
}

int CUintTrie::CUintTrieNode::FindCountsLessThan(const uint32_t a_val,
                                                 const bool a_inclusive)
{
    std::cout << "Finding Uint = " << std::setfill('0')
              << std::setw(8) << std::hex << a_val << '\n';

    if (0 == a_val)
    {
        return (a_inclusive)? m_zeroCount: 0;
    }

    uint8_t l_byte = (a_val & 0xFF000000) >> 24;

    TNodes::const_iterator l_it = m_children.lower_bound(l_byte);
    if (m_children.end() == l_it)
    {
        std::cout << "All elements greater than me, return cumulative count = " << m_count << '\n';
        return m_count;
    }
    else
    {
        // add up all elements before me
        TNodes::const_iterator l_it2(m_children.begin());
        int l_ret(0);
        for (; l_it2 != l_it; ++l_it2)
        {
            l_ret += l_it2->second->GetCount();
            std::cout << "After adding, new count = " << l_ret << '\n';
        }

        const uint32_t l_next(a_val << 8);
        if (l_it->first == l_byte)
        {
            std::cout << "Exact match, ";
            if (0 == l_next) // no need to go deeper
            {
                std::cout << "Final level ...\n";
                if (a_inclusive)
                {
                    std::cout << "Returning inclusive count = " 
                              << l_ret + l_it->second->GetCount() << '\n';
                    return l_ret + l_it->second->GetCount();
                }
                else
                {
                    std::cout << "Returning non-inclusive count = " 
                              << l_ret << '\n';
                    return l_ret;
                }
            }
            else
            {
                std::cout << "Digging deeper ...\n";
                return (l_ret + 
                        l_it->second->FindCountsLessThan(l_next, a_inclusive));
            }
        }
        else
        {
            std::cout << "Not an exact match, count all elements before me ...\n";
            return (l_ret);
        }
    }
}

int CUintTrie::CUintTrieNode::FindCountsGreaterThan(const uint32_t a_val,
                                                    const bool a_inclusive)
{
    std::cout << "Finding Uint = " << std::setfill('0')
              << std::setw(8) << std::hex << a_val << '\n';

    if (0 == a_val)
    {
        return (a_inclusive)? m_count: (m_count - m_zeroCount);
    }

    uint8_t l_byte = (a_val & 0xFF000000) >> 24;

    TNodes::const_iterator l_it = m_children.lower_bound(l_byte);
    if (m_children.end() == l_it)
    {
        std::cout << "All elements less than me, return 0!\n";
        return 0;
    }
    else
    {
        // add up all elements after me
        TNodes::const_iterator l_it2(l_it);
        ++l_it2; // point to the next element
        int l_ret(0);
        for (; l_it2 != m_children.end(); ++l_it2)
        {
            l_ret += l_it2->second->GetCount();
            std::cout << "After adding, new count = " << l_ret << '\n';
        }

        const uint32_t l_next(a_val << 8);
        if (l_it->first == l_byte)
        {
            std::cout << "Exact match, ";
            if (0 == l_next) // no need to go deeper
            {
                std::cout << "Final level ...\n";
                if (a_inclusive)
                {
                    std::cout << "Returning inclusive count = " 
                              << l_ret + l_it->second->GetCount() << '\n';
                    return l_ret + l_it->second->GetCount();
                }
                else
                {
                    std::cout << "Returning non-inclusive count = " 
                              << l_ret << '\n';
                    return l_ret;
                }
            }
            else
            {
                std::cout << "Digging deeper ...\n";
                return (l_ret + 
                        l_it->second->FindCountsGreaterThan(l_next, a_inclusive));
            }
        }
        else
        {
            std::cout << "Not an exact match, count me & all elements after me ...\n";
            return (l_ret + l_it->second->GetCount());
        }
    }
}

int CUintTrie::CUintTrieNode::FindCountsEq(const uint32_t a_val)
{
    std::cout << "Finding Uint = " << std::setfill('0')
              << std::setw(8) << std::hex << a_val << '\n';

    if (0 == a_val)
    {
        return m_zeroCount;
    }

    uint8_t l_byte = (a_val & 0xFF000000) >> 24;

    TNodes::const_iterator l_it = m_children.find(l_byte);
    if (m_children.end() == l_it)
    {
        std::cout << "Not found, return 0!\n";
        return 0;
    }
    else
    {
        const uint32_t l_next(a_val << 8);
        return l_it->second->FindCountsEq(l_next);
    }
}

int CUintTrie::CUintTrieNode::FindCountsNotEq(const uint32_t a_val)
{
    return m_count - FindCountsEq(a_val);
}

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
{
    m_root->Insert(a_val);
}

int CUintTrie::FindCounts(const uint32_t a_val,
                          const NumberOperator a_oper)
{
    int l_ret(-1);

    switch (a_oper)
    {
    case LT:
        l_ret = m_root->FindCountsLessThan(a_val, false);
        break;
    case LTE:
        l_ret = m_root->FindCountsLessThan(a_val, true);
        break;
    case GT:
        l_ret = m_root->FindCountsGreaterThan(a_val, false);
        break;
    case GTE:
        l_ret = m_root->FindCountsGreaterThan(a_val, true);
        break;
    case EQ:
        l_ret = m_root->FindCountsEq(a_val);
        break;
    case NOT_EQ:
        l_ret = m_root->FindCountsNotEq(a_val);
        break;
    default:
        std::cout << "Bad/un-supported operator = " << a_oper << '\n';
        break;
    }
    return l_ret;
}

int CUintTrie::FindCountsRange(const uint32_t a_start,
                               const uint32_t a_end,
                               const bool a_startInclusive,
                               const bool a_endInclusive)
{
    if (a_start >= a_end)
        return -1;

    int l_greater = m_root->FindCountsGreaterThan(a_start, a_startInclusive);
    int l_less = m_root->FindCountsLessThan(a_end, a_endInclusive);

    std::cout << "Greater" << (a_startInclusive? "Eq": "")
              << " than " << a_start << " = " << l_greater << '\n'
              << "Less" << (a_endInclusive? "Eq": "")
              << " than " << a_end << " = " << l_less << '\n';

    // todo: how to find the correct count for a range?

    return 0;
}
