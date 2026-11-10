// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00442C30
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTable(int row, ...)
        {
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row
                >= DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = row;
            DWORD const currentTime = timeGetTime();
            // a second click on the same map within 500 ms starts the game (button 65 of the map choice menu)
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    == DAT_MenuTextInputState::instance.lastClickedListIndex
                && (int)(currentTime - DAT_MenuTextInputState::instance.lastListClickTime) < 500) {
                DAT_MouseState::instance.waitCursorToggle = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                        MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands)(65);
            }
            if (DAT_MouseState::instance.leftClickStart) {
                DAT_MenuTextInputState::instance.lastClickedListIndex
                    = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                DAT_MenuTextInputState::instance.lastListClickTime = currentTime;
            }
            char fileName[1008];
            strcpy(fileName,
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset]));
            // ".map"
            strcat(fileName, S__MAP_005A2294);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, fileName);
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
            // the description's height and scroll position: mode 1 measures the text 413 pixels wide without drawing
            INT_00b95b74::instance = 0;
            DAT_00b960f4::instance = 0;
            if (DAT_GameCore::instance.mapDescUseStringTable == 0) {
                INT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                    DAT_GameCore::instance.mapDescription, 0, 0, 413, 0, 0, 1);
            } else if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
                INT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.mapDescUseStringTableIndex),
                    0, 0, 413, 0, 0, 1);
            }
            // map type 2 is siege (button 68)
            if (DAT_MapMissionType::instance != 2) {
                return;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ClearSiegeInformationArray2)();
            // section 1059 holds the map's siege army
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
                DAT_MapDefinedData::instance.MapSectionAddressArray, 1059);
            // the siege army's 21 unit counts as one array (nested [7][3] searches: quick_diff 0.9807 -> 0.8696)
            int* const siegeUnits = &DAT_SiegeInformationArray::instance[0][0];
            if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                // an army with no units yet starts empty, with 2000 points
                BOOLEnum hasUnits = FALSE;
                for (int unit = 0; unit < 21; ++unit) {
                    if (siegeUnits[unit] > 0) {
                        hasUnits = TRUE;
                        break;
                    }
                }
                if (!hasUnits) {
                    for (int unit = 0; unit < 21; ++unit) {
                        siegeUnits[unit] = 0;
                    }
                    DAT_SiegeRemainingPoints::instance = 2000;
                }
                // advanced mode, player slot 2, difficulty 1
                DAT_SH1_SiegeAdvancedMode::instance = 1;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                DAT_GameState::instance.mapAndTime.difficulty = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(1);
                return;
            }
            // an army with no units yet gets 70% of the map's own, with no points left
            for (int unit = 0; unit < 21; ++unit) {
                if (siegeUnits[unit] > 0) {
                    return;
                }
            }
            // SEC_SiegeInformation (SiegeUnitCounts) is read as 20 ints
            int const* const mapUnits = (int const*)&DAT_MapPropertiesState::instance.SEC_SiegeInformation;
            for (int unit = 0; unit < 20; ++unit) {
                siegeUnits[unit] = mapUnits[unit] * 7 / 10;
            }
            // slot 10 takes 70% of the tunnelers, over the loop's value
            siegeUnits[10] = DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount * 7 / 10;
            DAT_SiegeRemainingPoints::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(
                DAT_GameState::instance.mapAndTime.difficulty);
        }

    }
}
}
