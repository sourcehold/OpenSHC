#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004109F0
        void BuildingsState::extinguishBuildingFire(int buildingID)
        {
            if (this->buildings[buildingID].fireDuration == 0) {
                return;
            }

            int x = (short)this->buildings[buildingID].x;
            uint size = this->buildings[buildingID].widthOrHeight;
            int y = (short)this->buildings[buildingID].y;
            this->buildings[buildingID].fireDuration = 0;
            this->buildings[buildingID].cooldownTimer = 2000;
            // Farms burn including their fields
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WHEATFARM) {
                size = 9;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_HOPFARM) {
                size = 9;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DAIRYFARM) {
                size = 10;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_APPLEFARM) {
                size = 11;
            }

            // Remove the fire on the building tiles. The original does not check the tile count before the first
            // iteration.
            int t = 0;
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(t, size);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(
                    DAT_ViewportRenderState::instance.translationMatrix[y + DAT_TileMapState::instance.buildingY]
                        .addXgetTile
                    + DAT_TileMapState::instance.buildingX + x);
                ++t;
            } while (t < DAT_TileMapState::instance.constructionTileCount);

            // And on the tiles around it
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, i, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(
                    DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile + x
                    + this->DAT_TempXOffset);
            }
        }

    }
}
}
