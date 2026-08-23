#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00535560
BOOLEnum UnitsState::selectionHasArchers()

{
if (this->selectionEuropeanArchers != 0) {
return TRUE;
}
return (uint)(this->selectionArabArcher != 0);
}


}
}
}