#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042EBC0
        void MapEditorProperties::MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox(int unused, ...)
        {
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0
                || DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            int const x = DAT_ButtonX::instance;
            // top before right, as the original computes them
            int const top = DAT_ButtonY::instance + 4;
            int const right = DAT_ButtonW::instance + 24 + x;
            int const bottom = DAT_ButtonH::instance - 6 + DAT_ButtonY::instance;
            int const divider = right - 20;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x, top, divider, bottom);
            int const sideTop = bottom - 35;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                right - 19, sideTop, right, bottom);
            // the lines work from top, as the original does, not from the button's y
            int const lineTop = top - 1;
            // x - 1 at each use, as the original computes it each time
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x - 1, lineTop, right + 1, lineTop, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x - 1, top, x - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                divider, top, divider, sideTop, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                divider, top + 20, right, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                divider, bottom - 55, right, bottom - 55, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                divider, sideTop, right, sideTop, COL_VERY_SOFT_YELLOW::instance.shortValue);
            if (!DAT_GameCore::instance.mapLoadedForEditor) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)(
                DAT_ButtonY::instance + 7, DAT_ButtonH::instance - 42 + DAT_ButtonY::instance);
            if (!DAT_GameCore::instance.descriptionUseStringTable) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.temporaryTextBufferOfSize1000, DAT_ButtonX::instance + 5,
                    DAT_ButtonY::instance - DAT_00b960f4::instance + 11, 360, OpenSHC::Rendering::Colors::COL_C2F0EB,
                    19, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                    DAT_TextureRenderCoreObject::ptr)();
                return;
            }
            if (DAT_GameCore::instance.descriptionStringTableIndex != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.descriptionStringTableIndex,
                    DAT_ButtonX::instance + 5, DAT_ButtonY::instance - DAT_00b960f4::instance + 11, 360,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 19);
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                DAT_TextureRenderCoreObject::ptr)();
        }

    }
}
}
