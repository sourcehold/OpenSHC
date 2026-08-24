#include "OpenSHC/Map/Units/TribesState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00525B70
int TribesState::popUnitFromTribe(int tribeID)

{
uint _unitID;

_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, 0);
if (_unitID != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, this)(_unitID, tribeID);
}
return(int)( _unitID);
}


}
}
}