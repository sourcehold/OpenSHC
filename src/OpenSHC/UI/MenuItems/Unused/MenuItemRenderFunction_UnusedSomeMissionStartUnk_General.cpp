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

        using DE::SHCDE::eTextSections;
        using Text::TextAlignment;
        using UI::Enums::MenuModalType;
        using UI::Enums::RoundedBoxEdgeRoundingLevel;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426FB0
        void Unused::MenuItemRenderFunction_UnusedSomeMissionStartUnk_General(int param_1, ...)
        {
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), UI::Enums::RBERL_SLIGHT);
                    backgroundColor = 0x3e66;
                    foregroundColor = 0xa2ff;
                } else {
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        UI::Enums::RBERL_SLIGHT);
                    backgroundColor = 0;
                    foregroundColor = 0xffffff;
                }
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                alignment = Text::TTA_CENTER;
                int xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 8;
                textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAINOPTIONS, param_1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    textAddress, xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX,
                    blendStrength);
            }
        }

    }
}
}
