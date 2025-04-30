#pragma once
#include "CCarImpl.h"
#include "CPoliceMan.h"

class CPoliceCar : public CCarImpl<CPoliceCar, CPoliceMan>
{
};