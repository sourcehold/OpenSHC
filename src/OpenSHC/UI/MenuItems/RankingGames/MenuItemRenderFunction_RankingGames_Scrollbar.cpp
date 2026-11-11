#include "../RankingGames.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9C10
        void RankingGames::MenuItemRenderFunction_RankingGames_Scrollbar(
            int unused, int thumbYPos, int sliderValue, int thumbHeight, BOOLEnum isDragged)
        {
            DAT_ButtonUnknownZero::instance = FALSE;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonX::instance + 19,
                DAT_ButtonY::instance + DAT_ButtonH::instance - 1, COL_BLACK::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonH::instance, thumbYPos, isDragged, thumbHeight,
                0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance - 1, DAT_ButtonY::instance - 1, DAT_ButtonX::instance + 20,
                DAT_ButtonY::instance + DAT_ButtonH::instance, COL_VERY_SOFT_YELLOW::instance.shortValue);
        }

    }
}
}
