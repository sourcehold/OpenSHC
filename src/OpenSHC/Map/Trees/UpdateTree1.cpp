#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // Felled (zeroUpTo2 != 0): when the Tree_2 entry (A for stage 0) is <= 0 (signed jg 0x4F23C0) the index steps
    // back one. Standing: when the signed Tree_1 sway byte is <= 0 (jg 0x4F23EE) the index wraps to 0 and the
    // table is re-picked (B if one == 2). Frame per stage (jump table 0x4F2620, stages 0..4, rest 0x92);
    // 0x94 while field0_0x0.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2380
    void Trees::UpdateTree1()
    {
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2 != 0) {
            short const frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage == 0) {
                if (DAT_OrganismDefinedData::instance.Tree_2_A[frameIndex] <= 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = frameIndex - 1;
                }
            } else if (DAT_OrganismDefinedData::instance.Tree_2_B[frameIndex] <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = frameIndex - 1;
            }
        } else {
            int const frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[frameIndex] <= 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].one == 2;
                }
            } else if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[frameIndex] <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].one == 2;
            }
        }
        switch (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage) {
        case 0: {
            short const zeroUpTo2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2;
            if (zeroUpTo2 == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x8b;
                break;
            }
            if (zeroUpTo2 != 2) {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
                }
                break;
            }
        }
        // stage 0 with zeroUpTo2 2 shares the default frame (je 0x4F2600)
        default:
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0x92;
            break;
        case 1: {
            short const zeroUpTo2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2;
            if (zeroUpTo2 == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x81;
            } else if (zeroUpTo2 == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = 0x8c - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].treeAdultHoodStageRelatedVisual3;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
                }
            }
            break;
        }
        case 2: {
            short const zeroUpTo2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2;
            if (zeroUpTo2 == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x75;
            } else if (zeroUpTo2 == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = 0x82 - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].treeAdultHoodStageRelatedVisual3;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
                }
            }
            break;
        }
        case 3:
        case 4: {
            short const zeroUpTo2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2;
            if (zeroUpTo2 == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 100;
            } else if (zeroUpTo2 == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = 0x76 - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].treeAdultHoodStageRelatedVisual3;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
                }
            }
            break;
        }
        }
        if (DAT_LandscapeState::instance.field0_0x0 != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0x94;
        }
    }

}
}
