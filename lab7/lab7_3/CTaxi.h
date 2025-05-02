#pragma once
#include "CCarImpl.h"
#include "ITaxi.h"

class CTaxi: public CCarImpl<ITaxi, IPerson>
{
    using CCarImpl::CCarImpl;
};