#include "../SoundOptions.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492890
        void SoundOptions::MenuItemActionHandler_SoundOptions_VolumeSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 100;
                break;
            case 2:
            case 3:
                if (!param_1) {
                    if (DAT_MenuTextInputState::instance.pendingStreamVolume0 != *currentValue) {
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                            0, (int)(*currentValue));
                    }
                    DAT_MenuTextInputState::instance.pendingStreamVolume0 = *currentValue;
                }
                if (param_1 != 1) {
                    if (param_1 != 2) {}
                    if (DAT_MenuTextInputState::instance.pendingStreamVolume3 != *currentValue) {
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                            3, (int)(*currentValue));
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                            4, (int)(*currentValue));
                    }
                    DAT_MenuTextInputState::instance.pendingStreamVolume3 = *currentValue;
                }
                if (DAT_MenuTextInputState::instance.pendingStreamVolume1 != *currentValue) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                        1, (int)(*currentValue));
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                        2, (int)(*currentValue));
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                        -1, (int)(*currentValue));
                }
                DAT_MenuTextInputState::instance.pendingStreamVolume1 = *currentValue;
                return;
            case 4:
                break;
            default:
                return;
            }
            if (!param_1) {
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume0;
            }
            if (param_1 == 1) {
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume1;
            }
            if (param_1 == 2) {
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume3;
            }
        }

    }
}
}
