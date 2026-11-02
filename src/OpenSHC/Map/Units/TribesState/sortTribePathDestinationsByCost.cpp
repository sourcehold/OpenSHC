#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        // A bubble-sort pass ends at the first entry whose tile2 is 0 or whose successor has tile1 or tile2 0
        // (0x524A30..0x524A4C); unreached entries (cost 10000000) are compacted out afterwards.
        // FUNCTION: STRONGHOLDCRUSADER 0x00524930
        void TribesState::sortTribePathDestinationsByCost(int tribeIDThenSortIdx, int horseAndRamCount)
        {
            BOOLEnum const allAssassins = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeIDThenSortIdx);
            int const selectionTargetUnitID = this->tribes[tribeIDThenSortIdx].selectionTargetUnitID;
            int const x = DAT_UnitsState::instance.units[selectionTargetUnitID].x;
            if (horseAndRamCount != 0) {
                MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                    DAT_PathFindingState::ptr)(x, DAT_UnitsState::instance.units[selectionTargetUnitID].y, -1, -1, 100000);
            } else {
                int const y = DAT_UnitsState::instance.units[selectionTargetUnitID].y;
                if (allAssassins != FALSE) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                        DAT_PathFindingState::ptr)(x, y, 0xffffffff, 0xffffffff, 100000, 0);
                } else {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                        DAT_PathFindingState::ptr)(x, y, -1, -1, 100000, FALSE);
                }
            }
            for (int i = 0; DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile1 != 0; ++i) {
                int const tileUnk = DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile1;
                if (DAT_TileMapState::instance.WalkLayer[tileUnk]
                    == DAT_PathFindingState::instance.searchGeneration) {
                    DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile3OrAnotherHelper
                        = DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                } else {
                    DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile3OrAnotherHelper = 10000000;
                }
            }
            int swapped;
            do {
                tribeIDThenSortIdx = 0;
                swapped = 0;
                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 == 0) {
                    break;
                }
                do {
                    int const tile2 = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx]
                                          .tile2OrAHelper;
                    if (tile2 == 0) {
                        break;
                    }
                    int const nextTile1
                        = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1].tile1;
                    if (nextTile1 == 0) {
                        break;
                    }
                    int const nextTile2
                        = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1]
                              .tile2OrAHelper;
                    if (nextTile2 == 0) {
                        break;
                    }
                    int const cost
                        = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile3OrAnotherHelper;
                    int const nextCost
                        = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1].tile3OrAnotherHelper;
                    if (cost > nextCost) {
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1].tile1
                            = DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile1;
                        swapped = 1;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile1
                            = nextTile1;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile2OrAHelper
                            = nextTile2;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1]
                            .tile2OrAHelper = tile2;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile3OrAnotherHelper
                            = nextCost;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx + 1].tile3OrAnotherHelper
                            = cost;
                    }
                    ++tribeIDThenSortIdx;
                } while (DAT_PathFindingState::instance.searchQueue.destinationsArray[tribeIDThenSortIdx].tile1 != 0);
            } while (swapped != 0);
            int outCount = 0;
            for (int i = 0; DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile1 != 0; ++i) {
                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile3OrAnotherHelper != 10000000) {
                    if (i != outCount) {
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[outCount].tile1
                            = DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile1;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[outCount].tile2OrAHelper
                            = DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile2OrAHelper;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[outCount].tile3OrAnotherHelper
                            = DAT_PathFindingState::instance.searchQueue.destinationsArray[i].tile3OrAnotherHelper;
                    }
                    ++outCount;
                }
            }
            DAT_PathFindingState::instance.searchQueue.destinationsArray[outCount].tile1 = 0;
        }

    }
}
}
