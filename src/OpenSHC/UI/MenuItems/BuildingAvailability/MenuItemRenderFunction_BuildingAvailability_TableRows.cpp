#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BB3E0
        void BuildingAvailability::MenuItemRenderFunction_BuildingAvailability_TableRows(int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            int _structIndex;
            _structIndex = DAT_MissionAestheticsDefinedData::instance.BuildingAvailabilityStructIndexForNameArray
                               [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + param_1];
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(FALSE, param_1, 0);
            blendStrength = 0;
            keepOffsetX = FALSE;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            fontSize = 0x13;
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                if (DAT_MapPropertiesState::instance.buildingAvailability[_structIndex] == 0) {
                    color = 0x7f7f7f;
                } else {
                    color = 0xc2f0eb;
                }
            } else {
                color = 0xccfaff;
            }
            alignment = OpenSHC::Text::TTA_LEFT;
            yParam = DAT_ButtonY::instance + 6;
            xParam = DAT_ButtonX::instance + 0x14;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT,
                    DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[_structIndex]
                        .nameNumberInTextGroup),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
