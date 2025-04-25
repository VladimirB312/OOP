#pragma once
#include <string>

struct Node
{
	Node(Node* prev, Node* next)
		: m_prev(prev)
		, m_next(next)
	{
	}

	Node(std::string data, Node* prev, Node* next)
		: m_data(std::move(data))
		, m_prev(prev)
		, m_next(next)
	{
	}

	std::string m_data;
	Node* m_prev = nullptr;
	Node* m_next = nullptr;
};
