#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ed2794.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
#include "OpenSHC/Globals/DAT_00ed27bc.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed3130.hpp"
#include "OpenSHC/Globals/INT_00ed3134.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using DE::SHCDE::eGM;
        using DE::SHCDE::eTextSections;
        using Game::GameMode2;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD350
        void ScenarioDescription::MenuView_ScenarioDescription_DoEveryFrame()
        {
            DWORD _currentTime;
            int iVar1;
            char* pcVar2;
            int iVar3;
            uint uVar4;
            eTextSections eVar5;
            TextAlignment TVar6;
            BGR24 BVar7;
            int iVar8;
            BOOLEnum BVar9;
            int iVar10;
            int iVar11;
            int iVar12;
            int local_4;
            local_4 = 0;
            if (!(INT_00ed3134::instance & 1U)) {
                INT_00ed3134::instance = INT_00ed3134::instance | 1;
                INT_00ed3130::instance = timeGetTime();
            }
            _currentTime = timeGetTime();
            iVar1 = MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)();
            if (!iVar1) {
                return;
            }
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            if (((DAT_00ed2794::instance) && (0x5dc < (int)(_currentTime - DAT_00ed2794::instance)))
                && (DAT_00ed2794::instance = 0, DAT_GameCore::instance.missionNumber1to20 + -1 < 0x14)) {
                MACRO_CALL_MEMBER(
                    Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                    DAT_MissionDefinedData::instance.MissionSpeechFileNames[DAT_GameCore::instance.missionNumber1to20 + -1], 1);
            }
            uVar4 = (_currentTime - INT_00ed3130::instance) / 0xfa;
            if (uVar4 < 0x3c) {
                if (uVar4 < 26)
                    goto LAB_004dd411;
            } else {
                uVar4 = 0;
                INT_00ed3130::instance = timeGetTime();
            LAB_004dd411:
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                    DAT_MissionDefinedData::instance.ScenarioDescriptionSpriteIDs[uVar4] + 1, 0, 0);
            }
            if (DAT_00ed27bc::instance == 1) {
                iVar11 = 0;
                BVar9 = FALSE;
                iVar8 = 0x11;
                BVar7 = 0xccfaff;
                TVar6 = Text::TTA_LEFT;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e;
                DAT_TextManagerObject::instance.field9_0x24 = 1;
                /*
                  added by script: "Briefing"
                 */
                pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MISSION_BUTTONS, 6);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar3, iVar1, TVar6, BVar7, iVar8, BVar9, iVar11);
                local_4 = 0x28;
                goto LAB_004dd68d;
            }
            if (!DAT_00ed2798::instance) {
                local_4 = MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)();
                local_4 = local_4 + (-0x1e - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight);
            }
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            if (DAT_00ed2798::instance == 1) {
                MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)();
                return;
            }
            if (DAT_00ed2798::instance == 2) {
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    iVar3 = *(int*)(DAT_MissionDefinedData::instance.MissionSpeechFileNames[0xf]
                        + DAT_GameCore::instance.missionNumber1to20 * 4 + 0x1c);
                    eVar5 = (eTextSections)(DAT_GameCore::instance.missionNumber1to20
                        + DE::SHCDE::TEXT_MISSION15_HINTS);
                } else {
                    iVar3
                        = DAT_MissionDefinedData::instance.MissionHintCounts[DAT_GameCore::instance.missionNumber1to20 - 1];
                    eVar5 = (eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                        + (DE::SHCDE::TEXT_TUTORIAL_BUTTONS | DE::SHCDE::TEXT_GOODS));
                }
                DAT_TextManagerObject::instance.field9_0x24 = 1;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_HINTS, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32, Text::TTA_LEFT, 0xccfaff,
                    0x11, FALSE);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                    eVar5, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, iVar1 + 0x50, 0x2d0,
                    0xc2f0eb, 0x12);
                iVar1 = iVar1 + 0x6e + DAT_TextManagerObject::instance.field1_0x4;
                if (0 < iVar3) {
                    DAT_TextManagerObject::instance.field9_0x24 = 1;
                    if (iVar3 == 1) {
                        iVar8 = 3;
                    LAB_004dd598:
                        /*
                          added by script: "Hints"
                         */
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_HINTS, iVar8,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e, iVar1,
                            Text::TTA_LEFT, 0xccfaff, 0x11, FALSE);
                    } else if (1 < iVar3) {
                        iVar8 = 2;
                        goto LAB_004dd598;
                    }
                    iVar1 = iVar1 + 0x1e;
                    iVar8 = 0;
                    if (0 < iVar3) {
                        do {
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS3, 0x14,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, iVar1 + -2);
                            iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x41;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            if (*(char*)((int)DAT_GameState::instance.mapAndTime.emenyHitArray + iVar8 + 0x24)
                                == '\0') {
                                iVar12 = 0;
                                BVar9 = FALSE;
                                iVar10 = 0x12;
                                BVar7 = 0xc2f0eb;
                                TVar6 = Text::TTA_LEFT;
                                iVar3 = iVar1;
                                /*
                                  added by script: "Click to reveal a hint"
                                 */
                                pcVar2
                                    = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_HINTS, 4);
                                MACRO_CALL_MEMBER(
                                    Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                    pcVar2, iVar11, iVar3, TVar6, BVar7, iVar10, BVar9, iVar12);
                                if ((DAT_MouseState::instance.draggingStopped)
                                    && (BVar9 = MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, iVar1 + -2,
                                            0x13, 0x13),
                                        BVar9)) {
                                    *(undefined1*)((int)DAT_GameState::instance.mapAndTime.emenyHitArray + iVar8 + 0x24)
                                        = 1;
                                }
                                break;
                            }
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk,
                                DAT_TextManagerObject::ptr)(eVar5, iVar8 + 2, iVar11, iVar1, 0x2b7, 0xc2f0eb, 0x12);
                            iVar1 = iVar1 + DAT_TextManagerObject::instance.field1_0x4;
                            iVar8 = iVar8 + 1;
                        } while (iVar8 < iVar3);
                    }
                }
            }
            if (DAT_00ed2798::instance) {
                return;
            }
        LAB_004dd68d:
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                eVar5 = DE::SHCDE::TEXT_ECO_MISSION_BRIEFINGS;
                iVar1 = DAT_GameCore::instance.missionNumber1to20 + -0x20;
            } else {
                eVar5 = (eTextSections)(DAT_00ed2798::instance + 0x60
                    + DAT_GameCore::instance.missionNumber1to20 * 4);
                iVar1 = 1;
            }
            iVar12 = 1;
            iVar10 = 0;
            BVar7 = 0;
            iVar11 = 0x2d0;
            iVar8 = 0;
            iVar3 = 0;
            pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(eVar5, iVar1);
            iVar3 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                pcVar2, iVar3, iVar8, iVar11, BVar7, iVar10, iVar12);
            if ((0x1a4 < iVar3 + 0x32 + local_4) && (DAT_00ed27bc::instance != 1)) {
                DAT_ARRAY_00ed26d0::instance[0].y = 1;
                return;
            }
            iVar10 = 0;
            iVar11 = 0x12;
            uVar4 = 0xc2f0eb;
            local_4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32 + local_4;
            iVar8 = 0x2d0;
            iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28;
            pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(eVar5, iVar1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                pcVar2, iVar3, local_4, iVar8, uVar4, iVar11, iVar10);
            return;
        }

    }
}
}
