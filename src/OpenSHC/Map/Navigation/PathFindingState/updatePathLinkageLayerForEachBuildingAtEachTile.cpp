#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A5F60
        void PathFindingState::updatePathLinkageLayerForEachBuildingAtEachTile()
        {
            for (int tileIndex = 0; tileIndex < 80400; ++tileIndex) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileIndex], tileIndex);
            }
        }

    }
}
}
