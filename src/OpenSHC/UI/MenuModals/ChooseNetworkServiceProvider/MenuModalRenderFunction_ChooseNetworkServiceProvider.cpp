#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0047C860
        void ChooseNetworkServiceProvider::MenuModalRenderFunction_ChooseNetworkServiceProvider(
            int x, int y, int width, int height)
        {
            int iVar1;
            char* textAddress;
            DWORD DVar2;
            int bottom;
            int iVar3;
            TextAlignment alignment;
            BGR24 color;
            int iVar4;
            BOOLEnum keepOffsetX;
            int iVar5;
            /*
              added by script: "Service Providers"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4c, 6, x, y, width, height);
            if (DAT_GameSynchronyState::instance.kickedAtTime != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x, y + -0x3c, x + width, y + -0x12, 0x10);
                iVar5 = 0;
                keepOffsetX = FALSE;
                iVar4 = 0x10;
                color = 0xccfaff;
                alignment = OpenSHC::Text::TTA_CENTER;
                iVar3 = y + -0x32;
                iVar1 = width / 2 + x;
                /*
                  added by script: "You Were Ejected!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5c),
                    iVar1, iVar3, alignment, color, iVar4, keepOffsetX, iVar5);
                DVar2 = timeGetTime();
                if (5000 < DVar2 - DAT_GameSynchronyState::instance.kickedAtTime) {
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                }
            }
            iVar4 = y + 0xa5;
            iVar3 = y + 0x55;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, iVar3, x + 0x1b8, iVar4);
            iVar1 = x + 0x27;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                iVar1, y + 0x54, x + 0x1cd, y + 0x54, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                iVar1, y + 0xa6, x + 0x1cd, y + 0xa6, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                iVar1, iVar3, iVar1, iVar4, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1cd, iVar3, x + 0x1cd, iVar4, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1b8, iVar3, x + 0x1b8, iVar4, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                iVar3 = y + 0x109;
                bottom = y + 0x159;
                iVar1 = x + 0x1b8;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    x + 0x28, iVar3, iVar1, bottom);
                iVar5 = x + 0x1cd;
                iVar4 = x + 0x27;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar4, y + 0x108, iVar5, y + 0x108, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar4, y + 0x15a, iVar5, y + 0x15a, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar4, iVar3, iVar4, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar5, iVar3, iVar5, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1, iVar3, iVar1, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            }
        }

    }
}
}
