#include "../SiegeAttackingForceAndStartGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C0CF0
        void SiegeAttackingForceAndStartGoods::MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main(
            int button, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (button < 0) {
                // the negative buttons are the rows of the two lists
                int const index = -1 - button;
                if (index < 20) {
                    // a starting good: its amount and icon, on any map but a siege
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance.field_0x345c[index]],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance.field_0x345c[index]],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    }
                    int icon = DAT_MissionAestheticsDefinedData::instance.field_0x345c[index] * 2 + 141;
                    if (icon == 157) {
                        icon = 155;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, icon,
                        DAT_ButtonX::instance + 10,
                        DAT_ButtonY::instance
                            - DAT_GMImageHeaders::instance
                                    .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2] + icon
                                        - 1]
                                    .height
                                / 2
                            + 15);
                } else if (index < 30) {
                    // a unit of the attacking force, on a siege map
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance.SEC_SiegeInformation[index - 20],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance.SEC_SiegeInformation[index - 20],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    }
                    int imageID = index - 19;
                    if (index == 29) {
                        imageID = index - 18;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, imageID,
                        DAT_ButtonX::instance,
                        DAT_ButtonY::instance
                            - DAT_GMImageHeaders::instance
                                    .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_ARMY_UNITS] + imageID - 1]
                                    .height
                                / 2
                            + 15);
                } else if (index == 30) {
                    // "Popularity"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                            DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                            DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    }
                } else if (index >= 40 && index < 50) {
                    // a siege engine of the attacking force; row 46 reads tunnelersCount, which follows the engines
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[index - 40],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 8,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[index - 40],
                            DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 8,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    }
                    int imageID = index - 28;
                    if (index == 45) {
                        imageID = 10;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, imageID,
                        DAT_ButtonX::instance,
                        DAT_ButtonY::instance
                            - DAT_GMImageHeaders::instance
                                    .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_ARMY_UNITS] + imageID - 1]
                                    .height
                                / 2
                            + 15);
                }
            } else if (button < 1000) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
            } else if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonX::instance + DAT_ButtonW::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    OpenSHC::UI::Enums::RBERL_SLIGHT);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonX::instance + DAT_ButtonW::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
