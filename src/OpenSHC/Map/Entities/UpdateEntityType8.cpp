#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // travelledDistance is compared as a signed short (orig `cmp cx, imm; jge` from 0x406FE2).
    // FUNCTION: STRONGHOLDCRUSADER 0x00406FD0
    void Entities::UpdateEntityType8()
    {
        short travelledDistance
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].travelledDistance;
        if (travelledDistance < 0xe) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 8;
        }
        else if (travelledDistance < 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 9;
        }
        else if (travelledDistance < 0x12) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 10;
        }
        else if (travelledDistance < 0x14) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xb;
        }
        else if (travelledDistance < 0x16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xc;
        }
        else if (travelledDistance < 0x18) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xd;
        }
        else if (travelledDistance < 0x1a) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xe;
        }
        else if (travelledDistance < 0x1c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xf;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0x10;
        }
        if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 3) == 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += 0x10;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            MACRO_CALL(OpenSHC::Map::Entities_Func::SomeFireSpreadFunction)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                DAT_TileMapState::instance
                        .HeightLayer[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]
                    + 8,
                5);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition,
                OpenSHC::DE::SHCDE::FX_FIRE_START);
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
    }

}
}
