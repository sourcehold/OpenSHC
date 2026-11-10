#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AE7C0
    void Helpers::ClearLobbyHoveredAI() { DAT_LobbyAddAICurrentlyHoveredAI::instance = 0; }

}
}
