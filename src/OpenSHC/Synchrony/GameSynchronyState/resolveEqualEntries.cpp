#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E050
    void GameSynchronyState::resolveEqualEntries(GUID* pGUID)
    {
        int _count = this->DPLAY_SessionsCount;
        for (int _index = 0; _index < _count; ++_index) {
            BOOLEnum _equality
                = MACRO_CALL(OS_Func::isEqualGUID)(pGUID, DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_index]);
            if (_equality) {
                int _offset = this->scrollBarItemOffset;
                if ((_index <= _offset) || (_index >= _offset + 10)) {
                    _offset = _count - 10;
                    this->scrollBarItemOffset = _index;
                    this->scrollBarIndex = 0;
                    if (_index <= _offset) {
                        return;
                    }
                    _offset = max(_offset, 0);
                    this->scrollBarItemOffset = _offset;
                }
                this->scrollBarIndex = _index - _offset;
                return;
            }
        }
        this->scrollBarItemOffset = 0;
        this->scrollBarIndex = -1;
    }

}
}
