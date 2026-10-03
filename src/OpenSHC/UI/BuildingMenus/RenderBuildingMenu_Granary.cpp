#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::Graphics::GmID;
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
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043B3B0
    void BuildingMenus::RenderBuildingMenu_Granary()
    {
        char* pcVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        SpeechEffectID SVar7;
        TextAlignment TVar8;
        BGR24 BVar9;
        int iVar10;
        BOOLEnum BVar11;
        int iVar12;
        int blendStrength;
        int iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        iVar5 = 0;
        iVar6 = 0;
        INT_00b96120::instance = 4;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .timeTaxesOrRationsChange
            != 0) {
            DWORD DVar2 = timeGetTime();
            if (2000 < DVar2 - DAT_GameState::instance.playerDataArray[iVar1].timeTaxesOrRationsChange) {
                iVar12 = DAT_GameState::instance.playerDataArray[iVar1].rationsSetting3;
                if (iVar12 == 4) {
                    iVar12 = 2;
                } else if (iVar12 == 0) {
                    iVar12 = 3;
                } else {
                    iVar12 = 1;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(iVar12);
            }
            DVar2 = timeGetTime();
            if (2500 < DVar2 - DAT_GameState::instance.playerDataArray[iVar1].timeTaxesOrRationsChange) {
                iVar12 = DAT_GameState::instance.playerDataArray[iVar1].rationsSetting3;
                DAT_GameState::instance.playerDataArray[iVar1].timeTaxesOrRationsChange = 0;
                switch (iVar12) {
                case 0:
                    SVar7 = OpenSHC::Audio::SFX::SEID_FOOD_NONE;
                    break;
                case 1:
                    SVar7 = OpenSHC::Audio::SFX::SEID_FOOD_HALF;
                    break;
                case 2:
                    SVar7 = OpenSHC::Audio::SFX::SEID_FOOD_NORMAL;
                    break;
                case 3:
                    SVar7 = OpenSHC::Audio::SFX::SEID_FOOD_EXTRA;
                    break;
                case 4:
                    SVar7 = OpenSHC::Audio::SFX::SEID_FOOD_DOUBLE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(SVar7);
            }
        }
        blendStrength = 0;
        BVar11 = FALSE;
        iVar10 = 0x10;
        BVar9 = 0;
        TVar8 = OpenSHC::Text::TTA_LEFT;
        iVar12 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Granary"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 0),
            iVar4, iVar12, TVar8, BVar9, iVar10, BVar11, blendStrength);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        switch (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .rationsSetting3) {
        case 0:
            iVar6 = -1;
            iVar5 = -5;
            SVar7 = ((SpeechEffectID)0x11f);
            break;
        case 1:
            iVar6 = -1;
            iVar5 = 1;
            SVar7 = ((SpeechEffectID)0x120);
            break;
        case 2:
            iVar6 = 10;
            iVar5 = -10;
            SVar7 = ((SpeechEffectID)0x11c);
            break;
        case 3:
            iVar6 = 0;
            iVar5 = 0;
            SVar7 = ((SpeechEffectID)0x11d);
            break;
        case 4:
            iVar6 = 9;
            iVar5 = -5;
            SVar7 = ((SpeechEffectID)0x11e);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, (int)(SVar7), DAT_MenuHandlerState::instance.x + 0x159 + iVar6,
            DAT_MenuHandlerState::instance.y + 0x20f + iVar5);
        iVar12 = DAT_MenuHandlerState::instance.y;
        iVar6 = DAT_MenuHandlerState::instance.x;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x17;
        iVar5 = DAT_MenuHandlerState::instance.y + 0x1f2;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_SLIDER, 6, DAT_MenuHandlerState::instance.x + 0x1f, iVar5);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect, DAT_TextureRenderCoreObject::ptr)(0, 0,
            (DAT_GameState::instance.playerDataArray[iVar1].foodClock * 162) / 15000 + 0x10 + iVar4,
            DAT_WindowAndDirectDraw::instance.resolutionY);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 8, iVar6 + 0x1f, iVar5);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
            DAT_TextureRenderCoreObject::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 5, iVar4, iVar12 + 0x1ed,
            OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 7, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[iVar1].totalFood, DAT_MenuHandlerState::instance.x + 0x18,
            DAT_MenuHandlerState::instance.y + 0x210, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        iVar4 = 0;
        BVar11 = TRUE;
        iVar12 = 0x12;
        iVar5 = DAT_MenuHandlerState::instance.y + 0x210;
        iVar6 = DAT_MenuHandlerState::instance.x + 0x1c;
        BVar9 = 0;
        TVar8 = OpenSHC::Text::TTA_LEFT;
        if (DAT_GameState::instance.playerDataArray[iVar1].totalFood == 1) {
            iVar10 = 2;
        } else {
            iVar10 = 1;
        }
        /*
          added by script: "unit of food."
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar10),
            iVar6, iVar5, TVar8, BVar9, iVar12, BVar11, iVar4);
        iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .rationsSetting3;
        if (iVar5 == 3) {
            iVar5 = 0xc;
        } else if (iVar5 == 4) {
            iVar5 = 6;
        } else {
            iVar5 = iVar5 + 3;
        }
        iVar10 = 0;
        BVar11 = FALSE;
        iVar4 = 0x12;
        BVar9 = 0;
        TVar8 = OpenSHC::Text::TTA_RIGHT;
        iVar6 = DAT_MenuHandlerState::instance.y + 0x1d1;
        iVar12 = DAT_MenuHandlerState::instance.x + 0x21c;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar5),
            iVar12, iVar6, TVar8, BVar9, iVar4, BVar11, iVar10);
        if (DAT_GameState::instance.playerDataArray[iVar1].currentPopulation == 0) {
            SVar7 = OpenSHC::Audio::SFX::SEID_GENERAL_STARTGAME;
        } else if (DAT_GameState::instance.playerDataArray[iVar1].foodTypesInStock == 0) {
            SVar7 = ((SpeechEffectID)0xffffff38);
        } else {
            iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .rationsSetting3;
            if (iVar5 == 4) {
                SVar7 = ((SpeechEffectID)200);
            } else if (iVar5 == 3) {
                SVar7 = (OpenSHC::Audio::SFX::SpeechEffectID)(OpenSHC::Audio::SFX::SEID_GENERAL_MESSAGE3
                    | OpenSHC::Audio::SFX::SEID_TAXES_RATE7);
            } else if (iVar5 == 2) {
                SVar7 = OpenSHC::Audio::SFX::SEID_GENERAL_STARTGAME;
            } else if (iVar5 == 1) {
                SVar7 = (OpenSHC::Audio::SFX::SpeechEffectID)(~(
                    OpenSHC::Audio::SFX::SEID_GENERAL_MESSAGE3 | OpenSHC::Audio::SFX::SEID_TAXES_RATE6));
            } else {
                SVar7 = ((SpeechEffectID)0xffffff38);
                if (iVar5 != 0) {}
            }
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 0x208, DAT_MenuHandlerState::instance.y + 0x1e3, (int)(SVar7), FALSE);
        iVar5 = DAT_GameState::instance.playerDataArray[iVar1].foodStorageLevel;
        if (iVar5 != -1) {
            if (iVar5 == 0) {
                iVar5 = DAT_MenuHandlerState::instance.y + 0x224;
                iVar6 = DAT_MenuHandlerState::instance.x + 0xe;
                iVar12 = 0xb;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    iVar5, DAT_MenuHandlerState::instance.x + 0x18, DAT_MenuHandlerState::instance.y + 0x224,
                    OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
                iVar5 = DAT_MenuHandlerState::instance.y + 0x224;
                iVar6 = DAT_MenuHandlerState::instance.x + 0x1c;
                if (DAT_GameState::instance.playerDataArray[iVar1].foodStorageLevel == 1) {
                    iVar12 = 10;
                } else {
                    iVar12 = 9;
                }
            }
            iVar10 = 0;
            BVar11 = TRUE;
            iVar4 = 0x12;
            BVar9 = 0;
            TVar8 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "month supply."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar12),
                iVar6, iVar5, TVar8, BVar9, iVar4, BVar11, iVar10);
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[iVar1].foodTypesCurrentlyEaten,
            DAT_MenuHandlerState::instance.x + 0x18, DAT_MenuHandlerState::instance.y + 0x238, OpenSHC::Text::TTA_LEFT,
            0, 0x12, FALSE, 0);
        iVar4 = 0;
        BVar11 = TRUE;
        iVar12 = 0x12;
        BVar9 = 0;
        iVar5 = DAT_MenuHandlerState::instance.y + 0x238;
        TVar8 = OpenSHC::Text::TTA_LEFT;
        iVar6 = DAT_MenuHandlerState::instance.x + 0x1c;
        if (DAT_GameState::instance.playerDataArray[iVar1].foodTypesCurrentlyEaten == 1) {
            /*
              added by script: "food type eaten."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 8),
                iVar6, iVar5, TVar8, BVar9, iVar12, BVar11, iVar4);
            iVar5 = 8;
        } else {
            /*
              added by script: "food types eaten."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 7),
                iVar6, iVar5, TVar8, BVar9, iVar12, BVar11, iVar4);
            iVar5 = 7;
        }
        iVar6 = 0x12;
        /*
          added by script: "food type eaten."
         */
        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, iVar5),
            iVar6);
        iVar5 = DAT_GameState::instance.playerDataArray[iVar1].foodTypesCurrentlyEaten;
        if ((iVar5 == 0) || (iVar5 == 1)) {
            SVar7 = OpenSHC::Audio::SFX::SEID_GENERAL_STARTGAME;
        } else if (iVar5 == 2) {
            SVar7 = OpenSHC::Audio::SFX::SEID_TAXES_CONSTANT;
        } else if (iVar5 == 3) {
            SVar7 = OpenSHC::Audio::SFX::SEID_RESOURCE_NEED8;
        } else if (iVar5 == 4) {
            SVar7 = (OpenSHC::Audio::SFX::SpeechEffectID)(OpenSHC::Audio::SFX::SEID_GENERAL_MESSAGE3
                | OpenSHC::Audio::SFX::SEID_POP_POPULARITY3);
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 0x3c + iVar6, DAT_MenuHandlerState::instance.y + 0x238, (int)(SVar7),
            FALSE);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
