#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004588A0
int GameStateStructures::getBuyPrice(undefined4 playerID,int resourceType,int amount)

{
return (this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice / 5) * amount;
}


}
}