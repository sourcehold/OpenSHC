#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00426FB0
        void Unused::MenuItemRenderFunction_UnusedSomeMissionStartUnk_General(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)), OpenSHC::UI::Enums::RBERL_SLIGHT);
                    backgroundColor = 0x3e66;
                    foregroundColor = 0xa2ff;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                        (ushort)((int)(COL_BLUE::instance.shortValue)), OpenSHC::UI::Enums::RBERL_SLIGHT);
                    backgroundColor = 0;
                    foregroundColor = 0xffffff;
                }
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                alignment = OpenSHC::Text::TTA_CENTER;
                xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 8;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, param_1), xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
