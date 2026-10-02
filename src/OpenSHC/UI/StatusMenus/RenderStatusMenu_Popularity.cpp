#include "../StatusMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043E6C0
    void StatusMenus::RenderStatusMenu_Popularity()
    {
        short sVar1;
        short sVar2;
        short sVar3;
        short sVar4;
        short sVar5;
        short sVar6;
        int iVar7;
        char* pcVar8;
        int iVar9;
        uint uVar10;
        uint uVar11;
        int iVar12;
        byte bVar13;
        TextAlignment TVar14;
        BGR24 BVar15;
        int iVar16;
        int iVar17;
        int iVar18;
        int iVar19;
        BOOLEnum BVar20;
        int iVar21;
        int iVar22;
        int local_2c;
        int local_1c;
        uint local_18;
        uint local_14;
        uint local_10;
        uint local_c;
        uint local_8;
        uint local_4;
        iVar12 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                     .currentResources[0xf];
        iVar21 = 0;
        BVar20 = FALSE;
        iVar16 = 0x11;
        BVar15 = 0;
        TVar14 = OpenSHC::Text::TTA_LEFT;
        iVar7 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar9 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Popularity"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 1),
            iVar9, iVar7, TVar14, BVar15, iVar16, BVar20, iVar21);
        BVar20 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                     .areCarnivalUnitsPresent;
        bVar13 = BVar20 != FALSE;
        if ((bool)bVar13) {
            local_1c = 0;
        }
        uVar11 = (uint)bVar13;
        sVar1
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount58;
        uVar10 = uVar11;
        if (sVar1 != 0) {
            bVar13 = bVar13 + 1;
            uVar10 = uVar11 + 1;
            local_18 = uVar11;
        }
        sVar2
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount59;
        uVar11 = uVar10;
        if (sVar2 != 0) {
            bVar13 = bVar13 + 1;
            uVar11 = uVar10 + 1;
            local_14 = uVar10;
        }
        sVar3
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount54;
        uVar10 = uVar11;
        if (sVar3 != 0) {
            bVar13 = bVar13 + 1;
            uVar10 = uVar11 + 1;
            local_10 = uVar11;
        }
        sVar4
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount55;
        uVar11 = uVar10;
        if (sVar4 != 0) {
            bVar13 = bVar13 + 1;
            uVar11 = uVar10 + 1;
            local_c = uVar10;
        }
        sVar5
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount56;
        uVar10 = uVar11;
        if (sVar5 != 0) {
            bVar13 = bVar13 + 1;
            uVar10 = uVar11 + 1;
            local_8 = uVar11;
        }
        sVar6
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount57;
        if (sVar6 != 0) {
            bVar13 = bVar13 + 1;
            local_4 = uVar10;
        }
        DAT_GameCore::instance.field78_0x148 = (2 < bVar13) + 1;
        if (DAT_GameCore::instance.field78_0x148 <= DAT_GameCore::instance.field77_0x144) {
            DAT_GameCore::instance.field77_0x144 = 0;
        }
        local_2c = (int)sVar6 + (int)sVar5 + (int)sVar4 + (int)sVar3 + (int)sVar2 + (int)sVar1;
        if (BVar20 != FALSE) {
            local_2c = local_2c + 400;
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar21 = 0x12;
            iVar9 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 0x1db);
            iVar16 = DAT_MenuHandlerState::instance.x + 0xc1;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar7 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Food"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 5),
                iVar16, iVar9, TVar14, BVar15, iVar21, BVar20, iVar7);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            uVar10 = 0;
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .foodTypesInStock
            == 0) {
            uVar10 = 0xffffff38;
        } else {
            iVar7 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .rationsSetting;
            if (iVar7 == 4) {
                uVar10 = 200;
            } else if (iVar7 == 3) {
                uVar10 = 100;
            } else if (iVar7 == 2) {
                uVar10 = 0;
            } else if (iVar7 == 1) {
                uVar10 = 0xffffff9c;
            } else {
                uVar10 = 0xffffff38;
                if (iVar7 != 0) {
                    uVar10 = local_4;
                }
            }
        }
        iVar7 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .foodTypesCurrentlyEaten;
        if ((iVar7 != 0) && (iVar7 != 1)) {
            if (iVar7 == 2) {
                uVar10 = uVar10 + 0x19;
            } else if (iVar7 == 3) {
                uVar10 = uVar10 + 0x32;
            } else if (iVar7 == 4) {
                uVar10 = uVar10 + 0x4b;
            }
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0xab, DAT_MenuHandlerState::instance.y + 0x1da, (int)((int)(uVar10)),
                FALSE);
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar21 = 0x12;
            iVar9 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 499);
            iVar16 = DAT_MenuHandlerState::instance.x + 0xc1;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar7 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Tax"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 6),
                iVar16, iVar9, TVar14, BVar15, iVar21, BVar20, iVar7);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            iVar12 = 0;
        } else if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .taxesSliderUI
                       < 3)
            && (iVar12 < 1)) {
            iVar12 = 0x19;
        } else {
            iVar12 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                         .taxesSetting;
            if (iVar12 == 0) {
                iVar12 = 0xaf;
            } else if (iVar12 == 1) {
                iVar12 = 0x7d;
            } else if (iVar12 == 2) {
                iVar12 = 0x4b;
            } else if (iVar12 == 3) {
                iVar12 = 0x19;
            } else if (iVar12 == 4) {
                iVar12 = -0x32;
            } else if (iVar12 == 5) {
                iVar12 = -100;
            } else if (iVar12 == 6) {
                iVar12 = -0x96;
            } else if (iVar12 == 7) {
                iVar12 = -200;
            } else if (iVar12 == 8) {
                iVar12 = -300;
            } else if (iVar12 == 9) {
                iVar12 = -400;
            } else {
                iVar12 = (-(uint)(iVar12 != 10) & 0xffffff9c) - 500;
            }
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0xab, DAT_MenuHandlerState::instance.y + 0x1f2, iVar12, FALSE);
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar21 = 0x12;
            iVar9 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 0x20b);
            iVar16 = DAT_MenuHandlerState::instance.x + 0xc1;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar7 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Crowding"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 7),
                iVar16, iVar9, TVar14, BVar15, iVar21, BVar20, iVar7);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            iVar7 = 0;
        } else {
            iVar7 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .crowding;
            if (iVar7 < 0x65) {
                iVar7 = 0;
            } else if (iVar7 < 0x79) {
                iVar7 = -0x32;
            } else if (iVar7 < 0x8d) {
                iVar7 = -100;
            } else if (iVar7 < 0xa1) {
                iVar7 = -0x96;
            } else {
                iVar7 = ((0xb4 < iVar7) - 1 & 0x32) - 0xfa;
            }
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0xab, DAT_MenuHandlerState::instance.y + 0x20a, iVar7, FALSE);
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar17 = 0x12;
            iVar16 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 0x223);
            iVar21 = DAT_MenuHandlerState::instance.x + 0xc1;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar9 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Fear Factor"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 0xc),
                iVar21, iVar16, TVar14, BVar15, iVar17, BVar20, iVar9);
        }
        uVar11 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                     .fearFactorLevel;
        if ((int)uVar11 <= 0) {
            if (uVar11 < 0x80000000) {
                iVar9 = 0;
            } else {
                iVar9 = uVar11 * 0x19;
            }
        } else {
            iVar9 = uVar11 * 0x19;
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0xab, DAT_MenuHandlerState::instance.y + 0x222, iVar9, FALSE);
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar18 = 0x12;
            iVar21 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 0x1db);
            iVar17 = DAT_MenuHandlerState::instance.x + 0x163;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar16 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Religion"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 10),
                iVar17, iVar21, TVar14, BVar15, iVar18, BVar20, iVar16);
        }
        iVar16 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                     .blessedPeoplePercentage;
        if (iVar16 < 0x19) {
            iVar16 = 0;
        } else if (iVar16 < 0x32) {
            iVar16 = 0x32;
        } else if (iVar16 < 0x4b) {
            iVar16 = 100;
        } else {
            iVar16 = ((0x5e < iVar16) - 1 & 0xffffffce) + 200;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ownsChurchUnk
            != 0) {
            iVar16 = iVar16 + 0x19;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .ownsCathedralUnk
            != 0) {
            iVar16 = iVar16 + 0x32;
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0x14d, DAT_MenuHandlerState::instance.y + 0x1da, iVar16, FALSE);
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            iVar19 = 0x12;
            iVar17 = (OpenSHC::Text::TextAlignment)(DAT_MenuHandlerState::instance.y + 499);
            iVar18 = DAT_MenuHandlerState::instance.x + 0x163;
            TVar14 = (OpenSHC::Text::TextAlignment)(DAT_GameCore::instance.field77_0x144);
            BVar15 = DAT_GameCore::instance.field77_0x144;
            BVar20 = DAT_GameCore::instance.field77_0x144;
            iVar21 = DAT_GameCore::instance.field77_0x144;
            /*
              added by script: "Ale coverage"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 0xb),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar21);
        }
        iVar21 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage, DAT_GameState::ptr)(
            DAT_GameSynchronyState::instance.currentPlayerSlotID);
        if (iVar21 < 0x19) {
            iVar21 = 0;
        } else if (iVar21 < 0x32) {
            iVar21 = 0x32;
        } else if (iVar21 < 0x4b) {
            iVar21 = 100;
        } else {
            iVar21 = ((99 < iVar21) - 1 & 0xffffffce) + 200;
        }
        if (DAT_GameCore::instance.field77_0x144 == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 0x14d, DAT_MenuHandlerState::instance.y + 0x1f2, iVar21, FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .areCarnivalUnitsPresent
                != FALSE)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_1c][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_1c][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_1c][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Fair"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 9),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(DAT_MenuHandlerState::instance.x
                    + -0x16 + DAT_RenderingDefinedData::instance.field1049_0x556cc[local_1c][1],
                (int)((int)(DAT_MenuHandlerState::instance.y + -1
                    + DAT_RenderingDefinedData::instance.field1049_0x556cc[local_1c][2])),
                400, FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount58
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_18][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_18][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_18][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Marriage"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x95),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_18][1] + -0x16
                    + DAT_MenuHandlerState::instance.x,
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_18][2] + -1
                    + DAT_MenuHandlerState::instance.y,
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount58)),
                FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount59
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_14][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_14][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_14][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Jester"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x96),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_14][1] + -0x16
                    + DAT_MenuHandlerState::instance.x,
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_14][2] + -1
                    + DAT_MenuHandlerState::instance.y,
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount59)),
                FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount54
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_10][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_10][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_10][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Plague"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x8b),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_10][1] + -0x16
                    + DAT_MenuHandlerState::instance.x,
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_10][2] + -1
                    + DAT_MenuHandlerState::instance.y,
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount54)),
                FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount55
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_c][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_c][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_c][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Lion Attack"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x91),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(DAT_MenuHandlerState::instance.x
                    + -0x16 + DAT_RenderingDefinedData::instance.field1049_0x556cc[local_c][1],
                (int)((int)(DAT_MenuHandlerState::instance.y + -1
                    + DAT_RenderingDefinedData::instance.field1049_0x556cc[local_c][2])),
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount55)),
                FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount56
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_8][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_8][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_8][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Bandits"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x92),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_8][1] + -0x16
                    + DAT_MenuHandlerState::instance.x,
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_8][2] + -1
                    + DAT_MenuHandlerState::instance.y,
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount56)),
                FALSE);
        }
        if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount57
                != 0)
            && (DAT_RenderingDefinedData::instance.field1049_0x556cc[local_4][0]
                == DAT_GameCore::instance.field77_0x144)) {
            iVar17
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_4][2] + DAT_MenuHandlerState::instance.y;
            iVar18
                = DAT_RenderingDefinedData::instance.field1049_0x556cc[local_4][1] + DAT_MenuHandlerState::instance.x;
            iVar22 = 0;
            BVar20 = FALSE;
            iVar19 = 0x12;
            BVar15 = 0;
            TVar14 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Fire!"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xb3),
                iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_4][1] + -0x16
                    + DAT_MenuHandlerState::instance.x,
                DAT_RenderingDefinedData::instance.field1049_0x556cc[local_4][2] + -1
                    + DAT_MenuHandlerState::instance.y,
                (int)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount57)),
                FALSE);
        }
        iVar22 = 0;
        BVar20 = FALSE;
        iVar19 = 0x12;
        BVar15 = 0;
        TVar14 = OpenSHC::Text::TTA_LEFT;
        iVar17 = DAT_MenuHandlerState::instance.y + 0x241;
        iVar18 = DAT_MenuHandlerState::instance.x + 0xdc;
        /*
          added by script: "In the coming month"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 4),
            iVar18, iVar17, TVar14, BVar15, iVar19, BVar20, iVar22);
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xfa + DAT_MenuHandlerState::instance.x,
            DAT_MenuHandlerState::instance.y + 0x241, local_2c + uVar10 + iVar12 + iVar7 + iVar9 + iVar16 + iVar21,
            TRUE);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
