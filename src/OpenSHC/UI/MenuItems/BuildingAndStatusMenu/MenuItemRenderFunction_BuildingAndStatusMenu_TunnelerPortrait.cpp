#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466D10
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait(int param_1, ...)
        {
            ButtonGmData* pBVar1;
            BOOLEnum BVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int blendStrengthUnk;
            if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0)) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_EnoughGoldForRequestedUnit::instance != FALSE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                BVar2 = MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckGoldResource)(param_1);
                if (BVar2 == FALSE) {
                    blendStrengthUnk = 0x16;
                    pBVar1
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    iVar4 = DAT_ButtonX::instance;
                    iVar5 = DAT_ButtonY::instance;
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
                        FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::IO::Graphics::GmID)pBVar1->gmId_0x0, iVar3, iVar4, iVar5, blendStrengthUnk);
                } else {
                    pBVar1
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                    iVar4 = DAT_ButtonX::instance;
                    iVar5 = DAT_ButtonY::instance;
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
                        DAT_ButtonCurrentlyInteracting::instance);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar3, iVar4, iVar5);
                }
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
        }

    }
}
}
