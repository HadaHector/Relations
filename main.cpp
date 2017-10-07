#include "Hierarchical.h"
#include <string>

class UnitData
{
	std::string m_sName;
};
typedef Hierarchical<UnitData> Unit;

class Soldier : public Unit
{
	bool m_bGender;
};

class Vehicle : public Unit
{
	int m_nWheels;
};

int main()
{
	Soldier Rambo;
	Vehicle Jeep;

	Jeep.AttachChild(&Rambo);

	return 0;
}