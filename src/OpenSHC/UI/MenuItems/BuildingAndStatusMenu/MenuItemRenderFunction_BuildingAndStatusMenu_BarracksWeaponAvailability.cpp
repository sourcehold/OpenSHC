#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
#include "OpenSHC/Globals/INT_00df3350.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x004649D0
            void MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability(int resourceType, ...)
            {
                // Set when the unit under the mouse needs this item.
                BOOLEnum neededByHoveredUnit = FALSE;
                // fixme: the horses' button (-1) falls through to the item part, which reads euroRecruitable[-11] and
                // currentResources[-1]
                if (resourceType == -1) {
                    if (!DAT_EnoughGoldForRequestedUnit::instance
                        || !DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    } else {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        if ((int)INT_00df3350::instance >= 0) {
                            for (int i = 0; i < countof(DAT_UnitPropertiesDefinedData::instance
                                                    .EuroUnitResourceCosts[INT_00df3350::instance]);
                                ++i) {
                                if (DAT_UnitPropertiesDefinedData::instance
                                        .EuroUnitResourceCosts[INT_00df3350::instance][i]
                                    == -1) {
                                    neededByHoveredUnit = TRUE;
                                }
                            }
                        }
                        if (neededByHoveredUnit) {
                            // 287 pictures on: the icon marked as needed by the unit under the mouse.
                            ButtonGmData* const buttonGmData
                                = &DAT_UIButtonDefinedData::instance
                                       .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                                MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                    DAT_ButtonCurrentlyInteracting::instance)
                                    + 287,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                            short const horses
                                = DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .availableHorses;
                            if (horses != 0) {
                                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2,
                                    DAT_TextManagerObject::ptr)(horses, DAT_ButtonX::instance + 8,
                                    DAT_ButtonY::instance + 40, Text::TTA_LEFT, 0, 18, FALSE, 0);
                            }
                        } else if (DAT_GameState::instance
                                       .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                       .availableHorses
                            != 0) {
                            ButtonGmData* const buttonGmData
                                = &DAT_UIButtonDefinedData::instance
                                       .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                                MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                    DAT_ButtonCurrentlyInteracting::instance),
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                            MACRO_CALL_MEMBER(
                                Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                                DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .availableHorses,
                                DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 40, Text::TTA_LEFT, 0, 18, FALSE, 0);
                        } else {
                            // None left: the greyed picture, 9 on, which can't be pressed.
                            ButtonGmData* const buttonGmData
                                = &DAT_UIButtonDefinedData::instance
                                       .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                                MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                    FALSE)
                                    + 9,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                        }
                        DAT_CurrentButtonPictureInGm::instance
                            = DAT_UIButtonDefinedData::instance
                                  .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                  .pictureInGm_0x4;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                }
                if (!DAT_EnoughGoldForRequestedUnit::instance
                    || !DAT_GameState::instance.mapAndTime.euroRecruitable[resourceType - 10]) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ((int)INT_00df3350::instance >= 0) {
                    // The item part tests only the first three cost slots, as the original does.
                    for (int i = 0; i < 3; ++i) {
                        if (DAT_UnitPropertiesDefinedData::instance.EuroUnitResourceCosts[INT_00df3350::instance][i]
                            == resourceType) {
                            neededByHoveredUnit = TRUE;
                        }
                    }
                }
                if (neededByHoveredUnit) {
                    ButtonGmData* const buttonGmData
                        = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                    MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                        MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                            DAT_ButtonCurrentlyInteracting::instance)
                            + 287,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    int const stock
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .currentResources[resourceType];
                    if (stock != 0) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            stock, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 40, Text::TTA_LEFT, 0, 18, FALSE,
                            0);
                    }
                } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .currentResources[resourceType]
                    != 0) {
                    ButtonGmData* const buttonGmData
                        = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                    MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                        MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                            DAT_ButtonCurrentlyInteracting::instance),
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[resourceType],
                        DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 40, Text::TTA_LEFT, 0, 18, FALSE, 0);
                } else {
                    // None left: the greyed picture, 9 on, which can't be pressed.
                    ButtonGmData* const buttonGmData
                        = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                        MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE) + 9,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                }
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }

        }
    }
}
}
