#include "../BuildingsState.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004109F0
        void BuildingsState::extinguishBuildingFire(int buildingID)
        {
            if (this->buildings[buildingID].fireDuration == 0) {
                return;
            }
            int const x = this->buildings[buildingID].x;
            int const y = this->buildings[buildingID].y;
            int size = this->buildings[buildingID].widthOrHeight;
            this->buildings[buildingID].fireDuration = 0;
            this->buildings[buildingID].cooldownTimer = 2000;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WHEATFARM) {
                size = 9;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_HOPFARM) {
                size = 9;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DAIRYFARM) {
                size = 10;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_APPLEFARM) {
                size = 11;
            }
            int tile = 0;
            do {
                MACRO_CALL_MEMBER(TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    tile, size);
                MACRO_CALL_MEMBER(Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(
                    DAT_ViewportRenderState::instance.translationMatrix[y + DAT_TileMapState::instance.buildingY]
                        .addXgetTile
                    + DAT_TileMapState::instance.buildingX + x);
                ++tile;
            } while (tile < DAT_TileMapState::instance.constructionTileCount);
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            for (int try_ = 0; try_ < tileCount; ++try_) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupBuildingEntrancesOffset, this)(size, 1, try_, 0);
                MACRO_CALL_MEMBER(Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(x
                    + DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
                    + this->DAT_TempXOffset);
            }
        }

    }
}
}
