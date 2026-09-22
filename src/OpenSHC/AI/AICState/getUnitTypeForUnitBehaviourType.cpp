#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC250
    UnitType AICState::getUnitTypeForUnitBehaviourType(int playerID, AIUnitBehaviourType unitBehaviourType)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return (UnitType)0;
        int aicIndex = aiType - 1;

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ENGINEERING)
            return OpenSHC::Map::Units::UT_E_ENGINEER;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_DIGGING)
            return (UnitType)this->aics[aicIndex].AttDiggingUnit;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_ASSASSINATION)
            return OpenSHC::Map::Units::UT_A_ASSASSIN;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_ATTUNIT2)
            return (UnitType)this->aics[aicIndex].AttUnit2;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_LADDERING)
            return OpenSHC::Map::Units::UT_E_LADDER;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_TUNNELING)
            return OpenSHC::Map::Units::UT_TUNNELER;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_PATROLLING)
            return (UnitType)this->aics[aicIndex].AttUnitPatrol;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_BACKUPING)
            return (UnitType)this->aics[aicIndex].AttUnitBackup;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_ENGAGING)
            return (UnitType)this->aics[aicIndex].AttUnitEngage;
        if (unitBehaviourType == OpenSHC::AI::AIUBT_SIEGEDEFENSE)
            return (UnitType)this->aics[aicIndex].AttUnitSiegeDef;
        if (unitBehaviourType != OpenSHC::AI::AIUBT_ATTUNITMAIN)
            return (UnitType)this->aics[aicIndex].AttUnitMain1;

        if ((&this->aics[aicIndex].AttUnitMain1)[DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex]
            == 0)
            DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex >= 4)
            DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = 0;

        int choice = DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex;
        UnitType unitType = (UnitType)(&this->aics[aicIndex].AttUnitMain1)[choice];
        DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = choice + 1;
        return unitType;
    }

}
}
