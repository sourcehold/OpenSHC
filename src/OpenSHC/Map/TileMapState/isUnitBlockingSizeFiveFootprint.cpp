#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAEE0
    BOOLEnum TileMapState::isUnitBlockingSizeFiveFootprint(int buildingID)
    {
        int const buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
        int const buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
        int const variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation / 2;
        int buildingSizeTileIndex = 0;
        int const* mapping = DAT_TerrainDefinedData::instance.field_0x21ec[variation];
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            if (*mapping == 0
                && this->UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + buildingY]
                                       .addXgetTile
                       + this->buildingX + buildingX]
                    != 0) {
                return TRUE;
            }
            buildingSizeTileIndex++;
            mapping++;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
        return FALSE;
    }

}
}
