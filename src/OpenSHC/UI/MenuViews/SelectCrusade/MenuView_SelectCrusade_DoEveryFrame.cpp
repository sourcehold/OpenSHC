#include "../SelectCrusade.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_HighlightedSkirmishType.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042BBF0
        void SelectCrusade::MenuView_SelectCrusade_DoEveryFrame()
        {
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
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 88,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, 624, 400);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 88,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, 624, 400);
            int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 130;
            int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // "Choose type of Crusader game"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 0),
                titleX, titleY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE, 0);
            if (DAT_HighlightedSkirmishType::instance == 1) {
                int const nameY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                int const nameX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Crusader 'First Edition' Trail"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 1),
                    nameX, nameY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE, 0);
                int const descriptionY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 440;
                int const descriptionX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Fight through 50 linked Crusader games"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 2),
                    descriptionX, descriptionY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                    FALSE, 0);
            }
            if (DAT_HighlightedSkirmishType::instance == 2) {
                int const nameY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                int const nameX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Custom Game"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 3),
                    nameX, nameY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE, 0);
                int const descriptionY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 440;
                int const descriptionX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Customize your own Crusader game."
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 4),
                    descriptionX, descriptionY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                    FALSE, 0);
            }
            if (DAT_HighlightedSkirmishType::instance == 3) {
                int const nameY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                int const nameX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Crusader 'Warchest' Trail"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 21),
                    nameX, nameY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE, 0);
                int const descriptionY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 440;
                int const descriptionX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Fight through 30 linked Crusader games"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 22),
                    descriptionX, descriptionY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                    FALSE, 0);
            }
            if (DAT_HighlightedSkirmishType::instance == 4) {
                int const nameY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 400;
                int const nameX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Crusader Extreme Trail"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 23),
                    nameX, nameY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE, 0);
                int const descriptionY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 440;
                int const descriptionX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Fight through 20 linked Extreme games"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 24),
                    descriptionX, descriptionY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                    FALSE, 0);
            }
        }

    }
}
}
