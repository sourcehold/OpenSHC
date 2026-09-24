#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F460
        undefined4 BuildingsState::determinePeasantSitPosition(int campfireID, int availablePeasants)
        {
            if (availablePeasants > 24) {
                availablePeasants = 23;
            }

            int tile = (&this->buildings[campfireID].tileRef1)[availablePeasants];
            this->campfireSpotY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->campfireSpotX
                = tile - DAT_ViewportRenderState::instance.translationMatrix[this->campfireSpotY].addXgetTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(this->campfireSpotX, this->campfireSpotY,
                this->buildings[campfireID].x + 3, this->buildings[campfireID].y + 3);
            this->campfireSpotOrientation = DAT_DirectionAlgorithmState::instance.orientation;
            return 1;
        }

    }
}
}
