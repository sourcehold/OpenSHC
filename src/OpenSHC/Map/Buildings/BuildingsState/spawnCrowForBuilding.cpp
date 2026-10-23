#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A260
        int BuildingsState::spawnCrowForBuilding(int buildingID)
        {
            switch (this->buildings[buildingID].buildingType) {
            case BT_DRAWBRIDGE:
            case BT_TUNNEL:
            case BT_CAMPFIRE:
            case BT_SIGNPOST:
            case BT_PARADEGROUND:
            case BT_FIREBALLISTA:
            case BT_CAMPGROUND:
            case BT_PARADEGROUND2:
            case BT_PARADEGROUND3:
            case BT_PARADEGROUND4:
            case BT_PARADEGROUND5:
            case BT_KILLINGPIT:
            case BT_CATAPULT:
            case BT_TREBUCHET:
            case BT_BATTERINGRAM:
            case BT_SIEGETOWER:
            case BT_SHIELD:
            case BT_UNKNOWN4:
            case BT_DANCINGBEAR:
                break;
            default: {
                // One crow in the middle of the building and some more on random tiles of it
                int halfSize = (int)this->buildings[buildingID].widthOrHeight / 2;
                int microY = ((short)this->buildings[buildingID].y + halfSize) * 8;
                int microX = ((short)this->buildings[buildingID].x + halfSize) * 8;
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, 0, 0, microX, microY,
                    DAT_TileMapState::instance
                        .DefaultHeightLayer[this->buildings[buildingID].currentTilePositionAdjusted],
                    microX + 1, microY + 1,
                    DAT_TileMapState::instance
                        .DefaultHeightLayer[this->buildings[buildingID].currentTilePositionAdjusted],
                    (EntityType)0x1e, 0);

                // The original does not check the tile count before the first iteration
                int t = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                        DAT_TileMapState::ptr)(t, this->buildings[buildingID].widthOrHeight);
                    int random = (short)DAT_TileMapState::instance
                                     .RandomLayer[DAT_ViewportRenderState::instance
                                                      .translationMatrix[(short)this->buildings[buildingID].y
                                                          + DAT_TileMapState::instance.buildingY]
                                                      .addXgetTile
                                         + (short)this->buildings[buildingID].x + DAT_TileMapState::instance.buildingX];
                    if (random % 5 == 0) {
                        int tileMicroY
                            = ((short)this->buildings[buildingID].y + DAT_TileMapState::instance.buildingY) * 8;
                        int tileMicroX
                            = ((short)this->buildings[buildingID].x + DAT_TileMapState::instance.buildingX) * 8;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                            DAT_EntityState::ptr)(0, 0, 0, tileMicroX, tileMicroY,
                            DAT_TileMapState::instance
                                .DefaultHeightLayer[this->buildings[buildingID].currentTilePositionAdjusted],
                            tileMicroX + 1, tileMicroY + 1,
                            DAT_TileMapState::instance
                                .DefaultHeightLayer[this->buildings[buildingID].currentTilePositionAdjusted],
                            (EntityType)0x1e, -((random >> 4) % 20));
                    }
                    ++t;
                } while (t < DAT_TileMapState::instance.constructionTileCount);
                break;
            }
            }
            // The original has no meaningful return value
            return 0;
        }

    }
}
}
