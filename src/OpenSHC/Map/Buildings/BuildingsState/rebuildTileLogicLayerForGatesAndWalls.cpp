#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419AC0
        void BuildingsState::rebuildTileLogicLayerForGatesAndWalls()
        {
            for (int buildingID = 1; buildingID < 2000; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != 0
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSELARGE
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSESMALL
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WOODGATE1)) {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                            DAT_TileMapState::ptr)(i, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
                        int const tile = DAT_ViewportRenderState::instance
                                             .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].y
                                                 + DAT_TileMapState::instance.buildingY]
                                             .addXgetTile
                            + DAT_BuildingsState::instance.buildings[buildingID].x
                            + DAT_TileMapState::instance.buildingX;
                        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WOODGATE1) {
                            DAT_TileMapState::instance.LogicLayer[tile] = DAT_TileMapState::instance.LogicLayer[tile]
                                    & ~(LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_UNKNOWN_WALL_RELATED)
                                | LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
                            // MiscDisplayLayer is ushort in the header, but the original masks it as a signed short
                            // (and with imm8)
                            *(short*)&DAT_TileMapState::instance.MiscDisplayLayer[tile] &= ~0x20;
                            DAT_TileMapState::instance.HeightLayer[tile]
                                = (byte)DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk;
                        } else {
                            DAT_TileMapState::instance.LogicLayer[tile] |= LogicHelpers::L_WALL_OR_GATEHOUSE;
                            DAT_TileMapState::instance.WallOwnerLayer[tile]
                                = DAT_TileMapState::instance.WallOwnerLayer[tile] & 0xf8
                                | DAT_BuildingsState::instance.buildings[buildingID].owner - 1;
                        }
                        DAT_TileMapState::instance.LogicLayer[tile] &= ~LogicHelpers::L_BUILDING;
                        ++i;
                    } while (i < DAT_TileMapState::instance.constructionTileCount);
                }
            }
        }

    }
}
}
