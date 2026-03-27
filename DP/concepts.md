# concept.md

## 🧠 DP Core Concepts

### 1. The "Lazy Manager" Principle
Dynamic Programming is just the ultimate middle manager. When you are standing in a state like `dp[i][j]` and the current items do not match or cannot be easily resolved, you do not try to predict the future or trace the complex steps of the past.

> **The Philosophy:** "I don't know which item is the dead weight, and I am not going to do the heavy lifting to find out. I will just ask my immediate subordinates (`dp[i-1][j]` and `dp[i][j-1]`) for their optimal scores, take the `max()` (or `min()`), write it on my clipboard, and take 100% of the credit."

You delegate the work to the previously solved subproblems. You survive purely on the mathematical guarantee that if every small room is solved perfectly, the big room solves itself.

### 2. The True Definition of "Delete"
In string alignment/edit distance problems, taking the `Delete` path (`dp[i-1][j]`) often feels like a logical contradiction. How can you say you "successfully processed" $i$ characters if you just threw $S[i]$ in the trash?

* **The Trap:** Thinking `dp[i][j]` means "we perfectly paired up $i$ letters with $j$ letters."
* **The Reality:** `dp[i][j]` means "we have successfully *evaluated and dealt with* the first $i$ characters, doing whatever it takes (including murder), to make the surviving string match the target."
* **The Physical Action:** When you delete, you don't pretend $S[i]$ never existed. You look it dead in the eye, realize it is ruining your string, pay your $1 trash collection fee to drop it in the bin, and ask `dp[i-1][j]` for the rest of the recipe. You successfully *processed* that character by destroying it.