#include "OpenSHC/Map/Units/TribesState.func.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x00522BF0
void TribesState::queueUnitStance(undefined4 stanceID,undefined4 param_2)

{
DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_2;
DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = stanceID;
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNIT_STANCE);
return;
}


}
}
}