# upper_bound_and_dp_edges

## 🔍 `upper_bound()` Extreme Returns
* **Rightmost return** --> `m.end()` [target > even the highest value of the array]
* **Leftmost return** --> `m.begin()` [target < even the lowest value of the array]

These are the 2 extreme returns, so `-1` could arrive. 
*(btw, the lowest value of valid_index is -1 (fun fact))*

## 🏢 The Physics of `dp[0]`
`dp[0] = p[0]`

If I arrive at location 0 walking backwards, then why would I miss the chance to build the restaurant and gain profit? `dp[0]` gets counted!

Cause there is no restriction "Behind" location 0 ! 
not `dp[-1]` neither `dp[valid_index]`
so no need to check with `max()` just add it the total profit and count that location !

## 🛡️ The Padding Rule
> "Whenever you have a "Leave It" condition that looks at `i-1`, pad your DP array by making it size `N+1`, and let index 0 act as your safety net."
