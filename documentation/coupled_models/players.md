# Players Coupled Model
![img](players.png)
## X - Input
A player takes in cards, differentiated by the following ranks:
$$ X = \{A,2,3,4,5,6,7,8,9,10,J,Q,K\} $$

## Y - Output
Outputs the decision the player takes at the end of the turn. If they stand, they also report the score at the end (count value).
The controller keeps track of the current player, no need to encode it.

$$Y = {HIT,STAND\_count}$$
$$ count \in \mathbb{N} \cap [1, 30]$$

## M - Set of Component Models
M = {challenger, dealer}

## EIC - External Input Couplings
EIC = {(players.card_dealer, dealer.card), (players.card_challenger, challenger.card)}

## EOC - External Output Couplings
EOC = {(challenger.decision, players.decision), (dealer.decision, players.decision),
(players.dealerIn, dealer.cardIn), (players.challengerIn, challenger.cardIn)}

## IC - Internal Couplings
IC = $\emptyset$ 

## Select
Normally, player is supposed to take their turn first so they have priority. 
They're also supposed to take their turns sequentially, in a mutually exclusive manner.
This means if SELECT is needed there is likely an error in the simulation.

SELECT: ({dealer, player}) = player
