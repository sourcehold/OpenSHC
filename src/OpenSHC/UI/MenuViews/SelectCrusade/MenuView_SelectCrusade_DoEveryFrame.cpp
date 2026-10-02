#include "../SelectCrusade.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_HighlightedSkirmishType.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042BBF0
        void SelectCrusade::MenuView_SelectCrusade_DoEveryFrame()
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            TextAlignment TVar4;
            BGR24 BVar5;
            int iVar6;
            BOOLEnum BVar7;
            int iVar8;
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
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x58,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, 0x270, 400);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x58,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, 0x270, 400);
            iVar8 = 0;
            BVar7 = FALSE;
            iVar6 = 0x10;
            BVar5 = 0xccfaff;
            TVar4 = OpenSHC::Text::TTA_CENTER;
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x82;
            iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            /*
              added by script: "Choose type of Crusader game"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 0), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            if (DAT_HighlightedSkirmishType::instance == 1) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x10;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Crusader 'First Edition' Trail"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 1), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1b8;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Fight through 50 linked Crusader games"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 2), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
            if (DAT_HighlightedSkirmishType::instance == 2) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x10;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Custom Game"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 3), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1b8;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Customize your own Crusader game."
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 4), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
            if (DAT_HighlightedSkirmishType::instance == 3) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x10;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Crusader 'Warchest' Trail"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x15), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1b8;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Fight through 30 linked Crusader games"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x16), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
            if (DAT_HighlightedSkirmishType::instance == 4) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x10;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Crusader Extreme Trail"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x17), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1b8;
                iVar3 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Fight through 20 linked Extreme games"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x18), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
            return;
        }

    }
}
}
