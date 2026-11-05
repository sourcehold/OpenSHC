#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AE00
    void Version::ResetTeams()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
    }

}
}
