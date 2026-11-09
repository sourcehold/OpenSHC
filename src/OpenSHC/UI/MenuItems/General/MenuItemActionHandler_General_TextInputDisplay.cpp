#include "../General.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Text::TextArrayIndexType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CC10
        void General::MenuItemActionHandler_General_TextInputDisplay(int param_1, ...)
        {
            switch (param_1) {
            case 0:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_FIVE__NUMERIC_DOT) {
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                }
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_SIX__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                }
                break;
            case 2:
                if (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_SEVEN__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
                }
                break;
            case 3:
                if ((DAT_GameCore::instance.isNameEntryActive != TRUE)
                    && (DAT_UserTextHandlerState::instance.textArrayIndex != Text::TAIT_ZERO)) {
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
                }
            }
        }

    }
}
}
