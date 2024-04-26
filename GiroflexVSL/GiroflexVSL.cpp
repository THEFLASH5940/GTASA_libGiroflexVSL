#include "GiroflexVSL.h"

#include "menu/Draw.h"
#include "menu/Menu.h"

#include "Input.h"
#include "Vehicles.h"
#include "Globals.h"
#include "SoundPanelSystem.h"
#include "ModConfig.h"

#include "windows/WindowTest.h"
#include "windows/WindowMain.h"
#include "windows/WindowSettings.h"
#include "windows/WindowSelectPanel.h"
#include "windows/WindowPanel.h"
#include "windows/WindowSoundPanel.h"

#include <mod/amlmod.h>
#include <mod/logger.h>
#include <mod/config.h>

extern CVector2D *m_vecCachedPos;

const char* GiroflexVSL::m_Version = "3.1.0";

bool canTurnSirenOn = true;
bool canTurnPanelOn = true;

void GiroflexVSL::Update(int dt)
{
    while (Draw::m_DrawItems.size() > 0)
    {
        auto dw = Draw::m_DrawItems[0];
        Draw::m_DrawItems.erase(std::find(Draw::m_DrawItems.begin(), Draw::m_DrawItems.end(), dw));
        delete dw;
    }

    //

    Vehicles::TryFindNewVehicles();

    Vehicles::Update(dt);
    
    SoundPanelSystem::Update(dt);

    Menu::Update(dt);

    WindowSettings::Update(dt);
    WindowSettings::Draw();

    WindowSoundPanel::Draw();
    WindowSoundPanel::Update(dt);

    WindowPanel::Update();
    WindowPanel::Draw();
    
    Menu::Draw();

    Input::Update(dt);

    GiroflexVSL::ProcessMenuButtons(dt);

    //

    //check old giroflex.csa
    //theres a bug when displaying two popups at same time (when theres two .csa files)
    
    //Log::file << "Check 1 '" + std::string("/storage/emulated/0/cleo/sa/giroflex.csa") + "'" << std::endl;
    //Log::file << "Check 2 '" + std::string("/storage/emulated/0/Android/data/" + std::string(aml->GetCurrentGame()) + "/giroflex.csa") + "'" << std::endl;
    if (!ModConfig::IgnoreOldModVersionMessage)
    {
        if (
            ModConfig::FileExists("/storage/emulated/0/cleo/sa/giroflex.csa") ||
            ModConfig::FileExists("/storage/emulated/0/Android/data/" + std::string(aml->GetCurrentGame()) + "/giroflex.csa")
            )
        {
            //Log::file << "Found" << std::endl;
            Menu::ShowPopup(86, 0, 0, 1000);
        }
    }

    //

    //Draw::DrawBoxWithText(2, 1, 2, {0, 0}, {50, 50}, {255, 0, 0, 255}, {0, 0, 0, 255});

    //

    if (Menu::m_DrawCursor)
    {
        Draw::DrawText(2, m_vecCachedPos->x, m_vecCachedPos->y, CVector2D(50, 300), CRGBA(255, 180, 0));
        Draw::DrawText(1, Draw::m_DrawItems.size(), 0, CVector2D(20, 320), CRGBA(255, 255, 0));
        Draw::DrawText(1, dt, 0, CVector2D(20, 340), CRGBA(255, 255, 0));
        Draw::DrawText(1, Vehicles::m_CoronasToRender.size(), 0, CVector2D(20, 360), CRGBA(255, 255, 0));
        //Draw::DrawText(1, Input::GetTouchIdPressTime(6), 0, CVector2D(20, 400), CRGBA(255, 255, 0));

        //Draw::DrawText(2, (int)Menu::m_MenuOffset.x, (int)Menu::m_MenuOffset.y, CVector2D(20, 320), CRGBA(255, 255, 0));
    }
}

void GiroflexVSL::ProcessMenuButtons(int dt)
{
    //GiroflexVSL::ProcessTestMenuButtons(dt);

    //Main menu and toggle lights
    if (Input::GetTouchIdState(6) && Input::GetTouchIdState(5))
    {
        if (Input::GetTouchIdPressTime(6) > 500)
        {
            if (!Globals::IsPlayerInAnyVehicle())
            {
                Menu::ShowPopup(21, 0, 0, 1000);
                return;
            }

            auto vehicle = Globals::GetPlayerVehicle();

            if (canTurnSirenOn)
            {
                canTurnSirenOn = false;

                vehicle->SetGiroflexEnabled(!vehicle->prevLightsState);
            }

            if (Input::GetTouchIdPressTime(6) > 1000)
            {
                if (!WindowMain::m_Window)
                {
                    vehicle->SetGiroflexEnabled(true);

                    WindowMain::Create(vehicle->modelId);
                }
            }
        }
    }
    else {
        canTurnSirenOn = true;
    }

    //Panel
    if (Input::GetTouchIdState(5) && Input::GetTouchIdState(9))
    {
        if (Input::GetTouchIdPressTime(5) > 500 && Input::GetTouchIdPressTime(9) > 500)
        {
            if (Globals::IsPlayerInAnyVehicle())
            {
                auto veh = Globals::GetPlayerVehicle();

                if (canTurnPanelOn)
                {
                    canTurnPanelOn = false;

                    WindowSelectPanel::Create();
                    
                    //WindowPanel::Toggle(!WindowPanel::Visible);
                }
            }
            else {
                Menu::ShowPopup(21, 0, 0, 1000);
            }
        }
    }
    else {
        canTurnPanelOn = true;
    }
}

void GiroflexVSL::ProcessTestMenuButtons(int dt)
{
    //test menu, 5 and 6
    if (Input::GetTouchIdState(6) && Input::GetTouchIdState(5))
    {
        if (Input::GetTouchIdPressTime(6) > 500)
        {
            WindowTest::Create();
        }
    }
}