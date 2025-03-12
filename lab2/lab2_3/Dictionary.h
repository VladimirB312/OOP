#pragma once
#include <map>
#include <vector>
#include <string>

using Entries = std::map<std::string, std::vector<std::string>>;

class Dictionary {
public:
	Dictionary() = default;
	explicit Dictionary(const Entries& entries);
	std::vector<std::string> GetTranslations(const std::string& word);
	Entries GetAllEntries();
	void AddWord(const std::string& word, const std::string& translation);
	bool IsInclude(const std::string& word);
	bool WasChanged();
private:
	Entries m_entries{};
	bool m_wasChanged = false;
};