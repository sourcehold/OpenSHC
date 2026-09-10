#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::IO::PackagedFileMagicNum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00526370
        void TribesState::upgradeMapTribesState(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_Unknown1)();
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_Unknown2)();
            if ((receivedMapVersion != packagerMapVersion) && ((int)receivedMapVersion < 0x8e)) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_142)();
            }
        }

    }
}
}
