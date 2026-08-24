#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::Player::PlayerID;
using OpenSHC::Commands::MappersEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004ECA60
BOOLEnum AICState::shouldNotBeBuildingArmoury(PlayerID playerID,MappersEnum param_2)

{
if (param_2 != OpenSHC::Commands::M_MAPPER_ARMOURY) {
return FALSE;
}
return (uint)(DAT_GameState::instance.playerDataArray[playerID].isArmouryAlmostFilledUp == 0);
}


}
}