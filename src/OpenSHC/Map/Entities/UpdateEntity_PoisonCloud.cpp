#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401FF0
    void Entities::UpdateEntity_PoisonCloud()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = -1;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2++;
        short animFrame
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (animFrame < 8) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                - animFrame + 15;
        } else if (animFrame > 1016) {
            if (animFrame == 1024) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            } else {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                    + animFrame - 1008;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                    = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                          - 1016)
                    * 4;
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne > 31) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 31;
                }
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                    = -1 - DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne;
            }
        } else {
            if (animFrame >= 16) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 8;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1
                      + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                          .unknownAnimationFrameRelated
                      - 8)
                    % 8
                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 >= 800) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                    = 1016;
            }
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = (short)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 + 16;
        short linkedID
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownDistanceRelatedValue;
        if (linkedID != 0) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].uidRef
                == DAT_EntityState::instance.entityArray[linkedID].uid) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_EntityState::instance.entityArray[linkedID].xPosition,
                    DAT_EntityState::instance.entityArray[linkedID].yPosition,
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition,
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh >= 7) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownDistanceRelatedValue
                        = 0;
                }
            } else {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownDistanceRelatedValue = 0;
            }
        }
    }

}
}
