#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Synchrony/Commands.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::DE::SHCDE::eGM;
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
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043A9F0
    void BuildingMenus::RenderBuildingMenu_Keep()
    {
        char* _textAddress;
        int _displayNumber;
        int iVar3;
        int iVar4;
        TextAlignment _alignment;
        int _blendStrength;
        BGR24 _color;
        int _fontSize;
        BOOLEnum _keepOffsetX;
        int _xPos;
        iVar4 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        _displayNumber = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf];
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .timeTaxesOrRationsChange
            != 0) {
            DWORD DVar2 = timeGetTime();
            if (2000 < DVar2 - DAT_GameState::instance.playerDataArray[iVar4].timeTaxesOrRationsChange) {
                iVar3 = DAT_GameState::instance.playerDataArray[iVar4].taxesSliderUI;
                if (iVar3 < 3) {
                    iVar3 = 2;
                } else if (iVar3 < 5) {
                    iVar3 = 1;
                } else {
                    iVar3 = 3;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(iVar3);
            }
            DVar2 = timeGetTime();
            if (0x9c4 < DVar2 - DAT_GameState::instance.playerDataArray[iVar4].timeTaxesOrRationsChange) {
                iVar3 = DAT_GameState::instance.playerDataArray[iVar4].taxesSliderUI;
                DAT_GameState::instance.playerDataArray[iVar4].timeTaxesOrRationsChange = 0;
                if (8 < iVar3) {
                    iVar3 = iVar3 + -1;
                }
                if (6 < iVar3) {
                    iVar3 = iVar3 + -1;
                }
                if (4 < iVar3) {
                    iVar3 = iVar3 + -1;
                }
                if (0 < iVar3) {
                    iVar3 = iVar3 + -1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SpeechEffectID)(iVar3 + OpenSHC::Audio::SFX::SEID_TAXES_RATE1));
            }
        }
        iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[_displayNumber].buildingType;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (iVar3 - 0x47U <= 2) {
            iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[_displayNumber].quarryStockpileID;
            if ((iVar3 != 0)
                && (DAT_BuildingsState::instance.buildings[iVar3].uid
                    == DAT_BuildingsState::instance.buildings[_displayNumber].uidWhenPlaced)) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_IN_KEEP,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar3].buildingType * 2 + -0x50),
                    DAT_MenuHandlerState::instance.x + 0x19, DAT_MenuHandlerState::instance.y + 0x1d3,
                    OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE);
            }
        } else {
            _blendStrength = 0;
            _keepOffsetX = FALSE;
            _fontSize = 0x10;
            _color = 0;
            _alignment = OpenSHC::Text::TTA_LEFT;
            _displayNumber = DAT_MenuHandlerState::instance.y + 0x1d3;
            _xPos = DAT_MenuHandlerState::instance.x + 0x19;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, iVar3 * 2 + -0x50),
                _xPos, _displayNumber, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
        }
        _displayNumber = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .taxesSliderUI;
        _blendStrength = 0;
        _keepOffsetX = FALSE;
        _fontSize = 0x12;
        _color = 0;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x237;
        _alignment = OpenSHC::Text::TTA_LEFT;
        _xPos = DAT_MenuHandlerState::instance.x + 0xf0;
        if (_displayNumber < 3) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, _displayNumber + 7),
                _xPos, iVar3, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[iVar4].currentPopulation,
                DAT_MenuHandlerState::instance.x + 300, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7f,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x136 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1db);
            DAT_TextManagerObject::instance.currentXOffset_0x0 = DAT_TextManagerObject::instance.currentXOffset_0x0
                + DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x2e] + 0x7e].width;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(" = ",
                DAT_MenuHandlerState::instance.x + 0x140, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _xPos = DAT_MenuHandlerState::instance.y + 0x1e3;
            iVar3 = DAT_MenuHandlerState::instance.x + 0x14a;
            _displayNumber = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getNumberToDisplayBribeIncome,
                DAT_GameState::ptr)(iVar4, DAT_GameState::instance.playerDataArray[iVar4].taxesSliderUI,
                DAT_GameState::instance.playerDataArray[iVar4].currentPopulation);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                -_displayNumber, iVar3, _xPos, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _displayNumber
                = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x154 + DAT_MenuHandlerState::instance.x;
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, _displayNumber + 7),
                _xPos, iVar3, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[iVar4].currentPopulation,
                DAT_MenuHandlerState::instance.x + 300, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7f,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x136 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1db);
            DAT_TextManagerObject::instance.currentXOffset_0x0 = DAT_TextManagerObject::instance.currentXOffset_0x0
                + DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x2e] + 0x7e].width;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(" = ",
                DAT_MenuHandlerState::instance.x + 0x140, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _xPos = DAT_MenuHandlerState::instance.y + 0x1e3;
            iVar3 = DAT_MenuHandlerState::instance.x + 0x14a;
            _displayNumber
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getNumberToDisplayPlayerTaxIncome,
                    DAT_GameState::ptr)(iVar4, DAT_GameState::instance.playerDataArray[iVar4].taxesSliderUI,
                    DAT_GameState::instance.playerDataArray[iVar4].currentPopulation);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _displayNumber, iVar3, _xPos, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _displayNumber
                = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x154 + DAT_MenuHandlerState::instance.x;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c, _displayNumber, DAT_MenuHandlerState::instance.y + 0x1e1);
        iVar4 = 0x12;
        _displayNumber = 0;
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI
                    + 7),
            iVar4);
        if (0xbe < iVar4) {
            _displayNumber = iVar4 + -0xbe;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            iVar3 = 0;
        } else {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI;
            if ((2 < iVar4) || (0 < iVar1)) {
                if (iVar4 == 0) {
                    iVar3 = 0xaf;
                } else if (iVar4 == 1) {
                    iVar3 = 0x7d;
                } else if (iVar4 == 2) {
                    iVar3 = 0x4b;
                } else if (iVar4 != 3) {
                    if (iVar4 == 4) {
                        iVar3 = -0x32;
                    } else if (iVar4 == 5) {
                        iVar3 = -100;
                    } else if (iVar4 == 6) {
                        iVar3 = -0x96;
                    } else if (iVar4 == 7) {
                        iVar3 = -200;
                    } else if (iVar4 == 8) {
                        iVar3 = -300;
                    } else if (iVar4 == 9) {
                        iVar3 = -400;
                    } else if (iVar4 == 10) {
                        iVar3 = -500;
                    } else {
                        iVar3 = -600;
                        if (iVar4 != 0xb) {
                            iVar3 = iVar1;
                        }
                    }
                } else {
                    iVar3 = 0x19;
                }
            } else {
                iVar3 = 0x19;
            }
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 0x1cc + _displayNumber, DAT_MenuHandlerState::instance.y + 0x237, iVar3,
            FALSE);
        MACRO_CALL(OpenSHC::Synchrony::Commands_Func::QueueChangeTaxes)();
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
