#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::Player::PlayerData;
    using Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3150
    void LandscapeState::spawnCrowFromNearbyTree(int unitID)
    {
        int _treeID;
        uint uVar2;
        uint uVar3;
        int iVar5;
        PlayerData* _pKeep;
        uint uVar6;
        int iVar7;
        int iVar8;
        int local_2c;
        int _microY;
        int _microX;
        int local_1c;
        int local_c;
        bool bVar1 = false;
        for (local_c = 0; local_c < 8; local_c++) {
            int _y = (int)DAT_UnitsState::instance.units[unitID].y;
            if ((((DAT_TileMapState::instance
                          .OrganismLayer[DAT_TileMapState::instance.directionTranslationMatrix[_y][local_c]
                              + DAT_UnitsState::instance.units[unitID].tile]
                      != 0)
                     && (_treeID = (int)DAT_TileMapState::instance
                             .OrganismLayer[DAT_TileMapState::instance.directionTranslationMatrix[_y][local_c]
                                 + DAT_UnitsState::instance.units[unitID].tile],
                         _treeID < this->maxTreeCount))
                    && (this->trees[_treeID].state == 2))
                && ((this->trees[_treeID].unknownDistanceRelatedToCrow != 0
                    && (this->trees[_treeID].rng200till300 == 0)))) {
                int _playerID = (int)DAT_UnitsState::instance.units[unitID].owner;
                _microX = 0;
                _microY = 0;
                local_2c = 10000;
                local_1c = 3;
                _pKeep = &DAT_GameState::instance.playerDataArray[1];
                do {
                    if ((local_1c + -2 != _playerID) && ((_pKeep->keep).id)) {
                        iVar5 = (_pKeep->keep).xEntry;
                        iVar8 = (_pKeep->keep).yEntry;
                        uVar2 = DAT_UnitsState::instance.units[unitID].x - iVar5;
                        uVar6 = (int)uVar2 >> 0x1f;
                        uVar3 = _y - iVar8;
                        iVar7 = (uVar2 ^ uVar6) - uVar6;
                        uVar2 = (int)uVar3 >> 0x1f;
                        int iVar4 = (uVar3 ^ uVar2) - uVar2;
                        if (iVar4 < iVar7) {
                            iVar4 = iVar7;
                        }
                        if (iVar4 < local_2c) {
                            _microX = (int)SEC_RNG::instance.currentNumber2 % 5 + -2 + iVar5;
                            _microY = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 5 + -2 + iVar8;
                            local_2c = iVar4;
                        }
                    }
                    if ((local_1c + -1 != _playerID) && (_pKeep[1].keep.id != 0)) {
                        uVar2 = (int)DAT_UnitsState::instance.units[unitID].x - _pKeep[1].keep.xEntry;
                        uVar6 = (int)uVar2 >> 0x1f;
                        uVar3 = _y - _pKeep[1].keep.yEntry;
                        iVar8 = (uVar2 ^ uVar6) - uVar6;
                        uVar2 = (int)uVar3 >> 0x1f;
                        iVar5 = (uVar3 ^ uVar2) - uVar2;
                        if (iVar5 < iVar8) {
                            iVar5 = iVar8;
                        }
                        if (iVar5 < local_2c) {
                            _microX = (int)SEC_RNG::instance.currentNumber2 % 5 + -2 + _pKeep[1].keep.xEntry;
                            _microY = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 5 + -2 + _pKeep[1].keep.yEntry;
                            local_2c = iVar5;
                        }
                    }
                    if ((local_1c != _playerID) && (_pKeep[2].keep.id != 0)) {
                        uVar2 = (int)DAT_UnitsState::instance.units[unitID].x - _pKeep[2].keep.xEntry;
                        uVar6 = (int)uVar2 >> 0x1f;
                        uVar3 = _y - _pKeep[2].keep.yEntry;
                        iVar8 = (uVar2 ^ uVar6) - uVar6;
                        uVar2 = (int)uVar3 >> 0x1f;
                        iVar5 = (uVar3 ^ uVar2) - uVar2;
                        if (iVar5 < iVar8) {
                            iVar5 = iVar8;
                        }
                        if (iVar5 < local_2c) {
                            _microX = (int)SEC_RNG::instance.currentNumber2 % 5 + -2 + _pKeep[2].keep.xEntry;
                            _microY = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 5 + -2 + _pKeep[2].keep.yEntry;
                            local_2c = iVar5;
                        }
                    }
                    if ((local_1c + 1 != _playerID) && (_pKeep[3].keep.id != 0)) {
                        uVar2 = (int)DAT_UnitsState::instance.units[unitID].x - _pKeep[3].keep.xEntry;
                        uVar6 = (int)uVar2 >> 0x1f;
                        uVar3 = _y - _pKeep[3].keep.yEntry;
                        iVar8 = (uVar2 ^ uVar6) - uVar6;
                        uVar2 = (int)uVar3 >> 0x1f;
                        iVar5 = (uVar3 ^ uVar2) - uVar2;
                        if (iVar5 < iVar8) {
                            iVar5 = iVar8;
                        }
                        if (iVar5 < local_2c) {
                            _microX = (int)SEC_RNG::instance.currentNumber2 % 5 + -2 + _pKeep[3].keep.xEntry;
                            _microY = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 5 + -2 + _pKeep[3].keep.yEntry;
                            local_2c = iVar5;
                        }
                    }
                    iVar5 = local_1c + 2;
                    _pKeep = _pKeep + 4;
                    local_1c = local_1c + 4;
                } while (iVar5 < 9);
                if (local_2c == 10000) {
                    _microX = DAT_UnitsState::instance.units[unitID].x + -0x32
                        + (int)SEC_RNG::instance.currentNumber2 % 100;
                    _microY = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 100 + -0x32 + _y;
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                }
                MACRO_CALL_MEMBER(
                    Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                    (undefined4)((int)((int)DAT_UnitsState::instance.units[unitID].owner)), 0,
                    (int)((int)((short)this->trees[_treeID].xPosition * 8)),
                    (int)((int)((short)this->trees[_treeID].yPosition * 8)),
                    (int)((int)(DAT_TileMapState::instance.HeightLayer[this->trees[_treeID].tile] + 0x1e)), _microX * 8,
                    _microY * 8, 0xfa, Map::Entities::EntityTypeInt__ET_CROW, 0);
                this->trees[_treeID].rng200till300 = SEC_RNG::instance.currentNumber2 % 100 + 200;
                if (!bVar1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)this->trees[_treeID].xPosition, (int)((int)((short)this->trees[_treeID].yPosition)),
                        DE::SHCDE::FX_CROW);
                    bVar1 = true;
                }
            }
        }
    }

}
}
