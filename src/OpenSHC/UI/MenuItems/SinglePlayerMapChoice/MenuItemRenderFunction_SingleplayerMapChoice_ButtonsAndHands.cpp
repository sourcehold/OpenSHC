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
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...)
        {
            int iVar1;
            int yParam;
            uint uVar2;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            switch (param_1) {
            case -10:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, (int)(DAT_ButtonBackgroundBlendStrength::instance));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -11:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, (int)(DAT_ButtonBackgroundBlendStrength::instance));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -100:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, (int)(DAT_ButtonBackgroundBlendStrength::instance));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -101:
                // scroll arrows
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, (int)(DAT_ButtonBackgroundBlendStrength::instance));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case 2:
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                iVar1 /= 32;
                break;
            case 69:
                if (DAT_MapMissionType::instance == 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    // Difficulty
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24,
                        (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, (iVar1 / 32) + 32);
                } else {
                    // Difficulty
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24,
                        (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, (iVar1 / 32) + 32);
                }
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // "easy, normal, hard, very hard"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, DAT_GameState::instance.mapAndTime.difficulty + 19,
                    (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_00FF00, 18, FALSE, (iVar1 / 32) + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case 74:
                if (DAT_MapMissionType::instance != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if ((DAT_SH1_SiegeAdvancedMode::instance != 0) && (DAT_00b960dc::instance == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    iVar1 = (iVar1 / 32) + 32;
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                    yParam = DAT_ButtonY::instance + 7;
                    goto LAB_0042d4cd;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    // "Advanced"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                        (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                        (iVar1 / 32) + 32);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                iVar1 += (iVar1 >> 0x1f & 0x1fU);
                uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                goto LAB_0042d4c2;
            case 77:
                if (DAT_MapMissionType::instance != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                    param_1 = 78;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    iVar1 = (iVar1 / 32) + 32;
                    uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                    yParam = DAT_ButtonY::instance + 7;
                    goto LAB_0042d4cd;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                iVar1 += (iVar1 >> 0x1f & 0x1fU);
                uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
            LAB_0042d4c2:
                yParam = DAT_ButtonY::instance + 7;
                iVar1 = (iVar1 >> 5) + 32;
            LAB_0042d4cd:
                // "Attacking"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                    (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), yParam, OpenSHC::Text::TTA_CENTER, uVar2,
                    18, FALSE, iVar1);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case 65:
                iVar1 = 32;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < 0) {
                    iVar1 = 16;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                iVar1 *= 32 - DAT_ButtonBackgroundBlendStrength::instance;
                iVar1 = -(iVar1 / 32);
                break;
            default:
                goto switchD_0042d163_caseD_ffffff9d;
            }
            DAT_ButtonUnknownZero::instance = 0;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(iVar1 + 32);
        switchD_0042d163_caseD_ffffff9d:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
