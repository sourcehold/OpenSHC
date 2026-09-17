#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EEB0
    int GameSynchronyState::computeSomeHashOnUnitArray()
    {
        return MACRO_CALL_MEMBER(
            Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
            sizeof(DAT_UnitsState::instance.units), reinterpret_cast<int*>(DAT_UnitsState::instance.units));
    }

}
}
