#include "../NewMapMapsize.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::MapLockState;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042F940
        void NewMapMapsize::MenuItemActionHandler_NewMapMapsize_Buttons(int param_1, ...)
        {
            int iVar1;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                iVar1 = 400;
                if (0 < param_1) {
                    if (param_1 < 5) {
                        if (param_1 == 1) {
                            iVar1 = 0xa0;
                        } else if (param_1 == 2) {
                            iVar1 = 200;
                        } else if (param_1 == 3) {
                            iVar1 = 300;
                        }
                        DAT_TileMapState::instance.mapSize = iVar1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(iVar1);
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              updatePathLinkageLayerForEachBuildingAtEachTile,
                            DAT_PathFindingState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap,
                            DAT_PathFindingState::ptr)(1);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
                            DAT_BuildingsState::ptr)();
                        DAT_TileMapState::instance.forceUpdateMacroLayerFlag = 1;
                        DAT_TileMapState::instance.field68_0x55487c = 200;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameStateStructures_Func::processGameTick, DAT_GameState::ptr)();
                        iVar1 = 0;
                        do {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(iVar1);
                            iVar1 = iVar1 + 1;
                        } while (iVar1 < 0x28);
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize,
                            DAT_MinimapViewState::ptr)(0, 100);
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize,
                            DAT_MinimapViewState::ptr)(0, 100);
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                            DAT_ViewportRenderState::ptr)();
                        DAT_GameCore::instance.descriptionUseStringTable = 0;
                        DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_EDITABLE;
                        DAT_GameCore::instance.temporaryTextBufferOfSize1000[0] = '\0';
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                        DAT_GameCore::instance.field115_0x1d98 = 1;
                    } else if (param_1 == 7) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                    }
                }
            }
        }

    }
}
}
