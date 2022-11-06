#pragma once

#include "pch.h"
#include "Vehicle.h"

struct RenderCorona {
	int id = 25;
	int car = 0;
	CVector offset = CVector(0, 0, 0);
	CRGBA color = CRGBA(255, 0, 0);
	float radius = 1.0f;
};

class Vehicles {
public:
	static std::map<int, Vehicle*> m_Vehicles;
	static std::vector<RenderCorona> m_CoronasToRender;

	static void TryCreateVehicle(int hVehicle, int modelId);
	static bool HasVehicleHandle(int hVehicle);
	static Vehicle* GetVehicleByHandle(int hVehicle);
	static void RemoveVehicle(int hVehicle);
	static void CheckStreamedOutVehicles();

	static void Update(int dt);
};