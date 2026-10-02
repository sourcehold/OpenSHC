#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmID;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00462FF0
        void AlphaAndButtonSurface::prepareButtonAndAlphaSurface()
        {
            dword dVar1;
            int _currentIconIndex;
            int _byteNumber;
            int _numOfAdditionalIconStates;
            dword _maxImageHeight;
            GmIDInt _gmID;
            int _pictureInGm;
            _byteNumber = 0;
            this->dim1_intMinimal350_1 = 0;
            _maxImageHeight = 0;
            do {
                _numOfAdditionalIconStates
                    = *(int*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].numOfAdditionalIconStates_0x8
                          + _byteNumber)
                    + 1;
                _currentIconIndex = 0;
                if (0 < _numOfAdditionalIconStates) {
                    _gmID = *(
                        GmIDInt*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].gmId_0x0 + _byteNumber);
                    do {
                        if ((_gmID != ((GmID)0))
                            && (_pictureInGm
                                = *(int*)((int)&DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0].pictureInGm_0x4
                                    + _byteNumber),
                                _pictureInGm != 0)) {
                            dVar1 = (dword)DAT_GMImageHeaders::instance
                                        .imh[_currentIconIndex + GMTotalPicturesProcessed::instance[_gmID]
                                            + _pictureInGm + -1]
                                        .width;
                            if ((int)this->dim1_intMinimal350_1 < (int)dVar1) {
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
            if ((int)this->dim1_intMinimal350_1 < 350) {
                this->dim1_intMinimal350_1 = 350;
            }
            if ((int)_maxImageHeight < 350) {
                _maxImageHeight = 350;
            }
            this->dim2_intMinimal350_2 = _maxImageHeight;
            this->surfacePtr
                = (ushort*)(MACRO_CALL(OpenSHC::OS_Func::_malloc)(_maxImageHeight * this->dim1_intMinimal350_1 * 2));
        }

    }
}
}
