#include "../RankingGames.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00ed27a0.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D99F0
        void RankingGames::MenuItemRenderFunction_RankingGames_Main(int param_1, ...)
        {
            int iVar1;
            if ((param_1 == -10) || (param_1 == -0xb)) {
                iVar1 = 0x51;
                if (param_1 == -10) {
                    iVar1 = 0x55;
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    iVar1 = iVar1 + 1;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + -1, (int)((int)(DAT_ButtonY::instance + -1)),
                    (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 0x14)),
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            } else if (7 < param_1) {
                if (0xb < param_1 - 0x14U)
                    goto LAB_004d9a4f;
                if (param_1 == 0x14) {
                    DAT_00ed27a0::instance = 0;
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    DAT_00ed27a0::instance = param_1;
                }
                if ((param_1 < 0x1e) && (param_1 + -0x13 == DAT_MissionDefinedData::instance.sortColumn)) {
                LAB_004d9a62:
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    iVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                .pictureInGm_0x4
                        + 2;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                              .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                              .gmId_0x0,
                        iVar1, (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                    DAT_CurrentButtonPictureInGm::instance = iVar1;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (param_1 == 0x1e) {
                    if (DAT_00ed3124::instance == 1)
                        goto LAB_004d9a62;
                } else if ((param_1 == 0x1f) && (DAT_00ed3124::instance == 2))
                    goto LAB_004d9a62;
            LAB_004d9a4f:
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
        }

    }
}
}
