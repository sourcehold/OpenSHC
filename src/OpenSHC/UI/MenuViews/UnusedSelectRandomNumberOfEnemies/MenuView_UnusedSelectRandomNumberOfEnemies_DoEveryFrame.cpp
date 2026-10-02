#include "../UnusedSelectRandomNumberOfEnemies.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042B960
        void UnusedSelectRandomNumberOfEnemies::MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame()
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            TextAlignment alignment;
            BGR24 color;
            int iVar4;
            uint color_00;
            BOOLEnum keepOffsetX;
            int iVar5;
            int blendStrength;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 100,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, 600, 400);
            iVar5 = 0;
            keepOffsetX = FALSE;
            iVar4 = 0x11;
            color = 0xccfaff;
            alignment = OpenSHC::Text::TTA_CENTER;
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 200;
            iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            /*
              added by script: "How many opponents can you handle!"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 1), iVar3, iVar1, alignment, color, iVar4, keepOffsetX, iVar5);
            blendStrength = 0;
            iVar5 = 0x12;
            color_00 = 0xccfaff;
            iVar4 = 400;
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
            iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 200;
            /*
              added by script: "This will create some random opponents for you. You can   still change opponent types
              afterwards."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 2), iVar3, iVar1, iVar4, color_00, iVar5, blendStrength);
            return;
        }

    }
}
}
