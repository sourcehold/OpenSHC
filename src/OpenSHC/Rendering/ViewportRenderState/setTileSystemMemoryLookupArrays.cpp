#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    /*
      WARNING: Function: __alloca_probe replaced with injection: alloca_probe
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2050
    void ViewportRenderState::setTileSystemMemoryLookupArrays()

    {
        int* piVar1;
        int* piVar2;
        int* piVar3;
        int _i;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int _countdownBy1_199;
        int _countdown_by2_398;
        int _200;
        int _79600;
        int _stack[160001];
        int* _ptrStack;
        int _countupBy2_2;
        int _8;

        this->translationTracker1 = 0;
        _ptrStack = _stack;
        for (_i = 160000; _i != 0; _i = _i + -1) {
            *_ptrStack = 0;
            _ptrStack = _ptrStack + 1;
        }
        _countdownBy1_199 = 199;
        _countupBy2_2 = 2;
        _8 = 0;
        _countdown_by2_398 = 398;
        piVar1 = &this->translationMatrix[0].firstTileOfRow;
        do {
            ((TranslationMatrixTriplet*)(piVar1 + -1))->distanceToCenter = _countdown_by2_398 / 2;
            *piVar1 = this->translationTracker1;
            piVar1[1] = this->translationTracker1 - _countdown_by2_398 / 2;
            if (0 < _countupBy2_2) {
                piVar2 = _stack + _countdownBy1_199 + _8;
                iVar4 = _countupBy2_2;
                do {
                    *piVar2 = this->translationTracker1;
                    piVar2 = piVar2 + 1;
                    this->translationTracker1 = this->translationTracker1 + 1;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }
            _countdown_by2_398 = _countdown_by2_398 + -2;
            _countdownBy1_199 = _countdownBy1_199 + -1;
            _8 = _8 + 400;
            _countupBy2_2 = _countupBy2_2 + 2;
            piVar1 = piVar1 + 3;
        } while (_8 < 80000);
        /*
         *** change of meaning ***
         */

        _countdown_by2_398 = 80000;
        _8 = 400 - _countupBy2_2;
        piVar1 = &this->translationMatrix[200].firstTileOfRow;
        do {
            _countdownBy1_199 = _countdownBy1_199 + 1;
            _8 = _8 + 2;
            _countupBy2_2 = _countupBy2_2 + -2;
            ((TranslationMatrixTriplet*)(piVar1 + -1))->distanceToCenter = _8 / 2;
            *piVar1 = this->translationTracker1;
            piVar1[1] = this->translationTracker1 - _8 / 2;
            if (0 < _countupBy2_2) {
                piVar2 = _stack + _countdown_by2_398 + _countdownBy1_199;
                iVar4 = _countupBy2_2;
                do {
                    *piVar2 = this->translationTracker1;
                    piVar2 = piVar2 + 1;
                    this->translationTracker1 = this->translationTracker1 + 1;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }
            _countdown_by2_398 = _countdown_by2_398 + 400;
            piVar1 = piVar1 + 3;
        } while (_countdown_by2_398 < 160000);
        this->translationResult1 = (400 - _countupBy2_2) / 2;
        this->translationResult2 = this->translationTracker1 - this->translationResult1;
        this->field9_0x4e5e0 = 0;
        this->field10_0x4e5e4 = 0;
        this->field11_0x4e5e8 = 0;
        this->field12_0x4e5ec = 0;
        this->field13_0x4e5f0 = 0;
        this->field14_0x4e5f4 = 0;
        this->field15_0x4e5f8 = 0;
        this->field16_0x4e5fc = 0;
        _200 = 200;
        _countdownBy1_199 = 0;
        _79600 = 79600;
        piVar1 = this->screenPointToTileNumber;
        _8 = 8;
        do {
            iVar7 = _8;
            iVar6 = 200;
            piVar3 = piVar1 + 200;
            piVar2 = piVar1;
            _8 = _countdownBy1_199;
            iVar4 = _79600;
            do {
                *piVar2 = _stack[iVar4 + _8];
                iVar6 = iVar6 + -1;
                piVar2 = piVar2 + 1;
                _8 = _8 + 1;
                iVar4 = iVar4 + -400;
            } while (0 < iVar6);
            _79600 = _79600 + 400;
            piVar1 = piVar1 + 401;
            iVar6 = 200;
            _8 = _countdownBy1_199;
            iVar4 = _79600;
            do {
                *piVar3 = _stack[iVar4 + _8];
                iVar6 = iVar6 + -1;
                piVar3 = piVar3 + 1;
                _8 = _8 + 1;
                iVar4 = iVar4 + -400;
            } while (-1 < iVar6);
            _200 = _200 + -1;
            _countdownBy1_199 = _countdownBy1_199 + 1;
            _8 = iVar7 + 401;
        } while (0 < _200);
        _8 = 200;
        piVar1 = this->screenPointToTileNumber + iVar7 + 393;
        iVar4 = 159600;
        do {
            *piVar1 = _stack[iVar4 + _countdownBy1_199];
            _8 = _8 + -1;
            piVar1 = piVar1 + 1;
            _countdownBy1_199 = _countdownBy1_199 + 1;
            iVar4 = iVar4 + -400;
        } while (0 < _8);
        _countdownBy1_199 = 399;
        _79600 = 0x26f70;
        piVar1 = this->screenPointToTileNumber + iVar7 + 0x251;
        _countdown_by2_398 = 200;
        _8 = iVar7 + 0x259;
        iVar4 = 199;
        do {
            iVar6 = _8;
            _200 = 200;
            piVar3 = piVar1 + 200;
            piVar2 = piVar1;
            _8 = iVar4;
            iVar7 = _79600;
            do {
                *piVar2 = _stack[iVar7 + _8];
                piVar2 = piVar2 + 1;
                _8 = _8 + -1;
                iVar7 = iVar7 + -400;
                _200 = _200 + -1;
            } while (_200 != 0);
            iVar7 = iVar4 + 1;
            _200 = (iVar7 - iVar4) + 199;
            iVar4 = ((iVar7 - iVar4) + _countdownBy1_199) * 400;
            piVar1 = piVar1 + 0x191;
            _8 = iVar7;
            do {
                iVar4 = iVar4 + -400;
                *piVar3 = _stack[iVar4 + _8];
                piVar3 = piVar3 + 1;
                _8 = _8 + -1;
                _200 = _200 + -1;
            } while (-1 < _200);
            _countdownBy1_199 = _countdownBy1_199 + -1;
            _79600 = _79600 + -400;
            _countdown_by2_398 = _countdown_by2_398 + -1;
            _8 = iVar6 + 0x191;
            iVar4 = iVar7;
        } while (_countdown_by2_398 != 0);
        _8 = _countdownBy1_199 * 400;
        iVar4 = 200;
        piVar1 = this->screenPointToTileNumber + iVar6 + 0x189;
        do {
            *piVar1 = _stack[_8 + iVar7];
            piVar1 = piVar1 + 1;
            iVar7 = iVar7 + -1;
            _8 = _8 + -400;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        iVar7 = 199;
        _8 = 80000;
        piVar1 = this->screenPointToTileNumber + iVar6 + 0x251;
        iVar4 = iVar6 + 0x259;
        do {
            iVar5 = iVar4;
            iVar6 = 200;
            piVar3 = piVar1 + 200;
            piVar2 = piVar1;
            iVar4 = _8;
            do {
                *piVar2 = _stack[iVar7 + iVar4 + iVar6];
                iVar6 = iVar6 + -1;
                piVar2 = piVar2 + 1;
                iVar4 = iVar4 + 400;
            } while (0 < iVar6);
            _8 = _8 + -400;
            iVar6 = 200;
            piVar1 = piVar1 + 0x191;
            iVar4 = _8;
            do {
                *piVar3 = _stack[iVar7 + iVar4 + iVar6];
                piVar3 = piVar3 + 1;
                iVar4 = iVar4 + 400;
                iVar6 = iVar6 + -1;
            } while (-1 < iVar6);
            iVar7 = iVar7 + -1;
            iVar4 = iVar5 + 0x191;
        } while (0 < _8);
        _8 = 200;
        iVar4 = 0;
        piVar1 = this->screenPointToTileNumber + iVar5 + 0x189;
        do {
            *piVar1 = _stack[iVar4 + -1 + _8];
            _8 = _8 + -1;
            piVar1 = piVar1 + 1;
            iVar4 = iVar4 + 400;
        } while (0 < _8);
        _countdownBy1_199 = 0;
        _79600 = 0;
        piVar1 = this->screenPointToTileNumber + iVar5 + 0x251;
        _8 = 200;
        iVar4 = iVar5 + 0x259;
        do {
            iVar6 = iVar4;
            iVar5 = 200;
            piVar3 = piVar1 + 200;
            piVar2 = piVar1;
            iVar4 = _8;
            iVar7 = _79600;
            do {
                *piVar2 = _stack[iVar7 + iVar4];
                iVar5 = iVar5 + -1;
                piVar2 = piVar2 + 1;
                iVar4 = iVar4 + 1;
                iVar7 = iVar7 + 400;
            } while (0 < iVar5);
            iVar7 = _8 + -1;
            iVar4 = ((iVar7 - _8) + 1 + _countdownBy1_199) * 400;
            _200 = 200;
            piVar1 = piVar1 + 0x191;
            _8 = iVar7;
            do {
                *piVar3 = _stack[iVar4 + _8];
                piVar3 = piVar3 + 1;
                _8 = _8 + 1;
                iVar4 = iVar4 + 400;
                _200 = _200 + -1;
            } while (-1 < _200);
            _countdownBy1_199 = _countdownBy1_199 + 1;
            _79600 = _79600 + 400;
            _8 = iVar7;
            iVar4 = iVar6 + 0x191;
        } while (0 < iVar7);
        _8 = _countdownBy1_199 * 400;
        iVar4 = 200;
        piVar1 = this->screenPointToTileNumber + iVar6 + 0x189;
        do {
            *piVar1 = _stack[_8 + iVar7];
            iVar4 = iVar4 + -1;
            piVar1 = piVar1 + 1;
            iVar7 = iVar7 + 1;
            _8 = _8 + 400;
        } while (0 < iVar4);
        _8 = 0x21aec98;
        piVar1 = _stack;
        iVar4 = 400;
        do {
            iVar7 = 0;
            do {
                *(bool*)(_8 + iVar7) = 0 < *piVar1;
                iVar7 = iVar7 + 1;
                piVar1 = piVar1 + 1;
            } while (iVar7 < 400);
            _8 = _8 + 400;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        return;
    }

}
}
