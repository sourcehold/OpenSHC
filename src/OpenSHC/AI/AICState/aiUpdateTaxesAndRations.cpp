#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAEA0
    void AICState::aiUpdateTaxesAndRations(int playerID)
    {
        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == OpenSHC::AI::AIT_NULL)
            return;

        _aiType = _aiType - 1;
        int const _popularity = DAT_GameState::instance.playerDataArray[playerID].popularity;

        if (_popularity <= (int)this->aics[_aiType].criticalPopularity) {
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 2;
        } else if (_popularity <= (int)this->aics[_aiType].lowestPopularity) {
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 1;
        } else if (_popularity >= (int)this->aics[_aiType].highestPopularity) {
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 0;
        }

        int const _decision = DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue;

        if (_decision == 2) {
            int const _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 2;
            if (_totalFood <= 0) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else if (_totalFood <= 4) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = (_totalFood > 8) + 3;
            }
        } else if (_decision == 1) {
            int const _currentTaxes = DAT_GameState::instance.playerDataArray[playerID].taxesSetting;
            int const _taxesMin = (int)this->aics[_aiType].taxesMin;
            if (_currentTaxes > _taxesMin) {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _currentTaxes - 1;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxesMin;
            }
            int const _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;
            if (_totalFood <= 0) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else if (_totalFood <= 10) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 3;
            }
            int const _rationsMod = (int)this->aics[_aiType].doubleRationsFoodThreshold;
            if (_rationsMod != 0 && _totalFood >= _rationsMod)
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
        } else if (_decision == 0) {
            int const _taxes = DAT_GameState::instance.playerDataArray[playerID].taxesSetting;
            int const _taxesMax = (int)this->aics[_aiType].taxesMax;

            if (_taxes < _taxesMax) {
                int const _peasants = DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants;
                int _newTaxesVal;
                if (_peasants >= 0xf) {
                    _newTaxesVal = 6;
                } else {
                    _newTaxesVal = (_peasants >= 0xa) + 4;
                }

                if (!(DAT_GameState::instance.playerDataArray[playerID].storedPopularityPercent > _popularity)) {
                    DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxes + 1;
                } else if (_taxes > _newTaxesVal) {
                    DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxes - 1;
                }
            } else {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxesMax;
            }

            int const _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;
            if (_totalFood <= 10) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
                int const _rationsMod = (int)this->aics[_aiType].doubleRationsFoodThreshold;
                if (_rationsMod != 0 && _totalFood >= _rationsMod)
                    DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
            }
        }

        if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting < 0)
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 0;
        if (11 < DAT_GameState::instance.playerDataArray[playerID].taxesSetting)
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 11;
        if (DAT_GameState::instance.playerDataArray[playerID].rationsSetting < 0)
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
        if (4 < DAT_GameState::instance.playerDataArray[playerID].rationsSetting)
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
    }
}
}
