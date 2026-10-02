#include "../../../Rendering.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/Bink/UnsortedBinkFlag.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::Bink::UnsortedBinkFlag;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00408ED0
        void BinkControlClass::playBINK(
            int binkObjIndex, char* binkFileName, DWORD param_3, DWORD param_4, int xPos, int yPos, DWORD param_7)
        {
            char* _videoFileName;
            HBINK _binkObjPtr;
            int _fileSoundVolumne;
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_BINKS, (char const*)((int)(binkFileName)));
            if (this->binkObjPtrArray[binkObjIndex] != (HBINK)0x0) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                    binkObjIndex);
            }
            if ((DAT_SoundSystemState::instance.waveOutOpenUnk_0x8 == FALSE)
                || (DAT_SoundSystemState::instance.soundActiveUnk_0x0 == 0)) {
                _videoFileName = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                /*
                  That bink flag feels wrong. Maybe the sources are to old?   Could also be right. Would need
                  validation. -TheRedDaemon
                 */
                _binkObjPtr = BinkOpen(_videoFileName, OpenSHC::Rendering::Bink::UBF_BINKNOSKIP);
                this->binkObjPtrArray[binkObjIndex] = _binkObjPtr;
                BinkSetVolume(_binkObjPtr, 0, 0);
            } else {
                _videoFileName = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                /*
                  That flag bink feels wrong. -TheRedDaemon
                 */
                _binkObjPtr = BinkOpen(_videoFileName, OpenSHC::Rendering::Bink::UBF_BINKNOSKIP);
                this->binkObjPtrArray[binkObjIndex] = _binkObjPtr;
            }
            if ((DAT_SoundSystemState::instance.waveOutOpenUnk_0x8 != FALSE)
                && (DAT_SoundSystemState::instance.soundActiveUnk_0x0 != 0)) {
                _fileSoundVolumne = MACRO_CALL_MEMBER(
                    OpenSHC::Audio::SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(binkFileName);
                BinkSetVolume(this->binkObjPtrArray[binkObjIndex], 0, (long)((int)(_fileSoundVolumne * 0xfa)));
            }
            this->xPos[binkObjIndex] = xPos;
            this->yPos[binkObjIndex] = yPos;
            this->frameReadyToDisplay[binkObjIndex] = FALSE;
            this->unknown01_zero[binkObjIndex] = 0;
            this->unknown02_zero[binkObjIndex] = 0;
            this->soundStreamIndex[binkObjIndex] = OpenSHC::Audio::MSS::enums::SND_STR_MUSIC;
            this->startTime[binkObjIndex] = 0;
            this->unknownParam04[binkObjIndex] = param_4;
            this->unknownParam03[binkObjIndex] = param_3;
            this->unknownParam07[binkObjIndex] = param_7;
        }

    }
}
}
