#include "../BuildMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00439160
        void BuildMenu::MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            iVar3 = DAT_ButtonY::instance;
            iVar2 = DAT_ButtonX::instance;
            if (DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            iVar1 = DAT_UnitsState::instance.selectionSlots[param_1];
            DAT_ButtonUnknownZero::instance = 0;
            if (iVar1 == -1) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            switch (iVar1) {
            case 0:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -0xe;
                break;
            case 1:
                DAT_ButtonX::instance = DAT_ButtonX::instance + -3;
                break;
            case 2:
            case 7:
                DAT_ButtonX::instance = DAT_ButtonX::instance + 1;
                break;
            default:
                if (0x12 < iVar1) {
                    DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                    goto LAB_004391d6;
                }
                break;
            case 4:
                DAT_ButtonX::instance = DAT_ButtonX::instance + 2;
                DAT_ButtonY::instance = DAT_ButtonY::instance + -0x14;
                break;
            case 5:
                DAT_ButtonX::instance = DAT_ButtonX::instance + 1;
            case 8:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -8;
                break;
            case 6:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -0x14;
                DAT_ButtonX::instance = DAT_ButtonX::instance + -7;
                break;
            case 9:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -0x13;
                break;
            case 0x11:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -4;
                break;
            case 0x13:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -8;
                DAT_ButtonX::instance = DAT_ButtonX::instance + 2;
                DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                goto LAB_004391d6;
            case 0x14:
            case 0x18:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -9;
            case 0x19:
                DAT_ButtonX::instance = DAT_ButtonX::instance + 1;
                DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                goto LAB_004391d6;
            case 0x15:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -7;
                DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                goto LAB_004391d6;
            case 0x16:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                goto LAB_004391d6;
            case 0x17:
                DAT_ButtonY::instance = DAT_ButtonY::instance + -0xd;
            case 0x1a:
                DAT_ButtonX::instance = DAT_ButtonX::instance + -6;
                DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x209;
                goto LAB_004391d6;
            }
            DAT_CurrentButtonGmDataIndex::instance = iVar1 + 0x17c;
        LAB_004391d6:
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.selectionSlots[iVar1 + -0x1b], DAT_ButtonW::instance / 2 + iVar2, iVar3 + 0x53,
                OpenSHC::Text::TTA_CENTER, 0xffffff, 0, 0x11, FALSE, 0);
        }

    }
}
}
