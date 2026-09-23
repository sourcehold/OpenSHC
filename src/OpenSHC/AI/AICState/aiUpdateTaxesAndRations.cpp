#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAEA0
    void AICState::aiUpdateTaxesAndRations(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;

        int popularity = DAT_GameState::instance.playerDataArray[playerID].popularity;
        if (popularity <= this->aics[aicIndex].criticalPopularity)
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 2;
        else if (popularity <= this->aics[aicIndex].lowestPopularity)
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 1;
        else if (popularity >= this->aics[aicIndex].highestPopularity)
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 0;

        if (DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue == 2) {
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 2;
            if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 0)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            else if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 4)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
            else if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 8)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 3;
            else
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue == 1) {
            if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting > this->aics[aicIndex].taxesMin)
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting--;
            else
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = this->aics[aicIndex].taxesMin;

            if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 0)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            else if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 10)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
            else
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 3;
            if (this->aics[aicIndex].doubleRationsFoodThreshold != 0
                && DAT_GameState::instance.playerDataArray[playerID].totalFood
                    >= this->aics[aicIndex].doubleRationsFoodThreshold)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue == 0) {
            if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting < this->aics[aicIndex].taxesMax) {
                int lowerTaxesLimit;
                if (DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants >= 15)
                    lowerTaxesLimit = 6;
                else if (DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants >= 10)
                    lowerTaxesLimit = 5;
                else
                    lowerTaxesLimit = 4;

                if (DAT_GameState::instance.playerDataArray[playerID].storedPopularityPercent <= popularity)
                    DAT_GameState::instance.playerDataArray[playerID].taxesSetting++;
                else if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting > lowerTaxesLimit)
                    DAT_GameState::instance.playerDataArray[playerID].taxesSetting--;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = this->aics[aicIndex].taxesMax;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 10) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
                if (this->aics[aicIndex].doubleRationsFoodThreshold != 0
                    && DAT_GameState::instance.playerDataArray[playerID].totalFood
                        >= this->aics[aicIndex].doubleRationsFoodThreshold)
                    DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
            }
        }

        if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting < 0)
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting > 11)
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 11;
        if (DAT_GameState::instance.playerDataArray[playerID].rationsSetting < 0)
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].rationsSetting > 4)
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
    }
}
}
