#include "../EditorMapTypeQuickChange.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Map/MapLockStateInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::MapLockState;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Map::MapLockStateInt;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AC040
        void EditorMapTypeQuickChange::MenuItemRenderFunction_EditorMapTypeQuickChange_Main(int param_1, ...)
        {
            MapLockStateInt MVar1;
            BOOLEnum BVar2;
            char* textAddress;
            BGR24 color;
            BVar2 = DAT_ButtonCurrentlyInteracting::instance;
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MVar1 = DAT_GameCore::instance.U3_mapLockedState;
            if (param_1 < 3) {
            joined_r0x004ac081:
                if (param_1 != MVar1)
                    goto switchD_004ac099_caseD_4;
            } else {
                if (param_1 < 7) {
                    MVar1 = DAT_MapPropertiesState::instance.SEC_U3_MapType2_1
                        + (OpenSHC::Map::MLS_MISSION | OpenSHC::Map::MLS_PLAYABLE);
                    goto joined_r0x004ac081;
                }
                if (param_1 < 0x14) {
                    if (param_1 == 0xc) {
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        }
                        if (DAT_GameCore::instance.mapU4Int0 == 0)
                            goto switchD_004ac099_caseD_4;
                    } else if (param_1 == 10) {
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0)
                            goto switchD_004ac099_caseD_4;
                    } else if ((param_1 != 0xb) || ((int)DAT_GameCore::instance.U2_mapType_singleOrMulti < 1))
                        goto switchD_004ac099_caseD_4;
                } else {
                    switch (param_1) {
                    case 0x14:
                        if (DAT_TileMapState::instance.mapSize != 0xa0)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x15:
                        if (DAT_TileMapState::instance.mapSize != 200)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x16:
                        if (DAT_TileMapState::instance.mapSize != 300)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x17:
                        if (DAT_TileMapState::instance.mapSize != 400)
                            goto switchD_004ac099_caseD_4;
                        break;
                    default:
                        goto switchD_004ac099_caseD_4;
                    }
                }
            }
            DAT_ButtonCurrentlyInteracting::instance = TRUE;
        switchD_004ac099_caseD_4:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            textAddress = "";
            switch (param_1) {
            case 0:
                textAddress = "Editable";
                break;
            case 1:
                textAddress = "Playable";
                break;
            case 2:
                textAddress = "Mission";
                break;
            case 3:
                textAddress = "Siege";
                break;
            case 4:
                textAddress = "Invasion";
                break;
            case 5:
                textAddress = "Economic";
                break;
            case 6:
                textAddress = "Just Build";
                break;
            case 10:
                textAddress = "Single";
                break;
            case 0xb:
                textAddress = "Multi";
                break;
            case 0xc:
                textAddress = "King of the Hill";
                break;
            case 0x14:
                textAddress = "160x160";
                break;
            case 0x15:
                textAddress = "200x200";
                break;
            case 0x16:
                textAddress = "300x300";
                break;
            case 0x17:
                textAddress = "400x400";
            }
            if (BVar2 == FALSE) {
                color = 0xc2f0eb;
            } else {
                color = 0xccfaff;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textAddress, (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 4)), OpenSHC::Text::TTA_CENTER, color, 0x11, FALSE, 0);
        }

    }
}
}
