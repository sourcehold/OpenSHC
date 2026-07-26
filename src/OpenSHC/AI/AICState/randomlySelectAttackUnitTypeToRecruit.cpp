#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIUnitBehaviourType;

    /*
      doc:
       Determines which AI unit behaviour groups need recruiting because AIC Max units hasn't been
       reached for that category, then randomly selects one of those groups to recruit

       @returns AiUnitBehaviourType The selected unit behaviour type
       decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC070
    AIUnitBehaviourType AICState ::randomlySelectAttackUnitTypeToRecruit(int playerID)

    {

        int* piVar1;

        dword _engineersCount;

        int _index2;

        int _rng;

        int _index;

        int _aiTypeMin1;

        dword _maxDiggingUnits;

        dword _maxAssassins;

        dword _maxUnit2;

        dword _maxLaddermen;

        dword _maxTunnelers;

        dword _maxUnitPatrol;

        AITypeInt _aiType;

        int _attackedPlayerID;

        dword _maxEngineers;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {

            return OpenSHC::AI::AIUBT_ATTUNITMAIN;
        }

        _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;

        _index = 0;

        /*
            clear out flags */

        piVar1 = DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[0] + 1;

        do {

            *piVar1 = 0;

            piVar1 = piVar1 + 2;

        } while ((int)piVar1 < 0xb425ec);

        _maxEngineers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttMaxEngineers;

        _engineersCount = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave * 4;

        if ((int)_maxEngineers < (int)_engineersCount) {

            _engineersCount = _maxEngineers;
        }

        if ((_maxEngineers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops
                < (int)_engineersCount)) {

            _index = 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[0][1] = 1;
        }

        _maxDiggingUnits = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttDiggingUnitMax;

        if (((_maxDiggingUnits != 0)
                && (DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops < (int)_maxDiggingUnits))
            && (5 < DAT_GameState::instance.playerDataArray[_attackedPlayerID].field992_0x396c)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[1][1] = 1;
        }

        _maxAssassins = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttMaxAssassins;

        if ((_maxAssassins != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalAssassinTroops < (int)_maxAssassins)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[2][1] = 1;
        }

        _maxUnit2 = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttUnit2Max;

        if ((_maxUnit2 != 0) && (DAT_GameState::instance.playerDataArray[playerID].totalUnit2Troops < (int)_maxUnit2)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[3][1] = 1;
        }

        _maxLaddermen = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttMaxLaddermen;

        if ((_maxLaddermen != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalLaddermenTroops < (int)_maxLaddermen)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[4][1] = 1;
        }

        _maxTunnelers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttMaxTunnelers;

        if ((_maxTunnelers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalTunnelerTroops < (int)_maxTunnelers)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[5][1] = 1;
        }

        _maxUnitPatrol = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttUnitPatrolMax;

        if ((_maxUnitPatrol != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalUnitPatrolTroops < (int)_maxUnitPatrol)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[6][1] = 1;
        }

        _maxEngineers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttUnitBackupMax;

        if ((_maxEngineers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops < (int)_maxEngineers)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[7][1] = 1;
        }

        _maxEngineers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttUnitEngageMax;

        if ((_maxEngineers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops < (int)_maxEngineers)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[8][1] = 1;
        }

        _maxEngineers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttUnitSiegeDefMax;

        if ((_maxEngineers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops < (int)_maxEngineers)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[9][1] = 1;
        }

        _maxEngineers = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].AttMaxDefault;

        if ((_maxEngineers != 0)
            && (DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops < (int)_maxEngineers)) {

            _index = _index + 1;

            DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[10][1] = 1;
        }

        if (_index != 0) {

            _rng = (int)SEC_RNG::instance.currentNumber2 % _index;

            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

            _index2 = 0;

            do {

                if (DAT_SkirmishDefinedData::instance.DAT_AIBehaviourTypeUnitRequired[_index2][1] != 0) {

                    if (_rng == 0) {

                        return (AIUnitBehaviourType)(DAT_SkirmishDefinedData::instance
                                .DAT_AIBehaviourTypeUnitRequired[_index2][0]);
                    }

                    _rng = _rng + -1;
                }

                _index2 = _index2 + 1;

            } while (_index2 < 0xb);
        }

        return OpenSHC::AI::AIUBT_ATTUNITMAIN;
    }

}
}
