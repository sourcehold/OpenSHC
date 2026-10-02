#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::IO::Graphics::GmID;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042D9A0
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_MapTable(int param_1, ...)
        {
            dword dVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            uint color;
            int local_2c;
            int local_28;
            char local_24[32];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_2c;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected), param_1,
                (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber
                <= DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1)
                goto LAB_0042db95;
            if ((param_1 == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected)
                || (color = 0xc2f0eb, DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                color = 0xccfaff;
            }
            if (DAT_MapMissionType::instance == 2) {
                local_2c = 0xe6;
            LAB_0042da2d:
                iVar4 = 5;
                if (DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2[DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]]
                    == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x2d7,
                        (int)((int)(DAT_ButtonX::instance + 6)), (int)((int)(DAT_ButtonY::instance + 3)),
                        (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x7c,
                        (int)((int)(DAT_ButtonX::instance + 1)), (int)((int)(DAT_ButtonY::instance + 4)),
                        (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                }
            } else {
                local_2c = 0x172;
                if (DAT_MapMissionType::instance != 0)
                    goto LAB_0042da2d;
                iVar4 = -0x10;
            }
            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                        + -1]);
            pcVar2 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar2, &local_28);
            iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
            DAT_TextManagerObject::instance.field12_0x30 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                pcVar2, DAT_ButtonX::instance + 0x18 + iVar4, (int)((int)(DAT_ButtonY::instance + 3)), local_2c, color,
                0x12, ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            dVar1 = DAT_ResourceManager::instance.mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                    [DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1 + -1]];
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_24, "%02d/%02d/%02d %02d:%02d", (int)dVar1 >> 0x10 & 0x1f,
                (int)dVar1 >> 0x15 & 0xf, ((int)dVar1 >> 0x19) + -0x14, (int)dVar1 >> 0xb & 0x1f,
                (int)dVar1 >> 5 & 0x3f);
            iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(local_24,
                (int)((int)(DAT_ButtonX::instance + 0x134)), (int)((int)(DAT_ButtonY::instance + 3)),
                OpenSHC::Text::TTA_LEFT, (BGR24)((int)(color)), 0x12, FALSE,
                ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
        LAB_0042db95:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            ;
        }

    }
}
}
