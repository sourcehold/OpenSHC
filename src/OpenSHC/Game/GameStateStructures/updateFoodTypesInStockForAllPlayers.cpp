#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458A70
    void GameStateStructures::updateFoodTypesInStockForAllPlayers()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].keep.id > 0 && this->playerDataArray[playerID].campground.id > 0) {
                this->playerDataArray[playerID].foodTypesInStock = 0;
                if (this->playerDataArray[playerID].breadCount > 0) {
                    this->playerDataArray[playerID].foodTypesInStock = 1;
                }
                if (this->playerDataArray[playerID].cheeseCount > 0) {
                    this->playerDataArray[playerID].foodTypesInStock
                        = this->playerDataArray[playerID].foodTypesInStock + 1;
                }
                if (this->playerDataArray[playerID].meatCount > 0) {
                    this->playerDataArray[playerID].foodTypesInStock
                        = this->playerDataArray[playerID].foodTypesInStock + 1;
                }
                if (this->playerDataArray[playerID].appleCount > 0) {
                    this->playerDataArray[playerID].foodTypesInStock
                        = this->playerDataArray[playerID].foodTypesInStock + 1;
                }
            }
        }
    }

}
}
