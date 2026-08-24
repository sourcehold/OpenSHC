#include "OpenSHC/Map/Entities.func.hpp"



#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00402AB0
void Entities::UpdateBrazierEntity()

{
DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 =
((byte)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated &7) +
(int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
return;
}


}
}