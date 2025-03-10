# Scripts

## challenger_threshold
Tests the threshold component for the challenger (threshold-c, set threshold of 15), as per the experimental strategy description.

## dealer_threshold
Tests the threshold component for the dealer (threshold-d, set threshold of 17), as per the experimental strategy description.

## controller_lose
This encapsulates the test frame in which the CHALLENGER loses the game.
Demonstrated by rigging the inputs taken from the controller to give the edge to the DEALER.
the controller should outputs LOSE
## controller_win
This encapsulates the test frame in which the challenger wins the game.
Demonstrated by rigging the inputs taken from the controller to give the edge to the CHALLENGER.
the controller should outputs WIN
## controller_win
This encapsulates the test frame in which the CHALLENGER and DEALER tie the game.
Demonstrated by rigging the inputs taken from the controller to have the same hand value.
the controller should outputs TIE
## game
This test frame looks at a full game.
- On a shuffle of [5,...,10,10,9,10], the game should output LOSE.
- On a shuffle of [5,...,9,10,10,10], the game should output WIN.
- On a shuffle of [5,...,10,10,10,10], the game should output TIE.
## deck
This test frames draws a full deck to a player. This accounts for:
- Drawing for both players
- Drawing all the cards in the deck
- Edge cases of attempting to draw an empty deck
The test should reach a point where there is no more cards in the deck (printed in the output)
