#include "../Synchrony.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00428480
void Synchrony::PutPlayerIntoRandomSlot(int param_1)
{
    int iVar1 = 0;
    do {
        if ((int)DAT_GameSynchronyState::instance.playerPositionsArray[iVar1] == param_1 + -1) {}
        iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
    uint _playerPositionsCount = 0;
    uint uVar2 = 0;
    if (-1 < DAT_GameCore::instance.keepPositions[0].x) {
        uVar2 = 1;
        if (-1 < DAT_GameSynchronyState::instance.playerPositionsArray[0]) {
            _playerPositionsCount = 1;
            uVar2 = 1;
        }
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[1].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[1])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[2].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[2])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[3].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[3])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[4].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[4])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[5].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[5])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[6].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[6])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if ((-1 < DAT_GameCore::instance.keepPositions[7].x)
        && (uVar2 = uVar2 + 1, -1 < DAT_GameSynchronyState::instance.playerPositionsArray[7])) {
        _playerPositionsCount = _playerPositionsCount + 1;
    }
    if (_playerPositionsCount < uVar2) {
        int iVar3 = (int)SEC_RNG::instance.currentNumber1 % (int)(uVar2 - _playerPositionsCount);
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
        iVar1 = 0;
        while (DAT_GameCore::instance.keepPositions[iVar1].x < 0
            || -1 < DAT_GameSynchronyState::instance.playerPositionsArray[iVar1] || (iVar3 = iVar3 + -1, -1 < iVar3)) {
            iVar1 = iVar1 + 1;
            if (7 < iVar1) {}
        }
        DAT_GameSynchronyState::instance.playerPositionsArray[iVar1] = (char)param_1 + -1;
    }
}

}
