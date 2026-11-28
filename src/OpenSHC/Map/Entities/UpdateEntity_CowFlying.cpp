#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402180
    void Entities::UpdateEntity_CowFlying()
    {
        short* psVar1;
        uint uVar2;
        int iVar3;
        uVar2 = DAT_CurrentEntityID::instance;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround == 0) {
            if (0xb
                < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
            }
            iVar3 = (int)DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset
                + (int)DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
            DAT_EntityState::instance.entityArray[uVar2].graphicType2 = iVar3;
            DAT_EntityState::instance.entityArray[uVar2].imageID = (short)iVar3 + 0x11;
        } else {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                < 100) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 100;
            }
            if (120 < DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated) {
                DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0x77;
            }
            psVar1 = &DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround;
            *psVar1 = *psVar1 + -1;
            if (DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround < 1) {
                DAT_EntityState::instance.entityArray[uVar2].logicalState = 7;
            }
            iVar3 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + -100;
            DAT_EntityState::instance.entityArray[uVar2].graphicType2 = ((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2) + 0xc
                + (int)DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset;
            DAT_EntityState::instance.entityArray[uVar2].imageID = 0;
        }
        if (DAT_EntityState::instance.entityArray[uVar2].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[uVar2].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 7;
        }
    }

}
}
