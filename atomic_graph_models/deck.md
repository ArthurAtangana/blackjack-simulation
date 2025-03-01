# Deck Formal DEVS Specification
![deck model](deck.png)

## X - Inputs
{shuffle,draw}
- Shuffle: shuffles the cards in the deck
- draw: draw one card in the deck
## S - States

$$ S = \{(\text{deck},\text{active})\ |\ \text{deck} \subseteq D, \text{active} \in \{\text{idle},\text{draw},\text{shuffle}\}\} $$
- deck: the list of remaining cards
- D: the total deck
## Y - Outputs
{ace,2,3,4,5,6,7,8,9,10,jack,queen,king,updated}

## $\delta_{int}$ - Internal transitions
$$ if\ S_{\{\text{deck},\text{drawing}\}} \rightarrow \text{deck} - 1 \rightarrow S_{\{\text{deck},\text{idle}\}}$$ 
$$ if\ S_{\{\text{deck},\text{shuffle}\}} \rightarrow \text{shuffle deck} \rightarrow S_{\{\text{deck},\text{idle}\}}$$
## $\delta_{ext}$ - External transitions
$$ S_{(\text{draw}),\{\text{deck},\text{idle}\}} \rightarrow S_{\{\text{deck},\text{draw}\}} $$
$$ S_{(\text{shuffle}),\{\text{deck},\text{idle}\}} \rightarrow S_{\{\text{deck},\text{shuffle}\}} $$
## ta - Time advance function
$$ \text{if}\ S_{\{\text{deck},\text{idle}\}} \rightarrow \tau_a = \infty $$
$$ \text{if}\ S_{\{\text{deck},\text{draw}\}} \rightarrow \tau_a = 1s $$
$$ \text{if}\ S_{\{\text{deck},\text{shuffle}\}} \rightarrow \tau_a = 10s $$

## $\lambda$ - Output function
### random variable
- R={2,3,4,5,6,7,8,9,10,J,Q,K,A}
- S={♡,♢,♣,♠}
- deck=R×S
where deck is shuffled


$$ \text{if}\ S_{\{\text{deck},\text{draw}\}} \rightarrow top(deck)$$


