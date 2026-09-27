#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E1FA0
    ViewportRenderState* ViewportRenderState::Constructor_ViewportRenderState()
    {
        this->viewportState.viewportX = 32;
        this->viewportState.viewportY = 8;
        this->viewportState.field4_0x10 = -1;

        DWORD now = timeGetTime();
        this->previousIntervalTime_02 = now;
        this->previousIntervalTime_01 = now;
        this->previousIntervalTime_04 = now;
        this->previousIntervalTime_03 = now;

        this->viewportState.isZoomedOutUnk = 0;
        this->DAT_MapEditorDisplayLayer = 0;
        this->unknownCounterUntil_0x20 = 0;
        this->unknownCounterUntil_0x200 = 0;
        this->unknownCounterUntil_0x24 = 0;
        this->field55_0x18b764 = 0;
        this->unknownCounterUntil_0x10 = 0;
        this->viewportState.field37_0x94 = 0;

        this->interval_03_160 = 160;
        this->interval_04_180 = 180;
        this->interval_01_80 = 80;
        this->interval_02_100 = 100;
        this->availableFloaterIndex = 1;

        for (int i = 0; i < 45; i++) {
            this->landscapeAnimationRandomTileArray[i] = 0;
        }
        return this;
    }

}
}
