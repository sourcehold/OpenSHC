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
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C0CF0
        void SiegeAttackingForceAndStartGoods::MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main(
            int param_1, ...)
        {
            int iVar2;
            uint uVar4;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (param_1 < 0) {
                int iVar1 = -param_1;
                int iVar3 = iVar1 - 1;
                if (iVar3 < 20) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                                DAT_MapPropertiesState::instance.SEC_StartingResources
                                    [DAT_MissionAestheticsDefinedData::instance.field_0x345c[iVar3]],
                                (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                        } else {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                                DAT_MapPropertiesState::instance.SEC_StartingResources
                                    [DAT_MissionAestheticsDefinedData::instance.field_0x345c[iVar3]],
                                (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        }
                        iVar1 = DAT_MissionAestheticsDefinedData::instance.field_0x345c[iVar3] * 2 + 141;
                        if (iVar1 == 157) {
                            iVar1 = 155;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1,
                            (int)(DAT_ButtonX::instance + 10),
                            (DAT_ButtonY::instance
                                - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                                      + (GMFirstPictureIndex::instance[46] + iVar1) * 16 + 114)
                                    / 2)
                                + 15);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    return;
                }
                if (iVar3 < 30) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        uVar4 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                        iVar2 = DAT_MapPropertiesState::instance.SEC_StartingResources[iVar3 + 5];
                    } else {
                        uVar4 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                        iVar2 = DAT_MapPropertiesState::instance.SEC_StartingResources[iVar3 + 5];
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(iVar2, (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance),
                        (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT, uVar4, 18, FALSE, 0);
                    iVar2 = iVar1 - 20;
                    if (iVar3 == 29) {
                        iVar2 = iVar1 - 19;
                    }
                } else {
                    if (iVar3 == 30) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            // added by script: "Popularity"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79,
                                (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_CENTER,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                        } else {
                            // added by script: "Popularity"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, 79,
                                (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_CENTER,
                                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                        }
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    if (iVar1 > 9 - 0x29U) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar2 = DAT_MapPropertiesState::instance.SEC_StartingResources[iVar3 + 5];
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar2,
                            (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar2,
                            (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    }
                    iVar2 = iVar1 - 29;
                    if (iVar3 == 45) {
                        iVar2 = 10;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, iVar2,
                    (int)(DAT_ButtonX::instance),
                    (DAT_ButtonY::instance
                        - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMFirstPictureIndex::instance[174] + iVar2) * 16 + 114)
                            / 2)
                        + 15);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (param_1 < 1000) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                    OpenSHC::UI::Enums::RBERL_SLIGHT);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
