#include "../EditScenario.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventConditionIndex.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8220
        void EditScenario::MenuItemActionHandler_EditScenario_BaseMenuButtons(int button, ...)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            switch (button) {
            case 3:
                // back to the map's properties with the typed start year
                DAT_MapPropertiesState::instance.SEC_StartingYear
                    = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_10));
                if (DAT_MapPropertiesState::instance.year_copy != DAT_MapPropertiesState::instance.SEC_StartingYear) {
                    DAT_GameState::instance.mapAndTime.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                    DAT_GameState::instance.mapAndTime.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                return;
            case 38:
                // the trader settings; not on a siege map
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                }
                DAT_MapPropertiesState::instance.indexStored = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_TRADER_SETTINGS, FALSE);
                return;
            case 41: {
                char text[12];
                // the attacking force on a siege map, the starting goods otherwise
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    // The attacking force's rows start at 20
                    DAT_MapPropertiesState::instance.indexStored = 20;
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12);
                    // "%d"
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s__d_005aa7f0,
                        DAT_MapPropertiesState::instance
                            .SEC_SiegeInformation[DAT_MapPropertiesState::instance.indexStored - 20]);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(text);
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_NINE__FILTER_B);
                    DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum = MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_UNUSED_SIEGE_ATTACKING_FORCEUnk, FALSE);
                    return;
                }
                DAT_MapPropertiesState::instance.indexStored = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_12);
                // "%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s__d_005aa7f0,
                    DAT_MapPropertiesState::instance.SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance
                            .field_0x345c[DAT_MapPropertiesState::instance.indexStored]]);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(text);
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_START_GOODS, FALSE);
                return;
            }
            case 79:
                // the starting popularity slider; not on a siege map
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setSliderParameters,
                    DAT_MenuModalComposition2::ptr)(0, 100, DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                    (undefined*)&DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                DAT_MenuModalComposition2::instance.textGroup = OpenSHC::DE::SHCDE::TEXT_SCENARIO;
                // "Popularity"
                DAT_MenuModalComposition2::instance.textIndex = 79;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 2, DAT_ButtonY::instance + 25);
                return;
            case -1:
                // the start month, from December round to January
                ++DAT_MapPropertiesState::instance.SEC_StartingMonth;
                if (DAT_MapPropertiesState::instance.SEC_StartingMonth >= 12) {
                    DAT_MapPropertiesState::instance.SEC_StartingMonth = 0;
                }
                DAT_GameState::instance.mapAndTime.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                DAT_GameState::instance.mapAndTime.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                return;
            case 42: {
                char text[12];
                // a new invasion, on an invasion map
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_INVASION) {
                    return;
                }
                DAT_MapPropertiesState::instance.currentEventID = DAT_MapPropertiesState::instance.eventsCount;
                ++DAT_MapPropertiesState::instance.eventsCount;
                DAT_MapPropertiesState::instance.editedEventType = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::resetEvent,
                    &DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID])();
                DAT_MapPropertiesState::instance.SEC_StartingYear
                    = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_10));
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_14);
                // ""
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(s__005a5339);
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_11);
                // "%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s__d_005aa7f0,
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.year);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(text);
                DAT_MapPropertiesState::instance.field_0x1356c = 0;
                DAT_MapPropertiesState::instance.offset = 0;
                DAT_MapPropertiesState::instance.indexStored = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_INVASION, FALSE);
                return;
            }
            case 43: {
                char text[12];
                // a new event; not on a just-build map
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_JUST_BUILD) {
                    return;
                }
                DAT_MapPropertiesState::instance.currentEventID = DAT_MapPropertiesState::instance.eventsCount;
                ++DAT_MapPropertiesState::instance.eventsCount;
                DAT_MapPropertiesState::instance.editedEventType = 3;
                MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent,
                    &DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID])();
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_AUTO_STOP]
                    .enabled = 1;
                // Written out (a for loop over 5 to 7: quick_diff 0.9573 -> 0.9001)
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_FOOD_ACQUIRED]
                    .subType = 10;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED]
                    .subType = 10;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_GOODS_ACQUIRED]
                    .subType = 10;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED_17]
                    .subType = 10;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY]
                    .value = 5;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS]
                    .value = 5;
                DAT_MapPropertiesState::instance.SEC_StartingYear
                    = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_10));
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                DAT_MapPropertiesState::instance.invasionTroopIndex = 0;
                DAT_MapPropertiesState::instance.flag = TRUE;
                // fixme: the formatted year is not used (the original does the same, 0x004B86E5)
                // "%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s__d_005aa7f0,
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.year);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_EVENT, FALSE);
                return;
            }
            case 168:
                // the attacking force's gold slider, on a siege map
                // textGroup first (168, 169, 61): a shared tail (textIndex first: quick_diff 0.9573 -> 0.9197)
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                    10000, DAT_MapPropertiesState::instance.SEC_StartingResources[OpenSHC::Game::Resources::RT_GOLD],
                    (undefined*)&DAT_MapPropertiesState::instance
                        .SEC_StartingResources[OpenSHC::Game::Resources::RT_GOLD],
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                DAT_MenuModalComposition2::instance.textGroup = OpenSHC::DE::SHCDE::TEXT_SCENARIO;
                // "Starting Gold"
                DAT_MenuModalComposition2::instance.textIndex = 168;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 2, DAT_ButtonY::instance + 25);
                return;
            case 169:
                // the attacking force's partial pitch slider, on a siege map
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0, 100,
                    DAT_MapPropertiesState::instance.SEC_StartingResources[OpenSHC::Game::Resources::RT_PARTIALPITCH],
                    (undefined*)&DAT_MapPropertiesState::instance
                        .SEC_StartingResources[OpenSHC::Game::Resources::RT_PARTIALPITCH],
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                DAT_MenuModalComposition2::instance.textGroup = OpenSHC::DE::SHCDE::TEXT_SCENARIO;
                // "Starting Pitch"
                DAT_MenuModalComposition2::instance.textIndex = 169;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 2, DAT_ButtonY::instance + 25);
                return;
            case 171:
                // the building availability
                DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
                return;
            case 61:
                // the scenario's gold slider, with the extra options on
                if (!DAT_GameState::instance.mapAndTime.editScenarioExtraOptions) {
                    return;
                }
                DAT_CopyOfScenarioGold::instance = DAT_GameState::instance.mapAndTime.scenarioGold;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                    10000, DAT_CopyOfScenarioGold::instance, (undefined*)DAT_CopyOfScenarioGold::ptr,
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RestoreScenarioGold));
                DAT_MenuModalComposition2::instance.textGroup = OpenSHC::DE::SHCDE::TEXT_SCENARIO;
                // "Gold"
                DAT_MenuModalComposition2::instance.textIndex = 61;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 2, DAT_ButtonY::instance + 25);
                return;
            case 166:
                // the rations setting, 0 to 4 and round again, with the extra options on
                if (!DAT_GameState::instance.mapAndTime.editScenarioExtraOptions) {
                    return;
                }
                ++DAT_GameState::instance.mapAndTime.scenarioRationsSetting;
                if (DAT_GameState::instance.mapAndTime.scenarioRationsSetting >= 5) {
                    DAT_GameState::instance.mapAndTime.scenarioRationsSetting = 0;
                }
                return;
            case 167:
                // the tax setting, 0 to 9 and round again, with the extra options on
                if (!DAT_GameState::instance.mapAndTime.editScenarioExtraOptions) {
                    return;
                }
                ++DAT_GameState::instance.mapAndTime.scenarioTaxesSetting;
                if (DAT_GameState::instance.mapAndTime.scenarioTaxesSetting >= 10) {
                    DAT_GameState::instance.mapAndTime.scenarioTaxesSetting = 0;
                }
                return;
            }
        }

    }
}
}
