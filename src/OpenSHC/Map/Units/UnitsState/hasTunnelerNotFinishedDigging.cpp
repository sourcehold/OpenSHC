#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005339F0
BOOLEnum UnitsState::hasTunnelerNotFinishedDigging(int param_1)

{
return (uint)(this->units[param_1].tunnelerFinishedDigging == 0);
}


}
}
}