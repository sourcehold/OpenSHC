#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B7C0
        void BuildingsState::computeBuildingEntranceFlagsForOrientations(int param_1)
        {
            // param_1 is the building ID. Marks the sides of a keep-like building that have an entrance
            // (field_0x280 holds one flag per side).
            uint const size = this->buildings[param_1].widthOrHeight;
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            // Matching note: the side length is kept apart from size and stored in a separate arm per size.
            int sideLength;
            if (size == 4) {
                sideLength = size;
            } else if (size == 5) {
                sideLength = size;
            } else if (size == 6) {
                sideLength = size;
            } else {
                return;
            }
            int tryIndex;
            if (size == 4) {
                tryIndex = tileCount - 1;
            } else {
                tryIndex = tileCount - 2;
            }
            for (int side = 0; side < countof(this->buildings[param_1].field_0x280); ++side) {
                this->buildings[param_1].field_0x280[side] = false;
            }
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, tryIndex, 0);
                ++tryIndex;
                if (tryIndex >= tileCount) {
                    tryIndex = 0;
                }
                uint const logic
                    = DAT_TileMapState::instance
                          .LogicLayer[DAT_ViewportRenderState::instance
                                          .translationMatrix[this->buildings[param_1].y + this->DAT_TempYOffset]
                                          .addXgetTile
                              + this->buildings[param_1].x + this->DAT_TempXOffset];
                if ((logic & LogicHelpers::L_WALL_OR_GATEHOUSE) != 0 && (logic & LogicHelpers::L_STOCKPILEUnk) == 0
                    && (logic & LogicHelpers::L_CRENEL) == 0) {
                    this->buildings[param_1].field_0x280[i / sideLength] = true;
                }
            }
        }

    }
}
}
