#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004652D0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            uint uVar2;
            int drawX;
            int drawY;
            uVar2 = (uint)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .gateOpenOrCloseClick
                == param_1);
            buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
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
