#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00464860
        void MapEditorLandscaping::MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons(int param_1, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            uint uVar2;
            uVar2 = (uint)(DAT_ButtonCurrentlyInteracting::instance != FALSE);
            if (param_1 - 0xe7U < 7) {
                if (DAT_GameCore::instance.activeMenuTab.tabType == param_1) {
                    uVar2 = 2;
                }
                goto LAB_0046490e;
            }
            uVar2 = 0;
            if (param_1 < 0xcd) {
                if (param_1 == 0xcc) {
                    if (DAT_TileMapState::instance.unknownZero_0x5548fc == 0) {
                        uVar2 = 6;
                    } else if (DAT_TileMapState::instance.unknownZero_0x5548fc != 1) {
                        uVar2 = 3;
                    }
                } else if (param_1 == 1) {
                    if ((7 < DAT_TileMapState::instance.editorActiveBrush)
                        || (DAT_TileMapState::instance.editorActiveBrush < 1)) {
                        DAT_TileMapState::instance.editorActiveBrush = 1;
                    }
                    uVar2 = DAT_TileMapState::instance.editorActiveBrush * 3 - 3;
                } else if (param_1 != 0x20)
                    goto LAB_004648f1;
            } else {
                if (param_1 == 0x14b) {}
            LAB_004648f1:
                if (DAT_TileMapState::instance.currentMapperCommand == param_1) {
                    uVar2 = 2;
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE)
                        goto LAB_0046490e;
                    uVar2 = 1;
                }
            }
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                uVar2 = uVar2 + 1;
            }
        LAB_0046490e:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
            if (DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                    .alphaGmIdUnk_0xc
                == ((GmID)0)) {
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
                iVar1 = iVar1 + uVar2;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)((OpenSHC::IO::Graphics::GmID)buttonGmData->gmId_0x0), iVar1,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            } else {
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
                iVar1 = iVar1 + uVar2;
                if (DAT_ButtonBlendStrength::instance != 0x20) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::IO::Graphics::GmID)buttonGmData->gmId_0x0, iVar1,
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                        DAT_ButtonBlendStrength::instance);
                    DAT_CurrentButtonPictureInGm::instance = iVar1;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_CurrentButtonPictureInGm::instance = iVar1;
        }

    }
}
}
