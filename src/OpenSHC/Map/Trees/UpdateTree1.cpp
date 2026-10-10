#include "../../Map.func.hpp"
#include "../Trees.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2380
    void Trees::UpdateTree1()
    {
        short sVar1;
        short _rng2;
        short _rng2_2;
        short _rng2_3;
        short _isZero1_1;
        short _isZero1_2;
        short _rng2_4;
        short _isZero1_stage2;
        short _rng2_stage2;
        byte _rng2Data;
        int _rng2_2_data;
        int _tree;
        _tree = DAT_CurrentTreeID::instance;
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].zeroUpTo2 == 0) {
            _rng2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (!DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                _rng2Data = DAT_OrganismDefinedData::instance.Tree_1_A[_rng2];
            } else {
                _rng2Data = DAT_OrganismDefinedData::instance.Tree_1_B[_rng2];
            }
            if ((char)_rng2Data <= '\0') {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                DAT_LandscapeState::instance.trees[_tree].flag
                    = (uint)(DAT_LandscapeState::instance.trees[_tree].one == 2);
            }
        } else {
            _rng2_2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage == 0) {
                _rng2_2_data = DAT_OrganismDefinedData::instance.Tree_2_A[_rng2_2];
            } else {
                _rng2_2_data = DAT_OrganismDefinedData::instance.Tree_2_B[_rng2_2];
            }
            if (_rng2_2_data < 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = _rng2_2 + -1;
            }
        }
        switch (DAT_LandscapeState::instance.trees[_tree].stage) {
        case 0:
            _isZero1_1 = DAT_LandscapeState::instance.trees[_tree].zeroUpTo2;
            if (_isZero1_1 == 1) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_A[DAT_LandscapeState::instance.trees[_tree].animationFrameIndex]
                    + 0x8b;
                break;
            }
            if (_isZero1_1 != 2) {
                _rng2_3 = DAT_LandscapeState::instance.trees[_tree].animationFrameIndex;
                if (!DAT_LandscapeState::instance.trees[_tree].flag) {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_A[_rng2_3] + 0x4b;
                } else {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_B[_rng2_3] + 0x4b;
                }
                break;
            }
        default:
            DAT_LandscapeState::instance.trees[_tree].animationFrameUnk = 0x92;
            break;
        case 1:
            _isZero1_2 = DAT_LandscapeState::instance.trees[_tree].zeroUpTo2;
            if (_isZero1_2 == 1) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[_tree].animationFrameIndex]
                    + 0x81;
            } else if (_isZero1_2 == 2) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = 0x8c - (short)DAT_LandscapeState::instance.trees[_tree].treeAdultHoodStageRelatedVisual3;
            } else {
                _rng2_4 = DAT_LandscapeState::instance.trees[_tree].animationFrameIndex;
                if (!DAT_LandscapeState::instance.trees[_tree].flag) {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_A[_rng2_4] + 0x32;
                } else {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_B[_rng2_4] + 0x32;
                }
            }
            break;
        case 2:
            _isZero1_stage2 = DAT_LandscapeState::instance.trees[_tree].zeroUpTo2;
            if (_isZero1_stage2 == 1) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[_tree].animationFrameIndex]
                    + 0x75;
            } else if (_isZero1_stage2 == 2) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = 0x82 - (short)DAT_LandscapeState::instance.trees[_tree].treeAdultHoodStageRelatedVisual3;
            } else {
                _rng2_stage2 = DAT_LandscapeState::instance.trees[_tree].animationFrameIndex;
                if (!DAT_LandscapeState::instance.trees[_tree].flag) {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_A[_rng2_stage2] + 0x19;
                } else {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (char)DAT_OrganismDefinedData::instance.Tree_1_B[_rng2_stage2] + 0x19;
                }
            }
            break;
        case 3:
        case 4:
            sVar1 = DAT_LandscapeState::instance.trees[_tree].zeroUpTo2;
            if (sVar1 == 1) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[_tree].animationFrameIndex]
                    + 100;
            } else if (sVar1 == 2) {
                DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                    = 0x76 - (short)DAT_LandscapeState::instance.trees[_tree].treeAdultHoodStageRelatedVisual3;
            } else {
                sVar1 = DAT_LandscapeState::instance.trees[_tree].animationFrameIndex;
                if (!DAT_LandscapeState::instance.trees[_tree].flag) {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (int)(char)DAT_OrganismDefinedData::instance.Tree_1_A[sVar1];
                } else {
                    DAT_LandscapeState::instance.trees[_tree].animationFrameUnk
                        = (int)(char)DAT_OrganismDefinedData::instance.Tree_1_B[sVar1];
                }
            }
        }
        if (DAT_LandscapeState::instance.field0_0x0) {
            DAT_LandscapeState::instance.trees[_tree].animationFrameUnk = 0x94;
        }
    }

}
}
