#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6C60
    void TileMapState::setupLogicalMapBorders()
    {
        int rowWidth = 0;
        int index = 0;
        for (; rowWidth < MC_MAP_XY_LIMIT; rowWidth += 2) {
            this->LogicLayer[index] = L_BORDER;
            index++;
            if (rowWidth > 0) {
                this->LogicLayer[index] = L_BORDER_EDGE;
            }
            index += rowWidth;
            if (rowWidth > 0) {
                this->LogicLayer[index - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[index] = L_BORDER;
            index++;
        }
        for (rowWidth = MC_MAP_XY_LIMIT - 2; rowWidth >= 0; rowWidth -= 2) {
            this->LogicLayer[index] = L_BORDER;
            index++;
            if (rowWidth > 0) {
                this->LogicLayer[index] = L_BORDER_EDGE;
            }
            index += rowWidth;
            if (rowWidth > 0) {
                this->LogicLayer[index - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[index] = L_BORDER;
            index++;
        }
    }

}
}
