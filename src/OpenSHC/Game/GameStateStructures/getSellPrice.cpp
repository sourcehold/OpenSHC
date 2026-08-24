#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00458910
int GameStateStructures::getSellPrice(int playerID,int resourceType,int amount)

{
return (this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5) * amount;
}


}
}