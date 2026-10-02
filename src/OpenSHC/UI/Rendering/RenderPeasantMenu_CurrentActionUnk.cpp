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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043CC30
    void Rendering::RenderPeasantMenu_CurrentActionUnk(int unitID, int xPos, int yPos)
    {
        int _unitStateCategory;
        char* pcVar1;
        int iVar2;
        int iVar3;
        TextAlignment TVar4;
        BGR24 BVar5;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        ResourceType _entry;
        eTextSections _group;
        _unitStateCategory
            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getUnitStateTextParameterAndResourceType,
                DAT_UnitsState::ptr)(unitID, &_entry);
        if (_unitStateCategory < 1) {}
        if (_unitStateCategory == 10) {
            if ((int)_entry < 1)
                goto LAB_0043cd7c;
            iVar8 = 0;
            BVar7 = FALSE;
            iVar6 = 0x12;
            BVar5 = 0;
            TVar4 = OpenSHC::Text::TTA_LEFT;
            iVar2 = xPos;
            iVar3 = yPos;
            /*
              added by script: "Taking"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 0x65), iVar2, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
            iVar8 = 0;
            BVar7 = TRUE;
            iVar6 = 0x12;
            BVar5 = 0;
            TVar4 = OpenSHC::Text::TTA_LEFT;
            iVar2 = xPos + 5;
            iVar3 = yPos;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, (int)((int)(_entry))), iVar2, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
            BVar7 = TRUE;
            xPos = xPos + 10;
            _entry = ((ResourceType)0x66);
        } else {
            if (_unitStateCategory == 6) {
                if (0 < (int)_entry) {
                    iVar8 = 0;
                    BVar7 = FALSE;
                    iVar6 = 0x12;
                    BVar5 = 0;
                    TVar4 = OpenSHC::Text::TTA_LEFT;
                    iVar2 = xPos;
                    iVar3 = yPos;
                    /*
                      added by script: "Returning with"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 100), iVar2, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
                    BVar7 = TRUE;
                    xPos = xPos + 5;
                    _group = OpenSHC::DE::SHCDE::TEXT_GOODS;
                    goto LAB_0043cd93;
                }
            } else if ((_unitStateCategory == 9) && (0 < (int)_entry)) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x12;
                BVar5 = 0;
                TVar4 = OpenSHC::Text::TTA_LEFT;
                iVar2 = xPos;
                iVar3 = yPos;
                /*
                  added by script: "Going to get"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS, 0x67), iVar2, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GOODS, (int)((int)(_entry)), xPos + 5, yPos, OpenSHC::Text::TTA_LEFT, 0,
                    0x12, TRUE);
            }
        LAB_0043cd7c:
            BVar7 = FALSE;
            /*
              Reuse!
             */
            _entry = (OpenSHC::Game::Resources::ResourceType)(_unitStateCategory);
        }
        /*
          important!
         */
        _group = OpenSHC::DE::SHCDE::TEXT_UNIT_ACTIONS;
    LAB_0043cd93:
        iVar3 = 0;
        iVar2 = 0x12;
        BVar5 = 0;
        TVar4 = OpenSHC::Text::TTA_LEFT;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(_group, (int)((int)(_entry))), xPos, yPos, TVar4, BVar5, iVar2, BVar7, iVar3);
    }

}
}
