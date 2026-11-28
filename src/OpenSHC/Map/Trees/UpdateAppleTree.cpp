#include "../Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F26C0
    void Trees::UpdateAppleTree()
    {
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage < 6) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker += 1;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker
                >= DAT_OrganismDefinedData::instance
                    .TreeStageLevels[TT_TREE_APPLE]
                                    [DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage + 1]) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage += 1;
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage > 5) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage = 0;
                }
            }
            int const color = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 & 7;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = color;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage == 0
                && DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker < 250) {
                if (color == 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 2;
                } else if (color == 1) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 4;
                } else if (color == 3) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 5;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 7;
                }
            } else if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage == 5) {
                if (color == 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 2;
                } else if (color == 1) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 4;
                } else if (color == 3) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 5;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 7;
                }
            } else if (color == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 0;
            } else if (color == 4) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 1;
            } else if (color == 5) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 3;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 6;
            }
        } else {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].appleTreeColorVariation = 0;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker += 1;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker > 1200) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].state = 3;
            }
        }
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
            if ((char)DAT_OrganismDefinedData::instance
                    .Tree_1_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag
                    = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].one == 2;
            }
        } else if ((char)DAT_OrganismDefinedData::instance
                       .Tree_1_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
            <= 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag
                = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].one == 2;
        }
        switch (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage) {
        case 0:
        case 6:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance.Tree_1_B
                          [DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance.Tree_1_A
                          [DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
            }
            break;
        case 1:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 25;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 25;
            }
            break;
        case 2:
        case 4:
        case 5:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 75;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 75;
            }
            break;
        case 3:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 50;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                    = (char)DAT_OrganismDefinedData::instance
                          .Tree_1_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 50;
            }
            break;
        }
        if (DAT_LandscapeState::instance.field_0x0 != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0;
        }
    }

}
}
