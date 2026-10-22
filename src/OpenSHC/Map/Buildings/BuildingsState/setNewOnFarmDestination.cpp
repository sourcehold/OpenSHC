#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EA00
        undefined4 BuildingsState::setNewOnFarmDestination(int buildingID)
        {
            uint const entryX = this->buildings[buildingID].buildingEntryX;
            uint const entryY = this->buildings[buildingID].buildingEntryY;
            if (entryX > 399 || entryY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[entryY * 400 + entryX] == 0) {
                return 0;
            }
            int const entryArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[entryY].addXgetTile
                          + entryX];
            // The header has no field for the short at 0x26e.
            int direction = *(short*)this->buildings[buildingID].padding_0x26e == 0x51 ? 4 : 2;
            for (int i = 0; i < 24; ++i) {
                // The header splits the tile reference array into tileRef1..tileRef19.
                int const tile = (&this->buildings[buildingID].tileRef1)[i];
                int const row = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const damage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                int const height
                    = MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
                if (this->buildings[buildingID].wheatGrowStateRelated == 5) {
                    if ((uint)(damage - 14) > 13) {
                        continue;
                    }
                    for (int k = 0; k < 4; ++k) {
                        DAT_BuildingsState::instance.hopFarmerDestinationOffsetX
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                  .int_.xOffset;
                        DAT_BuildingsState::instance.hopFarmerDestinationOffsetY
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                  .int_.yOffset;
                        int const target = DAT_TileMapState::instance.directionTranslationMatrix[row][direction] + tile;
                        if ((short)DAT_TileMapState::instance.PathConnectionLayer[target] == entryArea
                            && abs((int)MACRO_CALL_MEMBER(
                                       TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(target)
                                   - height)
                                < 16) {
                            return 1;
                        }
                        direction += 2;
                        if (direction >= 8) {
                            direction = 0;
                        }
                    }
                } else if (this->buildings[buildingID].wheatGrowStateRelated == 3) {
                    if ((uint)damage > 1) {
                        continue;
                    }
                    for (int k = 0; k < 4; ++k) {
                        DAT_BuildingsState::instance.hopFarmerDestinationOffsetX
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                  .int_.xOffset;
                        DAT_BuildingsState::instance.hopFarmerDestinationOffsetY
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                  .int_.yOffset;
                        int const target = DAT_TileMapState::instance.directionTranslationMatrix[row][direction] + tile;
                        if ((short)DAT_TileMapState::instance.PathConnectionLayer[target] == entryArea
                            && abs((int)MACRO_CALL_MEMBER(
                                       TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(target)
                                   - height)
                                < 16) {
                            return 1;
                        }
                        direction += 2;
                        if (direction >= 8) {
                            direction = 0;
                        }
                    }
                } else {
                    return 0;
                }
            }
            return 0;
        }

    }
}
}
