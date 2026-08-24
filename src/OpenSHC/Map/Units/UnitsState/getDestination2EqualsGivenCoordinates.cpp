#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00533920
BOOLEnum UnitsState::getDestination2EqualsGivenCoordinates(int unitID,int x,int y)

{
if (this->units[unitID].destinationX_2Unk != x) {
return TRUE;
}
return (uint)(this->units[unitID].destinationY_2Unk != y);
}


}
}
}