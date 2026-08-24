#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/AI/AIType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::AI::AIType;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0044B7D0
int GreatestLord::IfAiGreatestLordGetAiType()

{
int _highestRankingPlayer;

_highestRankingPlayer = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::GetPlayerAtRank)(0);
if ((_highestRankingPlayer != 0) &&
(DAT_GameSynchronyState::instance.currentAIArray[_highestRankingPlayer] != 0)) {
return(int)( DAT_GameState::instance.playerDataArray[_highestRankingPlayer].aiType + ~OpenSHC::AI::AIT_NULL);
}
return 0;
}


}
}