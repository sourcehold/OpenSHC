#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A67D0
        void PathFindingState::spawnUnitAndAddToTribe(
            int playerID, int displayColor, int count, UnitType unitType, undefined4 tribeID)
        {
            int* local_4;
            int _tile;
            this->calculations = this->calculations + 1;
            int iVar2 = -1;
            this->searchQueue.readIndex = 0;
            if (this->searchQueue.writeIndex != 0) {
                local_4 = &DAT_GameState::instance.mapAndTime.somePairArray.y;
                do {
                    uint _y = (uint)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uint _x = _tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                    if (DAT_TileMapState::instance.CertainPathLayer[_tile] != 100) {
                        int _unitID_2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                            DAT_UnitsState::ptr)(playerID, displayColor, (int)(_x * 8), (int)(_y * 8), 8, unitType);
                        if (_unitID_2 != 0) {
                            count = count + -1;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe,
                                DAT_TribesState::ptr)(_unitID_2, tribeID);
                        }
                        if (count < 1) {
                            return;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                            _x, _y, 10, 2);
                        ((XYPair*)(local_4 + -1))->x = _x;
                        *local_4 = _y;
                        local_4 = local_4 + 2;
                        iVar2 = _tile;
                    }
                    if (0x117cdef < (int)local_4)
                        break;
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            if ((0 < count) && (iVar2 != -1)) {
                short sVar1 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar2];
                _tile = DAT_ViewportRenderState::instance.translationMatrix[sVar1].addXgetTile;
                do {
                    int _unitID
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            playerID, displayColor, (iVar2 - _tile) * 8, (int)(sVar1 * 8), 8, unitType);
                    if (_unitID != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            _unitID, tribeID);
                    }
                    count = count + -1;
                } while (0 < count);
            }
            return;
        }

    }
}
}
