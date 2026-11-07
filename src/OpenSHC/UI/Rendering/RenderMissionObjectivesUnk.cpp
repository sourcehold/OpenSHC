#include "../Rendering.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventConditionIndex.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb0b24.hpp"
#include "OpenSHC/Globals/INT_00ec02e8.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb1238.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2630.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2fc8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed3070.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D76A0
    int Rendering::RenderMissionObjectivesUnk()
    {
        int y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
        int value = 0;
        int boxX = 300;
        int eventIndex = -1;
        int column = 200;
        int const headerX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30;
        int const headerY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50;
        DAT_TextManagerObject::instance.field_0x24 = 1;
        if (DAT_GameCore::instance.section1095 == 2) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 26),
                headerX, headerY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0),
                headerX, headerY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);

            // first pass: measure the texts for the number column and the tick boxes
            for (int objective = 0; objective < OpenSHC::Game::ScenarioEvents::Enums::SECI_WIN_TIMER; ++objective) {
                if (INT_ARRAY_00ed2630::instance[objective] == 0) {
                    continue;
                }
                if ((objective == OpenSHC::Game::ScenarioEvents::Enums::SECI_4_CATTLE_FARMS
                        || objective == OpenSHC::Game::ScenarioEvents::Enums::SECI_2_INNS)
                    && DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    continue;
                }
                int textIndex = objective;
                if (objective >= OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED) {
                    textIndex = objective + 1;
                }
                if (textIndex == 17) {
                    textIndex = 6;
                } else if (textIndex == 15) {
                    textIndex = 8;
                }
                int const textWidth
                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, textIndex),
                        18);
                int const textEnd = textWidth + 30;
                if (textEnd > boxX - 5) {
                    boxX = textWidth + 35;
                }
                int numberWidth;
                switch (objective) {
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_POPULATION:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOLD_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_DRINKING_ALE:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS:
                    if (textEnd > column - 5) {
                        column = textWidth + 35;
                    }
                    numberWidth = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                        DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[objective], 18);
                    if (DAT_GameCore::instance.gameSuspended == 1) {
                        numberWidth = numberWidth
                            + MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                DAT_TextManagerObject::ptr)((char*)s___005aaf78, 18);
                        switch (objective) {
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_POPULATION:
                            value = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .currentPopulation;
                            break;
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOLD_ACQUIRED:
                            value = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .currentResources[Game::Resources::RT_GOLD];
                            break;
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED:
                            value = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .previousBlessedPeoplePercentage;
                            break;
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_DRINKING_ALE:
                            value = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
                                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                            break;
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY:
                            value = -DAT_GameState::instance
                                         .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                         .fearFactorLevel;
                            break;
                        case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS:
                            value = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .fearFactorLevel;
                            break;
                        }
                        numberWidth = numberWidth
                            + MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                DAT_TextManagerObject::ptr)(value, 18);
                    }
                    if (numberWidth + column > boxX - 5) {
                        boxX = numberWidth + column + 5;
                    }
                    break;
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_FOOD_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOODS_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED_17:
                    if (textEnd > column - 5) {
                        column = textWidth + 35;
                    }
                    numberWidth = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                        DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[objective], 18);
                    if (INT_ARRAY_00eb1238::instance[objective] > 0) {
                        numberWidth = numberWidth
                            + MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(
                                    OpenSHC::DE::SHCDE::TEXT_GOODS, INT_ARRAY_00eb1238::instance[objective]),
                                18)
                            + 6;
                    }
                    if (DAT_GameCore::instance.gameSuspended == 1) {
                        numberWidth = numberWidth
                            + MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                DAT_TextManagerObject::ptr)((char*)s___005aaf78, 18);
                        int resource = INT_ARRAY_00eb1238::instance[objective];
                        if (resource == Game::Resources::RT_PARTIALPITCH) {
                            resource = Game::Resources::RT_PITCH;
                        }
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentResources[resource];
                        numberWidth = numberWidth
                            + MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                DAT_TextManagerObject::ptr)(value, 18);
                    }
                    if (numberWidth + column > boxX - 5) {
                        boxX = numberWidth + column + 5;
                    }
                    break;
                }
            }

            // second pass: draw them
            for (int objective = 0; objective < OpenSHC::Game::ScenarioEvents::Enums::SECI_WIN_TIMER; ++objective) {
                if (INT_ARRAY_00ed2630::instance[objective] == 0) {
                    continue;
                }
                if ((objective == OpenSHC::Game::ScenarioEvents::Enums::SECI_4_CATTLE_FARMS
                        || objective == OpenSHC::Game::ScenarioEvents::Enums::SECI_2_INNS)
                    && DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    continue;
                }
                int textIndex = objective;
                if (objective >= OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED) {
                    textIndex = objective + 1;
                }
                if (textIndex == 17 || textIndex == 5 || textIndex == 6) {
                    textIndex = 7;
                } else if (textIndex == 15) {
                    textIndex = 8;
                } else if (textIndex == 3 && DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameCore::instance.missionNumber1to20 == 13) {
                        textIndex = 12;
                    } else if (DAT_GameCore::instance.missionNumber1to20 == 18) {
                        textIndex = 13;
                    } else if (DAT_GameCore::instance.missionNumber1to20 == 21) {
                        textIndex = 14;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, textIndex),
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                switch (objective) {
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_POPULATION:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOLD_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_DRINKING_ALE:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[objective],
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    if (DAT_GameCore::instance.gameSuspended != 1) {
                        break;
                    }
                    // " ("
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        (char*)s___005aaf74, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column, y,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    switch (objective) {
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_POPULATION:
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentPopulation;
                        break;
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOLD_ACQUIRED:
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentResources[Game::Resources::RT_GOLD];
                        break;
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED:
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .previousBlessedPeoplePercentage;
                        break;
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_DRINKING_ALE:
                        value = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        break;
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY:
                        value = -DAT_GameState::instance
                                     .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                     .fearFactorLevel;
                        break;
                    case OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS:
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .fearFactorLevel;
                        break;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(value,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    // ")"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        (char*)s_brace_open_005a2774, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column, y,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    break;
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_FOOD_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_GOODS_ACQUIRED:
                case OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED_17:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[objective],
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    if (INT_ARRAY_00eb1238::instance[objective] > 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_GOODS, INT_ARRAY_00eb1238::instance[objective]),
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column + 6, y,
                            OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    }
                    if (DAT_GameCore::instance.gameSuspended != 1) {
                        break;
                    }
                    // " ("
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        (char*)s___005aaf74, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column + 6, y,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    {
                        int resource = INT_ARRAY_00eb1238::instance[objective];
                        if (resource == Game::Resources::RT_PARTIALPITCH) {
                            resource = Game::Resources::RT_PITCH;
                        }
                        value = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentResources[resource];
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(value,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column + 6, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    // ")"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        (char*)s_brace_open_005a2774,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + column + 6, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    break;
                }
                // tick box: done or not
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (INT_ARRAY_00ed3070::instance[objective] != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_BUTTONS, 6,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + boxX, y - 25);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_BUTTONS, 5,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + boxX, y);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                y += 30;
            }

            // The win timer: a progress bar
            if (INT_ARRAY_00ed2630::instance[OpenSHC::Game::ScenarioEvents::Enums::SECI_WIN_TIMER] != 0
                && DAT_MapPropertiesState::instance.SEC_Section1081) {
                int const total = DAT_MapPropertiesState::instance.SEC_Section1090;
                int done = DAT_MapPropertiesState::instance.SEC_Section1090
                    - DAT_MapPropertiesState::instance.SEC_Section1080;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 25),
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                int barX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 301;
                if (DAT_TextManagerObject::instance.currentXOffset_0x0
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40
                    > barX) {
                    barX = DAT_TextManagerObject::instance.currentXOffset_0x0
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 2, barX + 2, y + 1, 24);
                if (done > total) {
                    done = total;
                }
                if (done != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, done * 250 / total + barX + 2, DAT_WindowAndDirectDraw::instance.resolutionY);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 4, barX + 2, y + 1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                        DAT_TextureRenderCoreObject::ptr)();
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 1, barX, y - 1,
                    OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 3, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                y += 21;
            }

            // time until the next one-off invasion or the deadline of the mission, as a progress bar
            int timerText = 15;
            if (INT_ARRAY_00ed2630::instance[OpenSHC::Game::ScenarioEvents::Enums::SECI_NO_ENEMY_AND_INVASIONS_LEFT]
                    != 0
                || INT_ARRAY_00ed2630::instance[OpenSHC::Game::ScenarioEvents::Enums::SECI_NO_ENEMY_ON_MAP] != 0
                || INT_00ec02e8::instance) {
                for (int i = 0; i < DAT_MapPropertiesState::instance.eventsCount; ++i) {
                    if (DAT_MapPropertiesState::instance.scenarioEvents[i].header.tl_type == 1
                        && DAT_MapPropertiesState::instance.scenarioEvents[i].data.invasion.repeatMonths == 0) {
                        eventIndex = i;
                    } else if (DAT_MapPropertiesState::instance.scenarioEvents[i].header.tl_type == 3
                        && DAT_MapPropertiesState::instance.scenarioEvents[i]
                            .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_AUTO_STOP]
                            .enabled
                        && (DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.ScenarioEventType == 1
                            || DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.ScenarioEventType
                                == 27)) {
                        if (eventIndex == -1) {
                            eventIndex = i;
                            timerText = 17;
                        }
                        break;
                    }
                }
                if (eventIndex >= 0) {
                    int const start = DAT_MapPropertiesState::instance.SEC_StartingMonth
                        + DAT_MapPropertiesState::instance.SEC_StartingYear * 12;
                    int const total = DAT_MapPropertiesState::instance.scenarioEvents[eventIndex].header.month
                        + DAT_MapPropertiesState::instance.scenarioEvents[eventIndex].header.year * 12 - start;
                    int elapsed = DAT_GameState::instance.mapAndTime.year * 12 - start
                        + DAT_GameState::instance.mapAndTime.month;
                    if (!DAT_GameCore::instance.gameSuspended) {
                        elapsed = 0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, timerText),
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    int barX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 301;
                    if (DAT_TextManagerObject::instance.currentXOffset_0x0
                            + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40
                        > barX) {
                        barX = DAT_TextManagerObject::instance.currentXOffset_0x0
                            + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 2, barX + 2, y + 1, 24);
                    if (elapsed > total) {
                        elapsed = total;
                    }
                    if (elapsed != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, elapsed * 250 / total + barX + 2, DAT_WindowAndDirectDraw::instance.resolutionY);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 4, barX + 2, y + 1);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                            DAT_TextureRenderCoreObject::ptr)();
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 1, barX,
                        y - 1, OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 3, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    y += 21;
                }
            }
        }

        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
            return y;
        }
        // builder mode: the map name and its description, scrolled by pages
        int const offset = y - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight - 30;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(
                DAT_GameCore::instance.standaloneFilename, &eventIndex),
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10, OpenSHC::Text::TTA_CENTER,
            OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
        // the visible height, rounded up to whole lines of 23 pixels
        int pageHeight = 377 - offset;
        pageHeight += 22 - (pageHeight + 22) % 23;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + offset + 45,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + pageHeight + offset + 45);
        if (!DAT_GameCore::instance.descriptionUseStringTable) {
            INT_00ed27c4::instance = (MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                                          &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                                          DAT_GameCore::instance.temporaryTextBufferOfSize1000, 0, 0, 720, 0, 0, 1)
                                         - 1)
                    / pageHeight
                + 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                DAT_GameCore::instance.temporaryTextBufferOfSize1000,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight - INT_00eb0b24::instance * pageHeight + offset
                    + 50,
                720, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, 0);
        } else if (DAT_GameCore::instance.descriptionStringTableIndex) {
            INT_00ed27c4::instance
                = (MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                       &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                       MACRO_CALL_MEMBER(
                           OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                           OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.descriptionStringTableIndex),
                       0, 0, 720, 0, 0, 1)
                      - 1)
                    / pageHeight
                + 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.descriptionStringTableIndex),
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight - INT_00eb0b24::instance * pageHeight + offset
                    + 50,
                720, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
            DAT_TextureRenderCoreObject::ptr)();
        return y;
    }

}
}
