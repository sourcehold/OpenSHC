#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004596D0
BOOLEnum GameStateStructures::getTeamsDifferent(int firstPlayerId,int secondPlayerId)

{
if ((firstPlayerId != 0) && (secondPlayerId != 0)) {
return (uint)(this->mapAndTime.playerTeams[firstPlayerId] !=
this->mapAndTime.playerTeams[secondPlayerId]);
}
return FALSE;
}


}
}