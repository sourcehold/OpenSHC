#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Loads the map file for the given mission number (1-based) from   MissionAestheticsDefinedData.field14_0x38, then
      calls UnitsState::setMissionNumberSpecificLord to   configure the lord unit for that mission. Covers missions
      1-20.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C6880
    void MapPropertiesState::loadMissionMapAndSetLord(int missionNumber)
    {
        int iVar1;
        char** mapName;
        iVar1 = missionNumber + -1;
        if (iVar1 < 5) {
        LAB_004c688d:
            mapName = (&DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName)[missionNumber];
        } else {
            if (9 < iVar1) {
                if (iVar1 < 0xf)
                    goto LAB_004c688d;
                if (0x13 < iVar1)
                    goto LAB_004c68b3;
            }
            mapName = (&DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName)[missionNumber];
        }
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMap, this)((char*)mapName);
    LAB_004c68b3:
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setMissionNumberSpecificLord, DAT_UnitsState::ptr)(
            missionNumber);
    }

}
}
