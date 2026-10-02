#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004285F0
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDesc(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            BOOLEnum BVar3;
            int iVar4;
            char* pcVar5;
            int iVar6;
            int iVar7;
            int iVar8;
            int local_4;
            BVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            iVar2 = DAT_ButtonY::instance;
            iVar7 = DAT_ButtonX::instance;
            if (BVar3 == FALSE) {
                iVar6 = DAT_ButtonW::instance + 0x65 + DAT_ButtonX::instance;
                local_4 = iVar6 + -0x14;
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                iVar8 = DAT_ButtonH::instance + 0x7a + DAT_ButtonY::instance;
                iVar1 = DAT_ButtonY::instance + 3;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + -0x6e, iVar1, local_4, iVar8,
                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                    local_4 = iVar7 + -0x6f;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(local_4,
                        iVar2 + 2, iVar6 + 1, iVar2 + 2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(local_4,
                        iVar8 + 1, iVar6 + 1, iVar8 + 1, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        local_4, iVar1, local_4, iVar8, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        iVar6 + 1, iVar1, iVar6 + 1, iVar8, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar6 + -0x14, iVar1, iVar6 + -0x14, iVar8,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    local_4 = iVar6 + -0x14;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(local_4,
                        iVar2 + 0x17, iVar6, iVar2 + 0x17, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(local_4, iVar8 + -0x14, iVar6, iVar8 + -0x14,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                }
                if ((DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber != 0)
                    && (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected != -1)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
                        DAT_TextureRenderCoreObject::ptr)(iVar2 + 7, DAT_ButtonH::instance + 0x79 + iVar2);
                    if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                        pcVar5 = DAT_GameSynchronyState::instance.mapName;
                    } else {
                        pcVar5 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                                .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1]);
                    }
                    pcVar5 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar5, &local_4);
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    iVar1 = iVar7 + -100;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        pcVar5, iVar1, (iVar2 - DAT_00b960f4::instance) + -8, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13,
                        FALSE, ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "-", iVar7 + -0x5e, (iVar2 - DAT_00b960f4::instance) + -8, OpenSHC::Text::TTA_LEFT, 0xc2f0eb,
                        0x13, TRUE, ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    if (DAT_GameCore::instance.savedMapBalance == 0) {
                        iVar8 = 0x19b;
                    } else {
                        iVar8 = 0x19c;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar8, iVar7 + -0x58,
                        (iVar2 - DAT_00b960f4::instance) + -8, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, TRUE,
                        ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    if (DAT_GameCore::instance.mapDescUseStringTable != 0) {
                        if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
                            iVar7 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAP_NAMES,
                                DAT_GameCore::instance.mapDescUseStringTableIndex, iVar1,
                                (iVar2 - DAT_00b960f4::instance) + 0xb, (int)((int)(DAT_ButtonW::instance + 0xaa)),
                                0xc2f0eb, 0x13, ((int)(iVar7 + (iVar7 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                            DAT_TextureRenderCoreObject::ptr)();
                    }
                    iVar7 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                        DAT_TextManagerObject::ptr)(DAT_GameCore::instance.mapDescription, iVar1,
                        (iVar2 - DAT_00b960f4::instance) + 0xb, (int)((int)(DAT_ButtonW::instance + 0xaa)), 0xc2f0eb,
                        0x13, ((int)(iVar7 + (iVar7 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                        DAT_TextureRenderCoreObject::ptr)();
                }
            }
        }

    }
}
}
