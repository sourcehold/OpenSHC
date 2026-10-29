#include "../DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046C9A0
        void DirectionAlgorithmState::calculateOrientationFromTiles(int fromTile, int toTile)
        {
            int fromY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[fromTile];
            int toY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[toTile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation, this)(
                fromTile - DAT_ViewportRenderState::instance.translationMatrix[fromY].addXgetTile, fromY,
                toTile - DAT_ViewportRenderState::instance.translationMatrix[toY].addXgetTile, toY);
        }

    }
}
}
