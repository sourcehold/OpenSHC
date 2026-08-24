#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalStateShort;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004197C0
void BuildingsState::updatePathLinkageLayerForAllBuildings()

{
BuildingLogicalStateShort *_ptrLogicalState;
int _buildingID;

_buildingID = 1;
_ptrLogicalState = &this->buildings[1].logicalState;
do {
if (*_ptrLogicalState != ((BuildingLogicalState)0)) {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, DAT_TileMapState::ptr)(_buildingID);
}
_ptrLogicalState = _ptrLogicalState + 0x196;
_buildingID = _buildingID + 1;
} while ((int)_ptrLogicalState < 0x1124dc4);
return;
}


}
}
}