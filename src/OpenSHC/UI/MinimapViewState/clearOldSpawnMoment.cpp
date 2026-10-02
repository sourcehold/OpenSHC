#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B6480
    void MinimapViewState::clearOldSpawnMoment()
    {
        DWORD _now;
        int* piVar1;
        int _index;
        int _nextIndex;
        DWORD* _ptrMoment;
        if (this->spawnMomentCount != 0) {
            _now = timeGetTime();
            if (0 < this->spawnMomentCount) {
                _ptrMoment = this->spawnMoment;
                _index = 0;
                while (_nextIndex = _index + 1, (int)(_now - *_ptrMoment) < 20000) {
                    _ptrMoment = _ptrMoment + 1;
                    _index = _nextIndex;
                    if (this->spawnMomentCount <= _nextIndex) {}
                }
                /*
                  If there is a spawnmoment after 20 seconds
                 */
                if (_nextIndex < this->spawnMomentCount) {
                    piVar1 = this->spawnMomentX + _index;
                    do {
                        *piVar1 = piVar1[1];
                        piVar1[0x14] = piVar1[0x15];
                        piVar1[0x28] = piVar1[0x29];
                        _nextIndex = _nextIndex + 1;
                        piVar1 = piVar1 + 1;
                    } while (_nextIndex < this->spawnMomentCount);
                }
                this->spawnMomentCount = this->spawnMomentCount + -1;
            }
        }
    }

}
}
