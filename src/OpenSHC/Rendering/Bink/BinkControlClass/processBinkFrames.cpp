#include "../../../Rendering.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using Audio::MSS::enums::SHC_SoundStream;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00409200
        void BinkControlClass::processBinkFrames()
        {
            BOOLEnum _streamPlaying;
            BinkControlClass* _ptrInBinkControlStruct;
            int _binkObjIndex;
            HBINK _binkObjPtr;
            _ptrInBinkControlStruct = (BinkControlClass*)this->soundStreamIndex;
            _binkObjIndex = 0;
            do {
                if (_ptrInBinkControlStruct->soundStreamIndex[0] != Audio::MSS::enums::SND_STR_MUSIC) {
                    _streamPlaying = MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        (Audio::MSS::enums::SHC_SoundStream)(_ptrInBinkControlStruct->soundStreamIndex[0]));
                    if (_streamPlaying) {
                        DWORD _currentSysTime = timeGetTime();
                        if (_currentSysTime - _ptrInBinkControlStruct->startTime[0] < 20000)
                            goto LAB_0040923b;
                    }
                    _ptrInBinkControlStruct->soundStreamIndex[0] = Audio::MSS::enums::SND_STR_MUSIC;
                }
            LAB_0040923b:
                _ptrInBinkControlStruct->unknown01_zero[0] = 0;
                _ptrInBinkControlStruct->unknown02_zero[0] = 0;
                if (_ptrInBinkControlStruct->binkObjPtrArray[0] != (HBINK)0x0) {
                    long _frameNotDone = BinkWait(_ptrInBinkControlStruct->binkObjPtrArray[0]);
                    if (!_frameNotDone) {
                        BinkDoFrame(_ptrInBinkControlStruct->binkObjPtrArray[0]);
                        _binkObjPtr = _ptrInBinkControlStruct->binkObjPtrArray[0];
                        if ((_binkObjPtr->FrameNum == _binkObjPtr->Frames)
                            && (_ptrInBinkControlStruct->unknownParam03[0] == 0)) {
                            if (_ptrInBinkControlStruct->soundStreamIndex[0] == Audio::MSS::enums::SND_STR_MUSIC) {
                                if (_ptrInBinkControlStruct->unknownParam07[0] != 2) {
                                    _ptrInBinkControlStruct->unknown01_zero[0] = 1;
                                    MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                                        _binkObjIndex);
                                    goto LAB_0040929d;
                                }
                            } else if (_ptrInBinkControlStruct->unknownParam07[0] != 2)
                                goto LAB_0040929a;
                            _ptrInBinkControlStruct->unknown02_zero[0] = 1;
                        } else {
                            BinkNextFrame(_binkObjPtr);
                        }
                    LAB_0040929a:
                        _ptrInBinkControlStruct->frameReadyToDisplay[0] = TRUE;
                    }
                }
            LAB_0040929d:
                _binkObjIndex = _binkObjIndex + 1;
                _ptrInBinkControlStruct = (BinkControlClass*)(_ptrInBinkControlStruct->soundStreamIndex + 1);
                if (1 < _binkObjIndex) {}
            } while (true);
        }

    }
}
}
