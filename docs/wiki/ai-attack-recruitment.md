# Attack unit recruitment choice

`AICState::randomlySelectAttackUnitTypeToRecruit` chooses one attack role for a player. It clears eleven shared eligibility flags, then marks each role whose configured maximum has not been reached. The engineer target is the smaller of `AttMaxEngineers` and four times the current attack-wave number. Digging units additionally require the opponent to own more than five moat tiles.

If several roles are eligible, the function draws uniformly among those roles and advances the game's second random-number stream once. If none qualifies, it returns the ordinary main-attack role without drawing.

The function **reads** the player totals for attacking engineers, digging units, assassins, laddermen, tunnelers and the other attack roles. It does not count units or assign them. A recruitment-accounting correction must trace the writers of those totals and the unit's actual duty; changing this selector alone cannot fix a stale count.
