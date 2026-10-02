#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::TextArrayIndexType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B8990
        void EditScenario::MenuItemActionHandler_EditScenario_DateYearBox(int param_1, ...)
        {
            switch (param_1) {
            case 0:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    != (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xf);
                }
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    != (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_TWO__FILTER_A)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(10);
                }
                break;
            case 2:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    != (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_THREE__FILTER_A)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xb);
                }
                break;
            case 3:
            case 4:
            case 7:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != (OpenSHC::Text::TextArrayIndexTypeInt)0xc) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xc);
                }
                break;
            case 5:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    != (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xd);
                }
                break;
            case 6:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    != (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xe);
                }
            }
        }

    }
}
}
