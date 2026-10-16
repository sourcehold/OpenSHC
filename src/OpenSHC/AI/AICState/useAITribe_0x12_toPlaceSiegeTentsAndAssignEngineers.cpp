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
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;
        int aiTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0x12];
        if (aiTribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[aiTribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0x12])
            return;

        int availableEngineers = DAT_TribesState::instance.tribes[aiTribeID].size;
        int requiredEngineers;
        int totalRequiredEngineers = 0;

        for (int i = 0; i < 8; i++) {
            if ((&this->aics[aicIndex].SiegeEngine1)[i] <= 0)
                break;
            for (int j = 0; j < 6; j++) {
                if ((&this->aics[aicIndex].SiegeEngine1)[i]
                    == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[j]) {
                    requiredEngineers = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[j];
                    break;
                }
            }
            if (totalRequiredEngineers + requiredEngineers > availableEngineers)
                break;
            totalRequiredEngineers += requiredEngineers;
        }

        if (totalRequiredEngineers <= 0)
            return;

        for (; DAT_TribesState::instance.tribes[aiTribeID].size != 0; totalRequiredEngineers--) {
            if (totalRequiredEngineers <= 0)
                break;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(aiTribeID);
        }

        MappersEnum siegeEngineType;
        for (int i = 0; i < 8; i++) {
            if ((&this->aics[aicIndex].SiegeEngine1)[i] <= 0)
                return;
            for (int j = 0; j < 6; j++) {
                if ((&this->aics[aicIndex].SiegeEngine1)[i]
                    == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[j]) {
                    requiredEngineers = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[j];
                    siegeEngineType = (MappersEnum)DAT_SkirmishDefinedData::instance.SiegeEngineCommandBuildingTypes[j];
                    break;
                }
            }
            if (requiredEngineers > availableEngineers)
                return;
            availableEngineers -= requiredEngineers;

            int tribeID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToSelection, this)(
                playerID, requiredEngineers);
            if (tribeID == 0)
                return;

            DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
            DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
            DAT_TribesState::instance.tribes[tribeID].attackWave
                = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;

            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                DAT_TroopValueState::ptr)(tribeID, siegeEngineType, 60, (UnitInstructionType)15);
        }
    }

}
}
