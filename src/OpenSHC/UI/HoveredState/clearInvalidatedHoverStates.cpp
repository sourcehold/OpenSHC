#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/HoveredStateElement.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::UI::HoveredStateElement;

    // FUNCTION: STRONGHOLDCRUSADER 0x005010E0
    void HoveredState::clearInvalidatedHoverStates()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int i = 0; i < 20; ++i) {
            if (this->elements[i].type != OpenSHC::Commands::M_MAPPER_NULL
                && (int)DAT_GameCore::instance.mapTimeInTicks >= this->elements[i].time) {
                this->elements[i].type = OpenSHC::Commands::M_MAPPER_NULL;
            }
        }
    }

}
}
