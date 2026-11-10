#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

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
#include "OpenSHC/Globals/INT_00df3350.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466AB0
            void MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits(int unitType, ...)
            {
                // Outside solitary and single-player skirmish the portraits stay hidden while the no-rush time runs.
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                    && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                // Guarded, not an early return (early return: quick_diff 0.8738 -> 0.8350)
                if (DAT_DisableMercPostPortraits::instance) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    Map::Units::EuroRecruitableState const permission
                        = MACRO_CALL(Helpers_Func::GetUnitRecruitPermission)((Map::Units::UnitType)unitType);
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        INT_00df3350::instance = unitType - Map::Units::UT_A_ARCHER;
                    }
                    if (permission == Map::Units::ERS_CAN_RECRUITUnk) {
                        if (DAT_ButtonCurrentlyInteracting::instance) {
                            // The low bound returns on its own (one range test: quick_diff 0.8738 -> 0.7122)
                            if (unitType < Map::Units::UT_A_ARCHER) {
                                DAT_CurrentButtonPictureInGm::instance
                                    = DAT_UIButtonDefinedData::instance
                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                          .pictureInGm_0x4;
                                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                    = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                return;
                            }
                            if (unitType <= Map::Units::UT_A_FIRETHROWER) {
                                // Store through the array (through the pointer: quick_diff 0.8738 -> 0.6400)
                                DAT_UIButtonDefinedData::instance
                                    .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .stateTransitionTimeBaseUnk_0x18 = 0;
                                ButtonGmData* const buttonGmData
                                    = &DAT_UIButtonDefinedData::instance
                                           .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                                    MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                        DAT_ButtonCurrentlyInteracting::instance),
                                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                            }
                        } else {
                            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                .stateTransitionTimeBaseUnk_0x18 = 0;
                            ButtonGmData* const buttonGmData
                                = &DAT_UIButtonDefinedData::instance
                                       .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                                MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                    FALSE),
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                        }
                    } else if (permission == Map::Units::ERS_CAN_NOT_RECRUIT
                        || permission == Map::Units::ERS_UNABLE_MISSING_PEASANTS
                        || permission == Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY) {
                        // A mercenary the player can't hire now is drawn faded and can't be pressed.
                        ButtonGmData* const buttonGmData
                            = &DAT_UIButtonDefinedData::instance
                                   .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((IO::Graphics::GmID)buttonGmData->gmId_0x0,
                            MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE)
                                + 7,
                            DAT_ButtonX::instance, DAT_ButtonY::instance, 16);
                    }
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }

        }
    }
}
}
