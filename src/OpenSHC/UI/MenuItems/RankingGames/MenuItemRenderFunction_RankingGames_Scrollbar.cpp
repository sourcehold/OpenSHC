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

        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D9C10
        void RankingGames::MenuItemRenderFunction_RankingGames_Scrollbar(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged)
        {
            DAT_ButtonUnknownZero::instance = 0;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)), (int)((int)(DAT_ButtonX::instance + 0x13)),
                (int)((int)(DAT_ButtonH::instance + -1 + DAT_ButtonY::instance)),
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)), (int)((int)(DAT_ButtonH::instance)),
                thumbYPos, isDragged, thumbHeight, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance - 1, (int)((int)(DAT_ButtonY::instance + -1)),
                (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
        }

    }
}
}
