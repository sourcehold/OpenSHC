#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAEA0
    void AICState ::aiUpdateTaxesAndRations(int playerID)
    {
        int _offset;
        int _newTaxesVal;
        int _newTaxes;
        int _popularity;
        int _currentTaxes;
        int _taxesMin;
        int _taxesMax;
        int _peasants;
        int _decision;
        int _totalFood_2;
        int _totalFood_1;
        int _taxes;
        AITypeInt _aiType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        _offset = (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4;

        _popularity = DAT_GameState::instance.playerDataArray[playerID].popularity;

        // criticalPopularity - comparison order matches original: first jg sets decision=2 (critical)
        if (*(int*)((int)this + _offset + 0x18) >= _popularity) {
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 2;
        } else if (*(int*)((int)this + _offset + 0x1c) < _popularity) {
            // highestPopularity
            if (*(int*)((int)this + _offset + 0x20) >= _popularity) {
                DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 0;
            }
        } else {
            DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue = 1;
        }

        _decision = DAT_GameState::instance.playerDataArray[playerID].aiPopularityDecisionValue;

        if (_decision == 2) {
            _totalFood_2 = DAT_GameState::instance.playerDataArray[playerID].totalFood;
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 2;

            if (_totalFood_2 <= 0) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else if (_totalFood_2 < 5) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
            } else {
                int _r = 0;
                if (_totalFood_2 > 8) _r = 1;
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = _r + 3;
            }

            goto LAB_004cb010;
        }

        if (_decision == 1) {
            _currentTaxes = DAT_GameState::instance.playerDataArray[playerID].taxesSetting;
            _taxesMin = *(int*)((int)this + _offset + 0x24);

            if (_taxesMin < _currentTaxes) {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _currentTaxes - 1;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxesMin;
            }

            _totalFood_1 = DAT_GameState::instance.playerDataArray[playerID].totalFood;

            if (_totalFood_1 <= 0) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
            } else {
                if (_totalFood_1 <= 0xa)
                    goto LAB_004caff1;
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 3;
            }
        } else {
            if (_decision != 0)
                goto LAB_004cb010;

            _taxes = DAT_GameState::instance.playerDataArray[playerID].taxesSetting;
            _taxesMax = *(int*)((int)this + _offset + 0x28);

            if (_taxes < _taxesMax) {
                _peasants = DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants;
                int _r2 = 0;
                if (_peasants < 0xf) {
                    if (_peasants >= 0xa) _r2 = 1;
                    _newTaxesVal = _r2 + 4;
                } else {
                    _newTaxesVal = 6;
                }

                if (DAT_GameState::instance.playerDataArray[playerID].storedPopularityPercent > _popularity) {
                    if (_taxes <= _newTaxesVal)
                        goto LAB_004cafcd;
                    _newTaxes = _taxes - 1;
                } else {
                    _newTaxes = _taxes + 1;
                }
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _newTaxes;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].taxesSetting = _taxesMax;
            }

        LAB_004cafcd:
            _totalFood_1 = DAT_GameState::instance.playerDataArray[playerID].totalFood;

            if (_totalFood_1 < 0xb) {
                DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
                goto LAB_004cb010;
            }

        LAB_004caff1:
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 2;
        }

        _newTaxes = *(int*)((int)this + _offset + 0xa8);

        if ((_newTaxes != 0) && (_newTaxes <= _totalFood_1)) {
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
        }

    LAB_004cb010:
        if (DAT_GameState::instance.playerDataArray[playerID].taxesSetting < 0) {
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 0;
        }

        if (11 < DAT_GameState::instance.playerDataArray[playerID].taxesSetting) {
            DAT_GameState::instance.playerDataArray[playerID].taxesSetting = 11;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].rationsSetting < 0) {
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 0;
        }

        if (4 < DAT_GameState::instance.playerDataArray[playerID].rationsSetting) {
            DAT_GameState::instance.playerDataArray[playerID].rationsSetting = 4;
        }

        return;
    }
}
}
