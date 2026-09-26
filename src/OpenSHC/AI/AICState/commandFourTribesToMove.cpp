#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF7C0
    void AICState::commandFourTribesToMove(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        int destIndex = 0;
        for (int i = 0; i < 3; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[186 + i];
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 186])
                continue;

            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_STAND_GROUND;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                tribeID,
                DAT_GameState::instance.mapAndTime.aiTribeMoveDestinationXYPairArray1[playerID * 5][destIndex].xOffset,
                DAT_GameState::instance.mapAndTime.aiTribeMoveDestinationXYPairArray1[playerID * 5][destIndex].yOffset,
                0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
            destIndex++;
        }
    }

}
}
