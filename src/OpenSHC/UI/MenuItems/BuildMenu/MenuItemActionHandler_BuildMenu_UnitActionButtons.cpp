#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00446920
        void BuildMenu::MenuItemActionHandler_BuildMenu_UnitActionButtons(int param_1, ...)
        {
            int iVar1;
            uint uVar2;
            UnitType UVar3;
            int extraout_ECX;
            undefined4 uVar4;
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {}
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {}
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0) {}
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {}
                if (DAT_GameState::instance.mapAndTime.gameOver
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {}
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
            switch (param_1) {
            case 1:
                DAT_UnitsState::instance.unitControlsRelated = 1;
                DAT_UnitsState::instance.field5_0x14 = TRUE;
                DAT_TileMapState::instance.field162_0x5549c4 = 0;
                DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                return;
            case 2:
            case 6:
            case 7:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x15:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
                break;
            case 3:
                uVar4 = 3;
                DAT_UnitsState::instance.unitControlsRelated = TRUE;
                goto LAB_00446b3b;
            case 4:
                DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                DAT_UnitsState::instance.field5_0x14 = 4;
                DAT_UnitsState::instance.unitControlsRelated = 4;
                DAT_TileMapState::instance.field162_0x5549c4 = 0x20;
                DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                return;
            case 5:
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)();
                if (uVar2 != 0) {
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_UnitsState::instance.field5_0x14 = 0x14;
                    DAT_UnitsState::instance.unitControlsRelated = 0x14;
                    DAT_TileMapState::instance.field162_0x5549c4 = 0x20;
                    DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                }
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsTunnelersOnly, DAT_UnitsState::ptr)();
                if (iVar1 != 0) {
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                        OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION);
                }
                UVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedCatapultOrTrebuchetID, DAT_UnitsState::ptr)();
                if (((UVar3 != OpenSHC::Map::Units::UT_S_CATAPULT) && (UVar3 != OpenSHC::Map::Units::UT_S_TREBUCHET))
                    || (DAT_UnitsState::instance.units[uVar2]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        != 0)) {
                    DAT_UnitsState::instance.field5_0x14 = 5;
                    DAT_UnitsState::instance.unitControlsRelated = 5;
                    DAT_TileMapState::instance.field185_0x554a08 = 0xf;
                    DAT_TileMapState::instance.field162_0x5549c4 = 0x20;
                    DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                }
                break;
            case 8:
                DAT_UnitsState::instance.unitControlsRelated = 8;
                uVar4 = 8;
            LAB_00446b3b:
                DAT_UnitsState::instance.field5_0x14 = DAT_UnitsState::instance.unitControlsRelated;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, (undefined4)((int)(uVar4)));
                DAT_TileMapState::instance.field162_0x5549c4 = 0;
                DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                return;
            case 0x14:
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                if (uVar2 == 0) {
                    DAT_StopHandlingMenuItems::instance = 0;
                }
                DAT_UnitsState::instance.unitControlsRelated = 0x14;
                DAT_UnitsState::instance.field5_0x14 = 0x14;
                DAT_TileMapState::instance.field162_0x5549c4 = 0x20;
                DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                return;
            case 0x16:
                if (0 < *(int*)((int)DAT_GameState::instance.playerDataArray[0].isFoodTypeBanned + extraout_ECX + -8)) {
                    UVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                    uVar2
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedCatapultOrTrebuchetID,
                            DAT_UnitsState::ptr)();
                    if (((UVar3 == OpenSHC::Map::Units::UT_S_CATAPULT)
                            || (UVar3 == OpenSHC::Map::Units::UT_S_TREBUCHET))
                        && (DAT_UnitsState::instance.units[uVar2]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 0)) {
                        DAT_UnitsState::instance.field5_0x14 = 0x16;
                        DAT_UnitsState::instance.unitControlsRelated = 0x16;
                        DAT_TileMapState::instance.field185_0x554a08 = 0xf;
                        DAT_TileMapState::instance.field162_0x5549c4 = 0x20;
                        DAT_TileMapState::instance.field163_0x5549c8 = 0x6b;
                    }
                }
                break;
            case 0x1e:
                UVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar3 == ((UnitType)0xffffffff)) {
                    DAT_StopHandlingMenuItems::instance = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x1e);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::playPatrolCommandSpeech, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID);
                return;
            case 0x1f:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x1f);
                break;
            default:
                break;
            }
        }

    }
}
}
