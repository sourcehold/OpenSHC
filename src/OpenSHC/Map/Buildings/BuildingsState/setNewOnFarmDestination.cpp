#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        /* inlined copy of ViewportRenderState::xyAreValid */
        static inline int xyAreValid(uint x, uint y)
        {
            return x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0;
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EA00
        undefined4 BuildingsState::setNewOnFarmDestination(int buildingID)
        {
            int x = this->buildings[buildingID].buildingEntryX;
            int y = this->buildings[buildingID].buildingEntryY;
            if (!xyAreValid(x, y)) {
                return 0;
            }

            // Look for a field tileUnk that needs work and that can be reached from the entrance of the farm
            int entryConnection
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int direction = *(short*)this->buildings[buildingID].padding_0x26e == 0x51 ? 4 : 2;
            for (int i = 0; i < 24; ++i) {
                int tileUnk = this->buildings[buildingID].tileRefs[i];
                int tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
                int stage = (char)DAT_TileMapState::instance.DamageLayer[tileUnk];
                DAT_BuildingsState::instance.farmerDestinationTile = tileUnk;
                int high = MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tileUnk);
                if (*(short*)&this->buildings[buildingID].farmGrowState == 5) {
                    if (stage >= 14 && stage < 28) {
                        for (int n = 0; n < 4; ++n) {
                            int offsetX
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset;
                            int offsetY
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
                            int neighbour
                                = DAT_TileMapState::instance.directionTranslationMatrix[tileY][direction] + tileUnk;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetX = offsetX;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetY = offsetY;
                            if ((short)DAT_TileMapState::instance.PathConnectionLayer[neighbour] == entryConnection
                                && abs((int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                           DAT_TileMapState::ptr)(neighbour)
                                       - high)
                                    < 16) {
                                return 1;
                            }
                            direction += 2;
                            if (direction >= 8) {
                                direction = 0;
                            }
                        }
                    }
                } else if (*(short*)&this->buildings[buildingID].farmGrowState == 3) {
                    if ((uint)stage <= 1) {
                        for (int n = 0; n < 4; ++n) {
                            int offsetX
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset;
                            int offsetY
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
                            int neighbour
                                = DAT_TileMapState::instance.directionTranslationMatrix[tileY][direction] + tileUnk;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetX = offsetX;
                            DAT_BuildingsState::instance.hopFarmerDestinationOffsetY = offsetY;
                            if ((short)DAT_TileMapState::instance.PathConnectionLayer[neighbour] == entryConnection
                                && abs((int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                           DAT_TileMapState::ptr)(neighbour)
                                       - high)
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
