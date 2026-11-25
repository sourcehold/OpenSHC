#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6430
    void MinimapViewState::setSpawnMoment(int x, int y)
    {
        if (this->spawnMomentCount >= countof(this->spawnMoment)) {
            return;
        }
        this->spawnMomentX[this->spawnMomentCount] = x;
        this->spawnMomentY[this->spawnMomentCount] = y;
        this->spawnMoment[this->spawnMomentCount] = timeGetTime();
        this->spawnMomentCount++;
    }

}
}
