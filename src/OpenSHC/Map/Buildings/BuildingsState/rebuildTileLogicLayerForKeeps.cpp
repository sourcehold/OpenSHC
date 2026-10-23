#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00419BE0
        void BuildingsState::rebuildTileLogicLayerForKeeps()
        {
            for (int i = 1; i < 2000; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState == 0
                    || DAT_BuildingDefinedData::instance
                            .BuildingIsKeepArray[DAT_BuildingsState::instance.buildings[i].buildingType]
                        == 0) {
                    continue;
                }
                // The original does not check the tile count before the first iteration
                int t = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                        DAT_TileMapState::ptr)(t, DAT_BuildingsState::instance.buildings[i].widthOrHeight);
                    int tile = DAT_ViewportRenderState::instance
                                   .translationMatrix[(short)DAT_BuildingsState::instance.buildings[i].y
                                       + DAT_TileMapState::instance.buildingY]
                                   .addXgetTile
                        + (short)DAT_BuildingsState::instance.buildings[i].x + DAT_TileMapState::instance.buildingX;
                    DAT_TileMapState::instance.LogicLayer[tile]
                        = DAT_TileMapState::instance.LogicLayer[tile] & 0xfffffbff | 0x10000000;
                    ++t;
                } while (t < DAT_TileMapState::instance.constructionTileCount);
            }
        }

    }
}
}
