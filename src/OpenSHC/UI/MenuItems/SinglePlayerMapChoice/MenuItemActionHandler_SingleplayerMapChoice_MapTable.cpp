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
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x00442C30
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTable(int param_1, ...)
        {
            int* piVar4;
            // The original copies the name and appends the extension inline, so the macros are used here.
            char fileName[1008]; // the size of the original's buffer
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                >= DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = param_1;
            DWORD _currentTime = timeGetTime();
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    == DAT_MenuTextInputState::instance.lastClickedListIndex
                && (int)(_currentTime - DAT_MenuTextInputState::instance.lastListClickTime) < 500) {
                DAT_MouseState::instance.waitCursorToggle = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                        MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands)(65);
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                DAT_MenuTextInputState::instance.lastClickedListIndex
                    = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                DAT_MenuTextInputState::instance.lastListClickTime = _currentTime;
            }
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
            if (DAT_MapMissionType::instance == 2) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ClearSiegeInformationArray2)();
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray, 1059);
                piVar4 = &DAT_SiegeInformationArray::instance[0][0];
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    for (; (int)piVar4 < (int)&DAT_SiegeInformationArray::instance + 84; ++piVar4) {
                        if (*piVar4 > 0) {
                            break;
                        }
                    }
                    if (piVar4 == &DAT_SiegeInformationArray::instance[0][0] + 21) {
                        for (int i = 0; i < 21; ++i) {
                            (&DAT_SiegeInformationArray::instance[0][0])[i] = 0;
                        }
                        DAT_SiegeRemainingPoints::instance = 2000;
                    }
                    DAT_SH1_SiegeAdvancedMode::instance = 1;
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                    DAT_GameState::instance.mapAndTime.difficulty = 1;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(1);
                } else {
                    for (; (int)piVar4 < (int)&DAT_SiegeInformationArray::instance + 84; ++piVar4) {
                        if (*piVar4 > 0) {
                            return;
                        }
                    }
                    // SEC_SiegeInformation (SiegeUnitCounts) is read as 20 ints
                    int const* const siegeInformation
                        = (int const*)&DAT_MapPropertiesState::instance.SEC_SiegeInformation;
                    for (int i = 0; i < 20; ++i) {
                        (&DAT_SiegeInformationArray::instance[0][0])[i] = siegeInformation[i] * 7 / 10;
                    }
                    DAT_SiegeInformationArray::instance[3][1]
                        = (DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount * 7) / 10;
                    DAT_SiegeRemainingPoints::instance = 0;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(
                        DAT_GameState::instance.mapAndTime.difficulty);
                }
            }
        }

    }
}
}
