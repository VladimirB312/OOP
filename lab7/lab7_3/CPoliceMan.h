#pragma once
#include "CPersonImpl.h"
#include "IPoliceMan.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
    CPoliceMan(std::string name, std::string departmentName)
        : CPersonImpl(std::move(name)),
          m_departamentName(std::move(departmentName))
    {
    }

    std::string GetDepartmentName() const override
    {
        return m_departamentName;
    }

private:
    std::string m_departamentName;
};
