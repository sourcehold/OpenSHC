#include "OpenSHC/Map/Entities.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00407130
    uint Entities::IgniteFireAtMiniTile_Convenience(
        int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two)
    {
        return MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(
            playerID, miniTileX, miniTileY, tileHeightMin8, two, 0);
    }

}
}
