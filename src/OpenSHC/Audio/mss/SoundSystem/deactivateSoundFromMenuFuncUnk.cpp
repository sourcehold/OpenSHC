#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include <iostream>

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479F30
        void SoundSystem::deactivateSoundFromMenuFuncUnk()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            for (int i = 0; i < 5; ++i) {
                unsigned int const copy = *((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[i]) & 0x7fffffff;
                this->streamFlagsUnkAndLoopCount_0x34[i] = *((UnkSoundFlagsAndLoopCount*)&copy);
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(i);
            }

            int* piVar1 = this->sampleSoundIndex_0x20c + 1;
            unsigned int iVar3 = 32;
            do {
                AIL_end_sample((HSAMPLE)piVar1[-0x20]);
                *piVar1 = 0;
                piVar1 = piVar1 + 1;
                iVar3 = iVar3 + -1;
            } while (iVar3 != 1);

            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
            this->soundActiveUnk_0x0 = 0;
        }

    }
}
}
