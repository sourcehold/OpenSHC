#include "../Roundtable.func.hpp"

#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df4288.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B1AC0
        void Roundtable::MenuModalRenderFunction_Roundtable(int x, int y, int width, int height)
        {
            int iVar1;
            int gfxIndex;
            int iVar2;
            int* piVar3;
            int iVar4;
            int blendStrengthUnk;
            int local_40[16];
            iVar1 = y;
            if (DAT_MouseState::instance.rightClickStart != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(2, x + 8, y + 8);
            local_40[4] = 0x18e;
            local_40[8] = 0x18e;
            iVar2 = 1;
            local_40[2] = 0xd8;
            local_40[10] = 0xd8;
            y = 0;
            local_40[0] = 0xc;
            local_40[1] = 0xc;
            local_40[3] = 0xc;
            local_40[5] = 0xc;
            local_40[6] = 0x18d;
            local_40[7] = 0x67;
            local_40[9] = 0xc1;
            local_40[0xb] = 0xc0;
            local_40[0xc] = 0xc;
            local_40[0xd] = 0xc1;
            local_40[0xe] = 0xc;
            local_40[0xf] = 0x67;
            piVar3 = local_40;
            iVar4 = 1;
            do {
                if (((char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[iVar4] < 1)
                    || ((char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[(
                            char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[iVar4]]
                        < '\x01'))
                    break;
                if (y < (char)DAT_GameSynchronyState::instance
                        .DAT_PlayerGroupArray[(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[iVar4]]) {
                    y = y + 1;
                    iVar2 = iVar2 + 1;
                    if (1 < iVar2) {
                        iVar2 = 0;
                    }
                }
                if (iVar2 == 0) {
                    blendStrengthUnk = 0x10;
                    gfxIndex = iVar4 + 2;
                } else {
                    blendStrengthUnk = 0x14;
                    gfxIndex = iVar4 + 2 + iVar2 * 8;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGfxTgxWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(gfxIndex, *piVar3 + x, piVar3[1] + iVar1, blendStrengthUnk);
                iVar4 = iVar4 + 1;
                piVar3 = piVar3 + 2;
            } while (iVar4 < 9);
            DAT_ButtonY::instance = iVar1 + 0x17c;
            DAT_ButtonX::instance = x + 0x18;
            DAT_ButtonW::instance = 0x17c;
            DAT_ButtonH::instance = 0x28;
            if (DAT_00df4288::instance != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::BottomLeftTextDisplayState_Func::renderCurrentlyDisplayedTextConstructionCost,
                    DAT_BottomLeftTextDisplayState::ptr)(0);
                DAT_00df4288::instance = 0;
            }
        }

    }
}
}
