#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Commands/MappersEnumInt.hpp"
#include "OpenSHC/DE/SHCDE/eInBuildingModes.hpp"
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

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Commands::MappersEnumInt;
        using OpenSHC::DE::SHCDE::eInBuildingModes;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          WARNING: Enum "MappersEnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00440280
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu(int param_1, ...)
        {
            bool bVar1;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType,
                DAT_BuildingsState::ptr)((OpenSHC::Map::Buildings::BuildingType)(short)DAT_BuildingsState::instance
                                             .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                             .buildingType,
                1, (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID));
            if (DAT_MouseState::instance.rightClickStart != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            }
            if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0) {}
            if (DAT_GameCore::instance.activeMenuTab.inBuildingTab == OpenSHC::DE::SHCDE::IBM_INSIDE_BARRACKS) {
                if ((0x14b < (int)DAT_TileMapState::instance.currentMapperCommand)
                    && ((int)DAT_TileMapState::instance.currentMapperCommand < 0x153)) {}
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                if ((0x167 < (int)DAT_TileMapState::instance.currentMapperCommand)
                    && ((int)DAT_TileMapState::instance.currentMapperCommand < 0x16f)) {}
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD) {
                if ((0x16e < (int)DAT_TileMapState::instance.currentMapperCommand)
                    && ((int)DAT_TileMapState::instance.currentMapperCommand < 0x171)) {}
            } else {
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD) {
                    bVar1 = DAT_TileMapState::instance.currentMapperCommand
                        == OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1;
                } else {
                    if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_CATHEDRAL)
                        goto LAB_00440340;
                    bVar1 = DAT_TileMapState::instance.currentMapperCommand
                        == OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1;
                }
                if (bVar1) {}
            }
        LAB_00440340:
            if (DAT_MouseState::instance.leftClickStart != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 100);
            }
        }

    }
}
}
