#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BEC40
        void EditScenario::MenuItemRenderFunction_EditScenario_BaseMenuButtons(int param_1, ...)
        {
            int iVar1;
            uint color;
            if (param_1 == 3) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if (param_1 == 61 || param_1 == 166 || param_1 == 167) {
                if (DAT_GameState::instance.mapAndTime.editScenarioExtraOptions != 0) {
                    if (param_1 == 61) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            // added by script: "Gold"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 61, (int)(DAT_ButtonX::instance + 10),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                                (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                            return;
                        }
                        // added by script: "Gold"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 61, (int)(DAT_ButtonX::instance + 10),
                            (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                            DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                            (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    }
                    if (param_1 == 166) {
                        iVar1 = DAT_MissionAestheticsDefinedData::instance
                                    .field_0x3448[DAT_GameState::instance.mapAndTime.scenarioRationsSetting];
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar1,
                                (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_CENTER,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                            return;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar1,
                            (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                        return;
                    }
                    if (param_1 == 167) {
                        iVar1 = (int)DAT_GameState::instance.mapAndTime.scenarioTaxesSetting;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                        } else {
                            color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_KEEP, iVar1 + 7,
                            (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                            OpenSHC::Text::TTA_CENTER, color, 18, FALSE);
                    }
                }
            } else if (param_1 == 168) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        // added by script: "Starting Gold"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 168, (int)(DAT_ButtonX::instance + 10),
                            (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        iVar1 = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                    } else {
                        // added by script: "Starting Gold"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 168, (int)(DAT_ButtonX::instance + 10),
                            (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        iVar1 = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance.SEC_StartingResources[OpenSHC::Game::Resources::RT_GOLD],
                        iVar1, (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_RIGHT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 72,
                        (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance));
                }
            } else if (param_1 == 169) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        // added by script: "Starting Pitch"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 169, (int)(DAT_ButtonX::instance + 10),
                            (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        iVar1 = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                        return;
                    } else {
                        // added by script: "Starting Pitch"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 169, (int)(DAT_ButtonX::instance + 10),
                            (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        iVar1 = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[OpenSHC::Game::Resources::RT_PARTIALPITCH],
                        iVar1, (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_RIGHT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 58,
                        (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance));
                }
            } else if ((param_1 != 42)
                || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION)) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    if (param_1 != 38) {
                        if (param_1 == 79) {
                            return;
                        }
                    LAB_004beed3:
                        if (param_1 == 41) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                                param_1 = 164;
                            }
                        } else if (param_1 == 79) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                            if (DAT_ButtonCurrentlyInteracting::instance) {
                                // added by script: "Popularity"
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79,
                                    (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 6),
                                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                    DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                                    (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                                return;
                            }
                            // added by script: "Popularity"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79, (int)(DAT_ButtonX::instance + 10),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                                (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                            return;
                        }
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                    }
                } else if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_JUST_BUILD
                    || ((param_1 != 42 && (param_1 != 17)) && (param_1 != 43)))
                    goto LAB_004beed3;
            }
        }

    }
}
}
