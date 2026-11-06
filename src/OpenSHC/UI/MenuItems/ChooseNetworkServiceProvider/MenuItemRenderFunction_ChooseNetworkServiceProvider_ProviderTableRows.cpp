#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CB30
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows(
            int row, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(row == DAT_GameSynchronyState::instance.selectedProviderIndex, row, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // rows past the last provider only get their background
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + row
                >= DAT_GameSynchronyState::instance.scrollBarItemCount) {
                return;
            }
            // set in both branches: a preset colour overridden in one costs two instructions
            uint color;
            if (row == DAT_GameSynchronyState::instance.selectedProviderIndex
                || DAT_ButtonCurrentlyInteracting::instance) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
            }
            char providerName[1000];
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                DAT_WideCharMultiByteState::ptr)(providerName,
                DAT_GameSynchronyState::instance
                    .providerNames[DAT_GameSynchronyState::instance.scrollBarItemOffset + row]);
            DAT_TextManagerObject::instance.field_0x30 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                providerName, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 4, 384, color, 18, 0);
        }

    }
}
}
