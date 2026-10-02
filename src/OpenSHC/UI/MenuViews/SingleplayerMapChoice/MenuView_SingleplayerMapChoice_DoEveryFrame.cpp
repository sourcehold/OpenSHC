#include "../SingleplayerMapChoice.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::IO::FileResourceType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00448E90
        void SingleplayerMapChoice::MenuView_SingleplayerMapChoice_DoEveryFrame()
        {
            int top;
            char cVar1;
            DWORD DVar2;
            char* pcVar3;
            int iVar4;
            int iVar5;
            char* pcVar6;
            int iVar7;
            dword id;
            int iVar8;
            int bottom;
            undefined4 local_3f8;
            char local_3f4[4];
            char local_3f0[1004];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_3f8;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if (DAT_00b960dc::instance != 0) {
                DAT_GameCore::instance.hasMenuRenderedUnk = 1;
                if (DAT_00b960dc::instance < 0) {
                    DVar2 = timeGetTime();
                    DAT_ButtonBackgroundBlendStrength::instance
                        = DAT_ButtonBackgroundBlendStrength::instance - (DVar2 - DWORD_00b95b1c::instance) / 0x28;
                    if (DAT_ButtonBackgroundBlendStrength::instance < 1) {
                        DAT_ButtonBackgroundBlendStrength::instance = 0;
                        DAT_00b960dc::instance = 0;
                    }
                } else {
                    DVar2 = timeGetTime();
                    DAT_ButtonBackgroundBlendStrength::instance
                        = DAT_ButtonBackgroundBlendStrength::instance + (DVar2 - DWORD_00b95b1c::instance) / 0x28;
                    if (0x1f < DAT_ButtonBackgroundBlendStrength::instance) {
                        DAT_ButtonBackgroundBlendStrength::instance = 0x20;
                        DAT_GameCore::instance.menuSwitchDelay = 0;
                    }
                }
            }
            if (DAT_GameSynchronyState::instance.reparseMaps != FALSE) {
                DAT_GameSynchronyState::instance.reparseMaps = FALSE;
                DAT_MouseState::instance.waitCursorToggle = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::mapNames_syncLoadedMapNames, DAT_ResourceManager::ptr)();
                iVar8 = 0;
                iVar7 = -1;
                id = 0;
                if (0 < DAT_ResourceManager::instance.mapFileCounter) {
                    do {
                        pcVar3 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(id);
                        pcVar6 = local_3f4;
                        do {
                            cVar1 = *pcVar3;
                            *pcVar6 = cVar1;
                            pcVar3 = pcVar3 + 1;
                            pcVar6 = pcVar6 + 1;
                        } while (cVar1 != '\0');
                        pcVar6 = (char*)((int)&local_3f8 + 3);
                        do {
                            pcVar3 = pcVar6;
                            pcVar6 = pcVar3 + 1;
                        } while (pcVar3[1] != '\0');
                        strcpy(pcVar3 + 1, ".map");
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, (char const*)((int)(local_3f4)));
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapMetaByID, DAT_ResourceManager::ptr)(
                            id);
                        iVar4 = DAT_GameCore::instance.savedMapEndInt2;
                        switch (DAT_MapPropertiesState::instance.scenarioMissionSiegeOrInvasion) {
                        case OpenSHC::Map::MT_SIEGE:
                            DAT_MapPropertiesState::instance.scenarionMissionType = 2;
                            break;
                        case OpenSHC::Map::MT_INVASION:
                            DAT_MapPropertiesState::instance.scenarionMissionType = 3;
                            break;
                        case OpenSHC::Map::MT_ECONOMIC:
                            DAT_MapPropertiesState::instance.scenarionMissionType = 1;
                            break;
                        case OpenSHC::Map::MT_JUST_BUILD:
                            DAT_MapPropertiesState::instance.scenarionMissionType = 0;
                        }
                        if (((DAT_GameCore::instance.mapType == 0)
                                && (DAT_MapPropertiesState::instance.scenarionMissionType
                                    == DAT_MapMissionType::instance))
                            && ((int)DAT_GameCore::instance.savedMapLocked < 2)) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar8 + -1] = id;
                            pcVar3 = DAT_GameCore::instance.standaloneFilename;
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar8 + 499] = id;
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2[id] = iVar4;
                            pcVar6 = MACRO_CALL_MEMBER(
                                OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(id);
                            iVar4 = MACRO_CALL(OpenSHC::OS_Func::__stricmp)(pcVar6, (char const*)((int)(pcVar3)));
                            if (iVar4 == 0) {
                                iVar7 = iVar8;
                            }
                            iVar8 = iVar8 + 1;
                        }
                        id = id + 1;
                    } while ((int)id < DAT_ResourceManager::instance.mapFileCounter);
                }
                DAT_MouseState::instance.waitCursorToggle = 0;
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
                DAT_GameSynchronyState::instance.skirmishRelated1 = 0;
                DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber = iVar8;
                if (iVar8 != 0) {
                    pcVar6 = DAT_GameCore::instance.standaloneFilename;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                    do {
                        cVar1 = *pcVar6;
                        pcVar6 = pcVar6 + 1;
                    } while (cVar1 != '\0');
                    if ((pcVar6 != DAT_GameCore::instance.standaloneFilename + 1) && (iVar8 = 0, -1 < iVar7)) {
                        while (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = iVar7,
                            DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar8,
                            0xc < DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                            iVar8 = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                            iVar7 = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1;
                        }
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                    DAT_GameSynchronyState::instance.skirmishRelated1 = 1;
                    DAT_GameCore::instance.standaloneFilename[0] = '\0';
                }
                DWORD_00b95b1c::instance = timeGetTime();
            }
            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            iVar8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            iVar7 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x118;
            if (DAT_MapMissionType::instance != 2) {
                iVar7 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x8c;
            }
            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
            top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xfd;
            local_3f8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x294;
            bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x216;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(iVar7, top, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x280,
                bottom, ((int)(iVar5 + (iVar5 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            if (DAT_00b960dc::instance == 0) {
                iVar8 = iVar8 + 0x295;
                iVar7 = iVar7 + -1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar7, iVar4 + 0xfc, iVar8, iVar4 + 0xfc,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar7, iVar4 + 0x217, iVar8, iVar4 + 0x217,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar7, iVar4 + 0x111, iVar8, iVar4 + 0x111,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar7, top, iVar7, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar8, top, iVar8, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    local_3f8 + -0x14, top, (int)((int)(local_3f8 + -0x14)), bottom,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    local_3f8 + -0x13, iVar4 + 0x202, (int)((int)(local_3f8)), iVar4 + 0x202,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            };
            return;
        }

    }
}
}
