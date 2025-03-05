#pragma once
#include "TrieNode.h"
#include <list>
#include <memory>
#include <string>
#include <queue>

using Patterns = std::map<std::string, std::string>;

class Replacer {
	using Matches = std::vector<std::string>;

public:
	Replacer(const Patterns& patterns);

	std::string ReplaceMatches(const std::string& str);

private:
	std::unique_ptr<TrieNode> root;
	TrieNode* currentNode = nullptr;
	Matches matches;
	size_t pos = 0;
	size_t lastPos = 0;
	Patterns patterns;

	void BuildTrie();

	void BuildSuffixLinks();

	void BuildSuffixRootChilds(std::queue<TrieNode*>& queue);

	void BuildSuffixOtherChilds(std::queue<TrieNode*>& queue);

	void AppendReplacementString(std::string& result, const std::string& text);

	bool FollowSuffixLink(char ch);

	void AddMatches();

	void ClearMatcherData();
};
