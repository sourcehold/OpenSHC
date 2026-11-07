#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

        /*
          Computes the AI zone layer: a flood fill from the attacked player's keep. Each round first spreads value 1
          over everything reachable by normal pathing (and through gatehouses), then gives the ring of tiles around that
          a distance: walls and gatehouses count 6 further, moat tiles one nearer on every other round. canReachKeep
          stops the fill after 2000 queued tiles instead of 6000.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4470
        void PathFindingState::computeAIZoneLayer(int attackedPlayerID, int canReachKeep, int param_3)
        {
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                    .id
                == 0) {
                return;
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            // the campfire tile in front of the keep
            this->searchQueue.yQueue[0] = DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                                              .yEntry;
            this->searchQueue.tilesQueue[0] = DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                                  .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                                                  .xEntry
                + DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_GameState::instance.playerDataArray[attackedPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .yEntry]
                      .addXgetTile;
            DAT_TileMapState::instance.AIZoneLayer[this->searchQueue.tilesQueue[0]]
                = (byte)this->searchQueue.currentDistance;
            int parity = 0;
            BOOLEnum full = FALSE;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                this->searchQueue.previousReadIndex = this->searchQueue.readIndex;
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    int const y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int const tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    for (int direction = 0; direction < 8; ++direction) {
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                        if ((char)DAT_TileMapState::instance.AIZoneLayer[neighbour] > 0) {
                            continue;
                        }
                        if (DAT_TileMapState::instance.PathConnectionLayer[neighbour] == 0) {
                            continue;
                        }
                        if ((DAT_TileMapState::instance.PathLinkageLayer[tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[direction])
                            == 0) {
                            if (DAT_TileMapState::instance.BuildingLayer[neighbour] == 0) {
                                continue;
                            }
                            BuildingTypeShort const buildingType
                                = DAT_BuildingsState::instance
                                      .buildings[DAT_TileMapState::instance.BuildingLayer[neighbour]]
                                      .buildingType;
                            if (buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                                && buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                                continue;
                            }
                        }
                        DAT_TileMapState::instance.AIZoneLayer[neighbour] = 1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                  .short_.yOffset
                            + y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = neighbour;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (this->searchQueue.writeIndex >= 80400) {
                            full = TRUE;
                            break;
                        }
                    }
                    if (full) {
                        break;
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (this->searchQueue.readIndex >= 80400) {
                        this->searchQueue.readIndex = 0;
                    }
                    if ((canReachKeep != 0 && this->searchQueue.writeIndex >= 2000)
                        || this->searchQueue.writeIndex >= 6000) {
                        full = TRUE;
                        break;
                    }
                }
                if (full) {
                    break;
                }
                this->searchQueue.readIndex = this->searchQueue.previousReadIndex;
                this->searchQueue.nextWriteIndex = this->searchQueue.writeIndex;
                while (this->searchQueue.readIndex != this->searchQueue.nextWriteIndex) {
                    int const tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    int const y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (char)DAT_TileMapState::instance.AIZoneLayer[tile] + 1;
                    for (int direction = 0; direction < 8; ++direction) {
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                        if ((char)DAT_TileMapState::instance.AIZoneLayer[neighbour] > 0) {
                            continue;
                        }
                        uint const logic = DAT_TileMapState::instance.LogicLayer[neighbour];
                        if ((logic & 0x31) != 0) {
                            continue;
                        }
                        if (DAT_TileMapState::instance.BuildingLayer[neighbour] != 0
                            && DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[neighbour]]
                                    .unknownFlag4
                                != 0) {
                            continue;
                        }
                        if ((logic & 0x100) != 0) {
                            // walls and gatehouses
                            DAT_TileMapState::instance.AIZoneLayer[neighbour]
                                = (byte)this->searchQueue.currentDistance + 6;
                        } else if ((logic & 0x40000000) != 0 && parity != 0) {
                            // moat
                            DAT_TileMapState::instance.AIZoneLayer[neighbour]
                                = (byte)this->searchQueue.currentDistance - 1;
                        } else {
                            DAT_TileMapState::instance.AIZoneLayer[neighbour] = (byte)this->searchQueue.currentDistance;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (this->searchQueue.readIndex >= 80400) {
                        this->searchQueue.readIndex = 0;
                    }
                }
                parity = parity + 1;
                if (parity >= 2) {
                    parity = 0;
                }
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
        }

    }
}
}
