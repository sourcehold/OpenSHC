#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419BE0
        void BuildingsState::rebuildTileLogicLayerForKeeps()
        {
            for (int buildingID = 1; buildingID < 2000; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != 0
                    && DAT_BuildingDefinedData::instance
                            .BuildingIsKeepArray[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        != 0) {
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
                        DAT_TileMapState::instance.LogicLayer[tile]
                            = DAT_TileMapState::instance.LogicLayer[tile] & ~LogicHelpers::L_BUILDING
                            | LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
                        ++i;
                    } while (i < DAT_TileMapState::instance.constructionTileCount);
                }
            }
        }

    }
}
}
