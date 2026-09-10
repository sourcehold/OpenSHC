#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EEB0
    int GameSynchronyState::computeSomeHashOnUnitArray()
    {
        return MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
            DAT_DirectionAlgorithmState::ptr)(2920000, (int*)((int)(DAT_UnitsState::instance.units)));
    }

}
}
