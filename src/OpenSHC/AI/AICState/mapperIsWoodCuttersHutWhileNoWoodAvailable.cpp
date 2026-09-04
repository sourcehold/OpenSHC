#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Commands::MappersEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnumShort": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004ECAB0
BOOLEnum AICState::mapperIsWoodCuttersHutWhileNoWoodAvailable(undefined4 playerID,MappersEnum param_2)

{
if ((param_2 == OpenSHC::Commands::M_MAPPER_WOODSMAN) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable < 1)) {
return TRUE;
}
return FALSE;
}


}
}