#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E050
    void GameSynchronyState::resolveEqualEntries(GUID* pGUID)
    {
        BOOLEnum _equality;
        int _count = this->DPLAY_SessionsCount;
        int _index = 0;
        if (0 < this->DPLAY_SessionsCount) {
            do {
                _equality = MACRO_CALL(OS_Func::isEqualGUID)(pGUID, (GUID*)((int)(this->DPLAY_SessionGUIDs[_index])));
                if (_equality) {
                    if ((_index <= this->scrollBarItemOffset) || (this->scrollBarItemOffset + 10 <= _index)) {
                        uint uVar1 = _count - 10;
                        if (_index <= (int)uVar1) {
                            this->scrollBarItemOffset = _index;
                            this->scrollBarIndex = 0;
                        }
                        this->scrollBarItemOffset = uVar1 & ((int)uVar1 <= 0) - 1;
                    }
                    this->scrollBarIndex = _index - this->scrollBarItemOffset;
                }
                _index = _index + 1;
            } while (_index < _count);
        }
        this->scrollBarIndex = -1;
        this->scrollBarItemOffset = 0;
    }

}
}
