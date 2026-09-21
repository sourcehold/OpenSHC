#include "../AICState.func.hpp"

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
    void AICState::sendTribeToAIVLocationSlot(int tribeID, AIVUnitType aivUnitType, int slotIndex)
    {
        int owner = DAT_TribesState::instance.tribes[tribeID].owner;

        // Find the slotIndex-th non-empty slot
        int tile = 0;
        for (int i = 0; i < 10; i++) {
            if (DAT_GameState::instance.playerDataArray[owner].aivUnitLocationSlots[aivUnitType][i] == 0) {
                continue;
            }
            slotIndex--;
            if (slotIndex < 0) {
                tile = DAT_GameState::instance.playerDataArray[owner].aivUnitLocationSlots[aivUnitType][i];
                break;
            }
        }

        int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;

        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(tribeID, tile)
            != FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                tribeID, x, y, 0);
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, owner);
    }
}
}
