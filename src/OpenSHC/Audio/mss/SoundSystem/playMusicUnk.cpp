#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A790
        void SoundSystem::playMusicUnk()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            if (!this->digSndDriver_0x4) {
                return;
            }

            int const _buffNum = AIL_sample_buffer_ready(this->musicSampleUnk_0x170);
            if (_buffNum == -1) {
                return;
            }

            int readFileBytes = MACRO_CALL(OS_Func::_ucrt_read)(this->musicSampleFileHandleUnk_0x174,
                this->sampleBufferPtrUnk_0x17c[_buffNum], this->sampleBufferSizeUnk_0x184);

            // if the buffer is not completely filled, it seems to go through potential options to fill it
            if (this->sampleBufferSizeUnk_0x184 != readFileBytes) {
                MACRO_CALL_MEMBER(SoundSystem_Func::playRandomBackgroundMusicUnk, this)();

                if (DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_PICTURE
                    || DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_INTRO
                    || DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION) {
                    if (this->sec_Section1055_0x3274 == 50) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[72].musicFile);
                    } else if (this->sec_Section1055_0x3274 == 72) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[50].musicFile);
                    }
                }

                if (DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_CREDITS) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playDarMehqOrGlory, this)();
                }

                if (this->sec_Section1055_0x3274 >= 73) {
                    if (this->sec_Section1055_0x3274 >= 97) {
                        if (0 < DAT_SoundEffectsHelperData1::ptr->field13_0x50) {
                            int _selection;
                            for (int i = 0; i < 16; ++i) {
                                /* this call is in a different thread! */
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                _selection = SEC_RNG::ptr->currentNumber1 % 19;
                                if (_selection
                                    != DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_02)
                                    break;
                            }
                            DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_02 = _selection;
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[_selection + 97].musicFile);
                            --DAT_SoundEffectsHelperData1::ptr->field13_0x50;
                            if (DAT_SoundEffectsHelperData1::ptr->field13_0x50 > 3) {
                                DAT_SoundEffectsHelperData1::ptr->field13_0x50 = 0;
                            }
                        }
                    } else {
                        if (0 < DAT_SoundEffectsHelperData1::ptr->DAT_NegativeCountdownMin1ToMin4Becomes0) {
                            int _selection;
                            for (int i = 0; i < 16; ++i) {
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                _selection = SEC_RNG::ptr->currentNumber1 % 24;
                                if (_selection
                                    != DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_01)
                                    break;
                            }
                            DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_01 = _selection;
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[_selection + 73].musicFile);
                            DAT_SoundEffectsHelperData1::ptr->DAT_NegativeCountdownMin1ToMin4Becomes0 += -1;
                            if (DAT_SoundEffectsHelperData1::ptr->DAT_NegativeCountdownMin1ToMin4Becomes0 > 3) {
                                DAT_SoundEffectsHelperData1::ptr->DAT_NegativeCountdownMin1ToMin4Becomes0 = 0;
                            }
                        }
                    }
                }

                if (this->musicFileHandle_0x178 != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->musicSampleFileHandleUnk_0x174);
                    this->musicSampleFileHandleUnk_0x174 = this->musicFileHandle_0x178;
                    this->musicFileHandle_0x178 = -1;
                    readFileBytes += MACRO_CALL(OS_Func::_ucrt_read)(this->musicSampleFileHandleUnk_0x174,
                        (void*)((int)this->sampleBufferPtrUnk_0x17c[_buffNum] + readFileBytes),
                        this->sampleBufferSizeUnk_0x184 - readFileBytes);
                } else if (this->streamFlagsUnkAndLoopCount_0x34[0].loopCount == 1) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                    return;
                } else if (this->streamFlagsUnkAndLoopCount_0x34[0].loopCount == 0) {
                    MACRO_CALL(OS_Func::_ucrt_lseek)(this->musicSampleFileHandleUnk_0x174, 0, FILE_BEGIN);
                    readFileBytes += MACRO_CALL(OS_Func::_ucrt_read)(this->musicSampleFileHandleUnk_0x174,
                        (void*)((int)this->sampleBufferPtrUnk_0x17c[_buffNum] + readFileBytes),
                        this->sampleBufferSizeUnk_0x184 - readFileBytes);
                }
            }
            AIL_load_sample_buffer(
                this->musicSampleUnk_0x170, _buffNum, this->sampleBufferPtrUnk_0x17c[_buffNum], readFileBytes);
        }

    }
}
}
