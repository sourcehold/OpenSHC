#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419AC0
        void BuildingsState::rebuildTileLogicLayerForGatesAndWalls()
        {
            for (int i = 1; i < 2000; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState == 0
                    || (DAT_BuildingsState::instance.buildings[i].buildingType != BT_GATEHOUSELARGE
                        && DAT_BuildingsState::instance.buildings[i].buildingType != BT_GATEHOUSESMALL
                        && DAT_BuildingsState::instance.buildings[i].buildingType != BT_WOODGATE1)) {
                    continue;
                }
                // The original does not check the tileUnk count before the first iteration
                int t = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                        DAT_TileMapState::ptr)(t, DAT_BuildingsState::instance.buildings[i].widthOrHeight);
                    int tileUnk = DAT_ViewportRenderState::instance
                                   .translationMatrix[(short)DAT_BuildingsState::instance.buildings[i].y
                                       + DAT_TileMapState::instance.buildingY]
                                   .addXgetTile
                        + (short)DAT_BuildingsState::instance.buildings[i].x + DAT_TileMapState::instance.buildingX;
                    if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_WOODGATE1) {
                        DAT_TileMapState::instance.LogicLayer[tileUnk]
                            = DAT_TileMapState::instance.LogicLayer[tileUnk] & 0xfffefeff | 0x10000000;
                        // The original clears the bit through a signed 16-bit access
                        DAT_TileMapState::instance.MiscDisplayLayer[tileUnk] &= ~0x20;
                        DAT_TileMapState::instance.HeightLayer[tileUnk]
                            = (byte)DAT_BuildingsState::instance.buildings[i].terrainHeightUnk;
                    } else {
                        DAT_TileMapState::instance.LogicLayer[tileUnk] |= 0x100;
                        DAT_TileMapState::instance.WallOwnerLayer[tileUnk]
                            = (char)DAT_BuildingsState::instance.buildings[i].owner - 1
                            | DAT_TileMapState::instance.WallOwnerLayer[tileUnk] & 0xf8;
                    }
                    DAT_TileMapState::instance.LogicLayer[tileUnk] &= 0xfffffbff;
                    ++t;
                } while (t < DAT_TileMapState::instance.constructionTileCount);
            }
        }

    }
}
}
