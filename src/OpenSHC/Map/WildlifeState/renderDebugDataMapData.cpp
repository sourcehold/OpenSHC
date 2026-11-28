#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Map {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052BF40
    void WildlifeState::renderDebugDataMapData(int x, int y, int width, int height)
    {
        int const x1 = x + 2;
        if (this->DAT_DebugDataMapDataDisplayType == 0) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Connect ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 1) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Chimps  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 2) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Farmland   ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 3) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Humans  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 4) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Mankind  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 5) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Deer  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 6) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Route  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 7) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Panic  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 8) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Siege  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        } else if (this->DAT_DebugDataMapDataDisplayType == 9) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Slink  ", x1 + 420, y + 4, Text::TTA_LEFT, 0xffffff, 17, FALSE, 0);
        }
        // render the squares
        for (int line = 0; line < 41; line++) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + line * 10, x1 + 400, y + line * 10, COL_WHITE::instance.shortValue);
        }
        for (int line = 0; line < 41; line++) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1 + line * 10, y, x1 + line * 10, y + 400, COL_WHITE::instance.shortValue);
        }
        for (int row = 0; row < 40; row++) {
            for (int column = 0; column < 40; column++) {
                if (this->grid[column][row].firstMember <= 0) {
                    continue;
                }
                int colour;
                if (this->DAT_DebugDataMapDataDisplayType == 0) {
                    int const areaColour = this->grid[column][row].separateAreaID & 7;
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (areaColour == 1) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (areaColour == 2) {
                        colour = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (areaColour == 3) {
                        colour = (ushort)COL_MODERATE_GREEN::instance.shortValue;
                    } else if (areaColour == 4) {
                        colour = (ushort)COL_WHITE::instance.shortValue;
                    } else if (areaColour == 5) {
                        colour = (ushort)COL_DARK_CYAN_GREY::instance.shortValue;
                    } else if (areaColour == 6) {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    } else if (areaColour == 7) {
                        colour = (ushort)COL_VIVID_BLUE::instance.shortValue;
                    } else {
                        colour = (ushort)COL_VERY_DARK_GREY::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 1) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].chimps) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 2) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].farmFieldTiles) {
                        colour = (ushort)COL_DARK_GREEN::instance.shortValue;
                    } else if (this->grid[column][row].rabbitCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].field_0x3c) {
                        colour = (ushort)COL_WHITE::instance.shortValue;
                    } else if (this->grid[column][row].field_0x50) {
                        colour = (ushort)COL_DARK_CYAN_GREY::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 3) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].unstalkedUnitCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 4) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].unstalkedUnitCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].buildingTiles) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].field_0x34) {
                        colour = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 5) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].unstalkedUnitCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].buildingTiles) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].lionCount) {
                        colour = (ushort)COL_BLACK::instance.shortValue;
                    } else if (this->grid[column][row].camelCount) {
                        colour = (ushort)COL_BLACK::instance.shortValue;
                    } else if (this->grid[column][row].deerCount) {
                        colour = (ushort)COL_MODERATE_GREEN::instance.shortValue;
                    } else if (this->grid[column][row].field_0x34) {
                        colour = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 6) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].deerCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].lionCount) {
                        colour = (ushort)COL_VIVID_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].field_0x3c) {
                        colour = (ushort)COL_WHITE::instance.shortValue;
                    } else if (this->grid[column][row].casDisRelated2) {
                        colour = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (this->grid[column][row].field_0x34) {
                        colour = (ushort)COL_BLACK::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 7) {
                    if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].field_0x48) {
                        colour = (ushort)COL_WHITE::instance.shortValue;
                    } else if (this->grid[column][row].deerCount) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].field_0x34) {
                        colour = (ushort)COL_BLACK::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 8) {
                    if (this->grid[column][row].field_0x60) {
                        colour = (ushort)COL_WHITE::instance.shortValue;
                    } else if (this->grid[column][row].field_0x64) {
                        colour = (ushort)COL_BLACK::instance.shortValue;
                    } else if (this->grid[column][row].castlebuildings) {
                        colour = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].unknownNonZero01) {
                        colour = (ushort)COL_VIVID_BLUE::instance.shortValue;
                    } else if (this->grid[column][row].field_0x6c) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else if (this->DAT_DebugDataMapDataDisplayType == 9) {
                    if (this->grid[column][row].field_0x74) {
                        colour = (ushort)COL_RED::instance.shortValue;
                    } else if (this->grid[column][row].unknownNonZero01) {
                        colour = (ushort)COL_VIVID_BLUE::instance.shortValue;
                    } else if (!this->grid[column][row].separateAreaID) {
                        colour = (ushort)COL_BLUE::instance.shortValue;
                    } else {
                        colour = (ushort)COL_LIME::instance.shortValue;
                    }
                } else {
                    continue;
                }
                int const boxX = x1 + column * 10;
                int const boxY = y + row * 10;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                    boxX + 1, boxY + 1, boxX + 9, boxY + 9, colour);
            }
        }
    }

}
}
