#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492A90
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_Buttons(int button, ...)
        {
            // online, "Load" (2) reads "Launch" (38)
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && button == 2) {
                button = 38;
            }
            // greyed out while no map is selected, and online for a map the handler refuses
            if ((button == 2 || button == 38)
                && ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices2
                                [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                        [DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                                            + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset]
                                    - 1]
                            == 0)
                    || DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex == -1)) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // y then x as locals, so the tails merge (in the call: quick_diff 0.9310 -> 0.6762; x first: 0.9195)
                int const textY = DAT_ButtonY::instance + 7;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 18, FALSE, 0);
                return;
            }
            // if/else keeps the arrows last, as the binary has them (early returns: quick_diff 0.9310 -> 0.8046)
            if (button >= 0) {
                // one call per colour, which MSVC merges (one call with a colour local: quick_diff 0.9310 -> 0.6458)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
            } else if (button == -1) {
                // -1 is the list's up arrow, the other negative buttons its down arrow
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, 0);
            }
        }

    }
}
}
