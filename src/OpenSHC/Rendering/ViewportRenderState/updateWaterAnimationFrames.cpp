#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5A90
    void ViewportRenderState::updateWaterAnimationFrames()
    {
        DWORD now = timeGetTime();

        this->field55_0x18b764 = 0;
        if ((int)(now - this->previousIntervalTime_04) >= (int)this->interval_04_180) {
            this->previousIntervalTime_04 = now;
            this->field55_0x18b764 = 1;
            for (int i = 0; i < 45; i++) {
                this->landscapeSeaWhiteCapsAnimationFrames[i] = this->landscapeSeaWhiteCapsAnimationFrames[i] + 1;
            }
        }

        if ((int)(now - this->previousIntervalTime_01) >= (int)this->interval_01_80) {
            this->previousIntervalTime_01 = now;
            this->unknownCounterUntil_0x10 = this->unknownCounterUntil_0x10 + 1;
            if (this->unknownCounterUntil_0x10 >= 0x10) {
                this->unknownCounterUntil_0x10 = 0;
            }
        }

        if ((int)(now - this->previousIntervalTime_02) >= (int)this->interval_02_100) {
            this->previousIntervalTime_02 = now;
            this->unknownCounterUntil_0x20 = this->unknownCounterUntil_0x20 + 1;
            if (this->unknownCounterUntil_0x20 >= 0x20) {
                this->unknownCounterUntil_0x20 = 0;
            }
        }

        if ((int)(now - this->previousIntervalTime_03) >= (int)this->interval_03_160) {
            this->previousIntervalTime_03 = now;
            this->unknownCounterUntil_0x24 = this->unknownCounterUntil_0x24 + 1;
            if (this->unknownCounterUntil_0x24 >= 0x24) {
                this->unknownCounterUntil_0x24 = 0;
            }
            this->unknownCounterUntil_0x200 = this->unknownCounterUntil_0x200 + 1;
            if (this->unknownCounterUntil_0x200 >= 0x200) {
                this->unknownCounterUntil_0x200 = 0;
            }
        }
    }

}
}
