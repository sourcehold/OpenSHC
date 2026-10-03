#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466320
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton(int param_1, ...)
        {
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color_00;
            int fontSize;
            int blendStrength;
            uint color;
            int iVar3 = DAT_BuildingsState::instance.menuSelectedBuildingID;
            DAT_ButtonUnknownZero::instance
                = (int)(DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID);
            BOOLEnum BVar1
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.menuSelectedBuildingID);
            BOOLEnum BVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                DAT_PathFindingState::ptr)((int)DAT_BuildingsState::instance.buildings[iVar3].owner,
                (uint)((short)DAT_BuildingsState::instance.buildings[iVar3].x),
                (uint)((short)DAT_BuildingsState::instance.buildings[iVar3].y),
                (int)((-(uint)(DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                          & 0xfffffff1)
                    + 0x1e));
            if ((BVar2 == FALSE) && (BVar1 != FALSE)) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_SCREEN_MENU);
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color_00 = 0xc2f0eb;
                } else {
                    color_00 = 0xccfaff;
                }
            } else {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(8, OpenSHC::Rendering::Enums::RT_SCREEN_MENU);
                color_00 = 0x7caaaf;
            }
            blendStrength = 0;
            BVar1 = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            yParam = DAT_ButtonY::instance + 7;
            iVar3 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            /*
              added by script: "Repair"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, 0x101),
                iVar3, yParam, alignment, color_00, fontSize, BVar1, blendStrength);
        }

    }
}
}
