#pragma once
#include <string>

template <typename Base>
class CPersonImpl : public Base
{
public:
    explicit CPersonImpl(std::string name)
        :m_name(std::move(name))
    {
    }

    std::string GetName() const override
    {
        return m_name;
    }
private:
    std::string m_name;
};
