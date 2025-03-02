# Experimentation Strategy
## Game Model
## Deck Model
- Receive a shuffle input -> the deck should be shuffled -> output a shuffled/updated msg.
- Receive a draw(player) input -> the deck should draw a card to a specific player -> deck = deck - 1
## Controller Model
## Players Model
- receive a card -> if hand value too low -> HIT
- receive a card -> if count at threshold -> STAND
- receive a card -> if hand value >= threshold -> STAND
## Dealer Model
- receive a card -> if hand value too low -> HIT
- receive a card -> if count at threshold -> STAND
- receive a card -> if hand value >= threshold -> STAND
## Challenger Model
- receive a count -> if count >= threshold -> STAND
- receive a count -> if count at threshold -> STAND
- receive a count -> if count <= threshold -> HIT
## Hand Model
- Receive a card -> transform the card into a value and add it to the count -> output current count value
## Threshold Model
- receive a count -> if count >= threshold -> STAND
- receive a count -> if count at threshold -> STAND
- receive a count -> if count <= threshold -> HIT

