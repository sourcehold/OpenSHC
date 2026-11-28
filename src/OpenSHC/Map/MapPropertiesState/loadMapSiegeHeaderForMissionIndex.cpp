#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Looks up the map filename for mission index param_1 (1-based, range 1-20) from
      MissionAestheticsDefinedData.field15_0x3c and calls loadMapSiegeHeaderSections. Covers all four   groups of 5
      missions (1-5, 6-10, 11-15, 16-20). Does nothing if param_1 is out of range.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C6820
    void MapPropertiesState::loadMapSiegeHeaderForMissionIndex(char* param_1)
    {
        char* pcVar1;
        pcVar1 = param_1 + -1;
        if ((int)pcVar1 < 5) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field15_0x3c)[(int)pcVar1]);
        }
        if ((int)pcVar1 < 10) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field15_0x3c)[(int)pcVar1]);
        }
        if ((int)pcVar1 < 0xf) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field15_0x3c)[(int)pcVar1]);
        }
        if ((int)pcVar1 < 20) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field15_0x3c)[(int)pcVar1]);
        }
    }

}
}
