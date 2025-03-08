# Controller Atomic Model
![controller model](controller.png)

## X - Inputs
Start: Input to start the game. 
Decisions: A player can ask to HIT to draw another card, and stand to stop drawing. 
Score: Final score reported when a player stands.

$$X = (start, decision, score)$$
$$ score \in \mathbb{N} \cap [1,30]$$
$$ decision \in \{HIT, STAND\}$$
$$ start \in \mathbb{B}$$

## S - States
The state of the controller is composed of four components. 
The player currently playing ($s_1$), the challenger's score($s_2$), the dealer's score($s_3$), 
the last input ($s_4$). We add the CHECK_WINNER to $s_4$ to allow to transition to checking the winner internally. 
Finally, the IDLE state is also added to s4 to idle in-between inputs.

$$ s1 \in \{CHALLENGER, DEALER\}$$
$$ s2, s3 \in \mathbb{N} \cap [1,30]$$
$$ s4 \in X \cup \{IDLE, CHECK\_WINNER\}$$
$$ S = \{(s1,s2,s3,s4)\} $$

## Y - Outputs
The controller outputs commands, and game outcomes. 
It also makes use of players to communicate who to draw for.
$$ Y =  (command, player, outcome)$$
$$ command \in \{SHUFFLE, DRAW\}$$
$$ player \in \{CHALLENGER, DEALER\}$$
$$ outcome \in \{WIN, TIE, LOSS\}$$

## $\delta$<sub>int</sub> - Internal transitions
The internal transition behaviour is strongly dependent on the value in $s_4$, 
therefore we define $\delta_{int}$ based on it. Note, $s_4$ = IDLE is ignored because of its infinite ta value.
Note: $v$ in $STAND\_v$ is the encoded score value when the player stands, it is assumed it can be parsed and stored.

### Bust Checker
Small helper function to short-circuit game in the case of a BUST. Returns HIT to continue the game if no bust, 
CHECK_WINNER otherwise.
$$check\_bust(v) = \{if\ v > 21\ then\ CHECK\_WINNER \ else\ HIT\}$$

### $\delta_{int}$
$$ \delta_{int}(\_, \_, \_, START) = (CHALLENGER, 0, 0, IDLE)$$
$$ \delta_{int}(s1, s2, s3, HIT) = (s1, s2, s3, IDLE)$$
$$ \delta_{int}(\_, \_, \_, STAND\_v) = \{if\ s1 = CHALLENGER\ then\ (DEALER, v, s3, check\_bust(v))\ else\ (s1, s2, v, CHECK\_WINNER)\}$$
$$ \delta_{int}(\_, \_, \_, CHECK\_WINNER) = (s1, s2, s3, IDLE)$$

## $\delta$<sub>ext</sub> - External transitions
External inputs simply get stored directly in s4, its purpose is to store the last input. 
We ignore inputs if there already is an input to process, although this should never happen normally. 
It is probably an error in the model in that case.

$$ \delta_{ext}(x, (s1,s2,s3,0))= (s1,s2,s3,x)$$
$$ \delta_{ext}(x, (s1,s2,s3,s4))= (s1,s2,s3,s4)$$

## ta - Time advance function
Note: The time advance is entirely dependent on $s_4$.

$$ \text{if}\ S_{\{\text{_, _, _, START}\}}\ or\ S_{\{\text{_, _, _, HIT}\}}\rightarrow \tau_a = 0 $$
$$ \text{if}\ S_{\{\text{_, _, _, STAND}\}}\ \rightarrow \tau_a = 1$$
$$ \text{if}\ S_{\{\text{_, _, _, CHECK_WINNER}\}}\ \rightarrow \tau_a = 2$$
$$ \text{if}\ S_{\{\text{_, _, _, IDLE}\}}\ \rightarrow \tau_a = inf$$

## $\lambda$ - Output function
Note: We don't handle the IDLE $s_4$ because it has an infinite time advance.
### Check Winner function
This function compares the internal state to determine the game winner
$$ \begin{align}
check\_winner(chal, deal) = \{\ &if\ chal > 21 &then\ LOSE \\
& if\ deal > 21 &then\ WIN \\
& if\ deal = chal &then\ TIE \\
& if\ chal > deal &then\ WIN \\
& if\ chal < deal &then\ LOSE \}
\end{align}
$$

### Output function
Note: _ indicates no output for that port
$$ \begin{align}
lambda(s) = \{\ &if\ s_4=HIT &then\ (DRAW, s_1, \_) \\
& if\ s_4=START &then\ (SHUFFLE, \_, \_)  \\
& if\ s_4=CHECK\_WINNER\ &then\ (\_, \_, check\_winner(s2, s3))\} 
\end{align}
$$