#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00464EF0
    void Actions::ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].armySize
                + DAT_GameState::instance.playerDataArray[playerID].count_2
            >= DAT_GameState::instance.mapAndTime.armySizeLimit)
            return;

        if (unitType == 0x1e) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_E_ENGINEER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id)), playerID, 0);
            return;
        }
        if (unitType == 5) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_TUNNELER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.id)), playerID, 0);
            return;
        }
        if (unitType == 0x1d) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_E_LADDER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id)), playerID, 0);
            return;
        }
        if (unitType == 0x25) {
            /*
              monk
             */
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_E_MONK, (undefined4)((int)(recruitmentBuildingID)), playerID, 0);
            return;
        }
        if (unitType == 0x46) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_ARCHER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x47) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_SLAVE,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x48) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_SLINGER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x49) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_ASSASSIN,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x4a) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_HARCHER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x4b) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_SWORDSMAN,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }
        if (unitType == 0x4c) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_A_FIRETHROWER,
                (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id)), playerID, 0);
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(
            unitType, (undefined4)((int)(DAT_GameState::instance.playerDataArray[playerID].barracks.id)), playerID, 0);
    }

}
}
