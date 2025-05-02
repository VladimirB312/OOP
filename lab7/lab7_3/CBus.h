#pragma once
#include "CVehicleImpl.h"
#include "IBus.h"

class CBus : public CVehicleImpl<IBus, IPerson>
{
    using CVehicleImpl::CVehicleImpl;
};