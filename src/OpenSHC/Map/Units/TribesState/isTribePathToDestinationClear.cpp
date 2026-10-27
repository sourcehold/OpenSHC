#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          The two guards stay as `||` chains. The original merges every failure into a
          single `return 0` at 0x524cd7 and places it inline right after the first chain,
          so the second chain's tests jump backward into it (`ja 0x00524cd7`, encoded
          `77ea`) - a full epilogue, `pop/pop/pop/xor eax,eax/pop/pop/ret 0x14`, not a
          jump to a shared one. Ours emits that block at the end of the function instead,
          and that placement is what the remaining gap is mostly made of.

          Writing the first chain positively with the whole rest of the function nested
          inside it, so that the shared `return 0` is the fall-out rather than the taken
          branch, measures 18.8% -> 18.8%. MSVC puts that epilogue at the end of the
          function whichever way round the guard is written.

          Splitting the chains into six separate `if`s is what took
          trySpawnAdditionalWildlifeForTribe from 87.2% to a full match, so it was worth
          retrying here. Measured with reccmp: 18.8% -> 17.4%. The earlier note against
          it cited quick_diff 0.6635 -> 0.6296, which is below the ratio that tool is
          documented to be reliable at; the conclusion was right anyway.

          What ours also lacks is the original's second local slot: it allocates one
          (`push ecx`) and reuses the dead tribeID parameter slot for the second counter,
          where the original has `sub esp, 8` and two proper locals.

          Copying the parameter into `int const _tribeID` and using that through the loop
          does not buy the slot: measured 18.8% -> 18.8%, MSVC coalesces the copy back onto
          the incoming argument. The slot comes from whatever second value the original
          keeps live, not from naming the first one.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524CA0
        undefined4 TribesState::isTribePathToDestinationClear(
            int tribeID, uint fromX, uint fromY, uint toX, uint toY)
        {
            int _unitIndex = 0;
            if (399 < fromX || 399 < fromY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[fromY * 400 + fromX] == 0) {
                return (undefined4)(0);
            }
            if (399 < toX || 399 < toY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[toY * 400 + toX] == 0) {
                return (undefined4)(0);
            }
            int const _toTile = DAT_ViewportRenderState::instance.translationMatrix[toY].addXgetTile + toX;
            if (DAT_TileMapState::instance.PathConnectionLayer
                    [DAT_ViewportRenderState::instance.translationMatrix[fromY].addXgetTile + fromX]
                != DAT_TileMapState::instance.PathConnectionLayer[_toTile]) {
                return (undefined4)(0);
            }
            this->ALG_ResultTileIndex = 0;
            /*
              The original computes this once, before the search is seeded. The
              decompiler's `2 - (uVar1 & 0x100)` subtracts the mask itself, but the binary
              has `and 0x100; neg; sbb; add 2`, which is 2 minus a 0/1 flag.
             */
            int const _searchMode = (DAT_TileMapState::instance.LogicLayer[_toTile] & 0x100) != 0 ? 1 : 2;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                DAT_PathFindingState::ptr)(toX, toY, -1, -1, 500, FALSE);
            /*
              The size lives behind a pointer the original takes once, after the search is
              seeded (`lea edx, [ecx + edi + 0x5c]` at 0x524d6e, kept in a stack slot and
              re-read at the top of every iteration).
             */
            short const* const _size = &this->tribes[tribeID].size;
            while (true) {
                int _unitID;
                do {
                    if (_unitIndex >= *_size) {
                        return (undefined4)(1);
                    }
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitIndex);
                    _unitIndex = _unitIndex + 1;
                } while ((DAT_UnitsState::instance.units[_unitID].logicalState != Map::Units::ULS_NORMAL)
                    || (DAT_UnitsState::instance.units[_unitID].dying != 0));
                int _blockingUnitID = MACRO_CALL_MEMBER(
                    Map::Navigation::PathFindingState_Func::findClosestTileToStartingTile, DAT_PathFindingState::ptr)(
                    _searchMode);
                this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                if ((int)this->ALG_ResultTileIndex >= 500)
                    break;
                _blockingUnitID = (int)(short)DAT_TileMapState::instance.UnitLayer[_blockingUnitID];
                if (_blockingUnitID && _unitID != _blockingUnitID
                    && DAT_UnitsState::instance.units[_blockingUnitID].tribeID != tribeID
                    && DAT_UnitsState::instance.units[_blockingUnitID].tunnelerFinishedDigging != 2) {
                    return (undefined4)(0);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
