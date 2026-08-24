#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045B7F0
int GameStateStructures::getSalesPrice(int playerID,int resourceType)

{
int _sellAmountUnk;

_sellAmountUnk = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellResourceAmount, this)(playerID, resourceType);
/* 
  Actually the same as "this", but the compiler used that EDX is not dirtied.
   The decompilation assumes this sadly. --TheRedDaemon
 */

return (this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5) *
_sellAmountUnk;
}


}
}