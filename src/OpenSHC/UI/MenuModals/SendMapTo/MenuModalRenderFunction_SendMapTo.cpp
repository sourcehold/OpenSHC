#include "../SendMapTo.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AC310
        void SendMapTo::MenuModalRenderFunction_SendMapTo(int x, int y, int width, int height)
        {
            int iVar1;
            int iVar2;
            int local_10;
            char (*local_c)[250];
            short* local_8;
            /*
              added by script: "Send Map To"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4f, 0x6a, x, y, width, height);
            iVar1 = 0;
            local_c = DAT_GameSynchronyState::instance.DAT_PlayerNames;
            local_8 = DAT_GameSynchronyState::instance.field282_0x109d98 + 1;
            local_10 = 0;
            do {
                local_c = local_c + 1;
                if (*local_8 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        *local_c, x + 0x14, iVar1 + 0x50 + y, OpenSHC::Text::TTA_LEFT,
                        (BGR24)((int)(DAT_RenderingDefinedData::instance.ColorArray[*(
                            int*)((int)DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + local_10 + 4)])),
                        0x11, FALSE, 0);
                    if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState != 0) {
                        iVar2 = width / 2;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                            DAT_PencilRenderCore::ptr)(iVar2 + x + -1, iVar1 + 0x52 + y, width + -0x13 + x,
                            iVar1 + 99 + y, (ushort)((int)(COL_BLACK::instance.shortValue)));
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                            DAT_PencilRenderCore::ptr)(iVar2 + x, iVar1 + 0x53 + y,
                            ((iVar2 + -0x14)
                                * *(int*)((int)DAT_GameSynchronyState::instance.mapSendingByteBufferAddress + local_10
                                    + 4))
                                    / DAT_GameSynchronyState::instance.mapSendingFileSize
                                + iVar2 + x,
                            iVar1 + 0x62 + y, (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                    }
                    iVar1 = iVar1 + 0x1e;
                }
                local_10 = local_10 + 4;
                local_8 = local_8 + 1;
            } while ((int)local_8 < 0x1a27512);
            return;
        }

    }
}
}
