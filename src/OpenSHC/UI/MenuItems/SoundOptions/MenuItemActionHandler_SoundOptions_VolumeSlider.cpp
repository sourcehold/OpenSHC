#include "../SoundOptions.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SoundOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00492890
            void MenuItemActionHandler_SoundOptions_VolumeSlider(
                int slider, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
            {
                switch (scrollbarEvent) {
                case 1:
                    // the slider's range, then its stored volume
                    *minValue = 0;
                    *maxValue = 100;
                    switch (slider) {
                    case 0:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume0;
                        break;
                    case 1:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume1;
                        break;
                    case 2:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume3;
                        break;
                    }
                    return;
                case 2:
                case 3:
                    // A new volume goes to the slider's sound channels when it differs from the stored one.
                    switch (slider) {
                    case 0:
                        if (DAT_MenuTextInputState::instance.pendingStreamVolume0 != *currentValue) {
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                0, *currentValue);
                        }
                        DAT_MenuTextInputState::instance.pendingStreamVolume0 = *currentValue;
                        return;
                    case 1:
                        if (DAT_MenuTextInputState::instance.pendingStreamVolume1 != *currentValue) {
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                1, *currentValue);
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                2, *currentValue);
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                -1, *currentValue);
                        }
                        DAT_MenuTextInputState::instance.pendingStreamVolume1 = *currentValue;
                        return;
                    case 2:
                        if (DAT_MenuTextInputState::instance.pendingStreamVolume3 != *currentValue) {
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                3, *currentValue);
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setVolumeUnk, DAT_SoundSystemState::ptr)(
                                4, *currentValue);
                        }
                        DAT_MenuTextInputState::instance.pendingStreamVolume3 = *currentValue;
                        return;
                    }
                    return;
                case 4:
                    // read back again here (one read-back after the switch: quick_diff 0.9222 -> 0.7797)
                    switch (slider) {
                    case 0:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume0;
                        break;
                    case 1:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume1;
                        break;
                    case 2:
                        *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume3;
                        break;
                    }
                }
            }

        }
    }
}
}
