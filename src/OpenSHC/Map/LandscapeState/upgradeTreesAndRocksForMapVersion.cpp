#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::IO::PackagedFileMagicNum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3D30
    void LandscapeState::upgradeTreesAndRocksForMapVersion(
        PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
    {
        MACRO_CALL(OpenSHC::Map::Version_Func::UpdateTreesOfCertainTypes)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpdateFixTrees2)();
        MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeRemoveCertainRockTypesUnk)();
        if ((receivedMapVersion != packagerMapVersion) && ((int)receivedMapVersion < 0xa5)) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeRemoveRocksBeyond1000)();
        }
    }

}
}
