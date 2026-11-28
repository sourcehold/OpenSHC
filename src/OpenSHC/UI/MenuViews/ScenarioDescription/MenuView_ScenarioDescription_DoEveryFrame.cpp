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
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed27bc.hpp"
#include "OpenSHC/Globals/INT_00ed3130.hpp"
#include "OpenSHC/Globals/INT_00ed3134.hpp"

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
            int textOffset = 0;
            if (!(INT_00ed3134::instance & 1U)) {
                INT_00ed3134::instance = INT_00ed3134::instance | 1;
                INT_00ed3130::instance = timeGetTime();
            }
            DWORD const now = timeGetTime();
            if (!MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)()) {
                return;
            }
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            if (DAT_00ed2794::instance && (int)(now - DAT_00ed2794::instance) > 1500) {
                int const missionIndex = DAT_GameCore::instance.missionNumber1to20 - 1;
                DAT_00ed2794::instance = 0;
                if (missionIndex < 20) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                        DAT_MissionDefinedData::instance.MissionSpeechFileNames[missionIndex], 1);
                }
            }
            int frame = (now - INT_00ed3130::instance) / 250;
            if (frame >= 60) {
                frame = 0;
                INT_00ed3130::instance = timeGetTime();
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                    DAT_MissionDefinedData::instance.ScenarioDescriptionSpriteIDs[frame] + 1, 0, 0);
            } else if (frame < 26) {
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                    DAT_MissionDefinedData::instance.ScenarioDescriptionSpriteIDs[frame] + 1, 0, 0);
            }
            if (INT_00ed27bc::instance == 1) {
                DAT_TextManagerObject::instance.field_0x24 = 1;
                // "Briefing"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MISSION_BUTTONS, 6),
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32, Text::TTA_LEFT, 0xccfaff, 0x11,
                    FALSE, 0);
                textOffset = 0x28;
            } else {
                if (!DAT_00ed2798::instance) {
                    textOffset = MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)()
                        + (-0x1e - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight);
                }
                if (DAT_00ed2798::instance == 1) {
                    MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)();
                    return;
                }
                if (DAT_00ed2798::instance == 2) {
                    int hintCount;
                    eTextSections hintSection;
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                        hintCount = *(int*)(DAT_MissionDefinedData::instance.MissionSpeechFileNames[0xf]
                            + DAT_GameCore::instance.missionNumber1to20 * 4 + 0x1c);
                        hintSection = (eTextSections)(DAT_GameCore::instance.missionNumber1to20
                            + DE::SHCDE::TEXT_MISSION15_HINTS);
                    } else {
                        hintCount = DAT_MissionDefinedData::instance
                                        .MissionHintCounts[DAT_GameCore::instance.missionNumber1to20 - 1];
                        hintSection = (eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                            + (DE::SHCDE::TEXT_TUTORIAL_BUTTONS | DE::SHCDE::TEXT_GOODS));
                    }
                    int y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
                    DAT_TextManagerObject::instance.field_0x24 = 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_HINTS, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e, y,
                        Text::TTA_LEFT, 0xccfaff, 0x11, FALSE);
                    y = y + 0x1e;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                        hintSection, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, y, 0x2d0,
                        0xc2f0eb, 0x12);
                    y = y + DAT_TextManagerObject::instance.field_0x4 + 0x1e;
                    if (hintCount > 0) {
                        DAT_TextManagerObject::instance.field_0x24 = 1;
                        // "Hints"
                        if (hintCount == 1) {
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_HINTS, 3, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                                y, Text::TTA_LEFT, 0xccfaff, 0x11, FALSE);
                        } else if (hintCount > 1) {
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_HINTS, 2, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                                y, Text::TTA_LEFT, 0xccfaff, 0x11, FALSE);
                        }
                        y = y + 0x1e;
                        for (int i = 0; i < hintCount; i++) {
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS3, 0x14,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, y - 2);
                            int const textX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x41;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            if (((char*)&DAT_GameState::instance.mapAndTime.field43_0xf0)[i] == 0) {
                                // "Click to reveal a hint"
                                MACRO_CALL_MEMBER(
                                    Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_HINTS, 4),
                                    textX, y, Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
                                if (DAT_MouseState::instance.draggingStopped
                                    && MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28, y - 2, 0x13,
                                        0x13)) {
                                    ((char*)&DAT_GameState::instance.mapAndTime.field43_0xf0)[i] = 1;
                                }
                                break;
                            }
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk,
                                DAT_TextManagerObject::ptr)(hintSection, i + 2, textX, y, 0x2b7, 0xc2f0eb, 0x12);
                            y = y + DAT_TextManagerObject::instance.field_0x4;
                        }
                    }
                }
                if (DAT_00ed2798::instance) {
                    return;
                }
            }
            eTextSections briefingSection;
            int briefingIndex;
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                briefingSection = DE::SHCDE::TEXT_ECO_MISSION_BRIEFINGS;
                briefingIndex = DAT_GameCore::instance.missionNumber1to20 - 0x20;
            } else {
                briefingSection
                    = (eTextSections)(DAT_00ed2798::instance + 0x60 + DAT_GameCore::instance.missionNumber1to20 * 4);
                briefingIndex = 1;
            }
            int const height = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    briefingSection, briefingIndex),
                0, 0, 0x2d0, 0, 0, 1);
            if (height + 0x32 + textOffset > 0x1a4 && INT_00ed27bc::instance != 1) {
                DAT_ARRAY_00ed26d0::instance[0].y = 1;
                return;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    briefingSection, briefingIndex),
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32 + textOffset, 0x2d0, 0xc2f0eb, 0x12, 0);
        }

    }
}
}
