#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6480
    void MinimapViewState::clearOldSpawnMoment()
    {
        if (this->spawnMomentCount == 0) {
            return;
        }
        DWORD const now = timeGetTime();
        for (int i = 0; i < this->spawnMomentCount; ++i) {
            // drop the first spawn moment older than 20 seconds and shift the rest down
            if (20000 < (int)(now - this->spawnMoment[i])) {
                for (int next = i + 1; next < this->spawnMomentCount; ++next) {
                    this->spawnMomentX[next - 1] = this->spawnMomentX[next];
                    this->spawnMomentY[next - 1] = this->spawnMomentY[next];
                    this->spawnMoment[next - 1] = this->spawnMoment[next];
                }
                --this->spawnMomentCount;
                return;
            }
        }
    }

}
}
