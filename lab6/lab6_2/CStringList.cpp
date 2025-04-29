#include "CStringList.h"
#include <algorithm>
#include <utility>

CStringList::CStringList()
{
	m_sentinel = new Node(nullptr, nullptr);
	m_sentinel->m_next = m_sentinel;
	m_sentinel->m_prev = m_sentinel;
}

CStringList::CStringList(const CStringList& other)
	: CStringList()
{
	try
	{
		m_size = other.m_size;
		for (const auto& str : other)
		{
			PushBack(str);
		}
	}
	catch (...)
	{
		Clear();
		throw;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
{
	m_sentinel = std::exchange(other.m_sentinel, nullptr);
	m_size = std::exchange(other.m_size, 0);
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (this != &other)
	{
		m_sentinel = std::exchange(other.m_sentinel, nullptr);
		m_size = std::exchange(other.m_size, 0);
	}

	return *this;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		CStringList copy(other);
		*this = std::move(copy);
	}

	return *this;
}

CStringList::~CStringList() noexcept
{
	Clear();
	delete m_sentinel;
}

void CStringList::Clear()
{
	if (!m_sentinel)
	{
		return;
	}

	auto curr = m_sentinel->m_prev;
	while (curr != m_sentinel)
	{
		auto temp = curr->m_prev;
		delete curr;
		curr = temp;
	}

	m_sentinel->m_next = m_sentinel;
	m_sentinel->m_prev = m_sentinel;
	m_size = 0;
}

void CStringList::PushFront(const std::string& data)
{
	auto it = begin();
	Insert(it, data);
}

void CStringList::PushBack(const std::string& data)
{
	auto it = end();
	Insert(it, data);
}

void CStringList::Insert(Iterator& it, const std::string& data)
{
	auto newNode = new Node(data, it.m_node->m_prev, it.m_node);
	it.m_node->m_prev->m_next = newNode;
	it.m_node->m_prev = newNode;
	m_size++;
}

void CStringList::Erase(Iterator& it)
{
	if (it.m_node == nullptr || it.m_node == m_sentinel)
	{
		throw std::logic_error("Iterator does not point to any element");
	}

	it.m_node->m_prev->m_next = it.m_node->m_next;
	it.m_node->m_next->m_prev = it.m_node->m_prev;
	delete it.m_node;
	it.m_node = nullptr;
	m_size--;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

Iterator CStringList::begin()
{
	return Iterator{ m_sentinel->m_next, m_sentinel };
}

Iterator CStringList::end()
{
	return Iterator{ m_sentinel, m_sentinel };
}

ConstIterator CStringList::begin() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel->m_next, m_sentinel };
}

ConstIterator CStringList::end() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel, m_sentinel };
}

ConstIterator CStringList::cbegin() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel->m_next, m_sentinel };
}

ConstIterator CStringList::cend() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel, m_sentinel };
}

ReverseIterator CStringList::rbegin()
{
	return std::reverse_iterator<CIterator<Node*, std::string>>(end());
}

ReverseIterator CStringList::rend()
{
	return std::reverse_iterator<CIterator<Node*, std::string>>(begin());
}

ConstReverseIterator CStringList::rbegin() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(end());
}

ConstReverseIterator CStringList::rend() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(begin());
}

ConstReverseIterator CStringList::rñbegin() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(end());
}

ConstReverseIterator CStringList::rñend() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(begin());
}