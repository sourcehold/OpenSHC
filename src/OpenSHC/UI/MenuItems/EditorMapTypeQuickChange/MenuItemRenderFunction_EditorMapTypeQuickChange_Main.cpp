#include "../EditorMapTypeQuickChange.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditorMapTypeQuickChange {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AC040
            void MenuItemRenderFunction_EditorMapTypeQuickChange_Main(int button, ...)
            {
                // The button of the map's current setting is drawn pressed; hovering only changes the text colour.
                BOOLEnum const hovered = DAT_ButtonCurrentlyInteracting::instance;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                if (button < 3) {
                    // 0 to 2: editable, playable, mission
                    if (button == DAT_GameCore::instance.U3_mapLockedState) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    }
                } else if (button < 7) {
                    // 3 to 6: siege, invasion, economic, just build
                    if (button == DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 + 3) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    }
                } else if (button >= 20) {
                    // 20 to 23: the map's size
                    switch (button) {
                    case 20:
                        if (DAT_TileMapState::instance.mapSize == OpenSHC::Map::MC_MAP_SIZE_160) {
                            DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        }
                        break;
                    case 21:
                        if (DAT_TileMapState::instance.mapSize == OpenSHC::Map::MC_MAP_SIZE_200) {
                            DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        }
                        break;
                    case 22:
                        if (DAT_TileMapState::instance.mapSize == OpenSHC::Map::MC_MAP_SIZE_300) {
                            DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        }
                        break;
                    case 23:
                        if (DAT_TileMapState::instance.mapSize == OpenSHC::Map::MC_MAP_SIZE_400) {
                            DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        }
                        break;
                    }
                } else if (button == 12) {
                    // King of the Hill: only on a multiplayer map, where it is drawn at all
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                        return;
                    }
                    if (DAT_GameCore::instance.mapU4Int0) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    }
                } else if (button == 10) {
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    }
                } else if (button == 11) {
                    if (DAT_GameCore::instance.U2_mapType_singleOrMulti >= 1) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // ""
                char const* text = s__005a5339;
                switch (button) {
                case 0:
                    // "Editable"
                    text = s_Editable_005a7660;
                    break;
                case 1:
                    // "Playable"
                    text = s_Playable_005a7654;
                    break;
                case 2:
                    // "Mission"
                    text = s_Mission_005a764c;
                    break;
                case 3:
                    // "Siege"
                    text = s_Siege_005a7644;
                    break;
                case 4:
                    // "Invasion"
                    text = s_Invasion_005a7638;
                    break;
                case 5:
                    // "Economic"
                    text = s_Economic_005a762c;
                    break;
                case 6:
                    // "Just Build"
                    text = s_Just_Build_005a7620;
                    break;
                case 10:
                    // "Single"
                    text = s_Single_005a7618;
                    break;
                case 11:
                    // "Multi"
                    text = s_Multi_005a7610;
                    break;
                case 12:
                    // "King of the Hill"
                    text = s_King_of_the_Hill_005a75fc;
                    break;
                case 20:
                    // "160x160"
                    text = s_160x160_005a75f4;
                    break;
                case 21:
                    // "200x200"
                    text = s_200x200_005a75ec;
                    break;
                case 22:
                    // "300x300"
                    text = s_300x300_005a75e4;
                    break;
                case 23:
                    // "400x400"
                    text = s_400x400_005a75dc;
                    break;
                }
                // two calls, one per colour (one call with a colour local: 100.0% -> 88.0%)
                if (hovered) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        text, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 4,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(text,
                    DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 4,
                    OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
            }

        }
    }
}
}
