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
        void EditScenario::MenuItemRenderFunction_EditScenario_BaseMenuButtons(int button, ...)
        {
            // 3 is "Exit"
            if (button == 3) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            // the extra options: 61 "Gold", 166 "Rationing" and 167 "Tax Rate"
            if (button == 61 || button == 166 || button == 167) {
                // the extra options are only drawn once they are switched on
                if (DAT_GameState::instance.mapAndTime.editScenarioExtraOptions == 0) {
                    return;
                }
                if (button == 61) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        // "Gold"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 61, DAT_ButtonX::instance + 10,
                            DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB,
                            18, FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                            DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                            DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                        return;
                    }
                    // "Gold"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 61, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_CopyOfScenarioGold::instance,
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    return;
                }
                if (button == 166) {
                    // "No rations" to "Extra rations"
                    int const rationsTextID
                        = DAT_MissionAestheticsDefinedData::instance
                              .field_0x3448[DAT_GameState::instance.mapAndTime.scenarioRationsSetting];
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, rationsTextID,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, rationsTextID,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    return;
                }
                if (button == 167) {
                    // the tax names start at 7, "Generous bribe"
                    int const taxesTextID = DAT_GameState::instance.mapAndTime.scenarioTaxesSetting + 7;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_KEEP, taxesTextID,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_KEEP, taxesTextID,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                }
                return;
            }
            if (button == 168) {
                // only a siege map has the starting gold button
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // fixme: both states draw the label in COL_C2F0EB, the number in COL_CCFAFF; other buttons switch
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    // "Starting Gold"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 168, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance.SEC_StartingResources[OpenSHC::Game::Resources::RT_GOLD],
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                } else {
                    // "Starting Gold"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 168, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance.SEC_StartingResources[OpenSHC::Game::Resources::RT_GOLD],
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 72, DAT_ButtonX::instance + 10, DAT_ButtonY::instance);
                return;
            }
            if (button == 169) {
                // only a siege map has the starting pitch button
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // fixme: both states draw the label in COL_C2F0EB, the number in COL_CCFAFF; other buttons switch
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    // "Starting Pitch"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 169, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    // pitch is kept in the partial-pitch slot
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[OpenSHC::Game::Resources::RT_PARTIALPITCH],
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                } else {
                    // "Starting Pitch"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 169, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    // pitch is kept in the partial-pitch slot
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[OpenSHC::Game::Resources::RT_PARTIALPITCH],
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 58, DAT_ButtonX::instance + 10, DAT_ButtonY::instance);
                return;
            }
            // 42 "New Invasion" belongs to invasion maps
            if (button == 42 && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_INVASION) {
                return;
            }
            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                // a siege has no 38 "Trader" and no 79 "Popularity"
                if (button == 38 || button == 79) {
                    return;
                }
            } else if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_JUST_BUILD
                && (button == 42 || button == 17 || button == 43)) {
                // a just-build map has no 42 "New Invasion", 17 "New Message" or 43 "New Event"
                return;
            }
            if (button == 41) {
                // a siege shows "Attacking Force" (164) instead of "Start Goods"
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    button = 164;
                }
            } else if (button == 79) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    // "Popularity"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                        DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    return;
                }
                // "Popularity"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                    DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                return;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
        }

    }
}
}
