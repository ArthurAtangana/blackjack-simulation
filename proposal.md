# Blackjack Model Proposal
## Authors
| Name | Student number |
|-|-|
| Arthur Atangana | 101005197 |
| Alexandre Marques | 1234 |
### Problem Description

- We would like to model the card game called BlackJack. The goal of the game is to get the closest to a hand value of 21 without going over. Face cards are worth 10, aces 1, and all other cards their face value.
- In our version of the game, each player takes their turn sequentially. A player starts their turn by receiving two cards. Afterwards, a player can decide to HIT or STAND. If the player hits, they draw a card, and they can again make a decision to HIT or STAND. This continues until the player stands (ends their turn) or busts (goes over 21, and loses the turn). The dealer goes after the player and behaves in the same way except they have a specific fixed threshold where they are forced to stand. If the dealer stands (did not bust), the hands are compared and the highest hand wins. It is possible to tie if the hands are equal.
- For simplicity, we will ignore some aspects of the real game. We do not model bets, as they would not impact the outcome of the game itself. We are currently thinking of excluding the ace rule where they can be worth 1 or 11 depending on the state of the hand. In our current conceptual model, they would simply be valued at one.

### Model
![blackjack model](model.png)

### Component Description
- **Blackjack**: The component representing the game itself. It contains Deck, Game Controller, and Players components.
- **Deck**: Has the cards of the game, can be shuffled and distributes cards one at a time.
- **Game Controller**: Keeps track of the game states, who is playing and who wins at the end.
- **Players**: A coupled model of all players in the game, including the dealer and the regular player.
- **Dealer**: The dealer of the game, follows special rules compared to normal players. Has a Hand and Threshold atomic model.
- **Regular Player**: Draws cards to reach a total up to 21. Can decide to stop drawing cards ending its turn. Has a Hand and Threshold atomic model.
- **Hand**: Holds the hand of a specific player, receives a card and outputs the current hand value.
- **Threshold**: The decision making model, takes in the current hand value and chooses to HIT or STAND (stop drawing) depending on a threshold value. The dealer’s threshold is fixed, while other players may vary.

