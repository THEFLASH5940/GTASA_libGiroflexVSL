#include "WindowSettings.h"
#include "WindowMain.h"
#include "../Input.h"
#include "../Mod.h"
#include "../Patterns.h"
#include "../Log.h"

bool WindowSettings::EditScreenModeEnabled = false;

void WindowSettings::ToggleEditScreenPos(bool enabled)
{
	EditScreenModeEnabled = enabled;
}

void WindowSettings::Create(Window* parent)
{
	auto window = Menu::AddWindow(50, parent);
	window->showPageControls = true;
	window->btnBack->onClick = [window]()
	{
		window->GoToPrevWindow();
	};

	window->AddCheckbox(57, &Menu::m_DrawCursor);
	
	window->AddIntRange(58, &Patterns::m_TimeBetweenPatterns, 1, 100000, 10);

	auto test_button = window->AddButton(66);
	test_button->onClick = [window]() {

		Log::file << "* pVehiclePool: " << (void*)Mod::pVehiclePool << std::endl;
		Log::file << printmem(Mod::pVehiclePool, 128) << std::endl;

		uintptr_t objArr = *(uintptr_t*)(Mod::pVehiclePool);
		Log::file << "* objArr: " << (void*)objArr << std::endl;
		Log::file << printmem(objArr, 128) << std::endl;

		/*
		for (int i = 0; i < 50; i++)
		{
			enum eFlags {
				POLICE = 2,
				MEDICAl = 4,
				FIRE_S = 8,
				ENGINE_ON = 16,
				HANDBRAKE_OR_NO_DRIVER = 32,
				HEADLIGHTS_ON = 64
			};

			uintptr_t vehAddress = (Mod::pVehiclePool + (i * 4));

			Log::file << "vehAddress: " << vehAddress << std::endl;

			uintptr_t pVeh = *(uintptr_t*)vehAddress;

			void* vehicle = (void*)(pVeh);

			if (vehicle == 0) return;

			Log::file << printmem(pVeh, 256) << std::endl;

			unsigned short id = *(short*)(pVeh + 0x22);
			Log::file << "id: " << std::to_string(id) << std::endl;

			unsigned char siren = *(unsigned char*)(pVeh + 0x42D);
			Log::file << "siren: " << std::to_string(siren) << std::endl;

			unsigned char siren2 = *(unsigned char*)(pVeh + 0x514);
			Log::file << "siren2: " << std::to_string(siren2) << std::endl;
			
			eFlags flags = *(eFlags*)(pVeh + 0x428);
			Log::file << "flags:" << std::endl;

			if (flags & eFlags::POLICE) Log::file << "POLICE" << std::endl;
			if (flags & eFlags::MEDICAl) Log::file << "MEDICAl" << std::endl;
			if (flags & eFlags::FIRE_S) Log::file << "FIRE_S" << std::endl;
			if (flags & eFlags::ENGINE_ON) Log::file << "ENGINE_ON" << std::endl;
			if (flags & eFlags::HANDBRAKE_OR_NO_DRIVER) Log::file << "HANDBRAKE_OR_NO_DRIVER" << std::endl;
			if (flags & eFlags::HEADLIGHTS_ON) Log::file << "HEADLIGHTS_ON" << std::endl;


			uintptr_t pointerToMatrix = *(uintptr_t*)(pVeh + 0x14);

			Log::file << "pointerToMatrix: " << pointerToMatrix << std::endl;

			Log::file << printmem(pointerToMatrix + 0x30, 16) << std::endl;

			CVector pos = *(CVector*)(pointerToMatrix + 0x30);

			Log::file << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

			
		}
		*/

		Menu::ShowPopup(0, 0, 0, 400);
	};
}

void WindowSettings::Update()
{
	if (!EditScreenModeEnabled) return;

	float speed = 0.05f;

	if (Input::GetTouchIdState(3))
	{
		Menu::m_MenuOffset.x -= speed * Mod::m_DeltaTime;
	}

	if (Input::GetTouchIdState(9))
	{
		Menu::m_MenuOffset.x += speed * Mod::m_DeltaTime;
	}
}

void WindowSettings::Draw()
{
	if (!EditScreenModeEnabled) return;

	auto screenSize = Input::GetGTAScreenSize();
	auto btnSize = CVector2D(150, 150);

	Draw::DrawBoxWithText(51, 0, 0, CVector2D(0, 0), screenSize, CRGBA(0, 0, 20, 230), CRGBA(255, 255, 255));

	Draw::DrawBoxWithText(4, 0, 0, CVector2D(0, screenSize.y - btnSize.y), btnSize, CRGBA(0, 0, 100, 255), CRGBA(255, 255, 255));

	Draw::DrawBoxWithText(5, 0, 0, CVector2D(screenSize.x - btnSize.x, screenSize.y - btnSize.y), btnSize, CRGBA(0, 0, 100, 255), CRGBA(255, 255, 255));
}