#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9930
    BOOLEnum TileMapState::isFootprintIndexOnEdge(int counter, int size)
    {
        if (size < 3) {
            return TRUE;
        }
        if (counter < size) {
            return TRUE;
        }
        if (counter >= (size - 1) * size) {
            return TRUE;
        }
        if (counter % size == 0) {
            return TRUE;
        }
        return counter % size == size - 1;
    }

}
}
