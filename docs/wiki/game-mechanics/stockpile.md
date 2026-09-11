# Stockpile

Removing a stockpile clears its nine walkable tiles. Its four building parts
are removed separately.

For each walkable tile, cleanup:

1. Clears the stockpile and wall/gatehouse map-logic flags and restores the
   default terrain height.
2. Updates the former-building and display information according to the
   building's rubble setting. The exact visual effect of one display flag
   remains unidentified.
3. Removes the tile's building reference.

## Placement

Placing a keep creates a starting stockpile for both human and AI players.

The first stockpile needs no adjacent existing stockpile. Further stockpiles
require available capacity and adjacency to the owner's stockpile, as well as
suitable terrain. AI castle placement uses the same placement rules.
