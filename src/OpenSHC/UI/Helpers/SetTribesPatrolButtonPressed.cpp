#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00434340
    void Helpers::SetTribesPatrolButtonPressed(BOOLEnum pressed)
    {
        DAT_TribesState::instance.patrolButtonPressed = pressed;
    }

}
}
