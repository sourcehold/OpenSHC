#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7700
        void TribesState::giveUnitSelectionMoveInstructionNoMatchedSpeed(
            int tribeID, uint x, uint y, int rallyBool, int doRally)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                tribeID, x, y, rallyBool, doRally, Units::Instructions::UMSE_0);
        }

    }
}
}
