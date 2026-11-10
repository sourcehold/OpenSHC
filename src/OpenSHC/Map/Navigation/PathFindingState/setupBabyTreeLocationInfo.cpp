#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Trees::TreeType;
        using OpenSHC::Map::Trees::TreeTypeShort;

        /* inlined copy of ViewportRenderState::xyAreValid */
        inline static int xyAreValid(uint ySpace, uint y)
        {
            return ySpace <= MC_MAP_XY_LIMIT_MIN_1 && y <= MC_MAP_XY_LIMIT_MIN_1
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] != 0;
        }
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C020
        BOOLEnum PathFindingState::setupBabyTreeLocationInfo(int param_1, int treeType, uint ySpace, uint y)
        {
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (!xyAreValid(ySpace, y)) {
                return FALSE;
            }
            this->calculations += 1;
            this->searchGeneration += 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, (void*)(DAT_TileMapState::instance.WalkLayer));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = y;
            this->searchQueue.xQueue[0] = ySpace;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0) {
                    return FALSE;
                }
                if (_tile >= MC_MAP_TILES_COUNT) {
                    return FALSE;
                }
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                    return FALSE;
                }
                if (this->searchQueue.currentDistance > param_1) {
                    return TRUE;
                }
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                for (int _direction = 0; _direction < 8; ++_direction) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                        int _organism = DAT_TileMapState::instance.OrganismLayer[_candidate];
                        if ((_organism == 0) || (_organism >= 2000)) {
                            int _building = DAT_TileMapState::instance.BuildingLayer[_candidate];
                            if (_building != 0) {
                                switch (DAT_BuildingsState::instance.buildings[_building].buildingType) {
                                case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                                case OpenSHC::Map::Buildings::BT_QUARRY:
                                case OpenSHC::Map::Buildings::BT_WHEATFARM:
                                case OpenSHC::Map::Buildings::BT_HOPFARM:
                                case OpenSHC::Map::Buildings::BT_APPLEFARM:
                                case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                                case OpenSHC::Map::Buildings::BT_SIGNPOST:
                                case OpenSHC::Map::Buildings::BT_POND:
                                    break;
                                default:
                                    // any other building on the way ends the search
                                    return FALSE;
                                }
                            }
                            int _logic2 = DAT_TileMapState::instance.Logic2Layer[_candidate];
                            if ((DAT_TileMapState::instance.LogicLayer[_candidate]
                                    & (LogicHelpers::L_SEA | LogicHelpers::L_PLAIN1_AND_FARM | LogicHelpers::L_BORDER
                                        | LogicHelpers::L_BORDER_EDGE | LogicHelpers::L_ROCKY
                                        | LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_BUILDING
                                        | LogicHelpers::L_TREE_VARIATION | LogicHelpers::L_BOULDERS
                                        | LogicHelpers::L_PEBBLES | LogicHelpers::L_IRON | LogicHelpers::L_RIVER
                                        | LogicHelpers::L_FORD | LogicHelpers::L_KEEP_NON_MANOR_HOUSE
                                        | LogicHelpers::L_MARSH | LogicHelpers::L_MOAT))
                                == 0) {
                                if (treeType == 1) {
                                    if ((_logic2 & 0x90 /* fixme: no Logic2 enum for 0x10 | 0x80 yet */) != 0)
                                        continue;
                                } else if ((_logic2 & 0x90 /* fixme: no Logic2 enum for 0x10 | 0x80 yet */) == 0) {
                                    continue;
                                }
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.xOffset
                                    + _x;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.yOffset
                                    + _y;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex += 1;
                                if (MC_MAP_TILES_COUNT <= this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        } else {
                            TreeTypeShort _treeType = DAT_LandscapeState::instance.trees[_organism].treeType;
                            if (_treeType == (TreeType)1) {
                                return FALSE;
                            }
                            if (_treeType == (TreeType)2) {
                                return FALSE;
                            }
                            if (_treeType == (TreeType)3) {
                                return FALSE;
                            }
                            if (_treeType == (TreeType)4) {
                                return FALSE;
                            }
                        }
                    }
                }

                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return FALSE;
        }

    }
}
}
