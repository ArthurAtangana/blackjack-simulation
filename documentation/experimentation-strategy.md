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
Make sure that cards can be directed to the right player (regardless of order), and they still behave the same as they did isolated.
1. Interweave test
   - Use inputs from dealer, challenger tests defined below but alternate their sent timings.
   - Inputs from Challenger should go on challengerIn port, dealer on DealerIn

## Dealer Model
The dealer is supposed to have a set threshold of 17, 
Mostly a repeat of the challenger tests, with a set threshold of 17. 
1. Threshold test:
   1. Theshold is set to 17
   2. Inputs: 7, 9, A, A
   3. Outputs: (HIT, _), (HIT, _), (STAND, 17), (STAND, 18)

## Challenger Model
A coupling of hand and threshold, with the limitation that the threshold is set to 15.
Without the controller coupling yet, nothing prevents us from sending more inputs after the STAND.
1. Threshold test:
   1. Set threshold to 15
   2. Inputs: 2, 3, 5, 5, 5, K, A
   3. Outputs: (HIT, _), (HIT, _), (HIT, _), (STAND, 15), (STAND, 20), (STAND, 30), (STAND, 31)

## Hand Model
Hand has persistent cumulative state, need to test a series of inputs to see how it behaves.
Hand has a conversion function, need to test that it stores and outputs the right values.
1. Persistence, +conversion test: 
    - Inputs (in order) should be: {A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K}
    - Outputs (in order) should be: 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 65, 75, 85.
    - Limitations: Only testing this assumes a different order will show the same intended behaviour.
2. Test Illegal input NO_CARD. Assume it's a 0 card
   - Inputs: NO_CARD, ACE, NO_CARD 
   - Output: 0, 1, 1
## Threshold Model
Threshold has a threshold constant variable (in state). It can take in values to compare against it.
There is no persistence. There are two output types (HIT/STAND), but it also appends the input value if it STANDs.
1. Threshold-C:
   1. Threshold initialized to 15
   2. in: 15 out: STAND, 15
   5. in: 16 out: STAND, 16
   5. in: 14 out: HIT, _
   3. in: 1  out: HIT, _
   4. in: 44 out: STAND, 44

2. Theshold-D:
   1. Threshold initialized to 17
   2. in: 17 out: STAND, 17
   5. in: 18 out: STAND, 18
   5. in: 16 out: HIT, _
   3. in: 1  out: HIT, _
   4. in: 44 out: STAND, 44
