#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Commands::MappersEnum;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409FF0
int BuildingsState::getSpriteID2(MappersEnum commandBuildingType)

{
BuildingType BVar1;
int iVar2;

BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(commandBuildingType);
if (DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[BVar1] == 0) {
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, this)(commandBuildingType);
return iVar2;
}
return DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[BVar1];
}


}
}
}