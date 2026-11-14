#include "../UnitsState.func.hpp"

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
            if (receivedMapVersion == 100) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_100)();
            }
            if (receivedMapVersion == 100 || receivedMapVersion < 113) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_112)();
            }
            if (receivedMapVersion < 114) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_114)();
            }
            if (receivedMapVersion < 117) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_117)();
            }
            if (receivedMapVersion < 122) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsAttackTileLogicTo_122)();
            }
            if (receivedMapVersion < 130) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_130)();
            }
            if (receivedMapVersion < 149) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_149)();
            }
            if (receivedMapVersion < 154) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_154)();
            }
            if (receivedMapVersion < 155) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_155)();
            }
            if (receivedMapVersion < 169) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsLordHealthTo_169)();
            }
            if (receivedMapVersion < 170) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_170)();
            }
        }

    }
}
}
