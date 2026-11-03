#include "../Rendering.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043CC30
    void Rendering::RenderPeasantMenu_CurrentActionUnk(int unitID, int xPos, int yPos)
    {
        ResourceType resource;
        int const actionText
            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getUnitStateTextParameterAndResourceType,
                DAT_UnitsState::ptr)(unitID, &resource);
        if (actionText <= 0) {
            return;
        }
        if (actionText == 10) {
            if (resource > 0) {
                // "Taking"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 101),
                    xPos, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, resource),
                    xPos + 5, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 102),
                    xPos + 10, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
                return;
            }
        } else if (actionText == 6) {
            if (resource > 0) {
                // "Returning with"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 100),
                    xPos, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, resource),
                    xPos + 5, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
                return;
            }
        } else if (actionText == 9) {
            if (resource > 0) {
                // "Going to get"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 103),
                    xPos, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GOODS, resource, xPos + 5, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE);
                return;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, actionText),
            xPos, yPos, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
    }

}
}
