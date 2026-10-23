#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6C60
    void TileMapState::setupLogicalMapBorders()
    {
        int index = 0;
        for (int rowWidth = 0; rowWidth < 400; rowWidth += 2) {
            this->LogicLayer[index] = L_BORDER;
            index++;
            if (rowWidth > 0) {
                this->LogicLayer[index] = L_BORDER_EDGE;
            }
            index = index + rowWidth;
            if (rowWidth > 0) {
                this->LogicLayer[index - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[index] = L_BORDER;
            index++;
        }
        for (int rowWidth = 398; rowWidth >= 0; rowWidth -= 2) {
            this->LogicLayer[index] = L_BORDER;
            index++;
            if (rowWidth > 0) {
                this->LogicLayer[index] = L_BORDER_EDGE;
            }
            index = index + rowWidth;
            if (rowWidth > 0) {
                this->LogicLayer[index - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[index] = L_BORDER;
            index++;
        }
    }

}
}
