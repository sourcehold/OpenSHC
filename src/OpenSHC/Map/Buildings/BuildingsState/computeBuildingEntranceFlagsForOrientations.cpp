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
            // Marks the sides of a keep-like building that have an entrance (field_0x280 holds one flag per side)
            uint size = this->buildings[param_1].widthOrHeight;
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            // the side length is kept apart from size; the original stores it in a separate arm per size
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
            int try_ = size == 4 ? tileCount - 1 : tileCount - 2;
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
