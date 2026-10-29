#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B6430
    void MinimapViewState::setSpawnMoment(int x, int y)
    {
        DWORD _now;
        if (this->spawnMomentCount < 20) {
            this->spawnMomentX[this->spawnMomentCount] = x;
            this->spawnMomentY[this->spawnMomentCount] = y;
            _now = timeGetTime();
            this->spawnMoment[this->spawnMomentCount] = _now;
            this->spawnMomentCount = this->spawnMomentCount + 1;
        }
    }

}
}
