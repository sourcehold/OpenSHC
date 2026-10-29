#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00433260
    void Rendering::RenderScribeFrame()
    {
        BOOLEnum BVar1;
        int yParam;
        char* textAddress;
        int xParam;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int fontSize;
        int blendStrength;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameCore::instance.scribeAnimationFrame <= 0) {
            DAT_GameCore::instance.scribeAnimationFrame = 1;
        } else if (44 < DAT_GameCore::instance.scribeAnimationFrame) {
            DAT_GameCore::instance.scribeAnimationFrame = 44;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_SCRIBE, DAT_GameCore::instance.scribeAnimationFrame,
            DAT_MenuHandlerState::instance.x + 0x2c0, DAT_MenuHandlerState::instance.y + 399);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        if ((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                 && (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM))
                && (DAT_GameCore::instance.isTimeHalted == FALSE))
            && (BVar1 = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO),
                BVar1 == FALSE)) {
            blendStrength = 0;
            BVar1 = FALSE;
            fontSize = 0x12;
            backgroundColor = 0;
            foregroundColor = 0xb8eefb;
            alignment = OpenSHC::Text::TTA_LEFT;
            yParam = DAT_WindowAndDirectDraw::instance.resolutionY + -0x14;
            xParam = DAT_MenuHandlerState::instance.x + 0x124;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameState::instance.mapAndTime.month),
                xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, BVar1, blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.mapAndTime.year, DAT_MenuHandlerState::instance.x + 0x128,
                DAT_WindowAndDirectDraw::instance.resolutionY + -0x14, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE,
                0);
        }
    }

}
}
