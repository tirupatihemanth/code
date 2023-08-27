#include "leetcode.h"
using namespace std;


/* TRIES */
/* NEETCODE.IO */


class Trie {

    struct TrieNode {
        bool isEnd;
        vector<TrieNode*> next;
        TrieNode():isEnd(false){
            next = vector<TrieNode*>(26, nullptr);
        }
    };

    TrieNode *trie;

    TrieNode* find(string word){
        TrieNode *cur = trie;
        for(char c:word){
            if(!cur->next[c-'a']) return nullptr;
            cur = cur->next[c-'a'];
        }
        return cur;
    }

public:
    Trie() {
        trie = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode *cur = trie;
        for(char c:word){
            if(!cur->next[c-'a']){
                cur->next[c-'a'] = new TrieNode();
            }
            cur = cur->next[c-'a'];
        }
        cur->isEnd = true;
    }
    
    bool search(string word) {
        auto found = find(word);
        if(found) return found->isEnd;
        return false;
    }
    
    bool startsWith(string prefix) {
        return find(prefix);
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}