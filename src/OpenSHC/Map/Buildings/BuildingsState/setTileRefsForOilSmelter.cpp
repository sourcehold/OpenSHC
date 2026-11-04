#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E740
        void BuildingsState::setTileRefsForOilSmelter(int buildingID)
        {
            for (int i = 0; i < 16; ++i) {
                uint x = DAT_BuildingDefinedData::instance.field412_0xa00c[i].x + (short)this->buildings[buildingID].x;
                uint y = DAT_BuildingDefinedData::instance.field412_0xa00c[i].y + (short)this->buildings[buildingID].y;
                if (x <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1 && y <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[x + y * OpenSHC::Map::MC_MAP_XY_LIMIT]
                        != 0) {
                    this->buildings[buildingID].tileRefs[i]
                        = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                }
            }
        }

    }
}
}
