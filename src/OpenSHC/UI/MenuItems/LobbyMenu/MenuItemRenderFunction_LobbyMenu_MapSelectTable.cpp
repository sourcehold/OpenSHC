#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042B4C0
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectTable(int param_1, ...)
        {
            BOOLEnum BVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            uint color;
            char* _Str2;
            int local_4;
            BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar1 != FALSE) {}
            if ((((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                     && (DAT_MenuModalComposition1::instance.activeModalDialogID
                         != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                        != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT))
                || (DAT_ButtonUnknownZero::instance = 1, DAT_GameSynchronyState::instance.isHost == FALSE)) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            iVar4 = 0;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                iVar4 = -1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                    _Str2 = DAT_GameSynchronyState::instance.mapName;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]);
                    iVar3 = MACRO_CALL(OpenSHC::OS_Func::__stricmp)(pcVar2, (char const*)((int)(_Str2)));
                    if (iVar3 == 0) {
                        iVar4 = 1;
                        BVar1 = TRUE;
                        goto LAB_0042b579;
                    }
                }
                BVar1 = FALSE;
            } else {
                BVar1 = (BOOLEnum)(param_1 == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
            }
        LAB_0042b579:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(BVar1, param_1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                iVar3 = 0;
                if (DAT_GameSynchronyState::instance.unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]]
                    < 1) {
                    color = 0x7f7f7f;
                } else if ((((param_1 != DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected)
                                && (DAT_ButtonCurrentlyInteracting::instance == FALSE))
                               && (iVar4 != 1))
                    || (color = 0xccfaff, iVar4 < 0)) {
                    color = 0xc2f0eb;
                }
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]],
                    (int)((int)(DAT_ButtonX::instance + 8)), (int)((int)(DAT_ButtonY::instance + 3)),
                    OpenSHC::Text::TTA_LEFT, color, 0x12, FALSE, ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_GameSynchronyState::instance.mapBalanceArray[DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]]
                    != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xd2,
                        (int)((int)(DAT_ButtonX::instance + 0x18)), (int)((int)(DAT_ButtonY::instance + 5)),
                        (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    iVar3 = 0x14;
                }
                if (DAT_GameSynchronyState::instance.mapU4Int0_2Array[DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]]
                    != 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x18a,
                        DAT_ButtonX::instance + 0x18 + iVar3, (int)((int)(DAT_ButtonY::instance + 5)),
                        (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + param_1 + -1]);
                    pcVar2 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar2, &local_4);
                    iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    DAT_TextManagerObject::instance.field12_0x30 = 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(pcVar2,
                        DAT_ButtonX::instance + 0x2c + iVar3, (int)((int)(DAT_ButtonY::instance + 3)), 0x96 - iVar3,
                        color, 0x12, ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                            + -1]);
                pcVar2 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar2, &local_4);
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    pcVar2, DAT_ButtonX::instance + 0x18 + iVar3, (int)((int)(DAT_ButtonY::instance + 3)), 0xaa - iVar3,
                    color, 0x12, ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
        }

    }
}
}
