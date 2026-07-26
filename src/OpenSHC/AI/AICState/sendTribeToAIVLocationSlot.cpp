#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      [doc]
       @param slotIndex int slotIndex to browse to
       decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2E00
    void AICState ::sendTribeToAIVLocationSlot(int tribeID, AIVUnitType aivUnitType, int slotIndex)

    {

        int _slotIndex;

        BOOLEnum _canNavigate;

        int* _ptrSlot;

        int _tile;

        int _x;

        int _owner;

        short _y;

        /*
            all experimental, heavy local reuse... */

        _owner = DAT_TribesState::instance.tribes[tribeID].owner;

        _tile = 0;

        _slotIndex = 0;

        /*
            aivUnitLocationSlots */

        _ptrSlot = (int*)(_owner * 0x39f4 + 0x115eb14 + aivUnitType * 0x28);

        while ((*_ptrSlot == 0 || (slotIndex = slotIndex + -1, -1 < slotIndex))) {

            _slotIndex = _slotIndex + 1;

            _ptrSlot = _ptrSlot + 1;

            if (9 < _slotIndex) {

            LAB_004d2e6d:
                _y = DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_tile];

                _x = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;

                _canNavigate = MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(tribeID, _tile);

                if (_canNavigate == FALSE) {

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, _owner);

                    return;
                }

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                    tribeID, (uint)((int)(_tile - _x)), (uint)((int)((int)_y)), 0);

                return;
            }
        }

        _tile = DAT_GameState::instance.playerDataArray[_owner].aivUnitLocationSlots[aivUnitType][_slotIndex];

        goto LAB_004d2e6d;
    }

}
}
