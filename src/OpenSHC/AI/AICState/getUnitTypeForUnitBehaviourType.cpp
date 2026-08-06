#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIUnitBehaviourType;
    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC250
    UnitType AICState ::getUnitTypeForUnitBehaviourType(int playerID, AIUnitBehaviourType unitBehaviourType)

    {

        AITypeInt AVar1;

        int iVar2;

        UnitType UVar3;

        AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {

            return ((UnitType)0);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ENGINEERING) {

            return OpenSHC::Map::Units::UT_E_ENGINEER;
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_DIGGING) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttDiggingUnit);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ASSASSINATION) {

            return OpenSHC::Map::Units::UT_A_ASSASSIN;
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ATTUNIT2) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnit2);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_LADDERING) {

            return OpenSHC::Map::Units::UT_E_LADDER;
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_TUNNELING) {

            return OpenSHC::Map::Units::UT_TUNNELER;
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_PATROLLING) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnitPatrol);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_BACKUPING) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnitBackup);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ENGAGING) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnitEngage);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_SIEGEDEFENSE) {

            return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnitSiegeDef);
        }

        if (unitBehaviourType == OpenSHC::AI::AIUBT_ATTUNITMAIN) {

            if (*(int*)((int)this->aics + DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex * 4
                    + AVar1 * 0x2a4 + -0x1c)
                == 0) {

                DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = 0;
            }

            if (3 < DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex) {

                DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = 0;
            }

            iVar2 = DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex;

            /*
                  AttUnitMain[] */

            UVar3 = *(UnitType*)((int)this->aics + AVar1 * 0x2a4 + iVar2 * 4 + -0x1c);

            DAT_GameState::instance.playerDataArray[playerID].aiAttUnitMainChoiceIndex = iVar2 + 1;

            return UVar3;
        }

        return (UnitType)(this->aics[AVar1 + ~OpenSHC::AI::AIT_NULL].AttUnitMain1);
    }

}
}
