#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8990
        void EditScenario::MenuItemActionHandler_EditScenario_DateYearBox(int box, ...)
        {
            switch (box) {
            case 0:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_15) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_15);
                }
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_10) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_10);
                }
                break;
            case 2:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_11) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_11);
                }
                break;
            case 3:
            case 4:
            case 7:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_12) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_12);
                }
                break;
            case 5:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_13) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_13);
                }
                break;
            case 6:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_UNKNOWN_14) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                        Text::TAIT_UNKNOWN_14);
                }
            }
        }

    }
}
}
