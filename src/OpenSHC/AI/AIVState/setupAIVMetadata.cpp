#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECEF0
    int AIVState::setupAIVMetadata(int playerID)
    {
        int aivID = 1;
        AIVSpec* pSlot = &this->SEC_AIVS[1];
        do {
            if (pSlot->playerID == 0) {
                this->SEC_AIVS[aivID].playerID = playerID;

                int aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
                this->SEC_AIVS[aivID].aiType = aiType;

                this->SEC_AIVS[aivID].currentStepGoal = 0;
                this->SEC_AIVS[aivID].aivPoorCounter = 0;
                this->SEC_AIVS[aivID].aivSubType = 0;

                this->SEC_AIVS[aivID].aivPoorLimit_OR_AIC_buildInterval
                    = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);

                this->aivCount = this->aivCount + 1;

                return aivID;
            }
            aivID = aivID + 1;
            pSlot = pSlot + 1;
        } while (aivID < 9);
        return 0;
    }

}
}
