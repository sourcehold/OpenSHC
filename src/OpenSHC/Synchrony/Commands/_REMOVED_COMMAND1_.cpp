#include "OpenSHC/Synchrony/Commands.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00482280
    void Commands::_REMOVED_COMMAND1_() { DAT_GameSynchronyState::instance.DAT_CommandSize = 0; }

}
}
