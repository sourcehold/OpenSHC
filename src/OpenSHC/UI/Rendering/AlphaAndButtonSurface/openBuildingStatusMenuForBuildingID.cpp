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

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00463310
        BOOLEnum AlphaAndButtonSurface::openBuildingStatusMenuForBuildingID(int buildingID)
        {
            if (buildingID <= 0) {
                return FALSE;
            }
            if (DAT_GameCore::instance.gamePausedLogical != 0) {
                return FALSE;
            }
            short const owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            dword menuTab = 1;
            if (owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                // Someone else's building: most types are only selected, walls and towers of allies open their menu.
                if (owner == 0
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_STATUE) {
                    menuTab = 89;
                    goto openMenu;
                }
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
                    DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                    DAT_BuildingsState::instance.selectedBuildingUID
                        = DAT_BuildingsState::instance.buildings[buildingID].uid;
                    return FALSE;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                case OpenSHC::Map::Buildings::BT_TOWER1:
                case OpenSHC::Map::Buildings::BT_TOWER2:
                case OpenSHC::Map::Buildings::BT_TOWER3:
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                        DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                        DAT_BuildingsState::instance.selectedBuildingUID
                            = DAT_BuildingsState::instance.buildings[buildingID].uid;
                        return FALSE;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                        DAT_BuildingsState::instance.selectedBuildingUID
                            = DAT_BuildingsState::instance.buildings[buildingID].uid;
                        return FALSE;
                    }
                    break;
                default:
                    return FALSE;
                }
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType,
                DAT_BuildingsState::ptr)(
                (OpenSHC::Map::Buildings::BuildingType)(DAT_BuildingsState::instance.buildings[buildingID]
                        .buildingType),
                1, DAT_GameSynchronyState::instance.currentPlayerSlotID);
            int const currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                menuTab = 44;
                break;
            case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
            case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    menuTab = 45;
                    break;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                DAT_BuildingsState::instance.selectedBuildingUID
                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                return FALSE;
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_KEEPFOUR:
            case OpenSHC::Map::Buildings::BT_KEEPFIVE:
            case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
            case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
            case OpenSHC::Map::Buildings::BT_KEEPDOOR: {
                int const taxes
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSetting;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .taxesSetting2 = taxes;
                menuTab = 2;
                DAT_GameState::instance.playerDataArray[currentPlayer].taxesSliderUI = taxes;
                break;
            }
            case OpenSHC::Map::Buildings::BT_INN:
                menuTab = 3;
                break;
            case OpenSHC::Map::Buildings::BT_HOVEL:
            case OpenSHC::Map::Buildings::BT_HOUSE:
                menuTab = 5;
                break;
            case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                menuTab = 6;
                break;
            case OpenSHC::Map::Buildings::BT_OXTETHER:
                menuTab = 7;
                break;
            case OpenSHC::Map::Buildings::BT_IRONMINE:
                menuTab = 8;
                break;
            case OpenSHC::Map::Buildings::BT_PITCHRIG:
                menuTab = 9;
                break;
            case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                menuTab = 10;
                break;
            case OpenSHC::Map::Buildings::BT_STOCKPILE:
                menuTab = 11;
                break;
            case OpenSHC::Map::Buildings::BT_ARMORY:
                menuTab = 12;
                break;
            case OpenSHC::Map::Buildings::BT_FLETCHER:
                menuTab = 13;
                break;
            case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                menuTab = 14;
                break;
            case OpenSHC::Map::Buildings::BT_POLETURNER:
                menuTab = 15;
                break;
            case OpenSHC::Map::Buildings::BT_ARMOURER:
                menuTab = 16;
                break;
            case OpenSHC::Map::Buildings::BT_TANNER:
                menuTab = 17;
                break;
            case OpenSHC::Map::Buildings::BT_BAKERY:
                menuTab = 18;
                break;
            case OpenSHC::Map::Buildings::BT_BREWERY:
                menuTab = 19;
                break;
            case OpenSHC::Map::Buildings::BT_GRANARY: {
                int const rations
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .rationsSetting;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .rationsSetting2 = rations;
                menuTab = 4;
                DAT_GameState::instance.playerDataArray[currentPlayer].rationsSetting3 = rations;
                break;
            }
            case OpenSHC::Map::Buildings::BT_QUARRY:
                menuTab = 20;
                break;
            case OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE:
                menuTab = 21;
                break;
            case OpenSHC::Map::Buildings::BT_APOTHECARY:
                menuTab = 22;
                break;
            case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                menuTab = 23;
                break;
            case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                menuTab = 24;
                break;
            case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                menuTab = 25;
                break;
            case OpenSHC::Map::Buildings::BT_WELL:
                menuTab = 26;
                break;
            case OpenSHC::Map::Buildings::BT_WATERPOT:
                menuTab = 40;
                break;
            case OpenSHC::Map::Buildings::BT_OILSMELTER:
                menuTab = 27;
                break;
            case OpenSHC::Map::Buildings::BT_SIEGETENT:
                menuTab = 28;
                break;
            case OpenSHC::Map::Buildings::BT_WHEATFARM:
                menuTab = 29;
                break;
            case OpenSHC::Map::Buildings::BT_HOPFARM:
                menuTab = 30;
                break;
            case OpenSHC::Map::Buildings::BT_APPLEFARM:
                menuTab = 31;
                break;
            case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                menuTab = 32;
                break;
            case OpenSHC::Map::Buildings::BT_MILL:
                menuTab = 33;
                break;
            case OpenSHC::Map::Buildings::BT_STABLES:
                menuTab = 34;
                break;
            case OpenSHC::Map::Buildings::BT_CHAPEL:
            case OpenSHC::Map::Buildings::BT_CHURCH:
                menuTab = 35;
                break;
            case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                menuTab = 96;
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_WOODGATE1:
                if (DAT_BuildingsState::instance.buildings[buildingID].field_0x2c6 != 0) {
                    return FALSE;
                }
                menuTab = 36;
                break;
            case OpenSHC::Map::Buildings::BT_DRAWBRIDGE: {
                // The drawbridge belongs to the large or the small gatehouse next to it.
                int gatehouse = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                    DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].x),
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y),
                    (int)(DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight),
                    OpenSHC::Map::Buildings::BT_GATEHOUSELARGE, 0);
                if (gatehouse == 0) {
                    gatehouse = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].x),
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y),
                        (int)(DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight),
                        OpenSHC::Map::Buildings::BT_GATEHOUSESMALL, 0);
                }
                if (gatehouse != 0 && DAT_BuildingsState::instance.buildings[gatehouse].field_0x2c6 != 0) {
                    return FALSE;
                }
                menuTab = 37;
                break;
            }
            case OpenSHC::Map::Buildings::BT_WOODGATE2:
                menuTab = 38;
                break;
            case OpenSHC::Map::Buildings::BT_TUNNEL:
                menuTab = 39;
                break;
            case OpenSHC::Map::Buildings::BT_SIGNPOST:
                menuTab = 41;
                break;
            case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                menuTab = 42;
                break;
            case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                menuTab = 43;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                menuTab = 46;
                break;
            case OpenSHC::Map::Buildings::BT_GALLOWS:
                menuTab = 47;
                break;
            case OpenSHC::Map::Buildings::BT_STOCKS:
                menuTab = 48;
                break;
            case OpenSHC::Map::Buildings::BT_WITCHHOIST:
                menuTab = 49;
                break;
            case OpenSHC::Map::Buildings::BT_MAYPOLE:
                menuTab = 50;
                break;
            case OpenSHC::Map::Buildings::BT_GARDEN:
                menuTab = 51;
                break;
            case OpenSHC::Map::Buildings::BT_CAMPFIRE:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                menuTab = 52;
                break;
            case OpenSHC::Map::Buildings::BT_CATAPULT:
                menuTab = 58;
                break;
            case OpenSHC::Map::Buildings::BT_TREBUCHET:
                menuTab = 59;
                break;
            case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
                menuTab = 60;
                break;
            case OpenSHC::Map::Buildings::BT_SIEGETOWER:
                menuTab = 61;
                break;
            case OpenSHC::Map::Buildings::BT_SHIELD:
                menuTab = 62;
                break;
            case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
                menuTab = 95;
                break;
            case OpenSHC::Map::Buildings::BT_CESSPIT:
                menuTab = 80;
                break;
            case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
                menuTab = 81;
                break;
            case OpenSHC::Map::Buildings::BT_GIBBET:
                menuTab = 82;
                break;
            case OpenSHC::Map::Buildings::BT_DUNGEON:
                menuTab = 83;
                break;
            case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
                menuTab = 84;
                break;
            case OpenSHC::Map::Buildings::BT_RACKFLOGGING:
                menuTab = 85;
                break;
            case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                menuTab = 86;
                break;
            case OpenSHC::Map::Buildings::BT_DUNKINGSTOOL:
                menuTab = 87;
                break;
            case OpenSHC::Map::Buildings::BT_DOGCAGE:
                menuTab = 88;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .releaseDogsFlag
                    = DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs;
                break;
            case OpenSHC::Map::Buildings::BT_SHRINE:
                menuTab = 90;
                break;
            case OpenSHC::Map::Buildings::BT_BEEHIVE:
                menuTab = 91;
                break;
            case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
                menuTab = 92;
                break;
            case OpenSHC::Map::Buildings::BT_BEARCAVE:
                menuTab = 94;
                break;
            case OpenSHC::Map::Buildings::BT_BARRACKS:
                break;
            default:
                return FALSE;
            case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                DAT_BuildingsState::instance.selectedBuildingUID
                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                return FALSE;
            case OpenSHC::Map::Buildings::BT_STATUE:
                menuTab = 89;
                break;
            }
        openMenu:
            MACRO_CALL_MEMBER(
                OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = menuTab;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            DAT_BuildingsState::instance.newSelectedBuildingID = buildingID;
            DAT_BuildingsState::instance.newSelectedUnitID = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                    8, (BuildingType)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].buildingType)));
            }
            DAT_BuildingsState::instance.selectedBuildingID = 0;
            DAT_BuildingsState::instance.selectedBuildingUID = 0;
            return TRUE;
        }

    }
}
}
