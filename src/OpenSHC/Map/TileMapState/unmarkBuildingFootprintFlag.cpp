
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FAD20
    void TileMapState::unmarkBuildingFootprintFlag(int param_1, int param_2, int param_3)
    {
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, param_3);
            buildingSizeTileIndex++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_2].addXgetTile
                + this->buildingX + param_1;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_PLAIN1_AND_FARM;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
