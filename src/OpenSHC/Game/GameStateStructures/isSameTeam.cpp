#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401090
BOOLEnum GameStateStructures::isSameTeam(int playerID1,int playerID2)

{
return (uint)(this->mapAndTime.playerTeams[playerID1] ==
this->mapAndTime.playerTeams[playerID2]);
}


}
}