#include "../General.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::TextArrayIndexType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047CC10
        void General::MenuItemActionHandler_General_TextInputDisplay(int param_1, ...)
        {
            switch (param_1) {
            case 0:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                }
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                }
                break;
            case 2:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
                }
                break;
            case 3:
                if ((DAT_GameCore::instance.unknownFlag_0x118 != TRUE)
                    && (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_ZERO)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
                }
            }
        }

    }
}
}
