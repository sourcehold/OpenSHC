#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/UI/HoveredStateElement.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::UI::HoveredStateElement;
using OpenSHC::Game::GameMode;
using OpenSHC::Commands::MappersEnum;


/* 
  WARNING: Enum "MappersEnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005010E0
void HoveredState::clearInvalidatedHoverStates()

{
HoveredStateElement * _pElement;
int _index;

if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
_pElement = &this->elements[0];
_index = 20;
do {
if ((_pElement->type != OpenSHC::Commands::M_MAPPER_NULL) &&
(_pElement->time <= (int)DAT_GameCore::instance.mapTimeInTicks)) {
_pElement->type = OpenSHC::Commands::M_MAPPER_NULL;
}
_pElement = _pElement + 6;
_index = _index + -1;
} while (_index != 0);
}
return;
}


}
}