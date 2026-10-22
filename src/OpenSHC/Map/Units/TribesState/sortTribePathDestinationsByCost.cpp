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

        /*
          The unit-ID local stays `short`, although our movzx-plus-movsx pair against the
          original's single movsx says otherwise: widening it costs 2.2 points
          (28.8% -> 26.6%, norm 30.3% -> 28.0%). Its `bool` flag stays a byte for the same
          reason: BOOLEnum costs 5.3 points (28.8% -> 23.5%).
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524930
        void TribesState::sortTribePathDestinationsByCost(int tribeID, int horseAndRamCount)
        {
            BOOLEnum BVar8 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            short sVar1 = this->tribes[tribeID].selectionTargetUnitID;
            uint x = (uint)DAT_UnitsState::instance.units[sVar1].x;
            /*
              Both of these were the wrong way round. The original computes x before the
              first test and jumps away when the count is zero - `cmp dword ptr [esp +
              0x10], 0; je 0x1e` - so the ram-and-horse call is the fall-through, and
              inside the other branch `test ecx, ecx; je 0x7` falls through to the
              all-assassins call. Written `if (!count)` and `if (!BVar8)` both bodies are
              emitted in the far block and every branch past them shifts.
             */
            if (horseAndRamCount) {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                    DAT_PathFindingState::ptr)(x, (int)(DAT_UnitsState::instance.units[sVar1].y), -1, -1, 100000);
            } else {
                uint y = (uint)DAT_UnitsState::instance.units[sVar1].y;
                if (BVar8) {
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                        DAT_PathFindingState::ptr)(x, y, 0xffffffff, 0xffffffff, 100000, 0);
                } else {
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                        DAT_PathFindingState::ptr)(x, y, -1, -1, 100000, FALSE);
                }
            }
            /*
              All three loops walk one array. The decompiler printed them as byte offsets
              into two different spellings of the same address - the search queue itself
              and a `climbData + 200` cast - but climbData is at 0x1084 and the queue at
              0x1a3a4, which is 200 ClimbData further on, so both are
              `searchQueue.destinationsArray` and every `+ 0xc` offset is one entry.

              The array is subscripted off the global rather than through a local base
              pointer. The original addresses every field as `[offset + <global> + N]`,
              strength-reducing the subscript to a byte offset it recomputes from the
              counter at the bottom of each loop (`add ecx, 1; lea eax, [ecx + ecx*2];
              add eax, eax; add eax, eax`); a `PathHelper12* const` local for the array
              makes MSVC keep the base in a register and address `[ptr + N]` instead,
              which is worth almost thirty points across the three loops: the same code
              with a `PathHelper12* const _destinations` local measures 26.4%, and
              subscripting the global measures 56.2%.
             */
            int _index = 0;
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 != 0) {
                /*
                  The entry pointer is what the original reads the tile through
                  (`mov edx, [edx]`), recomputed from the counter at the bottom alongside
                  the offset it stores through.
                 */
                PathHelper12* _entry = DAT_PathFindingState::instance.searchQueue.destinationsArray;
                do {
                    /*
                      Ten million is the cost given to a destination the current search did
                      not reach, which is what the compaction loop below drops entries on.
                     */
                    int const _tile = _entry->tile1;
                    if (DAT_TileMapState::instance.WalkLayer[_tile]
                        == DAT_PathFindingState::instance.searchGeneration) {
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper
                            = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    } else {
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper = 10000000;
                    }
                    _index = _index + 1;
                    _entry = DAT_PathFindingState::instance.searchQueue.destinationsArray + _index;
                } while (_entry->tile1 != 0);
            }
            /*
              Bubble sort of the reached destinations by cost, cheapest first. Both the
              counter and the flag live in stack slots the original zeroes from one
              register before the emptiness test (`xor ecx, ecx; cmp [..], ecx;
              mov [esp + 0x14], ecx; mov [esp + 0x18], ecx`), so they are assigned at the
              top of the outer loop and the test follows them.
             */
            bool bVar7;
            do {
                _index = 0;
                bVar7 = false;
                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 == 0)
                    break;
                do {
                    /*
                      Three separate tests, each jumping to the flag check at the bottom of
                      the outer loop (`test ebp, ebp; jz 0x00524aab`).
                     */
                    int const _tile2 = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile2OrAHelper;
                    if (!_tile2)
                        break;
                    int const _nextTile1 = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile1;
                    if (!_nextTile1)
                        break;
                    int const _nextTile2 = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile2OrAHelper;
                    if (!_nextTile2)
                        break;
                    int const _cost = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper;
                    int const _nextCost = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile3OrAnotherHelper;
                    if (_nextCost < _cost) {
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile1 = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile1;
                        bVar7 = true;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile1 = _nextTile1;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile2OrAHelper = _nextTile2;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile2OrAHelper = _tile2;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper = _nextCost;
                        DAT_PathFindingState::instance.searchQueue.destinationsArray[_index + 1].tile3OrAnotherHelper = _cost;
                    }
                    _index = _index + 1;
                } while (DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile1 != 0);
            } while (bVar7);
            /*
              Compaction: the destinations the search did not reach are dropped and the
              array is terminated with a zero tile. Both counters are zeroed before the
              emptiness test again, and the write cursor is a pointer to the middle field
              of its entry - `lea esi, [<global> + 4]` advanced by 0xc, with the three
              fields written as [esi - 4], [esi] and [esi + 4].
             */
            int _keptCount = 0;
            _index = 0;
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 != 0) {
                PathHelper12* _entry = DAT_PathFindingState::instance.searchQueue.destinationsArray;
                int* _write = &DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    if (DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper != 10000000) {
                        if (_index != _keptCount) {
                            _write[-1] = _entry->tile1;
                            *_write = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile2OrAHelper;
                            _write[1] = DAT_PathFindingState::instance.searchQueue.destinationsArray[_index].tile3OrAnotherHelper;
                        }
                        _keptCount = _keptCount + 1;
                        _write = _write + 3;
                    }
                    _index = _index + 1;
                    _entry = DAT_PathFindingState::instance.searchQueue.destinationsArray + _index;
                } while (_entry->tile1 != 0);
            }
            DAT_PathFindingState::instance.searchQueue.destinationsArray[_keptCount].tile1 = 0;
        }

    }
}
}
