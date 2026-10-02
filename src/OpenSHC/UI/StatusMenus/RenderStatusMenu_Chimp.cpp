#include "../StatusMenus.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b6c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/INT_00b96124.hpp"
#include "OpenSHC/Globals/INT_00b98458.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Rendering::Colors::BGR24;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00447A50
    void StatusMenus::RenderStatusMenu_Chimp()
    {
        byte bVar1;
        char (*pacVar2)[32];
        int _yParam;
        char* pcVar3;
        int _xParam;
        int numInGroup;
        bool bVar4;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        int _unitID;
        _unitID = DAT_BuildingsState::instance.menuSelectedUnitID;
        if (DAT_BuildingsState::instance.menuSelectedUnitID != 0) {
            numInGroup
                = (int)(short)DAT_UnitsState::instance.units[DAT_BuildingsState::instance.menuSelectedUnitID].unitType;
            if (numInGroup == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(
                DAT_BuildingsState::instance.menuSelectedUnitID);
            bVar4 = _unitID != INT_00b96124::instance;
            if (bVar4) {
                INT_00b96124::instance = _unitID;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                1, DAT_MenuHandlerState::instance.x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x11;
            color = 0;
            _yParam = DAT_MenuHandlerState::instance.y + 0x1e1;
            alignment = OpenSHC::Text::TTA_LEFT;
            _xParam = DAT_MenuHandlerState::instance.x + 0x8c;
            if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_GHOST) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_CHIMP_NAMES, numInGroup), _xParam, _yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, (int)((int)((char)DAT_UnitsState::instance.units[_unitID].firstNameIndex))), _xParam, _yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                bVar1 = DAT_UnitsState::instance.units[_unitID].rng1_to_70;
                if (bVar1 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, (int)((int)((char)bVar1)),
                        DAT_MenuHandlerState::instance.x + 0x91, DAT_MenuHandlerState::instance.y + 0x1e1,
                        OpenSHC::Text::TTA_LEFT, 0, 0x11, TRUE);
                }
                if ((((numInGroup != 0x33) && (numInGroup != 0x3e)) && (numInGroup != 0x34))
                    && ((numInGroup != 9 && (numInGroup != 0x2b)))) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_CHIMP_NAMES, numInGroup, DAT_MenuHandlerState::instance.x + 0xa0,
                        DAT_MenuHandlerState::instance.y + 0x1e6, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPeasantMenu_CurrentActionUnk)(
                _unitID, DAT_MenuHandlerState::instance.x + 0x8c, DAT_MenuHandlerState::instance.y + 0x209);
            if (((((numInGroup != 0x38) && (numInGroup != 0x37))
                     && ((numInGroup != 0x33 && (((numInGroup != 0x3e && (numInGroup != 0x34)) && (numInGroup != 9))))))
                    && ((numInGroup != 0x2b && (numInGroup != 0x43))))
                && ((numInGroup != 0x42
                    && (((numInGroup != 0x41 && (numInGroup != 0x23))
                        && ((numInGroup != 0x36 && (numInGroup != 0x40)))))))) {
                if (DAT_00b95b6c::instance == -1) {
                    DAT_00b95b6c::instance
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectWorkerSpeechOrMoraleStateID,
                            DAT_UnitsState::ptr)(_unitID);
                }
                _yParam = DAT_00b95b6c::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_CHIMP_COMMENT, DAT_00b95b6c::instance,
                    DAT_MenuHandlerState::instance.x + 0x8c, DAT_MenuHandlerState::instance.y + 0x22d, 0x15e, 0, 0x12,
                    0);
                if (bVar4) {
                    if (((numInGroup == 0x15) || (numInGroup == 0x3f)) || (numInGroup == 0x11)) {
                        pacVar2 = DAT_RenderingDefinedData::instance.FemalePeasantSFXNames;
                    } else {
                        pacVar2 = DAT_RenderingDefinedData::instance.MalePeasantSFXNames;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                        pacVar2[_yParam]);
                    INT_00b98458::instance = _yParam;
                }
            }
        }
    }

}
}
