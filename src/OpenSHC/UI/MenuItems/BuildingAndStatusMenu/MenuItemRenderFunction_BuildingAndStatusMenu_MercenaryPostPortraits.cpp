#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df3350.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_DisableMercPostPortraits.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466AB0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits(
            int param_1, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            int iVar2;
            BOOLEnum buttonIsInteracting;
            int iVar3;
            int iVar4;
            if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0)) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_DisableMercPostPortraits::instance == 0) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::GetUnitRecruitPermission)(param_1);
            iVar4 = DAT_CurrentButtonGmDataIndex::instance;
            buttonIsInteracting = DAT_ButtonCurrentlyInteracting::instance;
            iVar3 = DAT_ButtonY::instance;
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                DAT_00df3350::instance = param_1 + -0x46;
            }
            if (iVar1 == 1) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .stateTransitionTimeBaseUnk_0x18 = 0;
                    buttonIsInteracting = FALSE;
                } else {
                    if ((param_1 < 0x46) || (0x4c < param_1))
                        goto LAB_00466bec;
                    DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .stateTransitionTimeBaseUnk_0x18 = 0;
                    iVar3 = DAT_ButtonY::instance;
                }
                iVar1 = DAT_ButtonX::instance;
                iVar2 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                    &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar4])(buttonIsInteracting);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar4].gmId_0x0, iVar2,
                    iVar1, iVar3);
            } else if (((iVar1 == 0) || (iVar1 == 4)) || (iVar1 == 3)) {
                iVar2 = 0x10;
                buttonGmData
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                iVar3 = DAT_ButtonX::instance;
                iVar4 = DAT_ButtonY::instance;
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::IO::Graphics::GmID)buttonGmData->gmId_0x0, iVar1 + 7, iVar3, iVar4, iVar2);
            }
        LAB_00466bec:
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
