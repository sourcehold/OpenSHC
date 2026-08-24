#include "OpenSHC/Map/TileMapState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401060
void TileMapState::processEntityDamageToBuildingCollateralThunk(int tile,uint x_2,uint y_2,int damage,int playerID,undefined4 unused)

{
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processEntityDamageToBuildingCollateral, this)(tile, x_2, y_2, damage, playerID, (undefined4)((int)(unused)), 0);
return;
}


}
}