#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7AB0
    int MapPropertiesState::getDifficultyMultipliedValue(int value)
    {
        if (DAT_GameCore::instance.gameMode_2 == 0 && DAT_GameCore::instance.missionNumber1to20 == 8) {
            return value;
        }
        return DAT_MissionAestheticsDefinedData::instance
                   .DifficultyEventMultipliers[DAT_GameState::instance.mapAndTime.difficulty]
            * value / 100;
    }

}
}
