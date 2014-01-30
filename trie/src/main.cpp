#include "string_trie.h"
#include "number_trie.h"

#include <cassert>

int main()
{
    // String test
    if (1)
    {
        CStringTrie l_trie;
        l_trie.Add("pawan");
        l_trie.Add("peter");
        l_trie.Add("the");
        l_trie.Add("there");
        l_trie.Add("their");

        assert(true == l_trie.Find("pawan"));
        assert(true == l_trie.Find("paw"));
        assert(true != l_trie.Find("pawans"));
    }

    // Zero number test
    if (0)
    {
        CUintTrie l_trie;

        l_trie.Add(0);
        l_trie.Add(0);
        l_trie.Add(0);

        assert(0 == l_trie.FindCounts(0, LT));
        assert(3 == l_trie.FindCounts(0, LTE));
        assert(0 == l_trie.FindCounts(0, GT));
        assert(3 == l_trie.FindCounts(0, GTE));
    }

    // Single number test
    if (1)
    {
        CUintTrie l_trie;

        l_trie.Add(100);
        assert(1 == l_trie.FindCounts(100, EQ));
        assert(0 == l_trie.FindCounts(100, NOT_EQ));

        assert(0 == l_trie.FindCounts(100, LT));
        assert(1 == l_trie.FindCounts(100, LTE));
        assert(0 == l_trie.FindCounts(99, LT));
        assert(0 == l_trie.FindCounts(99, LTE));
        assert(1 == l_trie.FindCounts(101, LT));
        assert(1 == l_trie.FindCounts(101, LTE));

        assert(0 == l_trie.FindCounts(100, GT));
        assert(1 == l_trie.FindCounts(100, GTE));
        assert(1 == l_trie.FindCounts(99, GT));
        assert(1 == l_trie.FindCounts(99, GTE));
        assert(0 == l_trie.FindCounts(101, GT));
        assert(0 == l_trie.FindCounts(101, GTE));
    }

    // Multiple numbers test
    if (1)
    {
        CUintTrie l_trie;

        l_trie.Add(100); // 1
        assert(1 == l_trie.FindCounts(100, EQ));
        assert(0 == l_trie.FindCounts(100, NOT_EQ));

        assert(0 == l_trie.FindCounts(100, LT));
        assert(1 == l_trie.FindCounts(100, LTE));

        l_trie.Add(120); // 2
        assert(1 == l_trie.FindCounts(120, EQ));
        assert(1 == l_trie.FindCounts(120, NOT_EQ));

        assert(1 == l_trie.FindCounts(100, GT));
        assert(2 == l_trie.FindCounts(100, GTE));

        assert(1 == l_trie.FindCounts(120, LT));
        assert(2 == l_trie.FindCounts(120, LTE));
        assert(0 == l_trie.FindCounts(120, GT));
        assert(1 == l_trie.FindCounts(120, GTE));

        l_trie.Add(200); // 3
        l_trie.Add(200); // 4
        assert(2 == l_trie.FindCounts(200, EQ));
        assert(2 == l_trie.FindCounts(200, NOT_EQ));

        assert(3 == l_trie.FindCounts(100, GT));
        assert(4 == l_trie.FindCounts(100, GTE));
        assert(2 == l_trie.FindCounts(120, GT));
        assert(3 == l_trie.FindCounts(120, GTE));

        assert(2 == l_trie.FindCounts(200, LT));
        assert(4 == l_trie.FindCounts(200, LTE));
        assert(0 == l_trie.FindCounts(200, GT));
        assert(2 == l_trie.FindCounts(200, GTE));

        l_trie.Add(201); // 5
        assert(1 == l_trie.FindCounts(201, EQ));
        assert(4 == l_trie.FindCounts(201, NOT_EQ));

        l_trie.Add(300); // 6
        assert(1 == l_trie.FindCounts(300, EQ));
        assert(5 == l_trie.FindCounts(300, NOT_EQ));

        l_trie.Add(900); // 7
        assert(1 == l_trie.FindCounts(900, EQ));
        assert(6 == l_trie.FindCounts(900, NOT_EQ));

        assert(6 == l_trie.FindCounts(900, LT));
        assert(7 == l_trie.FindCounts(900, LTE));
        assert(6 == l_trie.FindCounts(899, LT));
        assert(6 == l_trie.FindCounts(899, LTE));
        assert(7 == l_trie.FindCounts(901, LT));
        assert(7 == l_trie.FindCounts(901, LTE));

        assert(0 == l_trie.FindCounts(900, GT));
        assert(1 == l_trie.FindCounts(900, GTE));
        assert(1 == l_trie.FindCounts(899, GT));
        assert(1 == l_trie.FindCounts(899, GTE));
        assert(0 == l_trie.FindCounts(901, GT));
        assert(0 == l_trie.FindCounts(901, GTE));

        l_trie.Add(0xFFFFFFFF); // 8
        assert(1 == l_trie.FindCounts(0xFFFFFFFF, EQ));
        assert(7 == l_trie.FindCounts(0xFFFFFFFF, NOT_EQ));

        assert(0 == l_trie.FindCounts(0xFFFFFFFF, GT));
        assert(1 == l_trie.FindCounts(0xFFFFFFFF, GTE));
        assert(7 == l_trie.FindCounts(0xFFFFFFFF, LT));
        assert(8 == l_trie.FindCounts(0xFFFFFFFF, LTE));

        l_trie.FindCountsRange(0, 101);
        l_trie.FindCountsRange(0, 0xFFFFFFFF);
    }

    return 0;
}
