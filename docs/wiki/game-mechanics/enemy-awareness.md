# Enemy awareness

Units periodically check for enemies. These checks are distributed over
different game ticks rather than performed by every unit at once.

The nearest enemy and the enemy chosen for attack are not always the same.
Target selection takes account of the unit's orders, its current target and
the kind of enemy it is considering. A nearby enemy can still affect a unit's
awareness even when that enemy is not chosen as its next target.

Each player has a shared list of potential enemies. The game refreshes these
lists periodically, excluding allies and unsuitable units. The lists have a
fixed capacity. With very large opposing forces, additional enemies can
randomly replace earlier entries, so the list need not contain every enemy.
