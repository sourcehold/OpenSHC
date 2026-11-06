#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00440280
            void MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu(int param_1, ...)
            {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType,
                    DAT_BuildingsState::ptr)((Map::Buildings::BuildingType)DAT_BuildingsState::instance
                                                 .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                                 .buildingType,
                    1, DAT_GameSynchronyState::instance.currentPlayerSlotID);
                if (DAT_MouseState::instance.rightClickStart) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        Enums::MVT_BUILD_MENU, 0);
                    return;
                }
                if (!DAT_ViewportRenderState::instance.viewportState.field_0x0) {
                    return;
                }
                // The menu stays while the building's assembly point is being placed.
                if (DAT_GameCore::instance.activeMenuTab.tabType == Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                    if (DAT_TileMapState::instance.currentMapperCommand >= Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1
                        && DAT_TileMapState::instance.currentMapperCommand
                            <= Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7) {
                        return;
                    }
                } else if (DAT_GameCore::instance.activeMenuTab.tabType == Enums::BASMTT_MERCENARYPOST) {
                    if (DAT_TileMapState::instance.currentMapperCommand >= Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1
                        && DAT_TileMapState::instance.currentMapperCommand
                            <= Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7) {
                        return;
                    }
                } else if (DAT_GameCore::instance.activeMenuTab.tabType == Enums::BASMTT_ENGINEERSGUILD) {
                    if (DAT_TileMapState::instance.currentMapperCommand >= Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE1
                        && DAT_TileMapState::instance.currentMapperCommand
                            <= Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE2) {
                        return;
                    }
                } else if (DAT_GameCore::instance.activeMenuTab.tabType == Enums::BASMTT_TUNNELERSGUILD) {
                    if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1) {
                        return;
                    }
                } else if (DAT_GameCore::instance.activeMenuTab.tabType == Enums::BASMTT_CATHEDRAL) {
                    if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1) {
                        return;
                    }
                }
                if (DAT_MouseState::instance.leftClickStart) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        Enums::MVT_BUILD_MENU, 100);
                }
            }

        }
    }
}
}
