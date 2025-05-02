#pragma once
#include "CVehicleImpl.h"
#include "ICar.h"

template <typename Base, typename Passenger>
class CCarImpl : public CVehicleImpl<Base, Passenger>
{
public:
    CCarImpl(const MakeOfTheCar& make, size_t placeCount)
        : CVehicleImpl<Base, Passenger>(placeCount), m_make(make)
    {
    }

    MakeOfTheCar GetMakeOfTheCar() const override
    {
        return m_make;
    }

private:
    MakeOfTheCar m_make;
};
