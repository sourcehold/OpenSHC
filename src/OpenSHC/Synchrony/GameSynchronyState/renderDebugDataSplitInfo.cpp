#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EED0
    void GameSynchronyState::renderDebugDataSplitInfo(int x, int y, int width, int height)
    {
        int const left = x + 2;
        // "Splinter box "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Splinter_box_005a725c, left, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        if (this->splinterType == 0) {
            // " - Chimps"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Chimps_005a7250, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        } else if (this->splinterType == 1) {
            // " - Structures"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Structures_005a7240, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        } else if (this->splinterType == 2) {
            // " - Vegetation"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Vegetation_005a7230, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        } else if (this->splinterType == 3) {
            // " - Tribes"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Tribes_005a7224, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        } else if (this->splinterType == 4) {
            // " - Players"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Players_005a7218, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        } else if (this->splinterType == 5) {
            // " - Game elements"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___Game_elements_005a7204, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, TRUE, 0);
        }
        // "Total split data items:  "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Total_split_data_items__005a71e8, left, y + 28, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->totalSplitDataItems, left + 10, y + 28, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        if (this->splinterType == 0) {
            // "Total split chimps:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_chimps__005a71d0, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitChimps, left + 10, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "First split chimp:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_chimp__005a71b8, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitChimps, left + 210, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // The first ten unit hashes of players 1 and 2, red where they differ.
            // The column lives only here and steps after the unit, in the for header: other forms swap y and the
            // column.
            int column = left + 10;
            for (int unit = 1; unit < 11; ++unit, column += 40) {
                uint color;
                if (this->HASH_Units[1][unit] == this->HASH_Units[2][unit]) {
                    color = Rendering::Colors::COL_FFFFFF;
                } else {
                    color = Rendering::Colors::COL_0000FF;
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->HASH_Units[1][unit], column, y + 70, Text::TTA_LEFT, color, 18, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->HASH_Units[2][unit], column, y + 84, Text::TTA_LEFT, color, 18, FALSE, 0);
            }
        } else if (this->splinterType == 1) {
            // "Total split structures:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_structures__005a719c, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitStructures, left + 10, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
                0);
            // "First split structure:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_structure__005a7180, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF,
                18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitStructures, left + 210, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
                0);
        } else if (this->splinterType == 2) {
            // "Total split veg:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_veg__005a716c, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitVeg, left + 10, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "First split veg:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_veg__005a7158, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitVeg, left + 210, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        } else if (this->splinterType == 3) {
            // "Total split tribes:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_tribes__005a7140, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitTribes, left + 10, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "First split tribe:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_tribe__005a7128, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitTribe, left + 210, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        } else if (this->splinterType == 4) {
            // "Total split players:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_players__005a7110, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitPlayers, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split player:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_player__005a70f8, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitPlayer, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 5) {
            // "Total split elements:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_elements__005a70e0, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitElements, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split element:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_element__005a70c8, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitElement, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 6) {
            // "Total split layers:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_layers__005a70b0, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitLayers, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split layer:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_layer__005a7098, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitLayer, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 7) {
            // "Total split flies:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_flies__005a7080, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitFlies, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split fly:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_fly__005a706c, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitFly, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 8) {
            // "Total split moats:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_moats__005a7054, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitMoats, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split moat:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_moat__005a7040, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitMoat, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 9) {
            // "Total split teleports:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_teleports__005a7024, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitTeleports, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split teleport:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_teleport__005a700c, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitTeleports, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 10) {
            // "Total split pitch ditchs:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_pitch_ditchs__005a6ff0, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitPitchDitches, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split pitch ditch:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_pitch_ditch__005a6fd4, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF,
                18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitPitchDitch, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        } else if (this->splinterType == 11) {
            // "Total split zones:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Total_split_zones__005a6fbc, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitZones, left + 10, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
            // "First split zone:  "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_First_split_zone__005a6fa8, left + 200, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18,
                FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->firstSplitZone, left + 210, y + 42, Rendering::Colors::COL_0080FF, 18, TRUE);
        }
    }

}
}
