#pragma once
#include "CIterator.h"
#include "Node.h"
#include <string>

using Iterator = CIterator<Node*, std::string>;
using ConstIterator = CIterator<const Node*, const std::string>;
using ReverseIterator = std::reverse_iterator<CIterator<Node*, std::string>>;
using ConstReverseIterator = std::reverse_iterator<CIterator<const Node*, const std::string>>;

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
	void Insert(Iterator& it, const std::string& data);
	void Erase(Iterator& it);
	size_t GetSize() const;
	bool IsEmpty() const;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	ConstReverseIterator rñbegin() const;
	ConstReverseIterator rñend() const;

private:
	size_t m_size = 0;
	Node* m_sentinel = nullptr;
};
