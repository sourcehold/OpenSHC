#include "../UCPointerStruct.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4D70
    void UCPointerStruct::loadMenuElement(int ucId, int* xPosPtr, int* yPosPtr, ushort* iconDeactivatedPtrUnk,
        int ucPositionIndex)
    {
        UC* uc = this->ucArrayPointer;
        *xPosPtr = 0;
        *yPosPtr = 0;
        *iconDeactivatedPtrUnk = 0;

        int selectedPosition = 0;
        for (; uc->defaultPosition.x != -1; ++uc) {
            if (uc->id == ucId) {
                if (ucPositionIndex == 0 || uc->ucPositionArray[ucPositionIndex - 1].x == -1) {
                    *xPosPtr = uc->defaultPosition.x;
                    *yPosPtr = uc->defaultPosition.y;
                    return;
                }
                selectedPosition = ucPositionIndex;
                break;
            }
        }
        if (selectedPosition != 0) {
            *xPosPtr = uc->ucPositionArray[selectedPosition - 1].x;
            *yPosPtr = uc->ucPositionArray[selectedPosition - 1].y;
            *iconDeactivatedPtrUnk = uc->isActiveArray[selectedPosition - 1] == 0;
        }
    }

} // namespace UI
} // namespace OpenSHC
