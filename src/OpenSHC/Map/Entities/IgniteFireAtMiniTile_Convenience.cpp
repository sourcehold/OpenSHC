#include "OpenSHC/Map/Entities.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00407130
uint Entities::IgniteFireAtMiniTile_Convenience(int playerID,int miniTileX,int miniTileY,int tileHeightMin8,int two)

{
uint uVar1;

uVar1 = MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(playerID, miniTileX, miniTileY, tileHeightMin8, two, 0);
return uVar1;
}


}
}