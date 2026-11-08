#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B7C0
        void BuildingsState::computeBuildingEntranceFlagsForOrientations(int param_1)
        {
            // Matching note: the original tests 5 and 6 in separate arms that each store the side length (the
            // instruction-exact nested form, with try_ shared after an inner if/else-if, scores lower because the
            // original places the size == 6 arm after the loop entry jump, which no shape tried reproduces).
            // Marks the sides of a keep-like building that have an entrance (field_0x280 holds one flag per side)
            uint size = this->buildings[param_1].widthOrHeight;
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            int try_;
            // the side length is kept apart from size, the original stores it once per arm
            int sideLength;
            if (size == 4) {
                sideLength = 4;
                try_ = tileCount - 1;
            } else if (size == 5 || size == 6) {
                sideLength = size;
                try_ = tileCount - 2;
            } else {
                return;
            }
            *(int*)this->buildings[param_1].field_0x280 = 0;
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, try_, 0);
                ++try_;
                if (try_ >= tileCount) {
                    try_ = 0;
                }
                uint logic
                    = DAT_TileMapState::instance
                          .LogicLayer[DAT_ViewportRenderState::instance
                                          .translationMatrix[(short)this->buildings[param_1].y + this->DAT_TempYOffset]
                                          .addXgetTile
                              + (short)this->buildings[param_1].x + this->DAT_TempXOffset];
                if ((logic & 0x100) != 0 && (logic & 2) == 0 && (logic & 0x200) == 0) {
                    this->buildings[param_1].field_0x280[i / sideLength] = 1;
                }
            }
        }

    }
}
}
