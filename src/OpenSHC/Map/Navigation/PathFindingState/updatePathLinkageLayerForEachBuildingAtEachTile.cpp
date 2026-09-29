#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5F60
        void PathFindingState::updatePathLinkageLayerForEachBuildingAtEachTile()
        {
            for (int _tileIndex = 0; _tileIndex < 80400; _tileIndex = _tileIndex + 1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tileIndex], _tileIndex);
            }
            return;
        }

    }
}
}
