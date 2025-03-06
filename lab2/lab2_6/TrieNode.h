#pragma once
#include <map>
#include <memory>
#include <string>

struct TrieNode {
    std::string Pattern;
    TrieNode* SuffixLink = nullptr;
    TrieNode* FinalsLink = nullptr;
    std::map<char, std::unique_ptr<TrieNode>> Child;
};