#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // Pictures in GID_INTERFACE_ICONS_3, 20 pixels wide: a highlighted cell's ends and middles (the right end
        // uses the middle's mask), or a run of stripe 69 or 71 by the row; each picture is followed by its mask.
        enum {
            TABLE_CELL_LEFT_PICTURE = 73,
            TABLE_CELL_MIDDLE_PICTURE = 74,
            TABLE_CELL_RIGHT_PICTURE = 75,
            TABLE_CELL_LEFT_MASK = 76,
            TABLE_CELL_MIDDLE_MASK = 77,
            TABLE_CELL_STRIPE_PICTURES = 69,
            TABLE_CELL_PIECE_WIDTH = 20
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x004692E0
        void PencilRenderCore::drawTableCellBackground(BOOLEnum isSelected, int indexToGetStripes, int blendStrength)
        {
            int x = DAT_ButtonX::instance;
            int const stripePicture = (indexToGetStripes & 1) * 2 | TABLE_CELL_STRIPE_PICTURES;
            if (isSelected) {
                if (DAT_ButtonW::instance > TABLE_CELL_PIECE_WIDTH) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_LEFT_PICTURE, x, DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_LEFT_MASK, blendStrength);
                    x += TABLE_CELL_PIECE_WIDTH;
                } else {
                    ++DAT_ButtonW::instance;
                }
                for (; x < DAT_ButtonW::instance + DAT_ButtonX::instance - TABLE_CELL_PIECE_WIDTH;
                    x += TABLE_CELL_PIECE_WIDTH) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_MIDDLE_PICTURE, x, DAT_ButtonY::instance,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, TABLE_CELL_MIDDLE_MASK, blendStrength);
                }
            } else if (DAT_ButtonCurrentlyInteracting::instance) {
                if (DAT_ButtonW::instance > TABLE_CELL_PIECE_WIDTH) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_LEFT_PICTURE, x, DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_LEFT_MASK, blendStrength);
                    x += TABLE_CELL_PIECE_WIDTH;
                } else {
                    ++DAT_ButtonW::instance;
                }
                for (; x < DAT_ButtonW::instance + DAT_ButtonX::instance - TABLE_CELL_PIECE_WIDTH;
                    x += TABLE_CELL_PIECE_WIDTH) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        TABLE_CELL_MIDDLE_PICTURE, x, DAT_ButtonY::instance,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, TABLE_CELL_MIDDLE_MASK, blendStrength);
                }
            } else {
                for (; x < DAT_ButtonW::instance + DAT_ButtonX::instance; x += TABLE_CELL_PIECE_WIDTH) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, stripePicture,
                        x, DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, stripePicture + 1,
                        blendStrength);
                }
                return;
            }
            if (DAT_ButtonW::instance > TABLE_CELL_PIECE_WIDTH + 1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    TABLE_CELL_RIGHT_PICTURE, x, DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    TABLE_CELL_MIDDLE_MASK, blendStrength);
            }
        }

    }
}
}
