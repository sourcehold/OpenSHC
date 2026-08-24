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


// FUNCTION: STRONGHOLDCRUSADER 0x00409300
BOOLEnum TileMapState::processDamageToBuildingThunk(int targetedTile,uint targetedTileX,uint targetedTileY,int damage,int param_5,int playerID,BOOLEnum aiBuildDelayRelated)

{
BOOLEnum BVar1;

BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding, this)(targetedTile, targetedTileX, targetedTileY, damage, param_5, 
playerID, aiBuildDelayRelated, 0);
return BVar1;
}


}
}