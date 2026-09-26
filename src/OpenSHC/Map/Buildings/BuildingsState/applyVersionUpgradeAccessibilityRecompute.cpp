#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

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
