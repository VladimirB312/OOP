#pragma once
#include "CIterator.h"
#include "Node.h"
#include <string>

class CStringList
{
public:
	CStringList();
	explicit CStringList(const CStringList& other);
	CStringList& operator=(const CStringList& other);	
	CStringList(CStringList&& other) noexcept;	
	CStringList& operator=(CStringList&& other) noexcept;	

	~CStringList() noexcept;
	void Clear();

	void PushFront(const std::string& data);
	void PushBack(const std::string& data);
	void Insert(CIterator<Node*, std::string>& it, const std::string& data);
	void Erase(CIterator<Node*, std::string>& it);
	size_t GetSize() const;
	bool IsEmpty() const;

	CIterator<Node*, std::string> begin();
	CIterator<Node*, std::string> end();
	CIterator<const Node*, const std::string> begin() const;
	CIterator<const Node*, const std::string> end() const;
	CIterator<const Node*, const std::string> cbegin() const;
	CIterator<const Node*, const std::string> cend() const;
	std::reverse_iterator<CIterator<Node*, std::string>> rbegin();
	std::reverse_iterator<CIterator<Node*, std::string>> rend();
	std::reverse_iterator<CIterator<const Node*, const std::string>> rbegin() const;
	std::reverse_iterator<CIterator<const Node*, const std::string>> rend() const;
	std::reverse_iterator<CIterator<const Node*, const std::string>> rñbegin() const;
	std::reverse_iterator<CIterator<const Node*, const std::string>> rñend() const;

private:
	size_t m_size = 0;
	Node* m_sentinel = nullptr;
};
