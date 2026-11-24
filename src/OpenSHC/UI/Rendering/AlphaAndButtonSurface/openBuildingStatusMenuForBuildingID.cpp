#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
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
            // No initial value: every path to the menu sets it, the barracks' arm too (an initial 1 loses the match).
            int menuTab;
            // Runs once: the unowned statue's break skips the countdown call and the second switch,
            // the other paths to the menu break at its end (a flag loses the match).
            for (;;) {
                if (owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    // Someone else's building: most types are only selected, allied gates and towers open their menu.
                    if (owner == 0
                        && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_STATUE) {
                        menuTab = OpenSHC::UI::Enums::BASMTT_STATUE;
                        // Straight to the menu, past the countdown call (an if around the call loses the match).
                        break;
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
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    menuTab = OpenSHC::UI::Enums::BASMTT_MERCENARYPOST;
                    break;
                case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                        menuTab = OpenSHC::UI::Enums::BASMTT_OUTPOST;
                        break;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                        DAT_TextEditorState::ptr)();
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
                    menuTab = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI = taxes;
                    break;
                }
                case OpenSHC::Map::Buildings::BT_INN:
                    menuTab = OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK;
                    break;
                case OpenSHC::Map::Buildings::BT_HOVEL:
                case OpenSHC::Map::Buildings::BT_HOUSE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_HOUSE;
                    break;
                case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_WOODCUTTERSHUT;
                    break;
                case OpenSHC::Map::Buildings::BT_OXTETHER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_OXTETHER;
                    break;
                case OpenSHC::Map::Buildings::BT_IRONMINE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_IRONMINE;
                    break;
                case OpenSHC::Map::Buildings::BT_PITCHRIG:
                    menuTab = OpenSHC::UI::Enums::BASMTT_PITCHRIG;
                    break;
                case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                    break;
                case OpenSHC::Map::Buildings::BT_STOCKPILE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_STOCKPILE;
                    break;
                case OpenSHC::Map::Buildings::BT_ARMORY:
                    menuTab = OpenSHC::UI::Enums::BASMTT_ARMORY;
                    break;
                case OpenSHC::Map::Buildings::BT_FLETCHER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_FLETCHER;
                    break;
                case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                    menuTab = OpenSHC::UI::Enums::BASMTT_BLACKSMITH;
                    break;
                case OpenSHC::Map::Buildings::BT_POLETURNER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_POLETURNER;
                    break;
                case OpenSHC::Map::Buildings::BT_ARMOURER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_ARMOURER;
                    break;
                case OpenSHC::Map::Buildings::BT_TANNER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_TANNER;
                    break;
                case OpenSHC::Map::Buildings::BT_BAKERY:
                    menuTab = OpenSHC::UI::Enums::BASMTT_BAKERY;
                    break;
                case OpenSHC::Map::Buildings::BT_BREWERY:
                    menuTab = OpenSHC::UI::Enums::BASMTT_BREWERY;
                    break;
                case OpenSHC::Map::Buildings::BT_GRANARY: {
                    int const rations
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .rationsSetting;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .rationsSetting2 = rations;
                    menuTab = OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .rationsSetting3 = rations;
                    break;
                }
                case OpenSHC::Map::Buildings::BT_QUARRY:
                    menuTab = OpenSHC::UI::Enums::BASMTT_QUARRY;
                    break;
                case OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_QUARRY_STONEPILE;
                    break;
                case OpenSHC::Map::Buildings::BT_APOTHECARY:
                    menuTab = OpenSHC::UI::Enums::BASMTT_APOTHECARY;
                    break;
                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    menuTab = OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD;
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    menuTab = OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD;
                    break;
                case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_MARKETPLACE;
                    break;
                case OpenSHC::Map::Buildings::BT_WELL:
                    menuTab = OpenSHC::UI::Enums::BASMTT_WELL;
                    break;
                case OpenSHC::Map::Buildings::BT_WATERPOT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_WATERPOT;
                    break;
                case OpenSHC::Map::Buildings::BT_OILSMELTER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_OILSMELTER;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETENT:
                    menuTab = 28; // the siege tent's tab, which has no BASMTT_ name
                    break;
                case OpenSHC::Map::Buildings::BT_WHEATFARM:
                    menuTab = OpenSHC::UI::Enums::BASMTT_WHEATFARM;
                    break;
                case OpenSHC::Map::Buildings::BT_HOPFARM:
                    menuTab = OpenSHC::UI::Enums::BASMTT_HOPFARM;
                    break;
                case OpenSHC::Map::Buildings::BT_APPLEFARM:
                    menuTab = OpenSHC::UI::Enums::BASMTT_APPLEFARM;
                    break;
                case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                    menuTab = OpenSHC::UI::Enums::BASMTT_DAIRYFARM;
                    break;
                case OpenSHC::Map::Buildings::BT_MILL:
                    menuTab = OpenSHC::UI::Enums::BASMTT_MILL;
                    break;
                case OpenSHC::Map::Buildings::BT_STABLES:
                    menuTab = OpenSHC::UI::Enums::BASMTT_STABLES;
                    break;
                case OpenSHC::Map::Buildings::BT_CHAPEL:
                case OpenSHC::Map::Buildings::BT_CHURCH:
                    menuTab = OpenSHC::UI::Enums::BASMTT_CHAPEL_AND_CHURCH;
                    break;
                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    menuTab = OpenSHC::UI::Enums::BASMTT_CATHEDRAL;
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    if (DAT_BuildingsState::instance.buildings[buildingID].field_0x2c6 != 0) {
                        return FALSE;
                    }
                    menuTab = OpenSHC::UI::Enums::BASMTT_GATEHOUSE;
                    break;
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE: {
                    // The drawbridge belongs to the large or the small gatehouse next to it.
                    int gatehouse
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                            DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y,
                            DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                            OpenSHC::Map::Buildings::BT_GATEHOUSELARGE, 0);
                    if (gatehouse == 0) {
                        gatehouse
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                                DAT_BuildingsState::instance.buildings[buildingID].x,
                                DAT_BuildingsState::instance.buildings[buildingID].y,
                                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                                OpenSHC::Map::Buildings::BT_GATEHOUSESMALL, 0);
                    }
                    if (gatehouse != 0 && DAT_BuildingsState::instance.buildings[gatehouse].field_0x2c6 != 0) {
                        return FALSE;
                    }
                    menuTab = OpenSHC::UI::Enums::BASMTT_DRAWBRIDGE;
                    break;
                }
                case OpenSHC::Map::Buildings::BT_WOODGATE2:
                    menuTab = OpenSHC::UI::Enums::BASMTT_UNUSED_POSTERNGATE;
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNEL:
                    menuTab = OpenSHC::UI::Enums::BASMTT_TUNNELENTRANCE;
                    break;
                case OpenSHC::Map::Buildings::BT_SIGNPOST:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIGNPOST;
                    break;
                case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_KILLINGPIT;
                    break;
                case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                    menuTab = OpenSHC::UI::Enums::BASMTT_CAMPFIRE;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                case OpenSHC::Map::Buildings::BT_TOWER2:
                case OpenSHC::Map::Buildings::BT_TOWER3:
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    menuTab = OpenSHC::UI::Enums::BASMTT_TOWER;
                    break;
                case OpenSHC::Map::Buildings::BT_GALLOWS:
                    menuTab = OpenSHC::UI::Enums::BASMTT_GALLOWS;
                    break;
                case OpenSHC::Map::Buildings::BT_STOCKS:
                    menuTab = OpenSHC::UI::Enums::BASMTT_STOCKS;
                    break;
                case OpenSHC::Map::Buildings::BT_WITCHHOIST:
                    menuTab = OpenSHC::UI::Enums::BASMTT_UNUSED_WITCHHOIST;
                    break;
                case OpenSHC::Map::Buildings::BT_MAYPOLE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_MAYPOLE;
                    break;
                case OpenSHC::Map::Buildings::BT_GARDEN:
                    menuTab = OpenSHC::UI::Enums::BASMTT_GARDENS;
                    break;
                case OpenSHC::Map::Buildings::BT_CAMPFIRE:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                    menuTab = OpenSHC::UI::Enums::BASMTT_TRAININGGROUNDS;
                    break;
                case OpenSHC::Map::Buildings::BT_CATAPULT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_CATAPULT;
                    break;
                case OpenSHC::Map::Buildings::BT_TREBUCHET:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_TREBUCHET;
                    break;
                case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETOWER:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                    break;
                case OpenSHC::Map::Buildings::BT_SHIELD:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD;
                    break;
                case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SIEGETENT_FIREBALLISTA;
                    break;
                case OpenSHC::Map::Buildings::BT_CESSPIT:
                    menuTab = OpenSHC::UI::Enums::BASMTT_CESSPIT;
                    break;
                case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_BURNINGSTAKE;
                    break;
                case OpenSHC::Map::Buildings::BT_GIBBET:
                    menuTab = OpenSHC::UI::Enums::BASMTT_GIBBET;
                    break;
                case OpenSHC::Map::Buildings::BT_DUNGEON:
                    menuTab = OpenSHC::UI::Enums::BASMTT_DUNGEON;
                    break;
                case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
                    menuTab = OpenSHC::UI::Enums::BASMTT_STRETCHINGRACK;
                    break;
                case OpenSHC::Map::Buildings::BT_RACKFLOGGING:
                    menuTab = OpenSHC::UI::Enums::BASMTT_UNUSED_FLOGGINGRACK;
                    break;
                case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                    menuTab = OpenSHC::UI::Enums::BASMTT_CHOPPINGBLOCK;
                    break;
                case OpenSHC::Map::Buildings::BT_DUNKINGSTOOL:
                    menuTab = OpenSHC::UI::Enums::BASMTT_DUNKINGSTOOL;
                    break;
                case OpenSHC::Map::Buildings::BT_DOGCAGE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_DOGCAGE;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .releaseDogsFlag
                        = DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs;
                    break;
                case OpenSHC::Map::Buildings::BT_STATUE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_STATUE;
                    break;
                case OpenSHC::Map::Buildings::BT_SHRINE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_SHRINE;
                    break;
                case OpenSHC::Map::Buildings::BT_BEEHIVE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_UNUSED_BEEHIVE;
                    break;
                case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
                    menuTab = OpenSHC::UI::Enums::BASMTT_DANCINGBEAR;
                    break;
                case OpenSHC::Map::Buildings::BT_BEARCAVE:
                    menuTab = OpenSHC::UI::Enums::BASMTT_UNUSED_BEARCAVE;
                    break;
                case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                    DAT_BuildingsState::instance.selectedBuildingID = buildingID;
                    DAT_BuildingsState::instance.selectedBuildingUID
                        = DAT_BuildingsState::instance.buildings[buildingID].uid;
                    return FALSE;
                case OpenSHC::Map::Buildings::BT_BARRACKS:
                    menuTab = OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
                    break;
                default:
                    return FALSE;
                }
                break;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = menuTab;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            DAT_BuildingsState::instance.newSelectedBuildingID = buildingID;
            DAT_BuildingsState::instance.newSelectedUnitID = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                    8, (BuildingType)DAT_BuildingsState::instance.buildings[buildingID].buildingType);
            }
            DAT_BuildingsState::instance.selectedBuildingID = 0;
            DAT_BuildingsState::instance.selectedBuildingUID = 0;
            return TRUE;
        }

    }
}
}
