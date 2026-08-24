#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004588D0
int GameStateStructures::getBuyPriceForOneUnit(int param_1)

{
return this->mapAndTime.buyAndSalesPriceArray[param_1].buyPrice / 5;
}


}
}