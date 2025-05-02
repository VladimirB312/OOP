#include <iostream>

#include "CPerson.h"
#include "CPoliceCar.h"
#include "CPoliceMan.h"
#include "CRacer.h"
#include "CTaxi.h"


int main()
{
    CPoliceCar johnsCar(MakeOfTheCar::FORD, 5);
    auto john = std::make_shared<CPoliceMan>("John Smith", "North West Police Station");
    auto jim = std::make_shared<CPoliceMan>("Jim Clark", "South East Police Station");

    johnsCar.AddPassenger(john);
    johnsCar.AddPassenger(jim);

    std::cout << "Names and departments of the policemen in the car:\n";
    for (int i = 0; i < johnsCar.GetPassengerCount(); i++)
    {
        const auto& p = johnsCar.GetPassenger(i);
        std::cout << p.GetName() << ", " << p.GetDepartmentName() << "\n";
    }

    johnsCar.RemovePassenger(1);

    CTaxi gandiCar(MakeOfTheCar::TOYOTA, 2);
    auto gandi = std::make_shared<CPerson>("Raja Gandhi");
    auto schumacher = std::make_shared<CRacer>("Michael Schumacher", 10);

    gandiCar.AddPassenger(gandi);
    gandiCar.AddPassenger(schumacher);

    gandiCar.RemovePassenger(0);
    gandiCar.AddPassenger(jim);

    try
    {
        gandiCar.AddPassenger(gandi);
    }
    catch (const std::logic_error& ex)
    {
        std::cout << ex.what();
    }

    return 0;
}
