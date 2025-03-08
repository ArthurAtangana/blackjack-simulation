# Deck Formal DEVS Specification
![deck model](deck.png)

## X - Inputs
Inputs are composed of commands, and players (to specify who to draw for).
$$ X = (c, p)$$
$$ p \in \{CHALLENGER, DEALER\}$$
$$ c \in \{SHUFFLE, DRAW\}$$
Command description:
- SHUFFLE: shuffles the cards in the deck
- DRAW: draw one card in the deck, for the given player (p).
## S - States

$$ S = \{(\text{deck, action})\ |\ \text{deck} \subseteq D, 
\text{active} \in \{\text{idle, draw_challenger, draw_dealer,  shuffle}\}\} $$

- deck: the list of remaining cards
- D: the 52 card standard deck
## Y - Outputs
There are two ports to select where the card is going. A card should only go on one port at a time.
There is also a port for the deck to notify the controller to draw after a shuffle.
$$ Y = (dealer_card, challenger_card, hit_out)$$
$$ dealer_card, challenger_card \in {A,2,3,4,5,6,7,8,9,10,J,Q,K}$$
$$ hit_out \in \{HIT\}$$


## $\delta_{int}$ - Internal transitions
Note: DRAW_X indicates don't care value, either one behaves the same.
$$ \delta_{int}( \{\text{deck, draw_dealer}\}) \rightarrow \text{deck}-1 \rightarrow S_{\{\text{deck, idle}\}} $$
$$ \delta_{int}( \{\text{deck, draw_challenger}\}) \rightarrow \text{deck}-1 \rightarrow S_{\{\text{deck, idle}\}} $$
$$ \delta_{int}(\{\text{deck, shuffle}\}) \rightarrow \text{shuffle deck} \rightarrow S_{\{\text{deck, idle}\}} $$
## $\delta_{ext}$ - External transitions
$$ \delta_{ext}(\text{\{draw, dealer\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, draw_dealer}\}} $$
$$ \delta_{ext}(\text{\{draw, challenger\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, draw_challenger}\}} $$
$$ \delta_{ext}(\text{\{shuffle, _\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, shuffle}\}} $$
## ta - Time advance function
Note: DRAW_X indicates don't care value, either one behaves the same.
$$ \text{if}\ S_{\{\text{deck, idle}\}} \rightarrow \tau_a = \infty $$
$$ \text{if}\ S_{\{\text{deck, draw_dealer}\}} \rightarrow \tau_a = 1s $$
$$ \text{if}\ S_{\{\text{deck, draw_challenger}\}} \rightarrow \tau_a = 1s $$
$$ \text{if}\ S_{\{\text{deck, shuffle}\}} \rightarrow \tau_a = 10s $$

## $\lambda$ - Output function
The draw outputs encode the player to send the card to first, then the card drawn (returned by the drawing function).
When the deck is shuffled, the deck model communicates back to draw immediately from it. 
Note: _ used to show that nothing is set on that output port. 

$$ \text{if}\ S_{\{\text{deck, draw_challenger}\}} \rightarrow (\_, draw(deck), \_)$$
$$ \text{if}\ S_{\{\text{deck, draw_dealer}\}} \rightarrow (draw(deck), \_, \_)$$
$$ \text{if}\ S_{\{\text{deck, shuffle}\}} \rightarrow (\_, \_, HIT)$$

- draw(deck) returns any card remaining in the deck, equally weighted.
