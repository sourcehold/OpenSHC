#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537070
        void UnitsState::giveTribeMoveInstructionHumans(
            int tribeID, uint x, uint y, int rallyBool, MatchSpeedInstructionEnum speedMatching)
        {
            DAT_TribesState::instance.tribes[tribeID].freeUnitSpeeds = 0;
            if ((char)speedMatching < 0) {
                speedMatching = (Instructions::MatchSpeedInstructionEnum)(speedMatching & 0xffffff7f);
                DAT_TribesState::instance.tribes[tribeID].freeUnitSpeeds = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                tribeID, x, y, rallyBool, 1, (UnitMatchSpeedEnum)speedMatching);
        }

    }
}
}
