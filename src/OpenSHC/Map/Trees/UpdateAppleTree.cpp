#include "../../Map.func.hpp"
#include "../Trees.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F26C0
    void Trees::UpdateAppleTree()
    {
        int* piVar1;
        byte bVar2;
        uint _rng1_0to8;
        int _frame;
        int _stage;
        short _index;
        int _treeID;
        _treeID = DAT_CurrentTreeID::instance;
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage < 6) {
            piVar1 = &DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker;
            *piVar1 = *piVar1 + 1;
            if (DAT_OrganismDefinedData::instance
                    .TreeStageLevels[0xf][DAT_LandscapeState::instance.trees[_treeID].stage + 1]
                <= DAT_LandscapeState::instance.trees[_treeID].stageTracker) {
                DAT_LandscapeState::instance.trees[_treeID].stageTracker = 0;
                piVar1 = &DAT_LandscapeState::instance.trees[_treeID].stage;
                /*
                  This updates the apple tree season state
                 */
                *piVar1 = *piVar1 + 1;
                if (5 < DAT_LandscapeState::instance.trees[_treeID].stage) {
                    DAT_LandscapeState::instance.trees[_treeID].stage = 0;
                }
            }
            _rng1_0to8 = DAT_LandscapeState::instance.trees[_treeID].rng1 & 7;
            DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = _rng1_0to8;
            _stage = DAT_LandscapeState::instance.trees[_treeID].stage;
            if ((!_stage) && (DAT_LandscapeState::instance.trees[_treeID].stageTracker < 0xfa)) {
                if (!_rng1_0to8) {
                    DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = 2;
                } else {
                LAB_004f274d:
                    if (_rng1_0to8 == 1) {
                        DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = 4;
                    } else {
                        DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation
                            = (uint)(_rng1_0to8 != 3) * 2 + 5;
                    }
                }
            } else if (_stage == 5) {
                if (_rng1_0to8)
                    goto LAB_004f274d;
                DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = 2;
            } else if (_rng1_0to8 == 2) {
                DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = 0;
            } else if (_rng1_0to8 == 4) {
                DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation = 1;
            } else {
                DAT_LandscapeState::instance.trees[_treeID].appleTreeColorVariation
                    = (-(uint)(_rng1_0to8 != 5) & 3) + 3;
            }
        } else {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 0;
            piVar1 = &DAT_LandscapeState::instance.trees[_treeID].stageTracker;
            *piVar1 = *piVar1 + 1;
            if (0x4b0 < DAT_LandscapeState::instance.trees[_treeID].stageTracker) {
                DAT_LandscapeState::instance.trees[_treeID].state = 3;
            }
        }
        _index = DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex;
        if (!DAT_LandscapeState::instance.trees[_treeID].flag) {
            bVar2 = DAT_OrganismDefinedData::instance.Tree_1_A[_index];
        } else {
            bVar2 = DAT_OrganismDefinedData::instance.Tree_1_B[_index];
        }
        if ((char)bVar2 <= '\0') {
            DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex = 0;
            DAT_LandscapeState::instance.trees[_treeID].flag
                = (uint)(DAT_LandscapeState::instance.trees[_treeID].one == 2);
        }
        switch (DAT_LandscapeState::instance.trees[_treeID].stage) {
        case 0:
        case 6:
            _index = DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex;
            if (!DAT_LandscapeState::instance.trees[_treeID].flag) {
                _frame = (int)(char)DAT_OrganismDefinedData::instance.Tree_1_A[_index];
            } else {
                _frame = (int)(char)DAT_OrganismDefinedData::instance.Tree_1_B[_index];
            }
            break;
        case 1:
            _index = DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex;
            if (!DAT_LandscapeState::instance.trees[_treeID].flag) {
                _frame = (char)DAT_OrganismDefinedData::instance.Tree_1_A[_index] + 0x19;
            } else {
                _frame = (char)DAT_OrganismDefinedData::instance.Tree_1_B[_index] + 0x19;
            }
            break;
        case 2:
        case 4:
        case 5:
            _index = DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex;
            if (!DAT_LandscapeState::instance.trees[_treeID].flag) {
                _frame = (char)DAT_OrganismDefinedData::instance.Tree_1_A[_index] + 0x4b;
            } else {
                _frame = (char)DAT_OrganismDefinedData::instance.Tree_1_B[_index] + 0x4b;
            }
            break;
        case 3:
            _index = DAT_LandscapeState::instance.trees[_treeID].animationFrameIndex;
            if (!DAT_LandscapeState::instance.trees[_treeID].flag) {
                bVar2 = DAT_OrganismDefinedData::instance.Tree_1_A[_index];
            } else {
                bVar2 = DAT_OrganismDefinedData::instance.Tree_1_B[_index];
            }
            _frame = (char)bVar2 + 0x32;
            break;
        default:
            goto switchD_004f281e_caseD_7;
        }
        DAT_LandscapeState::instance.trees[_treeID].animationFrameUnk = _frame;
    switchD_004f281e_caseD_7:
        if (DAT_LandscapeState::instance.field0_0x0) {
            DAT_LandscapeState::instance.trees[_treeID].animationFrameUnk = 0;
        }
    }

}
}
