#include "Replacer.h"
#include "TrieNode.h"
#include "algorithm"

Replacer::Replacer(const Patterns& patterns)
	: root(std::make_unique<TrieNode>()), patterns(patterns)
{
	BuildTrie();
	BuildSuffixLinks();
};

void Replacer::BuildTrie() {
	for (const auto& [pattern, value] : patterns)
	{
		TrieNode* node = root.get();
		for (auto ch : pattern)
		{
			if (!node->Child.contains(ch))
			{
				node->Child[ch] = std::make_unique<TrieNode>();
			}
			node = node->Child[ch].get();
		}
		node->Pattern = pattern;
	}
};

void Replacer::BuildSuffixRootChilds(std::queue<TrieNode*>& queue) {
	for (const auto& [key, node] : root->Child)
	{
		queue.push(node.get());
		node->SuffixLink = root.get();
	}
};

void Replacer::BuildSuffixOtherChilds(std::queue<TrieNode*>& queue)
{
	TrieNode* current = queue.front();
	queue.pop();

	for (const auto& [key, child] : current->Child) {
		queue.push(child.get());
		TrieNode* suffixLink = current->SuffixLink;
		while (suffixLink && !suffixLink->Child.contains(key))
		{
			suffixLink = suffixLink->SuffixLink;
		}
		if (suffixLink && suffixLink->Child.contains(key))
		{
			child->SuffixLink = suffixLink->Child[key].get();
		}
		else
		{
			child->SuffixLink = root.get();
		}
		child->FinalsLink = !child->SuffixLink->Pattern.empty()
			? child->SuffixLink
			: child->SuffixLink->FinalsLink;
	}
};

void Replacer::BuildSuffixLinks()
{
	std::queue<TrieNode*> queue;

	BuildSuffixRootChilds(queue);

	while (!queue.empty())
	{
		BuildSuffixOtherChilds(queue);
	}
};

std::string Replacer::ReplaceMatches(const std::string& text)
{
	ClearMatcherData();
	std::string result;

	while (pos < text.size()) {
		if (!currentNode->Child.contains(text[pos]))
		{
			AppendReplacementString(result, text);
		}

		if (!FollowSuffixLink(text[pos]))
		{
			continue;
		}

		currentNode = currentNode->Child[text[pos]].get();
		AddMatches();
		pos++;
	}

	AppendReplacementString(result, text);
	result.append(text, lastPos, text.size() - lastPos);

	return result;
};

void Replacer::AppendReplacementString(std::string& result, const std::string& text)
{
	if (matches.empty())
	{
		return;
	}

	std::sort(matches.begin(), matches.end(), [](
		const std::string& str1, const std::string& str2)
		{
			return str1.size() > str2.size();
		});

	result.append(text, lastPos, pos - matches[0].size() - lastPos);
	result.append(patterns[matches[0]]);
	lastPos = pos;
	matches.clear();
	currentNode = root.get();
};

bool Replacer::FollowSuffixLink(char ch) {
	while (currentNode && !currentNode->Child.contains(ch))
	{
		currentNode = currentNode->SuffixLink;
	}

	if (currentNode == nullptr)
	{
		currentNode = root.get();
		pos++;
		return false;
	}

	return true;
};

void Replacer::AddMatches()
{
	if (!currentNode->Pattern.empty())
	{
		matches.push_back(currentNode->Pattern);
	}

	TrieNode* finals = currentNode->FinalsLink;
	while (finals)
	{
		matches.push_back(finals->Pattern);
		finals = finals->FinalsLink;
	}
};

void Replacer::ClearMatcherData()
{
	currentNode = root.get();
	matches.clear();
	pos = 0;
	lastPos = 0;
};