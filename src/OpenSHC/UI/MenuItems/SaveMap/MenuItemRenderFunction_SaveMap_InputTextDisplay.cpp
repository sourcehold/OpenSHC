#include "../SaveMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Text::TextAlignment;
        using UI::Enums::RoundedBoxEdgeRoundingLevel;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004932E0
        void SaveMap::MenuItemRenderFunction_SaveMap_InputTextDisplay(int param_1, ...)
        {
            int iVar1;
            char* textAddress;
            int xParam;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), UI::Enums::RBERL_SLIGHT);
            iVar1 = MACRO_CALL_MEMBER(
                Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance + 6 + iVar1, (int)(DAT_ButtonY::instance + 2), DAT_ButtonX::instance + 7 + iVar1,
                (int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance),
                (ushort)(COL_DARK_LIME::instance.shortValue));
            iVar1 = DAT_ButtonY::instance + 7;
            xParam = DAT_ButtonX::instance + 8;
            textAddress
                = MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                textAddress, xParam, iVar1, Text::TTA_LEFT, 0xffffff, 0, 0x12, FALSE, 0);
        }

    }
}
}
