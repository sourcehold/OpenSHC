#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BEC40
        void EditScenario::MenuItemRenderFunction_EditScenario_BaseMenuButtons(int param_1, ...)
        {
            int iVar1;
            uint color;
            if (param_1 == 3) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            if (((param_1 == 0x3d) || (param_1 == 0xa6)) || (param_1 == 0xa7)) {
                if (DAT_GameState::instance.mapAndTime.editScenarioExtraOptions != 0) {
                    if (param_1 == 0x3d) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            /*
                              added by script: "Gold"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x3d, (int)((int)(DAT_ButtonX::instance + 10)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                                FALSE);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                                (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12,
                                FALSE, 0);
                        }
                        /*
                          added by script: "Gold"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x3d, (int)((int)(DAT_ButtonX::instance + 10)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                            DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                            (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0x12, FALSE,
                            0);
                    }
                    if (param_1 == 0xa6) {
                        iVar1 = DAT_MissionAestheticsDefinedData::instance
                                    .field1236_0x3448[DAT_GameState::instance.mapAndTime.scenarioRationsSetting];
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar1,
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar1,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE);
                    }
                    if (param_1 == 0xa7) {
                        iVar1 = (int)DAT_GameState::instance.mapAndTime.scenarioTaxesSetting;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                            color = 0xc2f0eb;
                        } else {
                            color = 0xccfaff;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_KEEP, iVar1 + 7,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, color, 0x12, FALSE);
                    }
                }
            } else if (param_1 == 0xa8) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        /*
                          added by script: "Starting Gold"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xa8, (int)((int)(DAT_ButtonX::instance + 10)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                        iVar1 = DAT_ButtonW::instance + -10 + DAT_ButtonX::instance;
                    } else {
                        /*
                          added by script: "Starting Gold"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xa8, (int)((int)(DAT_ButtonX::instance + 10)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                        iVar1 = DAT_ButtonW::instance + -10 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingResources[0xf], iVar1,
                        (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x48,
                        (int)((int)(DAT_ButtonX::instance + 10)), (int)((int)(DAT_ButtonY::instance)));
                }
            } else if (param_1 == 0xa9) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        /*
                          added by script: "Starting Pitch"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xa9, (int)((int)(DAT_ButtonX::instance + 10)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                        iVar1 = DAT_ButtonW::instance + -10 + DAT_ButtonX::instance;
                    } else {
                        /*
                          added by script: "Starting Pitch"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xa9, (int)((int)(DAT_ButtonX::instance + 10)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                        iVar1 = DAT_ButtonW::instance + -10 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingResources[8], iVar1,
                        (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x3a,
                        (int)((int)(DAT_ButtonX::instance + 10)), (int)((int)(DAT_ButtonY::instance)));
                }
            } else if ((param_1 != 0x2a)
                || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION)) {
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    if (param_1 != 0x26) {
                        if (param_1 == 0x4f) {}
                    LAB_004beed3:
                        if (param_1 == 0x29) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                                param_1 = 0xa4;
                            }
                        } else if (param_1 == 0x4f) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                                /*
                                  added by script: "Popularity"
                                 */
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x4f,
                                    (int)((int)(DAT_ButtonX::instance + 10)), (int)((int)(DAT_ButtonY::instance + 6)),
                                    OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE);
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                    DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                                    (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12,
                                    FALSE, 0);
                            }
                            /*
                              added by script: "Popularity"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x4f, (int)((int)(DAT_ButtonX::instance + 10)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12,
                                FALSE);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                                (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0x12,
                                FALSE, 0);
                        }
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                    }
                } else if ((DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_JUST_BUILD)
                    || (((param_1 != 0x2a && (param_1 != 0x11)) && (param_1 != 0x2b))))
                    goto LAB_004beed3;
            }
        }

    }
}
}
