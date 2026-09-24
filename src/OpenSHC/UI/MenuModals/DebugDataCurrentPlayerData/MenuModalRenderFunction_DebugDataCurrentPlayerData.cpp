#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataCurrentPlayerData.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataCurrentPlayerData {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAA40
            void MenuModalRenderFunction_DebugDataCurrentPlayerData(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::renderDebugDataCurrentPlayerData,
                    DAT_GameState::ptr)(x, y, width, height);
            }

        }
    }
}
}
