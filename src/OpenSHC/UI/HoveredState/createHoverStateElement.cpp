#include "../HoveredState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::MappersEnum;
    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00501110
    void HoveredState::createHoverStateElement(int x, int y, MappersEnum type, int size, int flag)
    {
        MappersEnumInt* _pElement;
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            int _index = 0;
            _pElement = &this->elements[0].type;
            while (*_pElement != Commands::M_MAPPER_NULL) {
                _index = _index + 1;
                _pElement = _pElement + 6;
                if (20 < _index) {}
            }
            this->elements[_index].x = x;
            this->elements[_index].y = y;
            this->elements[_index].type = type;
            this->elements[_index].size = size;
            this->elements[_index].time
                = DAT_GameSynchronyState::instance.commandDelay + 5 + DAT_GameCore::instance.mapTimeInTicks;
            if (80 <= flag) {
                flag = 15;
            }
            this->elements[_index].rotationOrExtraInfo = flag;
        }
    }

}
}
