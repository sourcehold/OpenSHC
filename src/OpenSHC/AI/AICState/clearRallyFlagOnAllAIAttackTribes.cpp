#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE790
    void AICState::clearRallyFlagOnAllAIAttackTribes(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        for (int i = 0; i < 11; i++) {
            int tribeType = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;
            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeType + j];
                if (tribeID == 0)
                    continue;
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[j + tribeType])
                    continue;

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits, DAT_TribesState::ptr)(
                    tribeID);
            }
        }
    }

}
}
