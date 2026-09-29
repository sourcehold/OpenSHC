#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::IO::PackagedFileMagicNum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E390
        void UnitsState::upgradeMapFormatForUnits(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_UnknownVersion1)();
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_117)();
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_UnknownVersion2)();
            if (receivedMapVersion == packagerMapVersion) {
                return;
            }
            if (receivedMapVersion == (PackagedFileMagicNum)100) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_100)();
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_112)();
            } else if ((int)receivedMapVersion <= 0x70) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_112)();
            }
            if ((int)receivedMapVersion < 0x72) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_114)();
            }
            if ((int)receivedMapVersion < 0x75) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_117)();
            }
            if ((int)receivedMapVersion < 0x7a) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsAttackTileLogicTo_122)();
            }
            if ((int)receivedMapVersion < 0x82) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_130)();
            }
            if ((int)receivedMapVersion < 0x95) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_149)();
            }
            if ((int)receivedMapVersion < 0x9a) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_154)();
            }
            if ((int)receivedMapVersion < 0x9b) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_155)();
            }
            if ((int)receivedMapVersion < 0xa9) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsLordHealthTo_169)();
            }
            if ((int)receivedMapVersion < 0xaa) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_170)();
            }
        }

    }
}
}
