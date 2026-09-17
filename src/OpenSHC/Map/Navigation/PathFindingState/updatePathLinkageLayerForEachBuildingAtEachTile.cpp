#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A5F60
        void PathFindingState::updatePathLinkageLayerForEachBuildingAtEachTile()
        {
            for (int _tileIndex = 0; _tileIndex < 80400; _tileIndex++) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tileIndex], _tileIndex);
            }
        }

    }
}
}
