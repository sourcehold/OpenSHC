#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_00df4290.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B1EB0
    void DisplayElements::RenderTimeUntilVictoryDisplayElement(int posX, int posY, DWORD elementState)
    {
        int iVar1;
        char* pcVar2;
        int left;
        int iVar3;
        int xParam;
        int yParam;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        int iVar4;
        if (DAT_GameCore::instance.section1095 == 2) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY, 0);
        }
        iVar4 = 0x12;
        /*
          added by script: "Time Until Victory"
         */
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x19),
            iVar4);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
            posX = posX + -0x70;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            posX = posX + -0xf0;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
            posX = posX + -400;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
            posX = posX + -0xf0;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
            posX = posX + -0x140;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
            posX = posX + -0x230;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
            posX = posX + -0x230;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
            posX = posX + -0x370;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
            posX = posX + -0x370;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
            posX = posX + -0x11b;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
            posX = posX + -0x1b8;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
            posX = posX + -400;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
            posX = posX + -0x70;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
            posX = posX + -0x118;
        }
        DAT_00df4290::instance = iVar4 + 0x10;
        iVar3 = iVar4 / 2;
        iVar1 = posX + 10 + iVar3;
        left = iVar1 - iVar3;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
            DAT_PencilRenderCore::ptr)(left + -7, posY + -5, iVar3 + 5 + iVar1, posY + 0x1e, 0x10);
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x12;
        backgroundColor = 0;
        foregroundColor = 0xc2f0eb;
        alignment = OpenSHC::Text::TTA_CENTER;
        xParam = iVar1;
        yParam = posY;
        /*
          added by script: "Time Until Victory"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x19),
            xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left + -1, posY + 0x12, iVar3 + 1 + iVar1, posY + 0x18, (ushort)((int)(COL_BLACK::instance.shortValue)));
        if (DAT_MapPropertiesState::instance.SEC_Section1080 != DAT_MapPropertiesState::instance.SEC_Section1090) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, posY + 0x13,
                (((DAT_MapPropertiesState::instance.SEC_Section1090 - DAT_MapPropertiesState::instance.SEC_Section1080)
                     * iVar4)
                        / DAT_MapPropertiesState::instance.SEC_Section1090
                    - iVar3)
                    + iVar1,
                posY + 0x17, (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        return;
    }

}
}
