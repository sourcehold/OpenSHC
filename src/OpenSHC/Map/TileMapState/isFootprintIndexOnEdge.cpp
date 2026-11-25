#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

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
