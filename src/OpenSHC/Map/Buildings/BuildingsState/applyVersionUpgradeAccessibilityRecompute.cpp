#include "../BuildingsState.func.hpp"

#include "OpenSHC/IO/PackagedFileMagicNum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::IO::PackagedFileMagicNum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00424310
        void BuildingsState::applyVersionUpgradeAccessibilityRecompute(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAccessibilityForAllBuildings, this)();
        }

    }
}
}
