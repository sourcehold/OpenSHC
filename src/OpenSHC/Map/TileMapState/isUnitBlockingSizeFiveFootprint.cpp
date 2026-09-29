
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FAEE0
    BOOLEnum TileMapState::isUnitBlockingSizeFiveFootprint(int buildingID)
    {
        int buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
        int buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
        int variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation / 2;
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            if (DAT_TerrainDefinedData::instance.field2469_0x21ec[variation][buildingSizeTileIndex] == 0
                && this->UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + buildingY]
                                       .addXgetTile
                       + this->buildingX + buildingX]
                    != 0) {
                return TRUE;
            }
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);
        return FALSE;
    }

}
}
