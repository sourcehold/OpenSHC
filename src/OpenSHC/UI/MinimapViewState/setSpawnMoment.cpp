#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6430
    void MinimapViewState::setSpawnMoment(int x, int y)
    {
        if (this->spawnMomentCount < 20) {
            this->spawnMomentX[this->spawnMomentCount] = x;
            this->spawnMomentY[this->spawnMomentCount] = y;
            DWORD _now = timeGetTime();
            this->spawnMoment[this->spawnMomentCount] = _now;
            this->spawnMomentCount = this->spawnMomentCount + 1;
        }
    }

}
}
