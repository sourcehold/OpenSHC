#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

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
        namespace MapEditorProperties {

            // FUNCTION: STRONGHOLDCRUSADER 0x0042E900
            void MenuItemRenderFunction_MapEditorProperties_MainButtons(int button, ...)
            {
                // before the guards, as the original loads them (after them: quick_diff 0.9612 -> 0.9078)
                int fontSize = 17;
                int textOffsetY = 10;
                // nothing while a dialog is open
                if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                    || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                    return;
                }
                if (button == 25) {
                    // "Edit Scenario": only for a single-player map loaded in the editor
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 1) {
                        return;
                    }
                    if (!DAT_GameCore::instance.mapLoadedForEditor) {
                        return;
                    }
                } else if (button == 5) {
                    // "Main Menu"
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    return;
                }
                // The description's "Edit" and its arrows only on a multiplayer map.
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0
                    && (button == 9 || button == -1 || button == -2)) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (button == 9) {
                    if (DAT_GameCore::instance.showTextMessageInsteadOfEdit) {
                        // "Message" in place of "Edit"
                        button = 32;
                    }
                    fontSize = 18;
                    textOffsetY = 8;
                }
                // one range test (== -4 || == -3: quick_diff 0.9612 -> 0.4466)
                if (button >= -4 && button <= -3) {
                    // A multiplayer map's pair for mapU4Int3_balanced: the one matching it shows its next picture.
                    DAT_ButtonUnknownZero::instance = 1;
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 1) {
                        return;
                    }
                    DAT_ButtonUnknownZero::instance = 0;
                    int frame = 0;
                    // two ifs, the unset case first (a ternary of the two tests: quick_diff 0.9612 -> 0.6190)
                    if (!DAT_GameCore::instance.mapU4Int3_balanced) {
                        if (button == -3) {
                            frame = 1;
                        }
                    } else if (button == -4) {
                        frame = 1;
                    }
                    // written out per pair, as the binary has them (a ButtonGmData local: quick_diff 0.9612 -> 0.7131)
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                              .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                              .gmId_0x0,
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                            DAT_ButtonCurrentlyInteracting::instance)
                            + frame,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4
                        + frame;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        DAT_MapEditorProperties_ClickedButton::instance = button;
                    }
                    return;
                }
                // one range test, as above
                if (button >= -6 && button <= -5) {
                    // A single-player invasion map's pair for mapU3EndInt, drawn the same way.
                    DAT_ButtonUnknownZero::instance = 1;
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0) {
                        return;
                    }
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_INVASION) {
                        return;
                    }
                    DAT_ButtonUnknownZero::instance = 0;
                    int frame = 0;
                    // two ifs, the unset case first (a ternary of the two tests: quick_diff 0.9612 -> 0.6190)
                    if (!DAT_GameCore::instance.mapU3EndInt) {
                        if (button == -5) {
                            frame = 1;
                        }
                    } else if (button == -6) {
                        frame = 1;
                    }
                    // written out again, as the binary has it
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                              .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                              .gmId_0x0,
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                            DAT_ButtonCurrentlyInteracting::instance)
                            + frame,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4
                        + frame;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        DAT_MapEditorProperties_ClickedButton::instance = button;
                    }
                    return;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    DAT_MapEditorProperties_ClickedButton::instance = button;
                }
                if (button < 0) {
                    // the description's arrows: -1 up, -2 down
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    // two calls (one with button != -1: 100.0% -> 89.1%)
                    if (button == -1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)(0, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)(1, 0);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // two calls, one per colour (one call with a colour local: 100.0% -> 67.3%)
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + textOffsetY, OpenSHC::Text::TTA_CENTER,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, fontSize, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + textOffsetY, OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, fontSize, FALSE);
            }

        }
    }
}
}
