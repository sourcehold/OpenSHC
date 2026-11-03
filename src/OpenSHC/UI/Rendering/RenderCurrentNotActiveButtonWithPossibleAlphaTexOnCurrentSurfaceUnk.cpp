#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using IO::Graphics::GmID;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004640D0
    void Rendering::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk()
    {
        int stateOffset = 0;
        if (DAT_ButtonUnknownZero::instance) {
            stateOffset = 2;
        }
        ButtonGmData* const buttonGmData
            = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
        int imageID = MACRO_CALL_MEMBER(UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
        if (DAT_ButtonCurrentlyInteracting::instance) {
            imageID = imageID + 1;
        }
        if (DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance].alphaGmIdUnk_0xc
            != (GmID)0) {
            if (DAT_ButtonBlendStrength::instance != 32) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)((IO::Graphics::GmID)buttonGmData->gmId_0x0, imageID + stateOffset,
                    DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonBlendStrength::instance);
            }
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4
                + stateOffset;
            return;
        }
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            (DE::SHCDE::eGM)buttonGmData->gmId_0x0, imageID + stateOffset, DAT_ButtonX::instance,
            DAT_ButtonY::instance);
        DAT_CurrentButtonPictureInGm::instance
            = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                  .pictureInGm_0x4
            + stateOffset;
    }

}
}
