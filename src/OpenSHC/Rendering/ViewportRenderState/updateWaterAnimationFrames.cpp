#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5A90
    void ViewportRenderState::updateWaterAnimationFrames()
    {
        DWORD now = timeGetTime();

        this->slowAnimationTicked = FALSE;
        if ((int)(now - this->slowAnimationPreviousTime) >= this->slowAnimationInterval) {
            this->slowAnimationPreviousTime = now;
            this->slowAnimationTicked = TRUE;
            for (int i = 0; i < countof(this->landscapeSeaWhiteCapsAnimationFrames); ++i) {
                this->landscapeSeaWhiteCapsAnimationFrames[i]++;
            }
        }

        if ((int)(now - this->animationFrame16PreviousTime) >= this->animationFrame16Interval) {
            this->animationFrame16PreviousTime = now;
            this->animationFrame16++;
            if (this->animationFrame16 >= 16) {
                this->animationFrame16 = 0;
            }
        }

        if ((int)(now - this->animationFrame32PreviousTime) >= this->animationFrame32Interval) {
            this->animationFrame32PreviousTime = now;
            this->animationFrame32++;
            if (this->animationFrame32 >= 32) {
                this->animationFrame32 = 0;
            }
        }

        if ((int)(now - this->animationFrame36PreviousTime) >= this->animationFrame36Interval) {
            this->animationFrame36PreviousTime = now;
            this->animationFrame36++;
            if (this->animationFrame36 >= 36) {
                this->animationFrame36 = 0;
            }
            this->animationFrame512++;
            if (this->animationFrame512 >= 512) {
                this->animationFrame512 = 0;
            }
        }
    }

}
}
