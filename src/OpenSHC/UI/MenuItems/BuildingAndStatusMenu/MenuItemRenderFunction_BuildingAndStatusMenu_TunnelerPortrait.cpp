#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

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
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466D10
            void MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait(int unitType, ...)
            {
                // Outside solitary and single-player skirmish the portrait stays hidden while the no-rush time runs.
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                    && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                // Guarded, not an early return: the original keeps the return block at the end (96.0 the other way).
                if (DAT_EnoughGoldForRequestedUnit::instance) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (MACRO_CALL(Helpers_Func::CheckGoldResource)((Map::Units::UnitType)unitType)) {
                        ButtonGmData* const buttonGmData
                            = &DAT_UIButtonDefinedData::instance
                                   .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)((DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                            MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                                DAT_ButtonCurrentlyInteracting::instance),
                            DAT_ButtonX::instance, DAT_ButtonY::instance);
                    } else {
                        // Without the gold the portrait is drawn faded and can't be pressed.
                        ButtonGmData* const buttonGmData
                            = &DAT_UIButtonDefinedData::instance
                                   .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((IO::Graphics::GmID)buttonGmData->gmId_0x0,
                            MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE),
                            DAT_ButtonX::instance, DAT_ButtonY::instance, 22);
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
