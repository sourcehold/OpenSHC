#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df3350.hpp"
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
        using OpenSHC::Map::Units::EuroRecruitableState;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466950
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_BarrackUnitPortraits(int param_1, ...)
        {
            int _resourceImageID;
            ButtonGmData* buttonGmData;
            int _yPosition;
            int _xPosition;
            if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0)) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_EnoughGoldForRequestedUnit::instance == FALSE) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            EuroRecruitableState EVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::IsEuroUnitRecruitableUnk)(param_1);
            int iVar2 = DAT_CurrentButtonGmDataIndex::instance;
            BOOLEnum buttonIsInteracting = DAT_ButtonCurrentlyInteracting::instance;
            _yPosition = DAT_ButtonY::instance;
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                DAT_00df3350::instance = param_1 + -0x16;
            }
            if (EVar1 == OpenSHC::Map::Units::ERS_CAN_RECRUITUnk) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .stateTransitionTimeBaseUnk_0x18 = 0;
                    buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + iVar2;
                    _xPosition = DAT_ButtonX::instance;
                    _resourceImageID = MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
                } else {
                    if ((param_1 < 0x16) || (0x1c < param_1))
                        goto LAB_00466a7d;
                    DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .stateTransitionTimeBaseUnk_0x18 = 0;
                    buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + iVar2;
                    _xPosition = DAT_ButtonX::instance;
                    _yPosition = DAT_ButtonY::instance;
                    _resourceImageID
                        = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            buttonGmData)(buttonIsInteracting);
                }
            } else {
                if (((EVar1 != OpenSHC::Map::Units::ERS_CAN_NOT_RECRUIT)
                        && (EVar1 != OpenSHC::Map::Units::ERS_UNABLE_MISSING_PEASANTS))
                    && (EVar1 != OpenSHC::Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY))
                    goto LAB_00466a7d;
                buttonGmData
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                _xPosition = DAT_ButtonX::instance;
                iVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
                _resourceImageID = iVar2 + 7;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                (OpenSHC::DE::SHCDE::eGM)buttonGmData->gmId_0x0, _resourceImageID, _xPosition, _yPosition);
        LAB_00466a7d:
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
