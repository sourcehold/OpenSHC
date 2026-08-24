#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00458740
BOOLEnum GameStateStructures::isResourceTypeTradeable(ResourceType resourceType)

{
if (resourceType == OpenSHC::Game::Resources::RT_PITCH) {
resourceType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
}
return (uint)(this->mapAndTime.isResourceTradeable[resourceType] != 0);
}


}
}