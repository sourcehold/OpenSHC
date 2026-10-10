#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
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

        using DE::SHCDE::eTextSections;
        using UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042EBC0
        void MapEditorProperties::MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox(int param_1, ...)
        {
            int iVar2 = DAT_ButtonY::instance;
            int iVar1 = DAT_ButtonX::instance;
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti
                && DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                int right_00 = DAT_ButtonW::instance + 0x18 + DAT_ButtonX::instance;
                int bottom = DAT_ButtonH::instance + -6 + DAT_ButtonY::instance;
                int top = DAT_ButtonY::instance + 4;
                int right = right_00 + -0x14;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance, top, right, bottom);
                int top_00 = bottom + -0x23;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    right_00 + -0x13, top_00, right_00, bottom);
                iVar1 = iVar1 + -1;
                int y1 = iVar2 + 3;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1, y1, right_00 + 1, y1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1, bottom + 1, right_00 + 1, bottom + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1, top, iVar1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right_00 + 1, top, right_00 + 1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right, top, right, top_00, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                iVar2 = iVar2 + 0x18;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right, iVar2, right_00, iVar2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(right,
                    bottom + -0x37, right_00, bottom + -0x37, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right, top_00, right_00, top_00, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                if (DAT_GameCore::instance.mapLoadedForEditor) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
                        DAT_TextureRenderCoreObject::ptr)(
                        DAT_ButtonY::instance + 7, (int)(DAT_ButtonH::instance + -0x2a + DAT_ButtonY::instance));
                    if (!DAT_GameCore::instance.descriptionUseStringTable) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                            DAT_GameCore::instance.temporaryTextBufferOfSize1000, (int)(DAT_ButtonX::instance + 5),
                            (DAT_ButtonY::instance - DAT_00b960f4::instance) + 0xb, 0x168, 0xc2f0eb, 0x13, 0);
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                            DAT_TextureRenderCoreObject::ptr)();
                    }
                    if (DAT_GameCore::instance.descriptionStringTableIndex) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_MAP_NAMES, (int)(DAT_GameCore::instance.descriptionStringTableIndex),
                            (int)(DAT_ButtonX::instance + 5), (DAT_ButtonY::instance - DAT_00b960f4::instance) + 0xb,
                            0x168, 0xc2f0eb, 0x13);
                    }
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                        DAT_TextureRenderCoreObject::ptr)();
                }
            }
        }

    }
}
}
