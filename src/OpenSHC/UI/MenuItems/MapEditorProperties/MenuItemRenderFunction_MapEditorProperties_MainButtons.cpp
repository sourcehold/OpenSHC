#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapEditorProperties_ClickedButton.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042E900
        void MapEditorProperties::MenuItemRenderFunction_MapEditorProperties_MainButtons(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            bool bVar4;
            uint color;
            iVar3 = 0x11;
            iVar2 = 10;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (param_1 == 0x19) {
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 1) {}
                    if (DAT_GameCore::instance.field115_0x1d98 == 0) {}
                } else if (param_1 == 5) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                if ((DAT_GameCore::instance.U2_mapType_singleOrMulti == 0)
                    && (((param_1 == 9 || (param_1 == -1)) || (param_1 == -2)))) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 9) {
                    if (DAT_GameCore::instance.unknownAlwaysZero03 != 0) {
                        param_1 = 0x20;
                    }
                    iVar3 = 0x12;
                    iVar2 = 8;
                }
                if (param_1 + 4U < 2) {
                    DAT_ButtonUnknownZero::instance = 1;
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 1) {
                        DAT_ButtonUnknownZero::instance = 0;
                        if (DAT_GameCore::instance.mapU4Int3_balanced == 0) {
                            bVar4 = param_1 == -3;
                        } else {
                            bVar4 = param_1 == -4;
                        }
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        iVar2 = DAT_ButtonX::instance;
                        iVar3 = DAT_ButtonY::instance;
                        iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                            DAT_ButtonCurrentlyInteracting::instance);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)(DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .gmId_0x0),
                            iVar1 + (uint)bVar4, iVar2, iVar3);
                        DAT_CurrentButtonPictureInGm::instance
                            = DAT_UIButtonDefinedData::instance
                                  .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                  .pictureInGm_0x4
                            + (uint)bVar4;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            DAT_MapEditorProperties_ClickedButton::instance = param_1;
                        }
                    }
                } else if (param_1 + 6U < 2) {
                    DAT_ButtonUnknownZero::instance = 1;
                    if ((DAT_GameCore::instance.U2_mapType_singleOrMulti == 0)
                        && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION)) {
                        DAT_ButtonUnknownZero::instance = 0;
                        if (DAT_GameCore::instance.mapU3EndInt == 0) {
                            bVar4 = param_1 == -5;
                        } else {
                            bVar4 = param_1 == -6;
                        }
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        iVar2 = DAT_ButtonX::instance;
                        iVar3 = DAT_ButtonY::instance;
                        iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                            DAT_ButtonCurrentlyInteracting::instance);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)(DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .gmId_0x0),
                            iVar1 + (uint)bVar4, iVar2, iVar3);
                        DAT_CurrentButtonPictureInGm::instance
                            = DAT_UIButtonDefinedData::instance
                                  .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                  .pictureInGm_0x4
                            + (uint)bVar4;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            DAT_MapEditorProperties_ClickedButton::instance = param_1;
                        }
                    }
                } else {
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        DAT_MapEditorProperties_ClickedButton::instance = param_1;
                    }
                    if (param_1 < 0) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)((uint)(param_1 != -1), 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        color = 0xc2f0eb;
                    } else {
                        color = 0xccfaff;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, param_1,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)), DAT_ButtonY::instance + iVar2,
                        OpenSHC::Text::TTA_CENTER, color, iVar3, FALSE);
                }
            }
        }

    }
}
}
