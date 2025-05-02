#pragma once
#include "CCarImpl.h"
#include "IPoliceCar.h"

class CPoliceCar : public CCarImpl<IPoliceCar, IPoliceMan>
{
    using CCarImpl::CCarImpl;
};
