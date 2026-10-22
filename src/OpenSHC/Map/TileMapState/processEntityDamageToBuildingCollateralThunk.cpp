#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401060
    void TileMapState::processEntityDamageToBuildingCollateralThunk(
        int tile, uint x_2, uint y_2, int damage, int playerID, undefined4 unused)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processEntityDamageToBuildingCollateral, this)(
            tile, x_2, y_2, damage, playerID, unused, 0);
    }

}
}
