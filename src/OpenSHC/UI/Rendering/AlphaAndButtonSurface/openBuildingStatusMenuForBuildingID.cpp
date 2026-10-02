#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::UI::Enums::MenuViewType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00463310
        BOOLEnum AlphaAndButtonSurface::openBuildingStatusMenuForBuildingID(int buildingID)
        {
            short sVar1;
            int iVar2;
            int iVar3;
            dword dVar4;
            if ((buildingID < 1) || (DAT_GameCore::instance.gamePausedLogical != 0)) {
                return FALSE;
            }
            sVar1 = DAT_BuildingsState::instance.buildings[buildingID].owner;
            dVar4 = 1;
            if (sVar1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            LAB_004633b5:
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType,
                    DAT_BuildingsState::ptr)(
                    (OpenSHC::Map::Buildings::BuildingType)(DAT_BuildingsState::instance.buildings[buildingID]
                            .buildingType),
                    1,
                    (int)((int)((
                        OpenSHC::Map::Buildings::BuildingType)DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                iVar3 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_HOVEL:
                case OpenSHC::Map::Buildings::BT_HOUSE:
                    dVar4 = 5;
                    break;
                case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                    dVar4 = 6;
                    break;
                case OpenSHC::Map::Buildings::BT_OXTETHER:
                    dVar4 = 7;
                    break;
                case OpenSHC::Map::Buildings::BT_IRONMINE:
                    dVar4 = 8;
                    break;
                case OpenSHC::Map::Buildings::BT_PITCHRIG:
                    dVar4 = 9;
                    break;
                case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                    dVar4 = 10;
                    break;
                case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    dVar4 = 0x2c;
                    break;
                case OpenSHC::Map::Buildings::BT_BARRACKS:
                    break;
                case OpenSHC::Map::Buildings::BT_STOCKPILE:
                    dVar4 = 0xb;
                    break;
                case OpenSHC::Map::Buildings::BT_ARMORY:
                    dVar4 = 0xc;
                    break;
                case OpenSHC::Map::Buildings::BT_FLETCHER:
                    dVar4 = 0xd;
                    break;
                case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                    dVar4 = 0xe;
                    break;
                case OpenSHC::Map::Buildings::BT_POLETURNER:
                    dVar4 = 0xf;
                    break;
                case OpenSHC::Map::Buildings::BT_ARMOURER:
                    dVar4 = 0x10;
                    break;
                case OpenSHC::Map::Buildings::BT_TANNER:
                    dVar4 = 0x11;
                    break;
                case OpenSHC::Map::Buildings::BT_BAKERY:
                    dVar4 = 0x12;
                    break;
                case OpenSHC::Map::Buildings::BT_BREWERY:
                    dVar4 = 0x13;
                    break;
                case OpenSHC::Map::Buildings::BT_GRANARY:
                    iVar2
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .rationsSetting;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .rationsSetting2 = iVar2;
                    dVar4 = 4;
                    DAT_GameState::instance.playerDataArray[iVar3].rationsSetting3 = iVar2;
                    break;
                case OpenSHC::Map::Buildings::BT_QUARRY:
                    dVar4 = 0x14;
                    break;
                case OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE:
                    dVar4 = 0x15;
                    break;
                case OpenSHC::Map::Buildings::BT_INN:
                    dVar4 = 3;
                    break;
                case OpenSHC::Map::Buildings::BT_APOTHECARY:
                    dVar4 = 0x16;
                    break;
                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    dVar4 = 0x17;
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    dVar4 = 0x18;
                    break;
                case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                    dVar4 = 0x19;
                    break;
                case OpenSHC::Map::Buildings::BT_WELL:
                    dVar4 = 0x1a;
                    break;
                case OpenSHC::Map::Buildings::BT_OILSMELTER:
                    dVar4 = 0x1b;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETENT:
                    dVar4 = 0x1c;
                    break;
                case OpenSHC::Map::Buildings::BT_WHEATFARM:
                    dVar4 = 0x1d;
                    break;
                case OpenSHC::Map::Buildings::BT_HOPFARM:
                    dVar4 = 0x1e;
                    break;
                case OpenSHC::Map::Buildings::BT_APPLEFARM:
                    dVar4 = 0x1f;
                    break;
                case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                    dVar4 = 0x20;
                    break;
                case OpenSHC::Map::Buildings::BT_MILL:
                    dVar4 = 0x21;
                    break;
                case OpenSHC::Map::Buildings::BT_STABLES:
                    dVar4 = 0x22;
                    break;
                case OpenSHC::Map::Buildings::BT_CHAPEL:
                case OpenSHC::Map::Buildings::BT_CHURCH:
                    dVar4 = 0x23;
                    break;
                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    dVar4 = 0x60;
                    break;
                default:
                switchD_004633df_caseD_27:
                    return FALSE;
                case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                case OpenSHC::Map::Buildings::BT_STONEKEEP:
                case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
                case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
                case OpenSHC::Map::Buildings::BT_KEEPDOOR:
                    iVar2
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSetting;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSetting2 = iVar2;
                    dVar4 = 2;
                    DAT_GameState::instance.playerDataArray[iVar3].taxesSliderUI = iVar2;
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    if (DAT_BuildingsState::instance.buildings[buildingID].field241_0x2c6 != 0) {
                        return FALSE;
                    }
                    dVar4 = 0x24;
                    break;
                case OpenSHC::Map::Buildings::BT_WOODGATE2:
                    dVar4 = 0x26;
                    break;
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].x)),
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)),
                        (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight)),
                        OpenSHC::Map::Buildings::BT_GATEHOUSELARGE, 0);
                    if (((iVar3 != 0)
                            || (iVar3 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                                    DAT_BuildingsState::ptr)(
                                    (int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                                    (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].x)),
                                    (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)),
                                    (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight)),
                                    OpenSHC::Map::Buildings::BT_GATEHOUSESMALL, 0),
                                iVar3 != 0))
                        && (DAT_BuildingsState::instance.buildings[iVar3].field241_0x2c6 != 0)) {
                        return FALSE;
                    }
                    dVar4 = 0x25;
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNEL:
                    dVar4 = 0x27;
                    break;
                case OpenSHC::Map::Buildings::BT_CAMPFIRE:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                    dVar4 = 0x34;
                    break;
                case OpenSHC::Map::Buildings::BT_SIGNPOST:
                    dVar4 = 0x29;
                    break;
                case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
                    dVar4 = 0x5f;
                    break;
                case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                    dVar4 = 0x2b;
                    break;
                case OpenSHC::Map::Buildings::BT_GALLOWS:
                    dVar4 = 0x2f;
                    break;
                case OpenSHC::Map::Buildings::BT_STOCKS:
                    dVar4 = 0x30;
                    break;
                case OpenSHC::Map::Buildings::BT_WITCHHOIST:
                    dVar4 = 0x31;
                    break;
                case OpenSHC::Map::Buildings::BT_MAYPOLE:
                    dVar4 = 0x32;
                    break;
                case OpenSHC::Map::Buildings::BT_GARDEN:
                    dVar4 = 0x33;
                    break;
                case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                    dVar4 = 0x2a;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                switchD_004633df_caseD_45:
                    DAT_BuildingsState::instance.field28_0x18e05c = buildingID;
                    DAT_BuildingsState::instance.field29_0x18e060
                        = DAT_BuildingsState::instance.buildings[buildingID].uid;
                    return FALSE;
                case OpenSHC::Map::Buildings::BT_WATERPOT:
                    dVar4 = 0x28;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                case OpenSHC::Map::Buildings::BT_TOWER2:
                case OpenSHC::Map::Buildings::BT_TOWER3:
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    dVar4 = 0x2e;
                    break;
                case OpenSHC::Map::Buildings::BT_CATAPULT:
                    dVar4 = 0x3a;
                    break;
                case OpenSHC::Map::Buildings::BT_TREBUCHET:
                    dVar4 = 0x3b;
                    break;
                case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
                    dVar4 = 0x3c;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETOWER:
                    dVar4 = 0x3d;
                    break;
                case OpenSHC::Map::Buildings::BT_SHIELD:
                    dVar4 = 0x3e;
                    break;
                case OpenSHC::Map::Buildings::BT_CESSPIT:
                    dVar4 = 0x50;
                    break;
                case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
                    dVar4 = 0x51;
                    break;
                case OpenSHC::Map::Buildings::BT_GIBBET:
                    dVar4 = 0x52;
                    break;
                case OpenSHC::Map::Buildings::BT_DUNGEON:
                    dVar4 = 0x53;
                    break;
                case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
                    dVar4 = 0x54;
                    break;
                case OpenSHC::Map::Buildings::BT_RACKFLOGGING:
                    dVar4 = 0x55;
                    break;
                case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                    dVar4 = 0x56;
                    break;
                case OpenSHC::Map::Buildings::BT_DUNKINGSTOOL:
                    dVar4 = 0x57;
                    break;
                case OpenSHC::Map::Buildings::BT_DOGCAGE:
                    dVar4 = 0x58;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .releaseDogsFlag
                        = DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs;
                    break;
                case OpenSHC::Map::Buildings::BT_STATUE:
                    goto switchD_004633df_caseD_64;
                case OpenSHC::Map::Buildings::BT_SHRINE:
                    dVar4 = 0x5a;
                    break;
                case OpenSHC::Map::Buildings::BT_BEEHIVE:
                    dVar4 = 0x5b;
                    break;
                case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
                    dVar4 = 0x5c;
                    break;
                case OpenSHC::Map::Buildings::BT_BEARCAVE:
                    dVar4 = 0x5e;
                    break;
                case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                            DAT_TextEditorState::ptr)();
                    LAB_0046340c:
                        DAT_BuildingsState::instance.field28_0x18e05c = buildingID;
                        DAT_BuildingsState::instance.field29_0x18e060
                            = DAT_BuildingsState::instance.buildings[buildingID].uid;
                        return FALSE;
                    }
                    dVar4 = 0x2d;
                }
            } else {
                if ((sVar1 != 0)
                    || (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        != OpenSHC::Map::Buildings::BT_STATUE)) {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case OpenSHC::Map::Buildings::BT_HOVEL:
                    case OpenSHC::Map::Buildings::BT_HOUSE:
                    case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                    case OpenSHC::Map::Buildings::BT_OXTETHER:
                    case OpenSHC::Map::Buildings::BT_IRONMINE:
                    case OpenSHC::Map::Buildings::BT_PITCHRIG:
                    case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                    case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    case OpenSHC::Map::Buildings::BT_BARRACKS:
                    case OpenSHC::Map::Buildings::BT_STOCKPILE:
                    case OpenSHC::Map::Buildings::BT_ARMORY:
                    case OpenSHC::Map::Buildings::BT_FLETCHER:
                    case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                    case OpenSHC::Map::Buildings::BT_POLETURNER:
                    case OpenSHC::Map::Buildings::BT_ARMOURER:
                    case OpenSHC::Map::Buildings::BT_TANNER:
                    case OpenSHC::Map::Buildings::BT_BAKERY:
                    case OpenSHC::Map::Buildings::BT_BREWERY:
                    case OpenSHC::Map::Buildings::BT_GRANARY:
                    case OpenSHC::Map::Buildings::BT_QUARRY:
                    case OpenSHC::Map::Buildings::BT_INN:
                    case OpenSHC::Map::Buildings::BT_APOTHECARY:
                    case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                    case OpenSHC::Map::Buildings::BT_WELL:
                    case OpenSHC::Map::Buildings::BT_OILSMELTER:
                    case OpenSHC::Map::Buildings::BT_SIEGETENT:
                    case OpenSHC::Map::Buildings::BT_WHEATFARM:
                    case OpenSHC::Map::Buildings::BT_HOPFARM:
                    case OpenSHC::Map::Buildings::BT_APPLEFARM:
                    case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                    case OpenSHC::Map::Buildings::BT_MILL:
                    case OpenSHC::Map::Buildings::BT_STABLES:
                    case OpenSHC::Map::Buildings::BT_CHAPEL:
                    case OpenSHC::Map::Buildings::BT_CHURCH:
                    case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    case OpenSHC::Map::Buildings::BT_WOODGATE2:
                    case OpenSHC::Map::Buildings::BT_TUNNEL:
                    case OpenSHC::Map::Buildings::BT_GALLOWS:
                    case OpenSHC::Map::Buildings::BT_STOCKS:
                    case OpenSHC::Map::Buildings::BT_WITCHHOIST:
                    case OpenSHC::Map::Buildings::BT_MAYPOLE:
                    case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                    case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                    case OpenSHC::Map::Buildings::BT_WATERPOT:
                    case OpenSHC::Map::Buildings::BT_CESSPIT:
                    case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
                    case OpenSHC::Map::Buildings::BT_GIBBET:
                    case OpenSHC::Map::Buildings::BT_DUNGEON:
                    case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
                    case OpenSHC::Map::Buildings::BT_RACKFLOGGING:
                    case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                    case OpenSHC::Map::Buildings::BT_DUNKINGSTOOL:
                    case OpenSHC::Map::Buildings::BT_DOGCAGE:
                    case OpenSHC::Map::Buildings::BT_STATUE:
                    case OpenSHC::Map::Buildings::BT_SHRINE:
                    case OpenSHC::Map::Buildings::BT_BEEHIVE:
                    case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
                    case OpenSHC::Map::Buildings::BT_BEARCAVE:
                        goto switchD_004633df_caseD_45;
                    default:
                        goto switchD_004633df_caseD_27;
                    case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                    case OpenSHC::Map::Buildings::BT_TOWER1:
                    case OpenSHC::Map::Buildings::BT_TOWER2:
                    case OpenSHC::Map::Buildings::BT_TOWER3:
                    case OpenSHC::Map::Buildings::BT_TOWER4:
                    case OpenSHC::Map::Buildings::BT_TOWER5:
                        if (DAT_GameState::instance.mapAndTime.playerTeams[sVar1]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])
                            goto switchD_004633df_caseD_45;
                        break;
                    case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                    case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
                        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                            goto LAB_0046340c;
                    }
                    goto LAB_004633b5;
                }
            switchD_004633df_caseD_64:
                dVar4 = 0x59;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = dVar4;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            DAT_BuildingsState::instance.newSelectedBuildingID = buildingID;
            DAT_BuildingsState::instance.newSelectedUnitID = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(8,
                    (BuildingType)((int)((int)(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType)));
            }
            DAT_BuildingsState::instance.field28_0x18e05c = 0;
            DAT_BuildingsState::instance.field29_0x18e060 = 0;
            return TRUE;
        }

    }
}
}
