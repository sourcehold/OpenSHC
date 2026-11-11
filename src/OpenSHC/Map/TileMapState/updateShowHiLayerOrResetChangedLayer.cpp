#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_RotateMapOrPullDownTerrain.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501A20
    void TileMapState::updateShowHiLayerOrResetChangedLayer()
    {
        BOOLEnum importHeight = FALSE;
        this->refreshRelatedTwo = 0;
        if (this->refreshCertainTileMap == 0) {
            return;
        }

        this->counter1 += 1;
        this->refreshCertainTileMap_old = this->refreshCertainTileMap;
        this->refreshRelatedOne = 0;
        for (int row = 0; row < countof(this->heightBasedScreenYOffset); row++) {
            int target = ((uint)row >> 2) + 1;
            int step;
            if (this->refreshCertainTileMap == 3) {
                step = this->heightBasedScreenYOffset[row] - target;
            } else if (this->refreshCertainTileMap == 4) {
                step = row - this->heightBasedScreenYOffset[row];
            } else {
                step = 0;
            }
            if (step > 60) {
                step = 30;
            } else if (step > 40) {
                step = 20;
            } else if (step > 30) {
                step = 14;
            } else if (step > 20) {
                step = 8;
            } else if (step > 10) {
                step = 4;
            } else if (step > 6) {
                step = 3;
            } else if (step > 2) {
                step = 2;
            } else if (step > 0) {
                step = 1;
            } else {
                step = 0;
            }

            if (this->refreshCertainTileMap == 1) {
                this->heightBasedScreenYOffset[row] = target;
            } else if (this->refreshCertainTileMap == 2) {
                this->heightBasedScreenYOffset[row] = row;
            } else if (this->refreshCertainTileMap == 3) {
                this->heightBasedScreenYOffset[row] -= step;
                if (this->heightBasedScreenYOffset[row] > target) {
                    importHeight = TRUE;
                }
            } else if (this->refreshCertainTileMap == 4) {
                this->heightBasedScreenYOffset[row] += step;
                if (this->heightBasedScreenYOffset[row] != row) {
                    importHeight = TRUE;
                }
            }
        }

        this->refreshRelatedTwo = 1;
        if (!importHeight) {
            if (this->refreshCertainTileMap == 4 || this->refreshCertainTileMap == 2) {
                this->refreshRelatedOne = 1;
            } else {
                this->refreshRelatedOne = 0;
                this->refreshRelatedTwo = 2;
            }
            this->refreshCertainTileMap = 0;
            this->forceUpdateLogicalAndMiscDisplayLayers = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
            this->counter1 = 0;
            DAT_RotateMapOrPullDownTerrain::instance = 1;
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::rebuildShowHiLayerFromHeights, this)();
    }

}
}
