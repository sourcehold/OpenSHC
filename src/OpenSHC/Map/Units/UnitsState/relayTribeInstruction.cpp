#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005371E0
        void UnitsState::relayTribeInstruction(
            int tribeID, UnitInstructionType instructionType, int targetID_1, int targetID_2, int param_5)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, instructionType, targetID_1, targetID_2, param_5);
        }
    }
}
}
