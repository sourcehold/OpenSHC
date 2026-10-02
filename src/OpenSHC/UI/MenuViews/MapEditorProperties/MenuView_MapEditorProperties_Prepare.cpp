#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Player/BuildingEntryInfo.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapEditorProperties_ClickedButton.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::Player::BuildingEntryInfo;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042DFD0
        void MapEditorProperties::MenuView_MapEditorProperties_Prepare()
        {
            char* piVar1;
            int* piVar2;
            char* text;
            int* piVar3;
            int* piVar4;
            int xPos;
            int yPos;
            int maxWidth;
            BGR24 color;
            int blendStrength;
            int modeUnk;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
            DAT_MapEditorProperties_ClickedButton::instance = 0;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_builder2.tgx");
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0) {
                DAT_GameCore::instance.mapU2PlayersCount = 0;
                piVar4 = DAT_GameState::instance.playerDataArray[1].startResources;
                do {
                    if (((BuildingEntryInfo*)(piVar4 + -0xf6))->id != 0) {
                        DAT_GameCore::instance.mapU2PlayersCount = DAT_GameCore::instance.mapU2PlayersCount + 1;
                    }
                    piVar2 = DAT_GameState::instance.mapAndTime.startGoods;
                    piVar3 = piVar4;
                    do {
                        *piVar3 = 0;
                        *piVar2 = 0;
                        piVar2 = piVar2 + 1;
                        piVar3 = piVar3 + 1;
                    } while ((int)piVar2 < 0x117ce50);
                    piVar4 = piVar4 + 0xe7d;
                } while ((int)piVar4 < 0x117cbf8);
            }
            DAT_00b95b74::instance = 0;
            DAT_00b960f4::instance = 0;
            if (DAT_GameCore::instance.field115_0x1d98 != 0) {
                if (DAT_GameCore::instance.descriptionUseStringTable == 0) {
                    modeUnk = 1;
                    blendStrength = 0;
                    color = 0;
                    maxWidth = 0x168;
                    yPos = 0;
                    xPos = 0;
                    text = DAT_GameCore::instance.temporaryTextBufferOfSize1000;
                } else {
                    if (DAT_GameCore::instance.descriptionStringTableIndex == 0)
                        goto LAB_0042e0bd;
                    modeUnk = 1;
                    blendStrength = 0;
                    color = 0;
                    maxWidth = 0x168;
                    yPos = 0;
                    xPos = 0;
                    text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAP_NAMES,
                        (int)((int)(DAT_GameCore::instance.descriptionStringTableIndex)));
                }
                DAT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(
                    text, xPos, yPos, maxWidth, color, blendStrength, modeUnk);
            }
        LAB_0042e0bd:
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
