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
            if (receivedMapVersion == (PackagedFileMagicNum)100) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_100)();
            }
            if (receivedMapVersion == (PackagedFileMagicNum)100 || (int)receivedMapVersion < 113) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_112)();
            }
            if ((int)receivedMapVersion < 114) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_114)();
            }
            if ((int)receivedMapVersion < 117) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_117)();
            }
            if ((int)receivedMapVersion < 122) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsAttackTileLogicTo_122)();
            }
            if ((int)receivedMapVersion < 130) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_130)();
            }
            if ((int)receivedMapVersion < 149) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_149)();
            }
            if ((int)receivedMapVersion < 154) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_154)();
            }
            if ((int)receivedMapVersion < 155) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_155)();
            }
            if ((int)receivedMapVersion < 169) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsLordHealthTo_169)();
            }
            if ((int)receivedMapVersion < 170) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapUnitsTo_170)();
            }
        }

    }
}
}
