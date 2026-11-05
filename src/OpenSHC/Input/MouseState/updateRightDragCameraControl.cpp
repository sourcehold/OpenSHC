#include "../MouseState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00470BC0
    void MouseState::updateRightDragCameraControl()
    {
        int newMapOrientation = this->mapOrientationCopy3;

        this->mouseBasedEvent = 0;
        this->field_0x17c = 0;
        this->field_0x178 = 0;
        this->field_0x1b8 = 0;

        DWORD currentTime = timeGetTime();

        this->currentTime3 = currentTime;
        this->field_0x1ac = currentTime - this->currentTime2;

        ++this->field_0x174;
        if (this->field_0x1ac > this->field_0x1b0) {
            this->currentTime2 = currentTime;
            this->field_0x1b4 = 0;
            this->field_0x198 = 0;
            this->field_0x19c = 0;
        }

        int dragDistance
            = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 4);

        if (dragDistance < 12 || this->field_0x1c0) {
            this->field_0x178 = 0;
        } else if (dragDistance < 28) {
            this->field_0x178 = dragDistance / 2;
            this->mouseBasedEvent = 2;
        } else {
            this->field_0x1b8 = 1;
            this->field_0x1bc = 1;
            this->field_0x1c4 = 1;
            this->field_0x1c8 = 1;
            this->field_0x178 = 40;
            this->mouseBasedEvent = 1;
        }

        dragDistance
            = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 0);
        if (dragDistance < 22 || this->field_0x1bc) {
            this->field_0x174 = 0;
            this->field_0x1b4 = 0;

            if (this->field_0x1b8 == 2 || dragDistance < 22) {
                this->currentTime2 = currentTime;
            }
        } else {
            this->field_0x1c0 = 1;
            this->field_0x1c4 = 1;
            this->field_0x1c8 = 1;
            this->field_0x1b8 = 2;
            this->field_0x1b0 = 1500;

            if (!this->field_0x1b4) {
                this->field_0x1b4 = 1;

                newMapOrientation = this->mapOrientationCopy3 + 6;
                if (newMapOrientation >= 8) {
                    newMapOrientation -= 8;
                }

                this->field_0x188 = 0;
            } else {
                this->field_0x188 = 8;
            }
        }

        if (newMapOrientation != this->mapOrientationCopy2) {
            this->mapOrientationCopy2 = newMapOrientation;
            this->mapOrientationCopy3 = newMapOrientation;
            this->mouseBasedEvent = 3;
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 2)
                < 55
            || this->field_0x1c8) {

            this->field_0x174 = 0;
            if (this->field_0x1b8 == 3) {
                this->currentTime2 = currentTime;
            }
        } else {
            this->field_0x1c0 = 1;
            this->field_0x1c4 = 1;
            this->field_0x1bc = 1;
            this->field_0x1b0 = 2000;
            this->field_0x1b8 = 3;

            if (this->field_0x198 != 2) {
                this->mouseBasedEvent = 4;
                this->field_0x198 = 1;
            }
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 6)
                < 55
            || this->field_0x1c4) {

            this->field_0x174 = 0;
            if (this->field_0x1b8 == 4) {
                this->currentTime2 = currentTime;
            }
        } else {
            this->field_0x1c0 = 1;
            this->field_0x1c8 = 1;
            this->field_0x1bc = 1;
            this->field_0x1b0 = 2000;
            this->field_0x1b8 = 4;

            if (this->field_0x19c != 2) {
                this->mouseBasedEvent = 5;
                this->field_0x19c = 1;
            }
        }
    }

}
}
