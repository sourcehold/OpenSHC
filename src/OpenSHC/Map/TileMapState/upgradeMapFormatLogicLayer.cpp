#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00511D70
    void TileMapState::upgradeMapFormatLogicLayer(
        PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
    {
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown1)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown2)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_Unknown3)();
        if (this->mapSize == 0) {
            this->mapSize = 400;
        }
        if (receivedMapVersion == packagerMapVersion) {
            return;
        }

        if ((int)receivedMapVersion < 0x66) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_102)();
        }
        if ((int)receivedMapVersion < 0x78) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_120)();
        }
        if ((int)receivedMapVersion < 0x7d) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_125)();
        }
        if ((int)receivedMapVersion < 0x80) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_128)();
        }
        if ((int)receivedMapVersion < 0x91) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_145)();
        }
        if ((int)receivedMapVersion < 0x93) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapLogicToVersion_147)();
        }
    }

}
}
