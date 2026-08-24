#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Entities {

using OpenSHC::Map::Entities::EntityType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401540
int EntityState::getFireEntityIDAtTile(int tile)

{
short _entityTileID;
int _entityTileID_2;

_entityTileID = DAT_TileMapState::instance.EntityLayer[tile];
while( true ) {
_entityTileID_2 = (int)_entityTileID;
if (_entityTileID_2 == 0) {
return 0;
}
if (this->entityArray[_entityTileID_2].entityType == OpenSHC::Map::Entities::ET_FIRE) break;
_entityTileID = this->entityArray[_entityTileID_2].nextEntityOnThisTileByID;
}
return _entityTileID_2;
}


}
}
}