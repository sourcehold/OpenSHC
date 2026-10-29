
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB360
    void TileMapState::clearBuildingDisplayFlagsAndEntities(int buildingID, int param_2)
    {
        int buildingSizeTileIndex = 0;
        int buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
        int buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
        uint widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, widthOrHeight);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + buildingY].addXgetTile
                + this->buildingX + buildingX;
            this->MiscDisplayLayer[tileUnk] &= ~0xc;
            if (param_2 == 1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(tileUnk);
            }
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
