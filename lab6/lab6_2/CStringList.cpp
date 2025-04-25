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
	auto newNode = new Node(data, m_sentinel, m_sentinel->m_next);
	m_sentinel->m_next->m_prev = newNode;
	m_sentinel->m_next = newNode;
	m_size++;
}

void CStringList::PushBack(const std::string& data)
{
	auto newNode = new Node(data, m_sentinel->m_prev, m_sentinel);
	m_sentinel->m_prev->m_next = newNode;
	m_sentinel->m_prev = newNode;
	m_size++;
}

void CStringList::Insert(CIterator<Node*, std::string>& it, const std::string& data)
{
	auto newNode = new Node(data, it.m_node->m_prev, it.m_node);
	it.m_node->m_prev->m_next = newNode;
	it.m_node->m_prev = newNode;
	m_size++;
}

void CStringList::Erase(CIterator<Node*, std::string>& it)
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

CIterator<Node*, std::string> CStringList::begin()
{
	return CIterator<Node*, std::string>{ m_sentinel->m_next, m_sentinel };
}

CIterator<Node*, std::string> CStringList::end()
{
	return CIterator<Node*, std::string>{ m_sentinel, m_sentinel };
}

CIterator<const Node*, const std::string> CStringList::begin() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel->m_next, m_sentinel };
}

CIterator<const Node*, const std::string> CStringList::end() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel, m_sentinel };
}

CIterator<const Node*, const std::string> CStringList::cbegin() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel->m_next, m_sentinel };
}

CIterator<const Node*, const std::string> CStringList::cend() const
{
	return CIterator<const Node*, const std::string>{ m_sentinel, m_sentinel };
}

std::reverse_iterator<CIterator<Node*, std::string>> CStringList::rbegin()
{
	return std::reverse_iterator<CIterator<Node*, std::string>>(end());
}

std::reverse_iterator<CIterator<Node*, std::string>> CStringList::rend()
{
	return std::reverse_iterator<CIterator<Node*, std::string>>(begin());
}

std::reverse_iterator<CIterator<const Node*, const std::string>> CStringList::rbegin() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(end());
}

std::reverse_iterator<CIterator<const Node*, const std::string>> CStringList::rend() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(begin());
}

std::reverse_iterator<CIterator<const Node*, const std::string>> CStringList::rñbegin() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(end());
}

std::reverse_iterator<CIterator<const Node*, const std::string>> CStringList::rñend() const
{
	return std::reverse_iterator<CIterator<const Node*, const std::string>>(begin());
}