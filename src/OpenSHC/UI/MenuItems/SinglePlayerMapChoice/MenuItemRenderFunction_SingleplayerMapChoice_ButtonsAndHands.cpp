#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eTextSections;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042D140
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...)
        {
            int iVar1;
            int yParam;
            uint uVar2;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            switch (param_1) {
            case 2:
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5;
                break;
            case 0x41:
                iVar1 = 0x20;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < 0) {
                    iVar1 = 0x10;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                iVar1 = (0x20 - DAT_ButtonBackgroundBlendStrength::instance) * iVar1;
                iVar1 = -((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5);
                break;
            case 0x45:
                if (DAT_MapMissionType::instance == 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    uVar2 = 0xc2f0eb;
                } else {
                    uVar2 = 0xccfaff;
                }
                /*
                  Difficulty
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 0x18, (int)((int)(DAT_ButtonX::instance + 10)),
                    (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_LEFT, uVar2, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                /*
                  "easy, normal, hard, very hard"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, DAT_GameState::instance.mapAndTime.difficulty + 0x13,
                    (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_RIGHT, 0xff00, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case 0x4a:
                if (DAT_MapMissionType::instance != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if ((DAT_SH1_SiegeAdvancedMode::instance != 0) && (DAT_00b960dc::instance == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                    uVar2 = 0xccfaff;
                    yParam = DAT_ButtonY::instance + 7;
                    goto LAB_0042d4cd;
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    /*
                      "Advanced"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE,
                        ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar1 = iVar1 + (iVar1 >> 0x1f & 0x1fU);
                uVar2 = 0xc2f0eb;
                goto LAB_0042d4c2;
            case 0x4d:
                if (DAT_MapMissionType::instance != 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                    param_1 = 0x4e;
                }
                if (DAT_GameCore::instance.mapU4Int1_2 != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                    uVar2 = 0xc2f0eb;
                    yParam = DAT_ButtonY::instance + 7;
                    goto LAB_0042d4cd;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar1 = iVar1 + (iVar1 >> 0x1f & 0x1fU);
                uVar2 = 0xccfaff;
            LAB_0042d4c2:
                iVar1 = (iVar1 >> 5) + 0x20;
                yParam = DAT_ButtonY::instance + 7;
            LAB_0042d4cd:
                /*
                  "Attacking"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)), yParam, OpenSHC::Text::TTA_CENTER,
                    uVar2, 0x12, FALSE, iVar1);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -0x65:
                /*
                  scroll arrows
                 */
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -100:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            default:
                goto switchD_0042d163_caseD_ffffff9d;
            case -0xb:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            case -10:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_ButtonUnknownZero::instance = 0;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(iVar1 + 0x20);
        switchD_0042d163_caseD_ffffff9d:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
