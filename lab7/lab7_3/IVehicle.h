#pragma once
#include "IBasicVehicle.h"
#include <memory>

// ������������ �������� ��������������� ��� �������� ��������� ���� ����������
template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	// �������� ��������� �� ����
	// �.�. �������� ����� ���� ����������� �����, ��������� ��� �� ������ ���������
	// ���� ��� �����, ������������� ���������� std::logic_error
	virtual void AddPassenger(shared_ptr<Passenger> pPassenger) = 0;

	// �������� ������ �� ��������� � �������� ��������
	// ����������� ���������� std::out_of_range � ������ ������������� �������
	virtual Passenger const& GetPassenger(size_t index) const = 0;

	// ������ ��������� � �������� ��������
	// ����������� ���������� std::out_of_range � ������ ������������� �������
	virtual void RemovePassenger(size_t index) = 0;
};