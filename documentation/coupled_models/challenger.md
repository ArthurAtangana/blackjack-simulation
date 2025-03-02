# Challenger Coupled Model
![img](challenger.png)
## X - Input
The player takes in cards, differentiated by the following ranks:
$$ X = \{A,2,3,4,5,6,7,8,9,10,J,Q,K\} $$
## Y - Output
Outputs the decision it takes at the end of the turn. If they stand, they also report the score at the end (count value).
$$Y = {HIT,STAND\_count}$$
$$ count \in \mathbb{N} \cap [1, 30]$$

## M - Set of Component Models
M = {hand, threshold}

## EIC - [External Input Couplings
EIC = {challenger.card->hand.card}
## EOC - External Output Couplings
EOC = {threshold.decision->challenger.decision}

## IC - Internal Couplings
IC = {hand.count->threshold.count}

## Select
It's better to take the decision of the previous turn first before processing the updated hand.
That said, you should never be drawing before your turn is ended so if this happens in simulation 
something has gone wrong already.

SELECT: ({hand, threshold}) = threshold
