#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00426D30
        void Unused::MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect(int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            uint color_00;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if ((DAT_GameCore::instance.unlockAllHistoricalCampaigns == 0)
                    && (-DAT_GameCore::instance.furthestMission != param_1
                        && (int)DAT_GameCore::instance.furthestMission <= -param_1)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                        DAT_PencilRenderCore::ptr)(FALSE, param_1, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    DAT_ButtonUnknownZero::instance = 1;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                    (uint)(-DAT_GameCore::instance.missionNumber1to20 == param_1), param_1, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (-DAT_GameCore::instance.missionNumber1to20 == param_1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(-0x20 - param_1, (int)((int)(DAT_ButtonX::instance + 8)),
                        (int)((int)(DAT_ButtonY::instance + 5)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, FALSE, 0);
                    blendStrength = 0;
                    keepOffsetX = FALSE;
                    fontSize = 0x13;
                    color = 0xccfaff;
                    alignment = OpenSHC::Text::TTA_LEFT;
                    yParam = DAT_ButtonY::instance + 5;
                    xParam = DAT_ButtonX::instance + 0x1e;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, -0xb - param_1),
                        xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                    DAT_ButtonUnknownZero::instance = 0;
                }
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(-0x20 - param_1, (int)((int)(DAT_ButtonX::instance + 8)),
                        (int)((int)(DAT_ButtonY::instance + 5)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, FALSE, 0);
                    color_00 = 0xc2f0eb;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(-0x20 - param_1, (int)((int)(DAT_ButtonX::instance + 8)),
                        (int)((int)(DAT_ButtonY::instance + 5)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, FALSE, 0);
                    color_00 = 0xccfaff;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, -0xb - param_1, (int)((int)(DAT_ButtonX::instance + 0x1e)),
                    (int)((int)(DAT_ButtonY::instance + 5)), OpenSHC::Text::TTA_LEFT, color_00, 0x13, FALSE);
                DAT_ButtonUnknownZero::instance = 0;
            }
        }

    }
}
}
