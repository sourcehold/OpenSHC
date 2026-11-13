#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB010
    BOOLEnum MapPropertiesState::isMapperAvailable(MappersEnum mapper)
    {
        if ((mapper == 178 || mapper == 179) && DAT_GameCore::instance.gameMode_2 != 1) {
            return FALSE;
        }
        if (DAT_GameCore::instance.gameMode_2 == 1 && DAT_GameCore::instance.U2_mapType_singleOrMulti >= 1) {
            if (mapper == 60 || (mapper > 61 && mapper <= 64)) {
                return FALSE;
            }
            return TRUE;
        }
        if (DAT_GameCore::instance.gameMode_2 == 1) {
            return TRUE;
        }
        if (mapper == 312) {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.currentGameMode != 99
                && DAT_GameState::instance.mapAndTime.skirmishNoDogs != 0) {
                return FALSE;
            }
        } else if (mapper == 78) {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameState::instance.mapAndTime.rawDeerCount == 0) {
                return FALSE;
            }
        }
        return (BOOLEnum)this->buildingAvailabilityRelatedFlags[mapper];
    }

}
}
