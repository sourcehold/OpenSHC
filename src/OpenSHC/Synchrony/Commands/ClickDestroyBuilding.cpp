#include "../Commands.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using namespace OpenSHC::Commands;
    using namespace OpenSHC::Map::Buildings;

    // FUNCTION: STRONGHOLDCRUSADER 0x00481F40
    void Commands::ClickDestroyBuilding()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 7;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != GCS_EXECUTE) {
            return;
        }
        short targetID;
        MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
            &targetID, 2, GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = targetID;
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
        MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
            &DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1, GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
            &DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4, GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            GCPRW_DESERIALIZE_FROM_PARAM1);

        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 > 0) {
            int const buildingID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            if (DAT_BuildingsState::instance.buildings[buildingID].uid
                != DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                return;
            }
            int drawbridgeID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].owner,
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y,
                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, 0);
            if (drawbridgeID != 0) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(BuildingsState_Func::giveBackResourceForDestroyedBuilding, DAT_BuildingsState::ptr)(
                    drawbridgeID, DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
                MACRO_CALL_MEMBER(BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(drawbridgeID);
                drawbridgeID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner,
                    DAT_BuildingsState::instance.buildings[buildingID].x,
                    DAT_BuildingsState::instance.buildings[buildingID].y,
                    DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, drawbridgeID);
                if (drawbridgeID != 0) {
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                    MACRO_CALL_MEMBER(BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(drawbridgeID, DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
                    MACRO_CALL_MEMBER(BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(drawbridgeID);
                }
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].suppressDestroyRefund == 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::giveBackResourceForDestroyedBuilding, DAT_BuildingsState::ptr)(
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                    DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
            }
            if (buildingID != 0
                && DAT_BuildingsState::instance.buildings[buildingID].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case BT_GATEHOUSELARGE:
                case BT_GATEHOUSESMALL:
                case BT_TOWER1:
                case BT_TOWER2:
                case BT_TOWER3:
                case BT_TOWER4:
                case BT_TOWER5:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, DE::SHCDE::FX_TOWER_SMASH);
                    break;
                default:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_buildingwreck_01_wav_005a4d78);
                    break;
                }
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
        } else {
            int const pitchDitchID = -DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            if (DAT_TileMapState::instance.pitchDitches[pitchDitchID].uid
                == DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::destroyPitchDitch, DAT_TileMapState::ptr)(pitchDitchID);
            }
        }
    }

}
}
