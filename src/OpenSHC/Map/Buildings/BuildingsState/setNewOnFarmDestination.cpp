#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EA00
        undefined4 BuildingsState::setNewOnFarmDestination(int buildingID)
        {
            int x = this->buildings[buildingID].buildingEntryX;
            int y = this->buildings[buildingID].buildingEntryY;
            if ((uint)x > 399 || (uint)y > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                return 0;
            }

            // Look for a field tile that needs work and that can be reached from the entrance of the farm
            int entryConnection
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int direction = (*(short*)this->buildings[buildingID].padding_0x26e == 0x51) * 2 + 2;
            for (int i = 0; i < 24; ++i) {
                int tile = (&this->buildings[buildingID].tileRef1)[i];
                int tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int stage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                int height = MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
                if (*(short*)&this->buildings[buildingID].wheatGrowStateRelated == 5) {
                    if (stage >= 14 && stage < 28) {
                        for (int n = 0; n < 4; ++n) {
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetX
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                      .int_.xOffset;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetY
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                      .int_.yOffset;
                            int neighbour
                                = DAT_TileMapState::instance.directionTranslationMatrix[tileY][direction] + tile;
                            if ((short)DAT_TileMapState::instance.PathConnectionLayer[neighbour] == entryConnection
                                && abs((int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                           DAT_TileMapState::ptr)(neighbour)
                                       - height)
                                    < 16) {
                                return 1;
                            }
                            direction += 2;
                            if (direction >= 8) {
                                direction = 0;
                            }
                        }
                    }
                } else if (*(short*)&this->buildings[buildingID].wheatGrowStateRelated == 3) {
                    if ((uint)stage < 2) {
                        for (int n = 0; n < 4; ++n) {
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetX
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                      .int_.xOffset;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetY
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                      .int_.yOffset;
                            int neighbour
                                = DAT_TileMapState::instance.directionTranslationMatrix[tileY][direction] + tile;
                            if ((short)DAT_TileMapState::instance.PathConnectionLayer[neighbour] == entryConnection
                                && abs((int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                           DAT_TileMapState::ptr)(neighbour)
                                       - height)
                                    < 16) {
                                return 1;
                            }
                            direction += 2;
                            if (direction >= 8) {
                                direction = 0;
                            }
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
