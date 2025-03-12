#include "Replacer.h"
#include "TrieNode.h"
#include "algorithm"

Replacer::Replacer(const Patterns& patterns)
	: m_root(std::make_unique<TrieNode>()), m_patterns(patterns)
{
	BuildTrie();
	BuildSuffixLinks();
};

void Replacer::BuildTrie() {
	for (const auto& [pattern, value] : m_patterns)
	{
		TrieNode* node = m_root.get();
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
	for (const auto& [key, node] : m_root->Child)
	{
		queue.push(node.get());
		node->SuffixLink = m_root.get();
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
			child->SuffixLink = m_root.get();
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

	while (m_pos < text.size()) {
		if (!m_currentNode->Child.contains(text[m_pos]))
		{
			AppendReplacementString(result, text);
		}

		if (!FollowSuffixLink(text[m_pos]))
		{
			continue;
		}

		m_currentNode = m_currentNode->Child[text[m_pos]].get();
		AddMatches();
		m_pos++;
	}

	AppendReplacementString(result, text);
	result.append(text, m_lastPos, text.size() - m_lastPos);

	return result;
};

void Replacer::AppendReplacementString(std::string& result, const std::string& text)
{
	if (m_matches.empty())
	{
		return;
	}

	std::sort(m_matches.begin(), m_matches.end(), [](
		const std::string& str1, const std::string& str2)
		{
			return str1.size() > str2.size();
		});

	result.append(text, m_lastPos, m_pos - m_matches[0].size() - m_lastPos);
	result.append(m_patterns[m_matches[0]]);
	m_lastPos = m_pos;
	m_matches.clear();
	m_currentNode = m_root.get();
};

bool Replacer::FollowSuffixLink(char ch) {
	while (m_currentNode && !m_currentNode->Child.contains(ch))
	{
		m_currentNode = m_currentNode->SuffixLink;
	}

	if (m_currentNode == nullptr)
	{
		m_currentNode = m_root.get();
		m_pos++;
		return false;
	}

	return true;
};

void Replacer::AddMatches()
{
	if (!m_currentNode->Pattern.empty())
	{
		m_matches.push_back(m_currentNode->Pattern);
	}

	TrieNode* finals = m_currentNode->FinalsLink;
	while (finals)
	{
		m_matches.push_back(finals->Pattern);
		finals = finals->FinalsLink;
	}
};

void Replacer::ClearMatcherData()
{
	m_currentNode = m_root.get();
	m_matches.clear();
	m_pos = 0;
	m_lastPos = 0;
};