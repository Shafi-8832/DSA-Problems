# mistakes.md

## 🚧 DP Backtracking Mistakes: The Highway Restaurants

### 1. The `i--` Dead Zone Violation
When backtracking through a DP array, using a strict `for (i--)` loop is a trap if the problem has exclusion zones. 
* **The Error:** After evaluating location `i`, `i--` forces you to step exactly one location backwards to `i-1`.
* **The Physical Reality:** If you decide to build a restaurant at location `i`, the law states you cannot have another restaurant within $k$ miles. 
* **The Fix:** If you build at `i`, you must fire up the Time Machine and jump completely over the dead zone straight to `valid_index`. If you just do `i--`, you will accidentally evaluate (and potentially build at) an illegal location inside the dead zone!

### 2. The "Leave It" Assumption Trap
* **The Error:** Assuming that if `dp[i-1]` won the `max()` calculation, you should immediately `locations.push_back(i-1)`.
* **The Lie:** Just because the optimal profit came from `dp[i-1]`, it does **not** mean you actually built a restaurant at `i-1`. Maybe `dp[i-1]` was also a "Leave It", and the actual restaurant is way back at `i-3`.
* **The Fix:** You cannot blindly push `i-1` onto the list. You have to step back (`curr = curr - 1`), wait, and strictly interrogate `i-1` on the next loop iteration to see what it actually did.

### 3. The "Build It" Identity Trap
* **The Error:** Assuming that if "Build It" won, you should push the `valid_index` to your answer list. 
* **The Lie:** If "Build It" won, it means you built a restaurant at your **current** location, `i`. 
* **The Fix:** You should be pushing `i`! The `valid_index` is just the *next* safe place you are allowed to check in the timeline. Push `i`, then teleport your pointer to `valid_index`.