
#include "string_trie.h"

#include <iostream>
#include <map>

struct CStringTrie::CStringTrieNode
{
    CStringTrieNode() {}
    ~CStringTrieNode();
    void Insert(const std::string& a_val);
    bool Find(const std::string& a_val);

    typedef std::map<char, CStringTrieNode*> TNodes;
    TNodes m_children;
};


CStringTrie::CStringTrieNode::~CStringTrieNode()
{
    TNodes::iterator l_it(m_children.begin());
    for (; m_children.end() != l_it; ++l_it)
    {
        std::cout << "Deleting node for key = " << l_it->first << '\n';
        delete l_it->second;
        l_it->second = NULL;
    }
    m_children.clear();
}

void CStringTrie::CStringTrieNode::Insert(const std::string& a_val)
{
    if (a_val.empty())
        return;

    std::cout << "Inserting String = " << a_val << '\n';

    CStringTrieNode* l_child(NULL);

    TNodes::const_iterator l_it(m_children.find(a_val[0]));
    if (m_children.end() == l_it)
    {
        l_child = new CStringTrieNode();
        m_children[a_val[0]] = l_child;
    }
    else
    {
        l_child = l_it->second;
    }
    l_child->Insert(a_val.substr(1));
}

bool CStringTrie::CStringTrieNode::Find(const std::string& a_val)
{
    std::cout << "Looking for string = " << a_val << '\n';

    if (a_val.empty())
        return true;

    TNodes::const_iterator l_it(m_children.find(a_val[0]));
    if (m_children.end() == l_it)
        return false;

    return l_it->second->Find(a_val.substr(1));
}

CStringTrie::CStringTrie()
    : m_root(new CStringTrieNode())
{
}

CStringTrie::~CStringTrie()
{
    if (m_root)
        delete m_root;
}

void CStringTrie::Add(const std::string& a_val)
{
    m_root->Insert(a_val);
}

bool CStringTrie::Find(const std::string& a_val)
{
    return m_root->Find(a_val);
}
