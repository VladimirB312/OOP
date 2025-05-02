#pragma once
#include <vector>
#include <memory>

template <typename Base, typename Passenger>
class CVehicleImpl : public Base
{
public:
    explicit CVehicleImpl(size_t placeCount)
        : m_placeCount(placeCount)
    {
    }

    bool IsEmpty() const override
    {
        return m_passengersCount == 0;
    }

    bool IsFull() const override
    {
        return m_passengersCount == m_placeCount;
    }

    size_t GetPlaceCount() const override
    {
        return m_placeCount;
    }

    size_t GetPassengerCount() const override
    {
        return m_passengersCount;
    }

    void RemoveAllPassengers() override
    {
        m_passengers.clear();
        m_passengersCount = 0;
    }

    void AddPassenger(std::shared_ptr<Passenger> pPassenger) override
    {
        if (m_passengersCount == m_placeCount)
        {
            throw std::logic_error("No more free places!");
        }
        m_passengers.push_back(std::move(pPassenger));
        m_passengersCount++;
    }

    const Passenger& GetPassenger(size_t index) const override
    {
        if (index >= m_passengersCount)
        {
            throw std::out_of_range("invalid passenger index");
        }

        return *m_passengers[index];
    }

    void RemovePassenger(size_t index) override
    {
        if (index >= m_passengersCount)
        {
            throw std::out_of_range("invalid passenger index");
        }

        m_passengers.erase(m_passengers.begin() + index);
        m_passengersCount--;
    }

private:
    std::vector<std::shared_ptr<Passenger>> m_passengers;
    size_t m_placeCount = 0;
    size_t m_passengersCount = 0;
};
