#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492A90
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_Buttons(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                if (param_1 != 2)
                    goto LAB_00492ab8;
            LAB_00492abd:
                if ((((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                         && (DAT_GameSynchronyState::instance.currentGameMode
                             != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                        && (DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                        [DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                                            + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex
                                            + -1]
                                    + 499]
                            == 0))
                    || (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex == -1)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    color = 0x7f7f7f;
                    goto LAB_00492b46;
                }
            } else {
                if (param_1 == 2) {
                    param_1 = 0x26;
                    goto LAB_00492abd;
                }
            LAB_00492ab8:
                if (param_1 == 0x26)
                    goto LAB_00492abd;
            }
            if (param_1 < 0) {
                if (param_1 == -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                        DAT_PencilRenderCore::ptr)(0, 0);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, 0);
            }
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                color = 0xc2f0eb;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                color = 0xccfaff;
            }
        LAB_00492b46:
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            yParam = DAT_ButtonY::instance + 7;
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
