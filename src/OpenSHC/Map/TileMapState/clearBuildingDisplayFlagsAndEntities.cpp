#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::MD_BUILDING_TILES;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB360
    void TileMapState::clearBuildingDisplayFlagsAndEntities(int buildingID, int destroyEntities)
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
            this->MiscDisplayLayer[tileUnk] &= ~MD_BUILDING_TILES;
            if (destroyEntities == 1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(tileUnk);
            }
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
