# Experimentation Strategy
## Game Model
The game is responsible for starting a game and getting a winner
- Start a game
- Mock deck to ensure:
   * Dealer Win
   * Challenger Win
   * Tie
## Deck Model
- Receive a shuffle input -> the deck should be shuffled -> output HIT.
- Receive a draw(player) input -> the deck should draw a card to a specific player -> deck = deck - 1
## Controller Model


## Players Model
Players is just a way


- receive a card -> if hand value too low -> HIT
- receive a card -> if count at threshold -> STAND
- receive a card -> if hand value >= threshold -> STAND

## Dealer Model
The dealer is supposed to have a set threshold of 17, 
it is the only difference between them and the challenger. 
Mostly a repeat of the challenger tests, with a set threshold of 17. 

1. Threshold test:
   1. (Threshold hardcoded to 17 for dealer)
   2. Inputs: 7, K
   3. Outputs: HIT, STAND_17
## Challenger Model
A coupling of hand and threshold, with the limitation that the threshold cannot be more than 21.
This implicitly limits hand value to 30, thus the final score to 30. 
Without the controller coupling yet, nothing prevents us from sending more inputs after the STAND.
1. Threshold test (21):
   1. Set threshold to 21
   2. Inputs: 2, 3, 5, 10, K, A
   3. Outputs: HIT, HIT, HIT, HIT, STAND_30, STAND_31
2. Threshold test (1):
   1. Set threshold to 1
   2. Inputs: A, A, 3, 5, 10, K, A
   3. Outputs: STAND_1, STAND_2, STAND_5, STAND_10, STAND_20, STAND_30, STAND_31

## Hand Model
Hand has persistent cumulative state, need to test a series of inputs to see how it behaves.
Hand has a conversion function, need to test that it stores and outputs the right values.
1. Persistence, +conversion test: 
    - Inputs (in order) should be: {A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K}
    - Outputs (in order) should be: 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 65, 75, 85.
    - Limitations: Only testing this assumes a different order will show the same intended behaviour.
## Threshold Model
Threshold has a threshold constant variable (in state). It can take in values to compare against it.
There is no persistence. There are two output types (HIT/STAND), but it also appends the input value if it STANDs.
1. Comparison + no persistence test:
   1. Threshold initialized to 18
   2. in: 18 out: STAND_18
   3. in: 10  out: HIT
   4. in: 44 out: STAND_44
   5. in: 22 out: STAND_22
