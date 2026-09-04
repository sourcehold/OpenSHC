#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"



#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::Commands::GameCommandType;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005370C0
void UnitsState::extendRallyPoint(int tribeID,int mouseX,int mouseY,int rallyCount)

{
DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = tribeID;
DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = mouseX;
DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = mouseY;
DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = rallyCount;
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNIT_EXTEND_RALLY_POINT);
return;
}


}
}
}