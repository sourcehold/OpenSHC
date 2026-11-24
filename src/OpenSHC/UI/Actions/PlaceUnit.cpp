#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Floaters/FloaterVariationFlags.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004381D0
    void Actions::PlaceUnit()
    {
        if (DAT_TileMapState::instance.DAT_ClickedTileX > OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
            || DAT_TileMapState::instance.DAT_ClickedTileY > OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[DAT_TileMapState::instance.DAT_ClickedTileY
                       * OpenSHC::Map::MC_MAP_XY_LIMIT
                   + DAT_TileMapState::instance.DAT_ClickedTileX]
                == 0) {
            return;
        }
        int secondImageID = -1;
        int tribeType = -1;
        UnitType unitType = OpenSHC::Map::Units::UT_INVALID;
        int imageID = 1;
        // declared between the two that start at 1: with both on one side of this line the match is lost
        int const tile
            = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                  .addXgetTile
            + DAT_TileMapState::instance.DAT_ClickedTileX;
        BOOLEnum canAfford = TRUE;
        uint blockingLogicMask = OpenSHC::Map::LogicHelpers::L_SEA | OpenSHC::Map::LogicHelpers::L_ROCKY
            | OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_TREE
            | OpenSHC::Map::LogicHelpers::L_RIVER | OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk
            | OpenSHC::Map::LogicHelpers::L_MOAT;
        // fixme: for a command outside the switch (the one caller sends none) the original leaves gmID unset and
        // still reads it below
        GmID gmID;
        GmID secondGmID;
        // the cases in the order of the original's code: the Arab units stand between 280 and 281
        switch (DAT_TileMapState::instance.currentMapperCommand) {
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARCHERS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARCHER;
            tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
            unitType = OpenSHC::Map::Units::UT_E_ARCHER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SPEARMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SPEARMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_SPEARMEN;
            unitType = OpenSHC::Map::Units::UT_E_SPEAR;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_PIKEMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_PIKEMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_PIKEMEN;
            unitType = OpenSHC::Map::Units::UT_E_PIKE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_MACEMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_MACEMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
            unitType = OpenSHC::Map::Units::UT_E_MACE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_XBOWMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_CROSSBOWMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_CROSSBOWMEN;
            unitType = OpenSHC::Map::Units::UT_E_XBOW;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SWORDSMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SWORDSMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
            unitType = OpenSHC::Map::Units::UT_E_SWORD;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_KNIGHTS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_KNIGHT;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_KNIGHT_TOP;
            tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
            unitType = OpenSHC::Map::Units::UT_E_KNIGHT;
            secondImageID = 1;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_LADDERMEN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_LADDER_BEARER;
            tribeType = OpenSHC::AI::Tribes::AITT_LADDERMEN;
            unitType = OpenSHC::Map::Units::UT_E_LADDER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SIEGE_ENGINEER;
            tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
            unitType = OpenSHC::Map::Units::UT_E_ENGINEER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS_POTS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SIEGE_ENGINEER;
            tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
            unitType = OpenSHC::Map::Units::UT_E_ENGINEER;
            imageID = 629;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_MONKS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_FIGHTING_MONK;
            tribeType = OpenSHC::AI::Tribes::AITT_HOPS_FARMER_UNK;
            unitType = OpenSHC::Map::Units::UT_E_MONK;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_BOW:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_SHORTBOW;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ARCHER;
            unitType = OpenSHC::Map::Units::UT_A_ARCHER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SLAVE:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_SLAVE;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SLAVE;
            unitType = OpenSHC::Map::Units::UT_A_SLAVE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SLINGER:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_SLINGER;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SLINGER;
            unitType = OpenSHC::Map::Units::UT_A_SLINGER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_ASSASIN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_ASSASIN;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ASSASSIN;
            unitType = OpenSHC::Map::Units::UT_A_ASSASSIN;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_HORSEMAN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_HORSE_ARCHER;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_HORSE_ARCHER;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_HORSE_ARCHER_TOP;
            unitType = OpenSHC::Map::Units::UT_A_HARCHER;
            secondImageID = 1;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SWORDSMAN:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_SWORDSMAN;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMAN;
            unitType = OpenSHC::Map::Units::UT_A_SWORDSMAN;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_GRENADIER:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_GRENADIER;
            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_FIRETHROWER;
            unitType = OpenSHC::Map::Units::UT_A_FIRETHROWER;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_BALLISTA:
            gmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_BALLISTA;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_ARAB_BALLISTA;
            secondImageID = 169;
            tribeType = OpenSHC::AI::Tribes::AITT_FIRE_BALLISTA;
            unitType = OpenSHC::Map::Units::UT_S_FBALLISTA;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_CATAPULTS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_CATAPULT;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_CATAPULT;
            unitType = OpenSHC::Map::Units::UT_S_CATAPULT;
            secondImageID = 225;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_TREBUCHETS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_TREBUTCHET;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_TREBUTCHET;
            unitType = OpenSHC::Map::Units::UT_S_TREBUCHET;
            secondImageID = 9;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER;
            secondImageID = 9;
            unitType = OpenSHC::Map::Units::UT_S_TOWER;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_BATTERING_RAM;
            secondGmID = OpenSHC::IO::Graphics::GID_BODY_BATTERING_RAM;
            secondImageID = 77;
            unitType = OpenSHC::Map::Units::UT_S_BATTERINGRAM;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_SHIELD;
            unitType = OpenSHC::Map::Units::UT_S_SHIELD;
            blockingLogicMask
                |= OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
            break;
        case OpenSHC::Commands::M_MAPPER_PEOPLE_TUNNELERS:
            gmID = OpenSHC::IO::Graphics::GID_BODY_TUNNELOR;
            tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;
            unitType = OpenSHC::Map::Units::UT_TUNNELER;
            break;
        }
        // in a siege the units cost gold
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            // declared in both cost blocks: the unset gmID then shares gold's stack slot, as in the original
            int stone;
            int gold;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                DAT_TileMapState::instance.currentMapperCommand, &stone, &gold);
            if (gold > DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[OpenSHC::Game::Resources::RT_GOLD]) {
                canAfford = FALSE;
            }
        }
        // while the drag goes on: only the pictures on the floating layer
        if (!DAT_MouseState::instance.draggingStopped) {
            if ((DAT_TileMapState::instance.LogicLayer[tile] & blockingLogicMask) == 0 && canAfford) {
                if (gmID == OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER) {
                    if (secondImageID > 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(secondGmID, secondImageID, 0, 71, tile,
                            OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                                | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT
                                | OpenSHC::Map::Floaters::FVF_RENDERED_OWNER_0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER, imageID, 0, 0, tile,
                        OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                            | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT
                            | OpenSHC::Map::Floaters::FVF_RENDERED_OWNER_0);
                    return;
                }
                if (secondImageID > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(secondGmID, secondImageID, 0, 0, tile,
                        OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                            | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT);
                }
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(gmID, imageID, 0, 0, tile,
                    OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                        | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT);
                return;
            }
            // not allowed here: the same pictures drawn blended (the high half of the variation is a blend strength)
            if (gmID == OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER) {
                if (secondImageID > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(secondGmID, secondImageID, 0, 71, tile,
                        OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                            | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT
                            | OpenSHC::Map::Floaters::FVF_RENDERED_OWNER_0 | (24 << 16));
                }
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_SIEGE_TOWER, imageID, 0, 0, tile,
                    OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                        | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT | OpenSHC::Map::Floaters::FVF_RENDERED_OWNER_0
                        | (24 << 16));
                return;
            }
            if (secondImageID > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(secondGmID, secondImageID, 0, 0, tile,
                    OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                        | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT | (24 << 16));
            }
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                DAT_ViewportRenderState::ptr)(gmID, imageID, 0, 0, tile,
                OpenSHC::Map::Floaters::FVF_SECOND_PASS | OpenSHC::Map::Floaters::FVF_SET_RENDERED_OWNER
                    | OpenSHC::Map::Floaters::FVF_USE_TOTAL_HEIGHT | (24 << 16));
            return;
        }
        // the drag has stopped: pay and place
        if ((DAT_TileMapState::instance.LogicLayer[tile] & blockingLogicMask) == 0 && canAfford) {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                int stone;
                int gold;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost,
                    DAT_BuildingsState::ptr)(DAT_TileMapState::instance.currentMapperCommand, &stone, &gold);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Resources::RT_GOLD, gold, 0);
            }
            if (tribeType >= 0) {
                int const tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                    DAT_TribesState::ptr)(-1, tribeType, DAT_TileMapState::instance.DAT_ClickedTileX,
                    DAT_TileMapState::instance.DAT_ClickedTileY, DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    unitType, OpenSHC::Map::Units::UT_NONE, DAT_TileMapState::instance.unitPlacementCount, 0);
                DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = OpenSHC::Map::Units::STBT_1;
                DAT_TribesState::instance.tribes[tribeID].initialMoveOrderGiven = 1;
                if (DAT_TileMapState::instance.currentMapperCommand
                    == OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS_POTS) {
                    // the engineers with pots start with oil in them
                    for (int i = 0; i < DAT_TileMapState::instance.unitPlacementCount; ++i) {
                        DAT_UnitsState::instance
                            .units[MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                DAT_TribesState::ptr)(tribeID, i)]
                            .resourceToDeposit = 1;
                    }
                }
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    DAT_TileMapState::instance.DAT_ClickedTileX * 8, DAT_TileMapState::instance.DAT_ClickedTileY * 8,
                    DAT_TileMapState::instance.HeightLayer[tile], unitType);
            }
        }
    }

}
}
