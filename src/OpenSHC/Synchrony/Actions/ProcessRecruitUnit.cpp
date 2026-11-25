#include "../Actions.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using namespace OpenSHC::Game::Player::Enums;
    using namespace OpenSHC::Map::Units;

    // FUNCTION: STRONGHOLDCRUSADER 0x00464EF0
    void Actions::ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].armySize
                + DAT_GameState::instance.playerDataArray[playerID].count_2
            >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
            return;
        }
        if (unitType == UT_E_ENGINEER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_ENGINEERSGUILD].id, playerID,
                0);
        } else if (unitType == UT_TUNNELER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_TUNNELERSGUILD].id, playerID,
                0);
        } else if (unitType == UT_E_LADDER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_ENGINEERSGUILD].id, playerID,
                0);
        } else if (unitType == UT_E_MONK) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                (UnitType)unitType, recruitmentBuildingID, playerID, 0);
        } else if (unitType == UT_A_ARCHER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_SLAVE) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_SLINGER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_ASSASSIN) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_HARCHER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_SWORDSMAN) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else if (unitType == UT_A_FIRETHROWER) {
            MACRO_CALL_MEMBER(UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)((UnitType)unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_MERCENARYPOST].id, playerID,
                0);
        } else {
            MACRO_CALL_MEMBER(UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(unitType,
                DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_BARRACKS].id, playerID, 0);
        }
    }

}
}
