#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // one face: 66 rows of 64 pixels of two bytes
    int const FACE_HEIGHT = 66;
    int const FACE_WIDTH = 64;
    int const FACE_SIZE = FACE_HEIGHT * FACE_WIDTH * 2;

    // FUNCTION: STRONGHOLDCRUSADER 0x004863A0
    void Commands::UpdateSkirmishGameMenuFaceBitmap()
    {
        int slot;
        int rowIndex;
        byte rowBytes[FACE_WIDTH * 2];
        // one row of the sender's face: the row's number, the sender's slot and the row's 64 pixels, as their 64 low
        // bytes followed by their 64 high bytes
        DAT_GameSynchronyState::instance.DAT_CommandSize = 136;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            // the row comes from the chosen lord's face
            byte* const row = (byte*)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                + (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                      + (DAT_GameCore::instance.lordIconUnk - 2) * FACE_HEIGHT)
                    * FACE_WIDTH);
            for (int pixel = 0; pixel < FACE_WIDTH; ++pixel) {
                rowBytes[pixel] = row[pixel * 2];
                rowBytes[pixel + FACE_WIDTH] = row[pixel * 2 + 1];
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(rowBytes, sizeof(rowBytes),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&rowIndex, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&slot, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (slot < 1 || slot > 8) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(rowBytes, sizeof(rowBytes), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // the row goes into the slot's face (the players' faces follow the 20 lords' faces; the slots start at 1)
        byte* const row = (byte*)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
            + (rowIndex + (slot + 19) * FACE_HEIGHT) * FACE_WIDTH);
        for (int pixel = 0; pixel < FACE_WIDTH; ++pixel) {
            row[pixel * 2] = rowBytes[pixel];
            row[pixel * 2 + 1] = rowBytes[pixel + FACE_WIDTH];
        }
        DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[slot + 19] = FACE_SIZE;
    }

}
}
