#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F460
        undefined4 BuildingsState::determinePeasantSitPosition(int campfireID, int availablePeasants)
        {
            // Matching note: The remaining difference is the register choice for this and the building
            // coordinates.
            if (availablePeasants >= 24) {
                availablePeasants = 23;
            }

            int buildingY = (short)DAT_BuildingsState::instance.buildings[campfireID].y;
            int buildingX = (short)DAT_BuildingsState::instance.buildings[campfireID].x;
            int tile = (&DAT_BuildingsState::instance.buildings[campfireID].tileRef1)[availablePeasants];
            int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            this->campfireSpotY = y;
            this->campfireSpotX = x;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(x, y, buildingX + 3, buildingY + 3);
            this->campfireSpotOrientation = DAT_DirectionAlgorithmState::instance.orientation;
            return 1;
        }

    }
}
}
