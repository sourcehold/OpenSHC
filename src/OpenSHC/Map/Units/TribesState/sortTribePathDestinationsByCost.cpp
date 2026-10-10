#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingStatePartB.hpp"
#include "OpenSHC/Map/Navigation/PathHelper12.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Navigation::PathFindingStatePartB;
        using Map::Navigation::PathHelper12;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524930
        void TribesState::sortTribePathDestinationsByCost(int tribeID, int horseAndRamCount)
        {
            short sVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            bool bVar7;
            BOOLEnum BVar8;
            int _nextOffset1;
            int iVar9;
            int _nextOffset2;
            uint y;
            PathFindingStatePartB* _p2;
            uint x;
            int _counter2;
            int* _p2Tile2;
            int _tile1;
            int _offset1;
            PathFindingStatePartB* _p;
            int _index1;
            int _index2;
            BVar8 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            sVar1 = this->tribes[tribeID].selectionTargetUnitID;
            x = (uint)DAT_UnitsState::instance.units[sVar1].x;
            if (!horseAndRamCount) {
                y = (uint)DAT_UnitsState::instance.units[sVar1].y;
                if (!BVar8) {
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                        DAT_PathFindingState::ptr)(x, y, -1, -1, 100000, FALSE);
                } else {
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                        DAT_PathFindingState::ptr)(x, y, 0xffffffff, 0xffffffff, 100000, 0);
                }
            } else {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                    DAT_PathFindingState::ptr)(
                    x, (int)((int)(DAT_UnitsState::instance.units[sVar1].y)), -1, -1, 100000);
            }
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 != 0) {
                _p = &DAT_PathFindingState::instance.searchQueue;
                _nextOffset1 = 0;
                _offset1 = 0;
                do {
                    _tile1 = _p->destinationsArray[0].tile1;
                    if (DAT_TileMapState::instance.WalkLayer[_tile1]
                        == DAT_PathFindingState::instance.searchGeneration) {
                        *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[0]
                                    .tile3OrAnotherHelper
                            + _nextOffset1) = (int)DAT_TileMapState::instance.CertainPathLayer[_tile1];
                    } else {
                        *(undefined4*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                           ->destinationsArray[0]
                                           .tile3OrAnotherHelper
                            + _nextOffset1) = 10000000;
                    }
                    _nextOffset1 = _offset1 * 0xc + 0xc;
                    _index1 = _offset1 + 1;
                    _p = (PathFindingStatePartB*)(((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData
                                                       + 200))
                                                      ->destinationsArray
                        + _offset1 + 1);
                    _offset1 = _offset1 + 1;
                } while (((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                             ->destinationsArray[_index1]
                             .tile1
                    != 0);
            }
            do {
                tribeID = 0;
                bVar7 = false;
                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 == 0)
                    break;
                iVar9 = 0;
                do {
                    iVar2 = *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                        ->destinationsArray[0]
                                        .tile2OrAHelper
                        + iVar9);
                    if (!iVar2
                        || (iVar3
                            = *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                          ->destinationsArray[1]
                                          .tile1
                                + iVar9),
                            iVar3 == 0)
                        || (iVar4
                            = *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                          ->destinationsArray[1]
                                          .tile2OrAHelper
                                + iVar9),
                            iVar4 == 0))
                        break;
                    iVar5 = *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                        ->destinationsArray[0]
                                        .tile3OrAnotherHelper
                        + iVar9);
                    iVar6 = *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                        ->destinationsArray[1]
                                        .tile3OrAnotherHelper
                        + iVar9);
                    if (iVar6 < iVar5) {
                        *(undefined4*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                           ->destinationsArray[1]
                                           .tile1
                            + iVar9)
                            = *(undefined4*)((int)&DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1
                                + iVar9);
                        bVar7 = true;
                        *(int*)((int)&DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 + iVar9)
                            = iVar3;
                        *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[0]
                                    .tile2OrAHelper
                            + iVar9) = iVar4;
                        *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[1]
                                    .tile2OrAHelper
                            + iVar9) = iVar2;
                        *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[0]
                                    .tile3OrAnotherHelper
                            + iVar9) = iVar6;
                        *(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[1]
                                    .tile3OrAnotherHelper
                            + iVar9) = iVar5;
                    }
                    iVar9 = tribeID * 0xc + 0xc;
                    iVar2 = tribeID + 1;
                    tribeID = tribeID + 1;
                } while (((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                             ->destinationsArray[iVar2]
                             .tile1
                    != 0);
            } while (bVar7);
            iVar9 = 0;
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 != 0) {
                _p2 = &DAT_PathFindingState::instance.searchQueue;
                _nextOffset2 = 0;
                _p2Tile2 = &DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper;
                _counter2 = 0;
                do {
                    if (*(int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                    ->destinationsArray[0]
                                    .tile3OrAnotherHelper
                            + _nextOffset2)
                        != 10000000) {
                        if (_counter2 != iVar9) {
                            ((PathHelper12*)(_p2Tile2 + -1))->tile1 = _p2->destinationsArray[0].tile1;
                            *_p2Tile2 = *(
                                int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                          ->destinationsArray[0]
                                          .tile2OrAHelper
                                + _nextOffset2);
                            _p2Tile2[1] = *(
                                int*)((int)&((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                                          ->destinationsArray[0]
                                          .tile3OrAnotherHelper
                                + _nextOffset2);
                        }
                        iVar9 = iVar9 + 1;
                        _p2Tile2 = _p2Tile2 + 3;
                    }
                    _nextOffset2 = _counter2 * 0xc + 0xc;
                    _index2 = _counter2 + 1;
                    _p2 = (PathFindingStatePartB*)(((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData
                                                        + 200))
                                                       ->destinationsArray
                        + _counter2 + 1);
                    _counter2 = _counter2 + 1;
                } while (((PathFindingStatePartB*)(DAT_PathFindingState::instance.climbData + 200))
                             ->destinationsArray[_index2]
                             .tile1
                    != 0);
            }
            DAT_PathFindingState::instance.searchQueue.destinationsArray[iVar9].tile1 = 0;
        }

    }
}
}
