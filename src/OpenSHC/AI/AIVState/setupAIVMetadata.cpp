#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECEF0
    int AIVState::setupAIVMetadata(int playerID)
    {
        for (int aivID = 1; aivID < 9; ++aivID) {
            if (this->aivs[aivID].playerID != 0) {
                continue;
            }

            this->aivs[aivID].playerID = playerID;

            this->aivs[aivID].aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;

            this->aivs[aivID].currentStepGoal = 0;
            this->aivs[aivID].aivPoorCounter = 0;
            this->aivs[aivID].aivSubType = 0;

            this->aivs[aivID].aivPoorLimit_OR_AIC_buildInterval
                = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);

            ++this->aivCount;
            return aivID;
        }
        return 0;
    }

}
}
