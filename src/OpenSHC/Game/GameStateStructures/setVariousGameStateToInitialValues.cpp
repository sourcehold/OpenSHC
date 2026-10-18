#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458990
    void GameStateStructures::setVariousGameStateToInitialValues()
    {
        this->mapAndTime.totalGameTicksUnk = 0;
        this->mapAndTime.treeSpreadCounter = 0;
        this->mapAndTime.treeSpreadInterval = 5;
        this->mapAndTime.gameOver = FALSE;
        this->mapAndTime.singlePlayerHasKeepAndGranary = FALSE;
        this->mapAndTime.eventCountdownRabbitInfestation = 0;
        this->mapAndTime.gameEventRelatedCountdown = 0;
        this->mapAndTime.unk_signpostDistance = 30;
        this->mapAndTime.field3171_0x27a8 = 0;
    }

}
}
