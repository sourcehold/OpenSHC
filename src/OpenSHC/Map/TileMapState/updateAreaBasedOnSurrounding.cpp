#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAA30
    void TileMapState::updateAreaBasedOnSurrounding(int x, int y, int buildingSize)
    {
        int buildingSizeTileIndex = 0;
        int area
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findAccessibleAreaNearBuildingLocation,
                DAT_BuildingsState::ptr)(x, y, buildingSize);
        // do-while, not a for loop: the bound is this->constructionTileCount, which the
        // getBuildingSizeIndexMappingData call in the body sets. Testing it before the first
        // iteration would read the count of the previous footprint.
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingSize);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (this->PathConnectionLayer[tileUnk] == 0) {
                this->PathConnectionLayer[tileUnk] = (ushort)area;
            }
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
