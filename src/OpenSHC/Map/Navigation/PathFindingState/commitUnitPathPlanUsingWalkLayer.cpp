#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00498FD0
        uint PathFindingState::commitUnitPathPlanUsingWalkLayer(uint param_1, int param_2, int param_3)
        {
            if (399 < (uint)this->unitX || 399 < (uint)this->unitY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->unitY * 400 + this->unitX] == 0) {
                return 0;
            }
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->unitY].addXgetTile + this->unitX;
            int y = this->unitY;
            if (DAT_TileMapState::instance.PathConnectionLayer[tile] == 0) {
                return 0;
            }
            if (param_1 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 80, 0);
            } else if (param_1 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 200, 0);
            } else if (param_1 == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 500, 0);
            } else if (param_1 == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 1000, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 2000, 0);
            }
            int lastDirection = 10;
            int const walk = DAT_TileMapState::instance.WalkLayer[tile];
            int rng = SEC_RNG::instance.currentNumber2;
            this->searchQueue.pathPlanIndex = 0;
            int current = 1;
            // phase 0 climbs the distances away from the spawn search, phase 1 descends them again
            int phase = 0;
            while (phase == 0 || current > 1) {
                int const threshold = current;
                int bestScore = current;
                int bestDirection = 8;
                for (int direction = 0; direction < 8; ++direction) {
                    int const candidate = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                    if (DAT_TileMapState::instance.WalkLayer[candidate] != walk) {
                        continue;
                    }
                    // the top two bits mark tiles already visited by each phase; one variable for the raw and the
                    // masked value is what lets MSVC keep it in one register as the original does (0.34 -> 0.71)
                    int distance = DAT_TileMapState::instance.CertainPathLayer[candidate];
                    if (phase == 0) {
                        if ((distance & 0x8000) != 0) {
                            continue;
                        }
                        distance = distance & 0x3fff;
                        if (distance < threshold) {
                            continue;
                        }
                        if (param_3 != 0 && distance == threshold) {
                            continue;
                        }
                        int const score = ((DAT_TileMapState::instance.RandomLayer[candidate] ^ rng) & 7) + distance;
                        int biasedScore = score;
                        if (direction == lastDirection) {
                            biasedScore = score + 1;
                        }
                        if (biasedScore > bestScore) {
                            current = distance;
                            bestScore = score;
                            bestDirection = direction;
                        }
                        rng = (rng >> 1 & 0x7fff) | (rng & 1) << 15;
                    } else if (phase == 1) {
                        if ((distance & 0x4000) != 0) {
                            continue;
                        }
                        distance = distance & 0x3fff;
                        if (distance > threshold) {
                            continue;
                        }
                        if (param_3 != 0 && distance == threshold) {
                            continue;
                        }
                        int const score = distance - ((DAT_TileMapState::instance.RandomLayer[candidate] ^ rng) & 7);
                        int biasedScore = score;
                        if (direction == lastDirection) {
                            biasedScore = score - 1;
                        }
                        if (biasedScore < bestScore) {
                            current = distance;
                            bestScore = score;
                            bestDirection = direction;
                        }
                        rng = (rng >> 1 & 0x7fff) | (rng & 1) << 15;
                    }
                }
                if (phase == 0) {
                    DAT_TileMapState::instance.CertainPathLayer[tile] |= 0x8000;
                } else {
                    DAT_TileMapState::instance.CertainPathLayer[tile] |= 0x4000;
                }
                if (bestDirection == 8) {
                    if (param_2 == 0 || phase != 0) {
                        break;
                    }
                    phase = 1;
                    continue;
                }
                tile = tile + DAT_TileMapState::instance.directionTranslationMatrix[y][bestDirection];
                y = y + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDirection].int_.yOffset;
                // two directions per byte, the even step in the low nibble
                if ((this->searchQueue.pathPlanIndex & 1) == 0) {
                    this->searchQueue.ptrPathPlan[this->searchQueue.pathPlanIndex / 2] = bestDirection;
                } else {
                    this->searchQueue.ptrPathPlan[this->searchQueue.pathPlanIndex / 2] &= 0xf;
                    this->searchQueue.ptrPathPlan[this->searchQueue.pathPlanIndex / 2] += bestDirection << 4;
                }
                this->searchQueue.pathPlanIndex = this->searchQueue.pathPlanIndex + 1;
                lastDirection = bestDirection;
                if (this->searchQueue.pathPlanIndex >= 800) {
                    break;
                }
            }
            return this->searchQueue.pathPlanIndex;
        }

    }
}
}
