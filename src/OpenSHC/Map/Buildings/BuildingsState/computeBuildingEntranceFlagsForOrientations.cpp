#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B7C0
        void BuildingsState::computeBuildingEntranceFlagsForOrientations(int buildingID)
        {
            int const size = this->buildings[buildingID].widthOrHeight;
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            int tilesPerSide;
            int try_;
            if (size == 4) {
                tilesPerSide = 4;
                try_ = tileCount - 1;
            } else if (size == 5) {
                tilesPerSide = 5;
                try_ = tileCount - 2;
            } else if (size == 6) {
                tilesPerSide = 6;
                try_ = tileCount - 2;
            } else {
                return;
            }
            // The four per-orientation entrance flags are cleared with a single dword store.
            *(undefined4*)this->buildings[buildingID].field162_0x280 = 0;
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupBuildingEntrancesOffset, this)(size, 1, try_, 0);
                ++try_;
                if (try_ >= tileCount) {
                    try_ = 0;
                }
                int const logic
                    = DAT_TileMapState::instance
                          .LogicLayer[DAT_ViewportRenderState::instance
                                          .translationMatrix[this->buildings[buildingID].y + this->DAT_TempYOffset]
                                          .addXgetTile
                              + this->buildings[buildingID].x + this->DAT_TempXOffset];
                if ((logic & LogicHelpers::L_WALL_OR_GATEHOUSE) != 0 && (logic & LogicHelpers::L_STOCKPILEUnk) == 0
                    && (logic & LogicHelpers::L_CRENEL) == 0) {
                    this->buildings[buildingID].field162_0x280[i / tilesPerSide] = true;
                }
            }
        }

    }
}
}
