#include "../SiegeAttackingForceAndStartGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004C0CF0
        void SiegeAttackingForceAndStartGoods::MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main(
            int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            uint uVar4;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (param_1 < 0) {
                iVar1 = -param_1;
                iVar3 = iVar1 + -1;
                if (iVar3 < 0x14) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                            uVar4 = 0xc2f0eb;
                        } else {
                            uVar4 = 0xccfaff;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance.SEC_StartingResources[*(
                                int*)((int)DAT_MissionAestheticsDefinedData::ptr + iVar3 * 4 + 0x345c)],
                            (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, uVar4, 0x12, FALSE, 0);
                        iVar1 = *(int*)((int)DAT_MissionAestheticsDefinedData::ptr + iVar3 * 4 + 0x345c) * 2 + 0x8d;
                        if (iVar1 == 0x9d) {
                            iVar1 = 0x9b;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1,
                            (int)((int)(DAT_ButtonX::instance + 10)),
                            (DAT_ButtonY::instance
                                - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                                      + (GMTotalPicturesProcessed::instance[0x2e] + iVar1) * 0x10 + 0x72)
                                    / 2)
                                + 0xf);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    return;
                }
                if (iVar3 < 0x1e) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        uVar4 = 0xc2f0eb;
                        iVar2 = *(int*)((int)DAT_MapPropertiesState::ptr + iVar3 * 4 + 0x9c);
                    } else {
                        uVar4 = 0xccfaff;
                        iVar2 = *(int*)((int)DAT_MapPropertiesState::ptr + iVar3 * 4 + 0x9c);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar2,
                        (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, uVar4, 0x12, FALSE, 0);
                    iVar2 = iVar1 + -0x14;
                    if (iVar3 == 0x1d) {
                        iVar2 = iVar1 + -0x13;
                    }
                } else {
                    if (iVar3 == 0x1e) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                            uVar4 = 0xc2f0eb;
                        } else {
                            uVar4 = 0xccfaff;
                        }
                        /*
                          added by script: "Popularity"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x4f,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, uVar4, 0x12, FALSE);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    if (9 < iVar1 - 0x29U) {
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
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        uVar4 = 0xc2f0eb;
                        iVar2 = *(int*)((int)DAT_MapPropertiesState::ptr + iVar3 * 4 + 0x9c);
                    } else {
                        uVar4 = 0xccfaff;
                        iVar2 = *(int*)((int)DAT_MapPropertiesState::ptr + iVar3 * 4 + 0x9c);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar2,
                        (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_RIGHT, uVar4, 0x12, FALSE, 0);
                    iVar2 = iVar1 + -0x1d;
                    if (iVar3 == 0x2d) {
                        iVar2 = 10;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, iVar2,
                    (int)((int)(DAT_ButtonX::instance)),
                    (DAT_ButtonY::instance
                        - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMTotalPicturesProcessed::instance[0xae] + iVar2) * 0x10 + 0x72)
                            / 2)
                        + 0xf);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (param_1 < 1000) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_BLUE::instance.shortValue)), OpenSHC::UI::Enums::RBERL_SLIGHT);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)), OpenSHC::UI::Enums::RBERL_SLIGHT);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }

    }
}
}
