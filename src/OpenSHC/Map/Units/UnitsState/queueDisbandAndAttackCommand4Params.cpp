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


// FUNCTION: STRONGHOLDCRUSADER 0x00537160
void UnitsState::queueDisbandAndAttackCommand4Params(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_2;
DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = param_3;
DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = param_4;
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
return;
}


}
}
}