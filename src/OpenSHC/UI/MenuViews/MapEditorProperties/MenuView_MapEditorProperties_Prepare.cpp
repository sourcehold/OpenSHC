#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapEditorProperties_ClickedButton.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MapEditorProperties {

            // FUNCTION: STRONGHOLDCRUSADER 0x0042DFD0
            void MenuView_MapEditorProperties_Prepare()
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
                DAT_MapEditorProperties_ClickedButton::instance = 0;
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "frontend_builder2.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_frontend_builder2_tgx_005a206c);
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0) {
                    // count the players with a first building and clear every player's start goods and the map's
                    DAT_GameCore::instance.mapU2PlayersCount = 0;
                    for (int player = 1; player < countof(DAT_GameState::instance.playerDataArray); ++player) {
                        if (DAT_GameState::instance.playerDataArray[player].buildingEntryInfos[0].id != 0) {
                            ++DAT_GameCore::instance.mapU2PlayersCount;
                        }
                        for (int good = 0; good < countof(DAT_GameState::instance.mapAndTime.startGoods); ++good) {
                            DAT_GameState::instance.playerDataArray[player].startResources[good] = 0;
                            DAT_GameState::instance.mapAndTime.startGoods[good] = 0;
                        }
                    }
                }
                INT_00b95b74::instance = 0;
                DAT_00b960f4::instance = 0;
                // the height of the map's description in pixels (mode 1 only measures)
                if (DAT_GameCore::instance.mapLoadedForEditor) {
                    if (!DAT_GameCore::instance.descriptionUseStringTable) {
                        INT_00b95b74::instance
                            = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                                &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                                DAT_GameCore::instance.temporaryTextBufferOfSize1000, 0, 0, 360,
                                OpenSHC::Rendering::Colors::COL_000000, 0, 1);
                    } else if (DAT_GameCore::instance.descriptionStringTableIndex != 0) {
                        INT_00b95b74::instance
                            = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                                &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAP_NAMES,
                                    DAT_GameCore::instance.descriptionStringTableIndex),
                                0, 0, 360, OpenSHC::Rendering::Colors::COL_000000, 0, 1);
                    }
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            }

        }
    }
}
}
