#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7700
        void TribesState::giveUnitSelectionMoveInstructionNoMatchedSpeed(
            undefined4 tribeID, undefined4 x, undefined4 y, undefined4 rallyBool, undefined4 doRally)

        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                tribeID, x, y, rallyBool, doRally, OpenSHC::Map::Units::Instructions::UMSE_0);
            return;
        }

    }
}
}
