#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047CB30
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows(
            int param_1, ...)
        {
            uint color;
            CHAR local_3ec[1000];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3ec;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_GameSynchronyState::instance.selectedProviderIndex), param_1, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1
                < DAT_GameSynchronyState::instance.scrollBarItemCount) {
                if ((param_1 == DAT_GameSynchronyState::instance.selectedProviderIndex)
                    || (color = 0xc2f0eb, DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                    color = 0xccfaff;
                }
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                    DAT_WideCharMultiByteState::ptr)(local_3ec,
                    (LPCWSTR)((int)(DAT_GameSynchronyState::instance
                            .providerNames[DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1])));
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    local_3ec, (int)((int)(DAT_ButtonX::instance + 8)), (int)((int)(DAT_ButtonY::instance + 4)), 0x180,
                    color, 0x12, 0);
            };
        }

    }
}
}
