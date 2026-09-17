#include "../ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C200
    void ResourceManager::loadMapMetaByID(dword id)
    {
        DAT_GameCore::instance.mapType = this->mapMetaInfoArray[id].mapType;
        DAT_GameCore::instance.savedMapLocked = this->mapMetaInfoArray[id].mapLocked;
        DAT_GameCore::instance.savedMapBalance = this->mapMetaInfoArray[id].mapBalance;
        DAT_GameCore::instance.savedMapEndInt2 = this->mapMetaInfoArray[id].mapEndInt2;
        DAT_GameCore::instance.mapPlayerCount = this->mapMetaInfoArray[id].mapPlayerCount;
        DAT_MapPropertiesState::instance.scenarionMissionType = this->mapMetaInfoArray[id].int0;
        DAT_MapPropertiesState::instance.scenarioMissionSiegeOrInvasion = this->mapMetaInfoArray[id].mapType2;
        DAT_GameCore::instance.mapU4Int0_2 = 0;
    }

} // namespace IO
} // namespace OpenSHC
