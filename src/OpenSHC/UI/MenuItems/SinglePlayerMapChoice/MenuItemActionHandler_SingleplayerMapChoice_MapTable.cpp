#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
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
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00442C30
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTable(int param_1, ...)
        {
            char cVar1;
            uint uVar2;
            DWORD _currentTime;
            char* pcVar3;
            char* puVar3;
            int* piVar4;
            char* pcVar5;
            int iVar6;
            int yPos;
            int maxWidth;
            BGR24 color;
            int blendStrength;
            int modeUnk;
            char local_3f4[1008];
            char* puVar2;
            uVar2 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber
                <= DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1)
                goto LAB_00442f24;
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = param_1;
            _currentTime = timeGetTime();
            if ((DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    == DAT_MenuTextInputState::instance.field38_0x8c)
                && ((int)(_currentTime - DAT_MenuTextInputState::instance.field39_0x90) < 500)) {
                DAT_MouseState::instance.waitCursorToggle = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                        MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands)(0x41);
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                DAT_MenuTextInputState::instance.field38_0x8c
                    = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                DAT_MenuTextInputState::instance.field39_0x90 = _currentTime;
            }
            pcVar3 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1]);
            pcVar5 = local_3f4;
            do {
                cVar1 = *pcVar3;
                *pcVar5 = cVar1;
                pcVar3 = pcVar3 + 1;
                pcVar5 = pcVar5 + 1;
            } while (cVar1 != '\0');
            puVar2 = (local_3f4 - 1);
            do {
                puVar3 = puVar2;
                puVar2 = puVar3 + 1;
            } while (puVar3[1] != '\0');
            strcpy(puVar3 + 1, ".map");
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, (char const*)((int)(local_3f4)));
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
            DAT_00b95b74::instance = 0;
            DAT_00b960f4::instance = 0;
            if (DAT_GameCore::instance.mapDescUseStringTable == 0) {
                modeUnk = 1;
                blendStrength = 0;
                color = 0;
                maxWidth = 0x19d;
                yPos = 0;
                iVar6 = 0;
                pcVar5 = DAT_GameCore::instance.mapDescription;
            LAB_00442d94:
                DAT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(
                    pcVar5, iVar6, yPos, maxWidth, color, blendStrength, modeUnk);
            } else if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
                modeUnk = 1;
                blendStrength = 0;
                color = 0;
                maxWidth = 0x19d;
                yPos = 0;
                iVar6 = 0;
                pcVar5 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.mapDescUseStringTableIndex);
                goto LAB_00442d94;
            }
            if (DAT_MapMissionType::instance == 2) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ClearSiegeInformationArray2)();
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray, 0x423);
                piVar4 = DAT_SiegeInformationArray::instance;
                if (DAT_GameCore::instance.mapU4Int1_2 == 0) {
                    do {
                        if (0 < *piVar4)
                            goto LAB_00442f24;
                        piVar4 = piVar4 + 1;
                    } while ((int)piVar4 < 0xb95b1c);
                    iVar6 = 0;
                    do {
                        *(int*)((int)DAT_SiegeInformationArray::instance + iVar6)
                            = (*(int*)((int)DAT_MapPropertiesState::instance.SEC_StartingResources + iVar6 + 100) * 7)
                            / 10;
                        iVar6 = iVar6 + 4;
                    } while (iVar6 < 0x50);
                    DAT_SiegeInformationArray::instance[10]
                        = (DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount * 7) / 10;
                    DAT_SiegeRemainingPoints::instance = 0;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
                    iVar6 = DAT_GameState::instance.mapAndTime.difficulty;
                } else {
                    do {
                        if (0 < *piVar4)
                            goto LAB_00442e64;
                        piVar4 = piVar4 + 1;
                    } while ((int)piVar4 < 0xb95b1c);
                    DAT_SiegeInformationArray::instance[0] = 0;
                    DAT_SiegeInformationArray::instance[1] = 0;
                    DAT_SiegeInformationArray::instance[2] = 0;
                    DAT_SiegeInformationArray::instance[3] = 0;
                    DAT_SiegeInformationArray::instance[4] = 0;
                    DAT_SiegeInformationArray::instance[5] = 0;
                    DAT_SiegeInformationArray::instance[6] = 0;
                    DAT_SiegeInformationArray::instance[7] = 0;
                    DAT_SiegeInformationArray::instance[8] = 0;
                    DAT_SiegeInformationArray::instance[9] = 0;
                    DAT_SiegeInformationArray::instance[10] = 0;
                    DAT_SiegeInformationArray::instance[0xb] = 0;
                    DAT_SiegeInformationArray::instance[0xc] = 0;
                    DAT_SiegeInformationArray::instance[0xd] = 0;
                    DAT_SiegeInformationArray::instance[0xe] = 0;
                    DAT_SiegeInformationArray::instance[0xf] = 0;
                    DAT_SiegeInformationArray::instance[0x10] = 0;
                    DAT_SiegeInformationArray::instance[0x11] = 0;
                    DAT_SiegeInformationArray::instance[0x12] = 0;
                    DAT_SiegeInformationArray::instance[0x13] = 0;
                    DAT_SiegeInformationArray::instance[0x14] = 0;
                    DAT_SiegeRemainingPoints::instance = 2000;
                LAB_00442e64:
                    DAT_SH1_SiegeAdvancedMode::instance = 1;
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                    DAT_GameState::instance.mapAndTime.difficulty = 1;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeUnitsComputation)(1);
                    iVar6 = 1;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(iVar6);
            }
        LAB_00442f24:;
        }

    }
}
}
