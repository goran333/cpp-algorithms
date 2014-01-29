
#pragma once

#include <string>

class CStringTrie
{
public:
    CStringTrie();
    ~CStringTrie();
    void Add(const std::string& a_val);
    bool Find(const std::string& a_val);

private:
    class CStringTrieNode;
    CStringTrieNode* m_root;
};
