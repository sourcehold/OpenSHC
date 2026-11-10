#include "../GreatestLord.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE720
        void GreatestLord::MenuItemRenderFunction_GreatestLord_Main(int button, ...)
        {
            // the header of the column the table is sorted by (11 for 1, 12 for 0, 10 for -1) gets its own picture
            if ((button == 11 && DAT_GreatestLordDefinedData::instance.tableSortBy == 1)
                || (button == 12 && DAT_GreatestLordDefinedData::instance.tableSortBy == 0)
                || (button == 10 && DAT_GreatestLordDefinedData::instance.tableSortBy == -1)) {
                // 14 pictures on from the hovered one, 1 for header 12
                int pictureOffset = 14;
                if (button == 12) {
                    pictureOffset = 1;
                }
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                        &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                        TRUE)
                        + pictureOffset,
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                return;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
        }

    }
}
}
