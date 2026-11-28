#include "../UCPointerStruct.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4D70
    void UCPointerStruct::loadMenuElement(
        int ucId, int* xPosPtr, int* yPosPtr, ushort* iconDeactivatedPtrUnk, int ucPositionIndex)
    {
        UC* uc = this->ucArrayPointer;
        *xPosPtr = 0;
        *yPosPtr = 0;
        *iconDeactivatedPtrUnk = 0;

        while (uc->defaultPosition.x != -1) {
            if (uc->id == ucId) {
                if (ucPositionIndex == 0) {
                    *xPosPtr = uc->defaultPosition.x;
                    *yPosPtr = uc->defaultPosition.y;
                } else if (uc->ucPositionArray[ucPositionIndex - 1].x == -1) {
                    *xPosPtr = uc->defaultPosition.x;
                    *yPosPtr = uc->defaultPosition.y;
                } else {
                    *xPosPtr = uc->ucPositionArray[ucPositionIndex - 1].x;
                    *yPosPtr = uc->ucPositionArray[ucPositionIndex - 1].y;
                    *iconDeactivatedPtrUnk = uc->isActiveArray[ucPositionIndex - 1] == 0;
                }
                return;
            }
            ++uc;
        }
    }

} // namespace UI
} // namespace OpenSHC
