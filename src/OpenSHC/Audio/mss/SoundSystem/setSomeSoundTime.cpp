#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A2A0
        void SoundSystem::setSomeSoundTime()
        {
            if (!(0 < this->sec_Section1055_0x3274 && this->mbr_0x154 != 2)) {
                return;
            }

            if (this->mbr_0x154 == 1) {
                DWORD _currentTime = timeGetTime();
                // This logic seems to smooth out a time difference by not having the timestamp jump directly on
                //   bigger delays. Instead, it settles slightly behind the real time, basically pushing the current
                //   timestamp back a small bit, but in such a way that is gets closer and closer to the real time.
                this->someSoundTime_0x158
                    = (_currentTime + ((_currentTime - this->someSoundTime_0x158) / 200) * -10) - 1;
                this->mbr_0x154 = 2;
            } else {
                this->mbr_0x154 = 2;
                this->someSoundTime_0x158 = timeGetTime();
            }
        }
    }

}
}
