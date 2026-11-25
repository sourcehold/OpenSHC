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

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // inlined copy of TextManager::renderTextFromTextGroup (0x00424470), which the original has inlined below.
    // Called through its resolver it stays a call, with /GL too.
    inline static void renderTextFromTextGroup(OpenSHC::DE::SHCDE::eTextSections group, int index, int x, int y,
        OpenSHC::Text::TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(group, index),
            x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x00447A50
    void StatusMenus::RenderStatusMenu_Chimp()
    {
        int const unitID = DAT_BuildingsState::instance.menuSelectedUnitID;
        if (unitID == 0) {
            return;
        }
        int const type = DAT_UnitsState::instance.units[unitID].unitType;
        // no unit in that slot any more: back to the build menu
        if (type == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            return;
        }
        // a newly shown unit (not the one shown last) speaks its comment (below)
        BOOLEnum newUnit = FALSE;
        // the result is not used: the original makes the call all the same
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(unitID);
        if (unitID != INT_00b96124::instance) {
            INT_00b96124::instance = unitID;
            newUnit = TRUE;
        }
        // 1: the unit type's sketch, which the menu's Prepare loads
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            1, DAT_MenuHandlerState::instance.x + 14, DAT_MenuHandlerState::instance.y + 489);
        // the first name, the surname if it has one, and the unit type (none for the five animals); a ghost has
        // its type only. The type is read from the unit again: the original compares it in memory here.
        if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_GHOST) {
            renderTextFromTextGroup(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES,
                DAT_UnitsState::instance.units[unitID].firstNameIndex, DAT_MenuHandlerState::instance.x + 140,
                DAT_MenuHandlerState::instance.y + 481, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
            char const surnameIndex = DAT_UnitsState::instance.units[unitID].rng1_to_70;
            if (surnameIndex != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, surnameIndex, DAT_MenuHandlerState::instance.x + 145,
                    DAT_MenuHandlerState::instance.y + 481, OpenSHC::Text::TTA_LEFT, 0, 17, TRUE);
            }
            if (type != OpenSHC::Map::Units::UT_COW && type != OpenSHC::Map::Units::UT_CHICKEN
                && type != OpenSHC::Map::Units::UT_HUNTERDOG && type != OpenSHC::Map::Units::UT_QUARRYOX
                && type != OpenSHC::Map::Units::UT_TRADERHORSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_CHIMP_NAMES, type, DAT_MenuHandlerState::instance.x + 160,
                    DAT_MenuHandlerState::instance.y + 486, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE);
            }
            // what the unit is doing; written in both arms, as the original evaluates the arguments in each
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPeasantMenu_CurrentActionUnk)(
                unitID, DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 521);
        } else {
            renderTextFromTextGroup(OpenSHC::DE::SHCDE::TEXT_CHIMP_NAMES, type, DAT_MenuHandlerState::instance.x + 140,
                DAT_MenuHandlerState::instance.y + 481, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPeasantMenu_CurrentActionUnk)(
                unitID, DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 521);
        }
        // the comment, chosen once per selected unit; these types have none
        if (type != OpenSHC::Map::Units::UT_LADY && type != OpenSHC::Map::Units::UT_LORD
            && type != OpenSHC::Map::Units::UT_COW && type != OpenSHC::Map::Units::UT_CHICKEN
            && type != OpenSHC::Map::Units::UT_HUNTERDOG && type != OpenSHC::Map::Units::UT_QUARRYOX
            && type != OpenSHC::Map::Units::UT_TRADERHORSE && type != OpenSHC::Map::Units::UT_CAGEDOG
            && type != OpenSHC::Map::Units::UT_FIREEATER && type != OpenSHC::Map::Units::UT_JUGGLER
            && type != OpenSHC::Map::Units::UT_DRUNK && type != OpenSHC::Map::Units::UT_GHOST
            && type != OpenSHC::Map::Units::UT_CHILD) {
            int commentID = DAT_00b95b6c::instance;
            if (commentID == -1) {
                commentID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectWorkerSpeechOrMoraleStateID,
                    DAT_UnitsState::ptr)(unitID);
                DAT_00b95b6c::instance = commentID;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_CHIMP_COMMENT, commentID, DAT_MenuHandlerState::instance.x + 140,
                DAT_MenuHandlerState::instance.y + 557, 350, 0, 18, 0);
            if (newUnit) {
                // the tanner, the mother and the brewer have the female voice
                if (type == OpenSHC::Map::Units::UT_TANNER || type == OpenSHC::Map::Units::UT_MOTHER
                    || type == OpenSHC::Map::Units::UT_BREWER) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                        DAT_RenderingDefinedData::instance.FemalePeasantSFXNames[commentID]);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                        DAT_RenderingDefinedData::instance.MalePeasantSFXNames[commentID]);
                }
                INT_00b98458::instance = commentID;
            }
        }
    }

}
}
