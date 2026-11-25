#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042D140
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int button, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            switch (button) {
            // the scroll arrows of the two lists
            case -10:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -11:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -100:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -101:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case 2:
                // the blend strength goes through * 32 / 32, as the original computes it (shl 5, then a signed divide)
                DAT_ButtonUnknownZero::instance = FALSE;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                break;
            case 69:
                // "Difficulty" and its setting, where the mission has one
                if (DAT_MapMissionType::instance != 0 && DAT_GameCore::instance.mapU4Int1_2 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24,
                            DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24,
                            DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS,
                        DAT_GameState::instance.mapAndTime.difficulty + 19,
                        DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_00FF00, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                break;
            case 74:
                // "Advanced", for the second player of a siege; shown as pressed while the advanced mode is on
                if (DAT_MapMissionType::instance == 2 && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2
                    && DAT_GameCore::instance.mapU4Int1_2 == 0) {
                    if (DAT_SH1_SiegeAdvancedMode::instance != 0 && DAT_00b960dc::instance == 0) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(
                            DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                            DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    } else if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(
                            DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                            DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(
                            DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                            DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    }
                }
                break;
            case 77:
                // the side the player is on: text 77, or 78 for the first player
                if (DAT_MapMissionType::instance == 2) {
                    if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                        button = 78;
                    }
                    if (DAT_GameCore::instance.mapU4Int1_2 == 0) {
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                                AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance,
                                OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                                DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 7,
                                OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                                AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance,
                                OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                                DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 7,
                                OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                        }
                    }
                }
                break;
            case 65: {
                // at half strength, and never as pressed, while no map is selected
                DAT_ButtonUnknownZero::instance = FALSE;
                int factor = 32;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    < 0) {
                    factor = 16;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    32 - (32 - DAT_ButtonBackgroundBlendStrength::instance) * factor / 32);
                break;
            }
            case 78:
                // nothing to draw; written out, since the original's switch has this case of its own
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
