#include "string_trie.h"
#include <cassert>

int main()
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
    
    return 0;
}
