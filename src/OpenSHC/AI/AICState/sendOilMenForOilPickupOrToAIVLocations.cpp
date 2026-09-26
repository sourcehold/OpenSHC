#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::Map::Units::UnitInstructionType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D44E0
    void AICState::sendOilMenForOilPickupOrToAIVLocations(int playerID)
    {
        int oilSmelterID = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id;
        int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[1];
        if (count < 1) {
            return;
        }
        if (count == 10) {
            count = 9;
        }

        // Oil men tribes start at offset 71 in the tribe ID array
        for (int i = 1; i <= count; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[70 + i];
            if (tribeID == 0) {
                continue;
            }
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[70 + i]) {
                continue;
            }

            if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                    .resourceToDeposit
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits, DAT_TribesState::ptr)(tribeID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(
                    tribeID, OpenSHC::AI::AIVUT_ENGINEER, i - 1);
                continue;
            }

            // Send for oil duty
            if (oilSmelterID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    tribeID, OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, oilSmelterID,
                    DAT_BuildingsState::instance.buildings[oilSmelterID].uid, 0);
            }
        }
    }

}
}
