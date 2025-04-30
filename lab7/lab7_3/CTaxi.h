#pragma once
#include "CCarImpl.h"
#include "ITaxi.h"
#include "IPerson.h"

class CTaxi: public CCarImpl<ITaxi, IPerson>
{

};