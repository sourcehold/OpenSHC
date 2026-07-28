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

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2E00
    void AICState ::sendTribeToAIVLocationSlot(int tribeID, AIVUnitType aivUnitType, int slotIndex)
    {
        int _owner = DAT_TribesState::instance.tribes[tribeID].owner;
        int _tile = 0;
        int _slotIndex = 0;
        int* _ptrSlot = (int*)(_owner * 0x39f4 + 0x115eb14 + aivUnitType * 0x28);

        // Find the slot at slotIndex, skipping empty entries
        while (*_ptrSlot == 0 || (slotIndex = slotIndex + -1, -1 < slotIndex)) {
            _slotIndex = _slotIndex + 1;
            _ptrSlot = _ptrSlot + 1;
            if (9 < _slotIndex)
                break;
        }

        if (_slotIndex <= 9)
            _tile = DAT_GameState::instance.playerDataArray[_owner].aivUnitLocationSlots[aivUnitType][_slotIndex];

        short _y = DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_tile];
        int _x = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;

        BOOLEnum _canNavigate = MACRO_CALL_MEMBER(
            OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(tribeID, _tile);

        if (_canNavigate == FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, _owner);
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
            tribeID, (uint)((int)(_tile - _x)), (uint)((int)((int)_y)), 0);
    }
}
}
