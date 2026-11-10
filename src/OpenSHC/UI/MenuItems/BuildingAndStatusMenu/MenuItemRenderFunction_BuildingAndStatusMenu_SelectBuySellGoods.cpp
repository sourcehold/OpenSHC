#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00465950
            void MenuItemRenderFunction_BuildingAndStatusMenu_SelectBuySellGoods(int resourceType, ...)
            {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                // Goods the map doesn't let the player trade get no button.
                if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                        (Game::Resources::ResourceType)resourceType)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                ButtonGmData* const buttonGmData
                    = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                    MACRO_CALL_MEMBER(Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                        DAT_ButtonCurrentlyInteracting::instance),
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }

        }
    }
}
}
