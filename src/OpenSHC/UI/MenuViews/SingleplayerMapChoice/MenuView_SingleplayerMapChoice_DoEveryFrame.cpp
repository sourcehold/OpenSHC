// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SingleplayerMapChoice.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/string-macros.hpp"

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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace SingleplayerMapChoice {

            // FUNCTION: STRONGHOLDCRUSADER 0x00448E90
            void MenuView_SingleplayerMapChoice_DoEveryFrame()
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                    DAT_TextureRenderCoreObject::ptr)(0,
                    (DAT_WindowAndDirectDraw::instance.resolutionX
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2,
                    (DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                        / 2);

                // the map table's background fades in (positive) or out (negative)
                if (DAT_00b960dc::instance != 0) {
                    DAT_GameCore::instance.hasMenuRenderedUnk = 1;
                    if ((int)DAT_00b960dc::instance < 0) {
                        DAT_ButtonBackgroundBlendStrength::instance = DAT_ButtonBackgroundBlendStrength::instance
                            - (timeGetTime() - DWORD_00b95b1c::instance) / 40;
                        if (DAT_ButtonBackgroundBlendStrength::instance <= 0) {
                            DAT_ButtonBackgroundBlendStrength::instance = 0;
                            DAT_00b960dc::instance = 0;
                        }
                    } else {
                        DAT_ButtonBackgroundBlendStrength::instance = DAT_ButtonBackgroundBlendStrength::instance
                            + (timeGetTime() - DWORD_00b95b1c::instance) / 40;
                        if (DAT_ButtonBackgroundBlendStrength::instance >= 32) {
                            DAT_ButtonBackgroundBlendStrength::instance = 32;
                            DAT_GameCore::instance.menuSwitchDelay = 0;
                        }
                    }
                }

                // list the maps of the chosen mission type, and select the one named in
                // standaloneFilename
                if (DAT_GameSynchronyState::instance.reparseMaps) {
                    DAT_GameSynchronyState::instance.reparseMaps = FALSE;
                    DAT_MouseState::instance.waitCursorToggle = 1;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                    MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::mapNames_syncLoadedMapNames, DAT_ResourceManager::ptr)();
                    int count = 0;
                    int selected = -1;
                    for (int id = 0; id < DAT_ResourceManager::instance.mapFileCounter; ++id) {
                        char fileName[1008]; // the size of the original's buffer
                        strcpy(fileName,
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(id));
                        // ".map"
                        strcat(fileName, S__MAP_005A2294);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapMetaByID, DAT_ResourceManager::ptr)(
                            id);
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
                            break;
                        }
                        if (DAT_GameCore::instance.mapType != 0
                            || DAT_MapPropertiesState::instance.scenarionMissionType != DAT_MapMissionType::instance
                            || DAT_GameCore::instance.savedMapLocked >= OpenSHC::Map::MLS_MISSION) {
                            continue;
                        }
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[count] = id;
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices2[count - 1] = id;
                        DAT_MenuTextInputState::instance.arrayOfMapEndInt2[id] = DAT_GameCore::instance.savedMapEndInt2;
                        if (MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                    DAT_ResourceManager::ptr)(id),
                                DAT_GameCore::instance.standaloneFilename)
                            == 0) {
                            selected = count;
                        }
                        ++count;
                    }
                    DAT_MouseState::instance.waitCursorToggle = 0;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber = count;
                    int scrollOffset = 0;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = scrollOffset;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
                    DAT_GameSynchronyState::instance.skirmishRelated1 = 0;
                    if (count != 0) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                        if (strlen(DAT_GameCore::instance.standaloneFilename) != 0 && selected >= 0) {
                            // scrolled so that the selected map is in the table's 13 rows
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = selected;
                            while (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected >= 13) {
                                --DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                                ++scrollOffset;
                                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = scrollOffset;
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

                // the map table's box, narrower for sieges
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                int const y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                int left = x + 280;
                if (DAT_MapMissionType::instance != 2) {
                    left = x + 140;
                }
                int const top = y + 253;
                int const right = x + 660;
                int const bottom = y + 534;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                if (DAT_00b960dc::instance != 0) {
                    return;
                }
                // its frame, the header line and the scroll bar's
                int const frameLeft = left - 1;
                int const frameRight = right + 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, top - 1, frameRight, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, bottom + 1, frameRight, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, top + 20, frameRight, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, top, frameLeft, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameRight, top, frameRight, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 19, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }

        }
    }
}
}
