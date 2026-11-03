#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523920
        int TribesState::scatterTribeUnitsRandomly(int tribeID)
        {
            if (tribeID == 0) {
                return 0;
            }
            int const _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
            int unitSelectionIndex = 0;
            int _searchQueueIndex = 100;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[_targetUnitID].x,
                DAT_UnitsState::instance.units[_targetUnitID].y, -1, -1, 5000, 0);
            int const _queueTileCount = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::getComputationalTileIndex, DAT_PathFindingState::ptr)();
            int _size = this->tribes[tribeID].size;
            if (_queueTileCount < _size * 16 + 200) {
                return 0;
            }
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    _searchQueueIndex = _searchQueueIndex + 1 + (DAT_UnitsState::instance.units[unitID].fixedRng & 15);
                    int const _targetTile
                        = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getTileInSearchQueue,
                            DAT_PathFindingState::ptr)(_searchQueueIndex);
                    int const _targetTileY
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile];
                    int const _rowStartTile
                        = DAT_ViewportRenderState::instance.translationMatrix[_targetTileY].addXgetTile;
                    DAT_UnitsState::instance.units[unitID].targetY = (short)_targetTileY;
                    DAT_UnitsState::instance.units[unitID].targetX = (short)_targetTile - (short)_rowStartTile;
                    DAT_UnitsState::instance.units[unitID].state.generic = 209;
                }
            }
            return 1;
        }

    }
}
}
