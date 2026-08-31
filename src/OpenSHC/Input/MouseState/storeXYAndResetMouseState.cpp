#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004687F0
    void MouseState::storeXYAndResetMouseState()
    {
        for (int i = 0; i < 10; ++i) {
            this->mouseXY[i].x = 0;
            this->mouseXY[i].y = 0;
            this->mouseXY[i].unknownZero01 = 0;
            this->mouseXY[i].unknownOne02 = 0;
        }

        this->index = 0;

        this->storedScreenSpaceX = this->screenSpaceX;
        this->storedScreenSpaceY = this->screenSpaceY;

        for (int i = 0; i < 10; ++i) {
            this->mouseXY8[i] = 8;
        }

        this->field46_0x184 = 0;
        this->field42_0x174 = 0;
        this->field47_0x188 = 8;
        this->field51_0x198 = 0;
        this->field52_0x19c = 0;

        this->mapOrientationCopy1 = DAT_TileMapState::instance.mapOrientation;
        this->mapOrientationCopy2 = DAT_TileMapState::instance.mapOrientation;
        this->mapOrientationCopy3 = DAT_TileMapState::instance.mapOrientation;

        this->field58_0x1b4 = 0;

        this->currentTime1 = timeGetTime();
        this->currentTime2 = timeGetTime();
        this->currentTime3 = timeGetTime();

        this->field56_0x1ac = 0;
        this->field59_0x1b8 = 0;
        this->field60_0x1bc = 0;
        this->field61_0x1c0 = 0;
        this->field62_0x1c4 = 0;
        this->field63_0x1c8 = 0;
    }

}
}
