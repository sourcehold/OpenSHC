#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00511D70
    void TileMapState::upgradeMapFormatLogicLayer(
        PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
    {
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown1)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown2)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown3)();
        if (this->mapSize == 0) {
            this->mapSize = MC_MAP_XY_LIMIT;
        }
        if (receivedMapVersion == packagerMapVersion) {
            return;
        }

        if (receivedMapVersion < 102) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_102)();
        }
        if (receivedMapVersion < 120) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_120)();
        }
        if (receivedMapVersion < 125) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_125)();
        }
        if (receivedMapVersion < 128) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_128)();
        }
        if (receivedMapVersion < 145) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_145)();
        }
        if (receivedMapVersion < 147) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_147)();
        }
    }

}
}
