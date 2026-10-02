#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
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

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00465110
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection(
            ResourceType _weapon, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            uint uVar2;
            bool _weaponIsDisabled;
            int drawX;
            int drawY;
            if (_weapon == OpenSHC::Game::Resources::RT_CROSSBOW) {
                _weaponIsDisabled = DAT_GameCore::instance.xbowProducible_logic == 0;
            } else if (_weapon == OpenSHC::Game::Resources::RT_PIKE) {
                _weaponIsDisabled = DAT_GameCore::instance.pikeProducible_logic == 0;
            } else if (_weapon == OpenSHC::Game::Resources::RT_SWORD) {
                _weaponIsDisabled = DAT_GameCore::instance.swordProducible_logic == 0;
            } else if (_weapon == OpenSHC::Game::Resources::RT_BOW) {
                _weaponIsDisabled = DAT_GameCore::instance.bowProducible_logic == 0;
            } else if (_weapon == OpenSHC::Game::Resources::RT_SPEAR) {
                _weaponIsDisabled = DAT_GameCore::instance.spearProducible_logic == 0;
            } else {
                if (_weapon != OpenSHC::Game::Resources::RT_MACE)
                    goto LAB_00465173;
                _weaponIsDisabled = DAT_GameCore::instance.maceProducible_logic == 0;
            }
            if (_weaponIsDisabled) {
                DAT_ButtonUnknownZero::instance = 1;
            }
        LAB_00465173:
            DAT_ButtonUnknownZero::instance = 0;
            uVar2 = (uint)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .weaponRelated
                == _weapon);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
            drawX = DAT_ButtonX::instance;
            drawY = DAT_ButtonY::instance;
            iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                DAT_ButtonCurrentlyInteracting::instance);
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                (OpenSHC::DE::SHCDE::eGM)buttonGmData->gmId_0x0, (int)(iVar1 + uVar2), drawX, drawY);
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4
                + uVar2;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
