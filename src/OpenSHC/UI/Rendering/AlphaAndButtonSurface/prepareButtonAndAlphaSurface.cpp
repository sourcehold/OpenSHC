#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00462FF0
        void AlphaAndButtonSurface::prepareButtonAndAlphaSurface()
        {
            dword dVar1;
            int _numOfAdditionalIconStates;
            GmIDInt _gmID;
            int _pictureInGm;
            int _byteNumber = 0;
            this->dim1_intMinimal350_1 = 0;
            dword _maxImageHeight = 0;
            do {
                _numOfAdditionalIconStates
                    = *(int*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].numOfAdditionalIconStates_0x8
                          + _byteNumber)
                    + 1;
                int _currentIconIndex = 0;
                if (0 < _numOfAdditionalIconStates) {
                    _gmID = *(
                        GmIDInt*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].gmId_0x0 + _byteNumber);
                    do {
                        if (_gmID != (GmID)0
                            && (_pictureInGm
                                = *(int*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].pictureInGm_0x4
                                    + _byteNumber),
                                _pictureInGm != 0)) {
                            dVar1 = (dword)DAT_GMImageHeaders::instance
                                        .imh[_currentIconIndex + GMTotalPicturesProcessed::instance[_gmID]
                                            + _pictureInGm + -1]
                                        .width;
                            if (this->dim1_intMinimal350_1 < (int)dVar1) {
                                this->dim1_intMinimal350_1 = dVar1;
                            }
                            dVar1 = (dword)DAT_GMImageHeaders::instance
                                        .imh[_currentIconIndex + GMTotalPicturesProcessed::instance[_gmID]
                                            + _pictureInGm + -1]
                                        .height;
                            if ((int)_maxImageHeight < (int)dVar1) {
                                _maxImageHeight = dVar1;
                            }
                        }
                        _currentIconIndex = _currentIconIndex + 1;
                    } while (_currentIconIndex < _numOfAdditionalIconStates);
                }
                _byteNumber = _byteNumber + 28;
            } while (_byteNumber < 18200);
            if (this->dim1_intMinimal350_1 < 350) {
                this->dim1_intMinimal350_1 = 350;
            }
            if ((int)_maxImageHeight < 350) {
                _maxImageHeight = 350;
            }
            this->dim2_intMinimal350_2 = _maxImageHeight;
            this->surfacePtr
                = (ushort*)(MACRO_CALL(OS_Func::_malloc)(_maxImageHeight * this->dim1_intMinimal350_1 * 2));
        }

    }
}
}
