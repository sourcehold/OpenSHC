#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00465110
            void MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection(ResourceType weapon, ...)
            {
                // Declared here: the original zeroes it on entry, before the producible checks.
                int pictureOffset = 0;
                // A weapon the map doesn't let the player make gets no button.
                // One arm per weapon: a single combined condition goes on testing the other weapons and loses the
                // match.
                if (weapon == Game::Resources::RT_CROSSBOW) {
                    if (!DAT_GameCore::instance.xbowProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else if (weapon == Game::Resources::RT_PIKE) {
                    if (!DAT_GameCore::instance.pikeProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else if (weapon == Game::Resources::RT_SWORD) {
                    if (!DAT_GameCore::instance.swordProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else if (weapon == Game::Resources::RT_BOW) {
                    if (!DAT_GameCore::instance.bowProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else if (weapon == Game::Resources::RT_SPEAR) {
                    if (!DAT_GameCore::instance.spearProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else if (weapon == Game::Resources::RT_MACE) {
                    if (!DAT_GameCore::instance.maceProducible_logic) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                }
                DAT_ButtonUnknownZero::instance = 0;
                // The weapon the workshop makes now shows its pressed picture.
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .weaponRelated
                    == weapon) {
                    pictureOffset = 1;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                ButtonGmData* const buttonGmData
                    = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                    MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                        DAT_ButtonCurrentlyInteracting::instance)
                        + pictureOffset,
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4
                    + pictureOffset;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }

        }
    }
}
}
