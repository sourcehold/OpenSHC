#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5A90
    void ViewportRenderState::updateWaterAnimationFrames()
    {
        DWORD now = timeGetTime();

        this->field_0x18b764 = 0;
        if ((int)(now - this->previousIntervalTime_04) >= this->interval_04_180) {
            this->previousIntervalTime_04 = now;
            this->field_0x18b764 = 1;
            for (int i = 0; i < countof(this->landscapeSeaWhiteCapsAnimationFrames); ++i) {
                this->landscapeSeaWhiteCapsAnimationFrames[i]++;
            }
        }

        if ((int)(now - this->previousIntervalTime_01) >= this->interval_01_80) {
            this->previousIntervalTime_01 = now;
            this->unknownCounterUntil_0x10++;
            if (this->unknownCounterUntil_0x10 >= 16) {
                this->unknownCounterUntil_0x10 = 0;
            }
        }

        if ((int)(now - this->previousIntervalTime_02) >= this->interval_02_100) {
            this->previousIntervalTime_02 = now;
            this->unknownCounterUntil_0x20++;
            if (this->unknownCounterUntil_0x20 >= 32) {
                this->unknownCounterUntil_0x20 = 0;
            }
        }

        if ((int)(now - this->previousIntervalTime_03) >= this->interval_03_160) {
            this->previousIntervalTime_03 = now;
            this->unknownCounterUntil_0x24++;
            if (this->unknownCounterUntil_0x24 >= 36) {
                this->unknownCounterUntil_0x24 = 0;
            }
            this->unknownCounterUntil_0x200++;
            if (this->unknownCounterUntil_0x200 >= 512) {
                this->unknownCounterUntil_0x200 = 0;
            }
        }
    }

}
}
