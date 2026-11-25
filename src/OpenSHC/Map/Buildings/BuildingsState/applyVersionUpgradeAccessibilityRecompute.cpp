#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424310
        void BuildingsState::applyVersionUpgradeAccessibilityRecompute(
            PackagedFileMagicNum param_1, PackagedFileMagicNum param_2)
        {
            MACRO_CALL_MEMBER(BuildingsState_Func::recomputeAccessibilityForAllBuildings, this)();
        }

    }
}
}
