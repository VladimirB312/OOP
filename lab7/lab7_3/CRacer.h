#pragma once
#include "CPersonImpl.h"
#include "IRacer.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
    CRacer(std::string name, size_t awardsCount):
        CPersonImpl(std::move(name)), m_awardsCount(awardsCount)
    {
    }

    size_t GetAwardsCount() const override
    {
        return m_awardsCount;
    }

private:
    size_t m_awardsCount;
};
