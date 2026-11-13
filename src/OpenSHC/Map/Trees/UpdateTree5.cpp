#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2640
    void Trees::UpdateTree5()
    {
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
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                = (char)DAT_OrganismDefinedData::instance
                      .Tree_1_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
        } else {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk
                = (char)DAT_OrganismDefinedData::instance
                      .Tree_1_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
        }
        if (DAT_LandscapeState::instance.field_0x0 != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0;
        }
    }

}
}
