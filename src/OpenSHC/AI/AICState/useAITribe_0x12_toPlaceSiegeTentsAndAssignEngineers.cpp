#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEFD0
    void AICState::useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers(int playerID)
    {
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == OpenSHC::AI::AIT_NULL)
            return;
        int _aicIndex = _aiType - 1;
        int _aiTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0x12];
        if (_aiTribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[_aiTribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0x12])
            return;

        int _availableEngineers = DAT_TribesState::instance.tribes[_aiTribeID].size;
        int _requiredEngineers;
        int _totalRequiredEngineers = 0;

        for (int i = 0; i < 8; i++) {
            if ((&this->aics[_aicIndex].SiegeEngine1)[i] <= 0)
                break;
            for (int j = 0; j < 6; j++) {
                if ((&this->aics[_aicIndex].SiegeEngine1)[i]
                    == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[j]) {
                    _requiredEngineers = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[j];
                    break;
                }
            }
            if (_totalRequiredEngineers + _requiredEngineers > _availableEngineers)
                break;
            _totalRequiredEngineers += _requiredEngineers;
        }

        if (_totalRequiredEngineers <= 0)
            return;

        for (; DAT_TribesState::instance.tribes[_aiTribeID].size != 0; _totalRequiredEngineers--) {
            if (_totalRequiredEngineers <= 0)
                break;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(
                _aiTribeID);
        }

        MappersEnum _siegeEngineType;
        for (int i = 0; i < 8; i++) {
            if ((&this->aics[_aicIndex].SiegeEngine1)[i] <= 0)
                return;
            for (int j = 0; j < 6; j++) {
                if ((&this->aics[_aicIndex].SiegeEngine1)[i]
                    == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[j]) {
                    _requiredEngineers = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[j];
                    _siegeEngineType
                        = (MappersEnum)DAT_SkirmishDefinedData::instance.SiegeEngineCommandBuildingTypes[j];
                    break;
                }
            }
            if (_requiredEngineers > _availableEngineers)
                return;
            _availableEngineers -= _requiredEngineers;

            int _tribeID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToSelection, this)(
                playerID, _requiredEngineers);
            if (_tribeID == 0)
                return;

            DAT_TribesState::instance.tribes[_tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
            DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
            DAT_TribesState::instance.tribes[_tribeID].attackWave
                = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;

            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                DAT_TroopValueState::ptr)(_tribeID, _siegeEngineType, 60, (UnitInstructionType)15);
        }
    }

}
}
