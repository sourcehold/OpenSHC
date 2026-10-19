#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E890
    int GameSynchronyState::countOccupiedPlayerSlots()
    {
        int* _aiPtr;
        int iVar1;
        int _sum = 0;
        for (_aiPtr = this->currentAIArray + 1, iVar1 = 2; iVar1; _aiPtr = _aiPtr + 4, iVar1 = iVar1 + -1) {
            if ((_aiPtr[-0x1b] != -1) || (*_aiPtr != 0)) {
                _sum = _sum + 1;
            }
            if ((_aiPtr[-0x1a] != -1) || (_aiPtr[1] != 0)) {
                _sum = _sum + 1;
            }
            if ((_aiPtr[-0x19] != -1) || (_aiPtr[2] != 0)) {
                _sum = _sum + 1;
            }
            if ((_aiPtr[-0x18] != -1) || (_aiPtr[3] != 0)) {
                _sum = _sum + 1;
            }
        }
        return _sum;
    }

}
}
