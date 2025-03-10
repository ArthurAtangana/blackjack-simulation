# Final Report
## Model Specifications
### Atomic Models
#### Controller
![controller model](controller.png)

##### X - Inputs
Start: Input to start the game. 
Decisions: A player can ask to HIT to draw another card, and stand to stop drawing. 
Score: Final score reported when a player stands.

$$ X = (start, decision, score)$$
$$ start \in \mathbb{B}$$
$$ decision \in \{HIT, STAND\}$$
$$ score \in \mathbb{N} \cap [1,30]$$

##### S - States
The state of the controller is composed of four components. 
The player currently playing ($s_1$), the challenger's score($s_2$), the dealer's score($s_3$), 
the last input ($s_4$). We add the IDLE to s4 to idle in-between inputs.

$$ s1 \in \{CHALLENGER, DEALER\}$$
$$ s2, s3 \in \mathbb{N} \cap [1,30]$$
$$ s4 \in decision \cup \{IDLE\}$$
$$ S = \{(s1,s2,s3,s4)\} $$

##### Y - Outputs
The controller outputs commands, and game outcomes. 
It also makes use of players to communicate who to draw for.
$$ Y =  (command, player, outcome)$$
$$ command \in \{SHUFFLE, DRAW\}$$
$$ player \in \{CHALLENGER, DEALER\}$$
$$ outcome \in \{WIN, TIE, LOSS\}$$

##### $\delta$<sub>int</sub> - Internal transitions
The internal transition behaviour is strongly dependent on the value in $s_4$, 
therefore we define $\delta_{int}$ based on it. Note, $s_4$ = IDLE is ignored because of its infinite ta value.

##### Check Winner function
This function compares the internal state to determine the game winner.
Note: CONTINUE indicates no winner, game should continue.
$$ \begin{align}
check\_winner(chal, deal) = \{\ 
&if\ chal > 21 &then\ LOSE \\
&if\ deal = 0 &then\ CONTINUE\\
& if\ deal > 21 &then\ WIN \\
& if\ deal = chal &then\ TIE \\
& if\ chal > deal &then\ WIN \\
& if\ chal < deal &then\ LOSE
\}
\end{align}
$$

##### $\delta_{int}$
$$ \delta_{int}(\_, \_, \_, START) = (CHALLENGER, 0, 0, IDLE)$$
$$ \delta_{int}(s1, s2, s3, HIT) = (s1, s2, s3, IDLE)$$
$$ \delta_{int}(\_, \_, \_, STAND) = \{if\ check\_winner(s2, s3) != CONTINUE\ then\ (s1, s2, s3, IDLE)\ else\ (DEALER, s2, s3, HIT)\}$$
- For stand, we check if the game should end. Otherwise, it must be the dealer's turn to go next 
(since it's always the challenger, then the dealer's turn to play before ending the game).

##### $\delta$<sub>ext</sub> - External transitions
External inputs simply get stored directly in s4, its purpose is to store the last input. 
We ignore inputs if there already is an input to process, although this should never happen normally. 
It is probably an error in the model in that case.

$$ \delta_{ext}((1, \_, \_), (s1,s2,s3,s4))= (s1,s2,s3,SHUFFLE)$$
$$ \delta_{ext}((0, HIT, _), (s1,s2,s3,s4))= (s1,s2,s3,HIT)$$
$$ \delta_{ext}((0, STAND, value), (CHALLENGER,s2,s3,s4))= (s1,value,s3,STAND)$$
$$ \delta_{ext}((0, STAND, value), (DEALER,s2,s3,s4))= (s1,s2,value,STAND)$$

##### ta - Time advance function
Note: The time advance is entirely dependent on $s_4$.

$$ \text{if}\ S_{\{\text{_, _, _, START}\}}\ or\ S_{\{\text{_, _, _, HIT}\}}\rightarrow \tau_a = 0 $$
$$ \text{if}\ S_{\{\text{_, _, _, STAND}\}}\ \rightarrow \tau_a = 1$$
$$ \text{if}\ S_{\{\text{_, _, _, CHECK_WINNER}\}}\ \rightarrow \tau_a = 2$$
$$ \text{if}\ S_{\{\text{_, _, _, IDLE}\}}\ \rightarrow \tau_a = inf$$

##### $\lambda$ - Output function
Note: We don't handle the IDLE $s_4$ because it has an infinite time advance. 
We re-use the check_winner function mentioned in the internal transition section

##### Output function
Note: _ indicates no output for that port
$$ \begin{align}
lambda(s) = \{\ &if\ s_4=HIT &then\ (DRAW, s_1, \_) \\
& if\ s_4=START &then\ (SHUFFLE, \_, \_)  \\
& if\ s_4=CHECK\_WINNER\ &then\ (\_, \_, check\_winner(s2, s3))\} 
\end{align}
$$
#### Deck
![deck model](deck.png)

##### X - Inputs
Inputs are composed of commands, and players (to specify who to draw for).
$$ X = (c, p)$$
$$ p \in \{CHALLENGER, DEALER\}$$
$$ c \in \{SHUFFLE, DRAW\}$$
Command description:
- SHUFFLE: shuffles the cards in the deck
- DRAW: draw one card in the deck, for the given player (p).
##### S - States

$$ S = \{(\text{deck, action})\ |\ \text{deck} \subseteq D, 
\text{active} \in \{\text{idle, draw_challenger, draw_dealer,  shuffle}\}\} $$

- deck: the list of remaining cards
- D: the 52 card standard deck
##### Y - Outputs
There are two ports to select where the card is going. A card should only go on one port at a time.
There is also a port for the deck to notify the controller to draw after a shuffle.
$$ Y = (dealer_card, challenger_card, hit_out)$$
$$ dealer_card, challenger_card \in {A,2,3,4,5,6,7,8,9,10,J,Q,K}$$
$$ hit_out \in \{HIT\}$$


##### $\delta_{int}$ - Internal transitions
Note: DRAW_X indicates don't care value, either one behaves the same.
$$ \delta_{int}( \{\text{deck, draw_dealer}\}) \rightarrow \text{deck}-1 \rightarrow S_{\{\text{deck, idle}\}} $$
$$ \delta_{int}( \{\text{deck, draw_challenger}\}) \rightarrow \text{deck}-1 \rightarrow S_{\{\text{deck, idle}\}} $$
$$ \delta_{int}(\{\text{deck, shuffle}\}) \rightarrow \text{shuffle deck} \rightarrow S_{\{\text{deck, idle}\}} $$
##### $\delta_{ext}$ - External transitions
$$ \delta_{ext}(\text{\{draw, dealer\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, draw_dealer}\}} $$
$$ \delta_{ext}(\text{\{draw, challenger\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, draw_challenger}\}} $$
$$ \delta_{ext}(\text{\{shuffle, _\}},\{\text{deck, idle}\}) \rightarrow S_{\{\text{deck, shuffle}\}} $$
##### ta - Time advance function
Note: DRAW_X indicates don't care value, either one behaves the same.
$$ \text{if}\ S_{\{\text{deck, idle}\}} \rightarrow \tau_a = \infty $$
$$ \text{if}\ S_{\{\text{deck, draw_dealer}\}} \rightarrow \tau_a = 1s $$
$$ \text{if}\ S_{\{\text{deck, draw_challenger}\}} \rightarrow \tau_a = 1s $$
$$ \text{if}\ S_{\{\text{deck, shuffle}\}} \rightarrow \tau_a = 10s $$

##### $\lambda$ - Output function
The draw outputs encode the player to send the card to first, then the card drawn (returned by the drawing function).
When the deck is shuffled, the deck model communicates back to draw immediately from it. 
Note: _ used to show that nothing is set on that output port. 

$$ \text{if}\ S_{\{\text{deck, draw_challenger}\}} \rightarrow (\_, draw(deck), \_)$$
$$ \text{if}\ S_{\{\text{deck, draw_dealer}\}} \rightarrow (draw(deck), \_, \_)$$
$$ \text{if}\ S_{\{\text{deck, shuffle}\}} \rightarrow (\_, \_, HIT)$$

- draw(deck) returns any card remaining in the deck, equally weighted.
#### Hand
![hand model](hand.png)

##### X - Inputs
The possible card ranks that can come into the hand:
$$X = \{A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K\}$$

##### S - States
The max is 30 in the case that the hand has 20 (max value before winning or busting), and gets a 10 value card.
v is the stored card value so far, c is the card received plus 0 if no new card has arrived yet (idle).
$$ S = \{(v, c)\} \quad$$
$$v \in \mathbb{N} \cap [1, 30]$$
$$c \in X \cup\{0\}$$

##### Y - Outputs
The output is $s'_v$ (see output function / internal transition), 
the addition of the card value and the current stored. It follows that it has the same domain as v.
$$ Y = \{(v)\} \quad
v \in \mathbb{N} \cap [1, 30]$$

##### $\delta$<sub>int</sub> - Internal transitions
Ignore when c = 0, infinite ta. The value needs to reset to 0 everytime it is processed:

$$ \delta_{int}(s)= (\lambda(s),\ 0)$$
Note: $s_v, s_c$ refers to the value component and the card component of the current state.

##### $\delta$<sub>ext</sub> - External transitions
We ignore the elapsed time, should not be relevant. Sets the card in state to the input card.
$$ \delta_{ext}(c, s)= (s_v,\ c)$$
Note: $s_v$ refers to the value component of the current state.

##### ta - Time advance function
There are two state categories the time advance cares about: There is an input to evaluate, or there isn't.
If there is, compute the value (compute time, around 0.1 seconds), otherwise, do nothing.
Note: "_" refers to any value (don't care value), we do not need this value to evaluate ta.

###### s = (_, 0)
ta = infinite
###### s != (_, 0)
ta = compute_time = 0.1s + variation


##### $\lambda$ - Output function

###### Card Conversion function
There are cards which have their ranks as numbers, 
but there are also special cards which need to be converted to a numerical value.
This function captures this part of the output function process.
$$ \begin{align}
    conv(c) = \{\ &if\ A &then\ 1 \\
    & if\ (J\ or\ Q\ or\ K) &then\ 10 \\
    & else &then \ c \} \\
    \end{align}
$$

###### Output function
$$ \lambda(s) = s_v + conv(s_c) $$ 
#### Threshold
![threshold model](threshold.png)

##### X - Inputs
The inputs are the values that are intended to be compared with the internal threshold value. 
The max is 30 in the case that the hand has 20, and gets a 10 value card.
$$ X = x \in \mathbb{N} \cap [1, 30]$$

##### S - States
Threshold states are tuples composed of two values: (t, v). t is the threshold value set by the component, static. 
v is the comparison value it receives as an input (+0 for the idle state). Their domain is specified as follows:

$$ S = \{(t,v)\} $$
$$ t \in \mathbb{N} \cap [1, 21]$$
$$ v \in X \cup\{0\}$$

##### Y - Outputs
Decisions to take, based on the comparison between the threshold and input value (see output function).
Note: STAND appends the player score at the end which shares the range of $v$.
$$ Y = (d, v) $$
$$ d \in \{HIT, STAND\} $$
$$ v \in X \cup\{0\}$$

##### $\delta_{int}$ - Internal transitions
Ignore when v = 0, infinite ta. The value needs to reset to 0 everytime it is processed:

$$ \delta_{int}(s)= (s_t,\ 0)$$
Note: $s_t$ refers to the threshold value component of the current state.

##### $\delta_{ext}$- External transitions
We ignore the elapsed time, should not be relevant. Sets the value in state to the input value.
$$ \delta_{ext}(v, s)= (s_t,\ v)$$
Note: $s_t$ refers to the threshold value component of the current state.

##### ta - Time advance function
There are two state categories the time advance cares about: There is an input to evaluate, or there isn't. 
If there is, take a decision (think time, around 0.1 seconds), otherwise, do nothing. 
Note: "_" refers to any value (don't care value), we do not need this value to evaluate ta.

###### s = (_, 0)
ta = infinite
###### s != (_, 0)
ta = think_time = 0.1s + variation

##### $\lambda$ - Output function
Ignore when v = 0, infinite ta. When the value meets the threshold (or above), take the decision to STAND. 
Otherwise, keep hitting (HIT).

$$ \begin{align}
\lambda(s) =\ & \{ if  &s_t > s_v & \quad then\ (HIT, 0) \\
&\ else && \quad then \ (STAND, s_v)
\end{align}$$ 

### Coupled Models
#### Challenger
![img](challenger.png)
##### X - Input
The player takes in cards, differentiated by the following ranks:
$$ X = \{A,2,3,4,5,6,7,8,9,10,J,Q,K\} $$
##### Y - Output
Outputs the decision it takes at the end of the turn. If they stand, they also report the score at the end (count value).
$$Y = {HIT,STAND\_count}$$
$$ count \in \mathbb{N} \cap [1, 30]$$

##### M - Set of Component Models
M = {hand, threshold}

##### EIC - [External Input Couplings
EIC = {challenger.card->hand.card}
##### EOC - External Output Couplings
EOC = {(challenger.cardIn->hand.cardIn),
(threshold.decision->challenger.decision),
(threshold.valueOut->challenger.scoreOut),
}

##### IC - Internal Couplings
IC = {hand.handValueOut->threshold.valueIn}

##### Select
It's better to take the decision of the previous turn first before processing the updated hand.
That said, you should never be drawing before your turn is ended so if this happens in simulation 
something has gone wrong already.

SELECT: ({hand, threshold}) = threshold

#### Dealer
![img](dealer.png)
##### X - Input
The dealer takes in cards, differentiated by the following ranks:
$$ X = \{A,2,3,4,5,6,7,8,9,10,J,Q,K\} $$
##### Y - Output
Outputs the decision it takes at the end of the turn. If they stand, they also report the score at the end (count value).
$$Y = {HIT,STAND\_count}$$
$$ count \in \mathbb{N} \cap [1, 30]$$

##### M - Set of Component Models
M = {hand, threshold}

##### EIC - [External Input Couplings
EIC = {dealer.card->hand.card}
##### EOC - External Output Couplings
EOC = {(dealer.cardIn->hand.cardIn),
(threshold.decision->dealer.decision),
(threshold.valueOut->dealer.scoreOut),
}

##### IC - Internal Couplings
IC = {hand.handValueOut->threshold.valueIn}

##### Select
It's better to take the decision of the previous turn first before processing the updated hand.
That said, you should never be drawing before your turn is ended so if this happens in simulation
something has gone wrong already.

SELECT: ({hand, threshold}) = threshold

#### Game
![game](game.png)
##### X - Input
{start}
##### Y - Output
{win,lose,tie}

##### M - Set of Component Models
{controller, deck, players}

##### EIC - External Input Couplings
{(game.start,controller.start)}

##### EOC - External Output Couplings
{(controller.outcome,game.out), (game.gameStartIn,controller.startIn)}

##### IC - Internal Couplings
{
 (controller.cmd,deck.cmd),
 (controller.player,deck.player),
 (deck.challengerOut,player.challengerIn),
 (deck.dealerOut,player.dealerIn),
 (deck.hitOut,controller.decision),
 (players.decision,controller.decision),
}

##### Select:
- It's better to take the decision of the previous turn first before processing the updated hand.
- That said, you should never be drawing before your turn is ended so if this happens in simulation something has gone wrong already.

SELECT: 
- {controller, deck} = deck
- {controller, players} = players
- {deck, players} = players
- {controller, players} = players
- {controller, players, deck} = players

#### Players
![img](players.png)
##### X - Input
A player takes in cards, differentiated by the following ranks:
$$ X = \{A,2,3,4,5,6,7,8,9,10,J,Q,K\} $$

##### Y - Output
Outputs the decision the player takes at the end of the turn. If they stand, they also report the score at the end (count value).
The controller keeps track of the current player, no need to encode it.

$$Y = {HIT,STAND\_count}$$
$$ count \in \mathbb{N} \cap [1, 30]$$

##### M - Set of Component Models
M = {challenger, dealer}

##### EIC - External Input Couplings
EIC = {(players.card_dealer, dealer.card), (players.card_challenger, challenger.card)}

##### EOC - External Output Couplings
EOC = {(challenger.decision, players.decision), (dealer.decision, players.decision),
(players.dealerIn, dealer.cardIn), (players.challengerIn, challenger.cardIn)}

##### IC - Internal Couplings
IC = $\emptyset$ 

##### Select
Normally, player is supposed to take their turn first so they have priority. 
They're also supposed to take their turns sequentially, in a mutually exclusive manner.
This means if SELECT is needed there is likely an error in the simulation.

SELECT: ({dealer, player}) = player

## Tests and Scripts


