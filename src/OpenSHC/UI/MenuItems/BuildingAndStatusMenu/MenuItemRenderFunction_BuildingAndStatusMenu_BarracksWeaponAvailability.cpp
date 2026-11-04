#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_00df3350.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004649D0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability(
            int param_1, ...)
        {
            ButtonGmData* pBVar1;
            int sVar2;
            bool bVar3;
            int iVar4;
            int iVar8;
            int iVar9;
            bVar3 = false;
            if (param_1 == -1) {
                if ((!DAT_EnoughGoldForRequestedUnit::instance)
                    || (DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                } else {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    // the original tests each cost with a one-armed if setting the flag
                    // (0x464a14..0x464a41), then branches on the flag once
                    if (0 <= (int)DAT_00df3350::instance) {
                        for (int i = 0; i < 4; ++i) {
                            if (DAT_UnitPropertiesDefinedData::instance.EuroUnitResourceCosts[DAT_00df3350::instance][i]
                                == -1) {
                                bVar3 = true;
                            }
                        }
                    }
                    if (bVar3) {
                        pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray
                            + DAT_CurrentButtonGmDataIndex::instance;
                        iVar8 = DAT_ButtonX::instance;
                        iVar9 = DAT_ButtonY::instance;
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            pBVar1)(DAT_ButtonCurrentlyInteracting::instance);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4 + 287, iVar8, iVar9);
                        sVar2 = (ushort)DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .availableHorses;
                        if (sVar2 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(sVar2, (int)(DAT_ButtonX::instance + 8),
                                (int)(DAT_ButtonY::instance + 40), OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                        }
                    } else if (DAT_GameState::instance
                                   .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                   .availableHorses
                        != 0) {
                        pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray
                            + DAT_CurrentButtonGmDataIndex::instance;
                        iVar8 = DAT_ButtonX::instance;
                        iVar9 = DAT_ButtonY::instance;
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            pBVar1)(DAT_ButtonCurrentlyInteracting::instance);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4, iVar8, iVar9);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            (int)DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .availableHorses,
                            (int)(DAT_ButtonX::instance + 8), (int)(DAT_ButtonY::instance + 40),
                            OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                    } else {
                        pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray
                            + DAT_CurrentButtonGmDataIndex::instance;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        iVar8 = DAT_ButtonX::instance;
                        iVar9 = DAT_ButtonY::instance;
                        iVar4 = MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(FALSE);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4 + 9, iVar8, iVar9);
                    }
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
            if ((!DAT_EnoughGoldForRequestedUnit::instance)
                || (DAT_GameState::instance.mapAndTime.euroRecruitable[param_1 - 10] == 0)) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (0 <= (int)DAT_00df3350::instance) {
                for (int i = 0; i < 3; ++i) {
                    if (DAT_UnitPropertiesDefinedData::instance.EuroUnitResourceCosts[DAT_00df3350::instance][i]
                        == param_1) {
                        bVar3 = true;
                    }
                }
            }
            if (bVar3) {
                pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                iVar8 = DAT_ButtonX::instance;
                iVar9 = DAT_ButtonY::instance;
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
                    DAT_ButtonCurrentlyInteracting::instance);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4 + 287, iVar8, iVar9);
                iVar8 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[param_1];
                if (iVar8 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(iVar8, (int)(DAT_ButtonX::instance + 8),
                        (int)(DAT_ButtonY::instance + 40), OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                }
            } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .currentResources[param_1]
                != 0) {
                pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                iVar8 = DAT_ButtonX::instance;
                iVar9 = DAT_ButtonY::instance;
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
                    DAT_ButtonCurrentlyInteracting::instance);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4, iVar8, iVar9);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[param_1],
                    (int)(DAT_ButtonX::instance + 8), (int)(DAT_ButtonY::instance + 40), OpenSHC::Text::TTA_LEFT, 0, 18,
                    FALSE, 0);
            } else {
                pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                iVar8 = DAT_ButtonX::instance;
                iVar9 = DAT_ButtonY::instance;
                iVar4
                    = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(FALSE);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar4 + 9, iVar8, iVar9);
            }
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
