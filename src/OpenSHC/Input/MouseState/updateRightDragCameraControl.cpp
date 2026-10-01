#include "../MouseState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00470BC0
    void MouseState::updateRightDragCameraControl()
    {
        int iVar6 = this->mapOrientationCopy3;

        this->mouseBasedEvent = 0;
        this->field44_0x17c = 0;
        this->field43_0x178 = 0;
        this->field59_0x1b8 = 0;

        DWORD DVar4 = timeGetTime();

        this->currentTime3 = DVar4;
        this->field56_0x1ac = DVar4 - this->currentTime2;

        ++this->field42_0x174;
        if (this->field56_0x1ac > this->field57_0x1b0) {
            this->currentTime2 = DVar4;
            this->field58_0x1b4 = 0;
            this->field51_0x198 = 0;
            this->field52_0x19c = 0;
        }

        int iVar5
            = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 4);

        if (iVar5 < 12 || this->field61_0x1c0) {
            this->field43_0x178 = 0;
        } else if (iVar5 < 28) {
            this->field43_0x178 = iVar5 / 2;
            this->mouseBasedEvent = 2;
        } else {
            this->field59_0x1b8 = 1;
            this->field60_0x1bc = 1;
            this->field62_0x1c4 = 1;
            this->field63_0x1c8 = 1;
            this->field43_0x178 = 40;
            this->mouseBasedEvent = 1;
        }

        iVar5 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
            DAT_DirectionAlgorithmState::ptr)(
            this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 0);
        if (iVar5 < 22 || this->field60_0x1bc) {
            this->field42_0x174 = 0;
            this->field58_0x1b4 = 0;

            if (this->field59_0x1b8 == 2 || iVar5 < 22) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->field61_0x1c0 = 1;
            this->field62_0x1c4 = 1;
            this->field63_0x1c8 = 1;
            this->field59_0x1b8 = 2;
            this->field57_0x1b0 = 1500;

            if (!this->field58_0x1b4) {
                this->field58_0x1b4 = 1;

                iVar6 = this->mapOrientationCopy3 + 6;
                if (iVar6 >= 8) {
                    iVar6 -= 8;
                }

                this->field47_0x188 = 0;
            } else {
                this->field47_0x188 = 8;
            }
        }

        if (iVar6 != this->mapOrientationCopy2) {
            this->mapOrientationCopy2 = iVar6;
            this->mapOrientationCopy3 = iVar6;
            this->mouseBasedEvent = 3;
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 2)
                < 55
            || this->field63_0x1c8) {

            this->field42_0x174 = 0;
            if (this->field59_0x1b8 == 3) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->field61_0x1c0 = 1;
            this->field62_0x1c4 = 1;
            this->field60_0x1bc = 1;
            this->field57_0x1b0 = 2000;
            this->field59_0x1b8 = 3;

            if (this->field51_0x198 != 2) {
                this->mouseBasedEvent = 4;
                this->field51_0x198 = 1;
            }
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 6)
                < 55
            || this->field62_0x1c4) {

            this->field42_0x174 = 0;
            if (this->field59_0x1b8 == 4) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->field61_0x1c0 = 1;
            this->field63_0x1c8 = 1;
            this->field60_0x1bc = 1;
            this->field57_0x1b0 = 2000;
            this->field59_0x1b8 = 4;

            if (this->field52_0x19c != 2) {
                this->mouseBasedEvent = 5;
                this->field52_0x19c = 1;
            }
        }
    }

}
}
