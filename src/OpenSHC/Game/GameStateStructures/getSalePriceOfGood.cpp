#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004588F0
int GameStateStructures::getSalePriceOfGood(ResourceType param_1)

{
return this->mapAndTime.buyAndSalesPriceArray[param_1].salesPrice / 5;
}


}
}