#pragma once
#include "CCarImpl.h"
#include "IRacingCar.h"

class CRacingCar : public CCarImpl<IRacingCar, IRacer>
{
    using CCarImpl::CCarImpl;
};
