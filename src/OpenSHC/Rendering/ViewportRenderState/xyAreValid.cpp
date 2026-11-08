#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00401000
    BOOLEnum ViewportRenderState::xyAreValid(uint x, uint y)
    {
        return x <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1 && y <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
            && this->DAT_BinaryTileMap400x400[y * OpenSHC::Map::MC_MAP_XY_LIMIT + x] != 0;
    }

}
}
