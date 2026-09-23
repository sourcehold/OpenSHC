#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD560
    void AICState::aiRecruitSortieRangedUnits(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;
        if (this->aics[aicIndex].SortieUnitRangedMin < 0)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6
            >= DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 / 2
                + this->aics[aicIndex].SortieUnitRangedMin)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].idlePeasantsCount <= 0)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;
        UnitType unitType = (UnitType)this->aics[aicIndex].SortieUnitRanged;
        if (unitType == OpenSHC::Map::Units::UT_E_ENGINEER || unitType == OpenSHC::Map::Units::UT_E_LADDER
            || unitType == OpenSHC::Map::Units::UT_TUNNELER)
            return;

        int buildingID;
        if (unitType < 70)
            buildingID = DAT_GameState::instance.playerDataArray[playerID].barracks.id;
        else
            buildingID = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
        if (buildingID == 0)
            return;

        int unitID;
        if (unitType < 70)
            unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(
                unitType, buildingID, playerID, 0);
        else
            unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                unitType, buildingID, playerID, 0);

        if (unitID == 0) {
            if (this->aics[aicIndex].tradeAmountEquipment > 0
                && DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 2)
                DAT_GameState::instance.playerDataArray[playerID]
                    .resourcesToAcquireArray[DAT_UnitsState::instance.euroUnitRequiredResource]
                    = this->aics[aicIndex].tradeAmountEquipment;
            return;
        }

        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 6;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
            unitID, MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::createTribeForUnitType, this)(playerID, 166));
    }

}
}
