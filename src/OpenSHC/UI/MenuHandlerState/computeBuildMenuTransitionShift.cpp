#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4CD0
    void MenuHandlerState::computeBuildMenuTransitionShift()
    {
        int _currentTime = timeGetTime();
        if (this->buildMenuTransitionProgress_0x38 == 100) {
            this->isBuildMenuTransitioning_0x18 = FALSE;
        }
        this->buildMenuTransitionProgress_0x38
            = ((_currentTime - this->buildMenuTransitionStartTime_0x30) * 100) / this->buildMenuTransitionDuration_0x34;
        if (this->buildMenuTransitionProgress_0x38 < 0x65) {
            if (this->buildMenuTransitionProgress_0x38 <= 0) {
                this->buildMenuTransitionProgress_0x38 = 1;
            }
        } else {
            this->buildMenuTransitionProgress_0x38 = 100;
        }
        int iVar2 = this->buildMenuTransitionProgress_0x38 * 0x178 >> 0x1f;
        int iVar3 = (this->buildMenuTransitionProgress_0x38 * 0x178) / 100 + iVar2;
        if (this->buildMenuTransitionDirection_0x2c <= 0) {
            dword dVar1 = -(iVar3 - iVar2);
            this->buildMenuBackgroundLeftShift_0x24 = dVar1 + 0x178;
            this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24;
            if (this->buildMenuTransitionProgress_0x38 < 0x32) {
                this->buildMenuItemsLeftShift_0x28 = dVar1;
            }
        } else {
            this->buildMenuBackgroundLeftShift_0x24 = iVar3 - iVar2;
            this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24;
            if (0x31 < this->buildMenuTransitionProgress_0x38) {
                this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24 - 0x178;
            }
        }
    }

}
}
