#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_00b986f0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"
#include "OpenSHC/Globals/FLOAT_00b986e8.hpp"
#include "OpenSHC/Globals/FLOAT_00b986ec.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044ABB0
        void SFXState::tweakVolume(int param_1, float param_2, int currentStreamID)
        {
            if (!MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SFX_2Unk);
                DAT_00b986f0::instance = 0;
                DAT_SpeechDefinedData::instance.field10_0x49d4b4 = -1;
                return;
            }
            if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == -1) {
                FLOAT_00b986ec::instance += param_2;
            } else {
                FLOAT_00b986ec::instance = 0.0f;
            }
            if (DAT_00b986f0::instance != 0 && DAT_SpeechDefinedData::instance.field10_0x49d4b4 == -1) {
                DAT_00b986f0::instance = 0;
            } else {
                if (DAT_00b986f0::instance == 1) {
                    FLOAT_00b986e8::instance += param_2 + param_2;
                    if (100.0 < FLOAT_00b986e8::instance) {
                        DAT_00b986f0::instance = 100;
                    }
                    if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == 7) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_2Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[5].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[5].field3_0x44]
                                      * FLOAT_00b986e8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == 8) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_2Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[6].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[6].field3_0x44]
                                      * FLOAT_00b986e8::instance)
                                / 100.0));
                    }
                    if (!(FLOAT_00b986e8::instance >= 100.0f)) {
                        return;
                    }
                    DAT_00b986f0::instance = 0;
                    return;
                }
                if (DAT_00b986f0::instance == 2) {
                    FLOAT_00b986e8::instance -= 2 * param_2;
                    if (FLOAT_00b986e8::instance < 1.0) {
                        FLOAT_00b986e8::instance = 1.0;
                    }
                    if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == 7) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_2Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[5].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[5].field3_0x44]
                                      * FLOAT_00b986e8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == 8) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_2Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[6].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[6].field3_0x44]
                                      * FLOAT_00b986e8::instance)
                                / 100.0));
                    }
                    if (FLOAT_00b986e8::instance <= 1.0) {
                        DAT_00b986f0::instance = 0;
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_SFX_2Unk);
                        DAT_SpeechDefinedData::instance.field10_0x49d4b4 = -1;
                    }
                }
                if (DAT_SpeechDefinedData::instance.field10_0x49d4b4 == -1
                    || MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SFX_2Unk)) {
                    if (0 < DAT_SpeechDefinedData::instance.field10_0x49d4b4
                        && DAT_SpeechDefinedData::instance.field10_0x49d4b4 != param_1) {
                        if (DAT_00b986f0::instance == 2) {
                            return;
                        }
                        FLOAT_00b986e8::instance = 100.0;
                        DAT_00b986f0::instance = 2;
                        return;
                    }
                } else {
                    DAT_SpeechDefinedData::instance.field10_0x49d4b4 = -1;
                }
            }
            if (param_1 <= 0 || DAT_SpeechDefinedData::instance.field10_0x49d4b4 == param_1
                || (FLOAT_00b986ec::instance < 900.0 && param_1 == 8)) {
                return;
            }
            switch (param_1) {
            case 7:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playAmbientSoundStream2Unk, this)(5);
                FLOAT_00b986e8::instance = 1.0;
                DAT_SpeechDefinedData::instance.field10_0x49d4b4 = 7;
                DAT_00b986f0::instance = 1;
                DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[2] = 1;
                break;
            case 8:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playAmbientSoundStream2Unk, this)(6);
                DAT_SpeechDefinedData::instance.field10_0x49d4b4 = 8;
                break;
            }
        }

    }
}
}
