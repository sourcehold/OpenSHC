#include "../HoveredState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::MappersEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00501110
    void HoveredState::createHoverStateElement(int x, int y, MappersEnum type, int size, int flag)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            return;
        }
        for (int i = 0; i < countof(this->elements); ++i) {
            if (this->elements[i].type == Commands::M_MAPPER_NULL) {
                this->elements[i].x = x;
                this->elements[i].y = y;
                this->elements[i].type = type;
                this->elements[i].size = size;
                this->elements[i].time
                    = DAT_GameCore::instance.mapTimeInTicks + DAT_GameSynchronyState::instance.commandDelay + 5;
                if (flag >= 80) {
                    flag = 15;
                }
                this->elements[i].rotationOrExtraInfo = flag;
                return;
            }
        }
    }

}
}
