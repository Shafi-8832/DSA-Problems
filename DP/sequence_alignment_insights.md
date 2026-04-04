# sequence_alignment_insights.md

## 🚪 The 3-Choice Dilemma & Overlapping Subproblems
When characters don't match, why don't we explicitly check the 3rd door: deleting from both (`dp[i-1][j-1] + 2`)?
* **The Truth:** You *can* write it, and it won't overcount or give the wrong answer. But it is computationally **redundant**.
* **The Physics:** If you check Door 1 (Delete from S: `dp[i-1][j] + 1`), that subproblem *already* checked its own doors, including deleting from T. Thus, Door 1 implicitly evaluates the `dp[i-1][j-1] + 2` path.
* **The Rule:** By checking the first two single-deletion doors, the `min()` function will naturally bubble up the `+2` cost if deleting both was truly the cheapest path. The DP grid is interconnected.

## ⚖️ Mutually Exclusive vs. Exhaustive Options
* **Exhaustive (Mandatory):** Your choices must cover all physical realities. If `S[i-1] != T[j-1]`, the final sequence *cannot* end with both. You *must* delete S, OR delete T, OR delete both. The 2 doors cover all 3 realities, making the search exhaustive.
* **Mutually Exclusive (Optional):** In combinatorial DP (counting total ways, like LC 115), paths must be mutually exclusive to avoid double-counting. But for `min/max` optimization DP, overlapping paths don't hurt the math (e.g., `min(5, 5) = 5`); they just waste a tiny bit of CPU.

## 🌌 The DP Reality: The Shrinking Universe
* **The Trap:** Looking at the whole global string. If you look globally, matching characters in the "middle" shouldn't necessarily be locked together (it could cross timelines).
* **The Reality:** The DP engine only thinks in **local prefixes**. When you are in room `dp[i][j]`, the rest of the string does not exist. You are strictly in a mini-universe where $S$ is exactly $i$ characters long, and $T$ is exactly $j$ characters long.
* **The Rule:** In this mini-universe, the characters $S[i-1]$ and $T[j-1]$ are **never** in the middle. They are strictly the **absolute end characters** of reality.

## 🧬 The Golden Rules of Local Prefixes
Because $dp[i][j]$ forces characters to be the absolute "end of the line", these rules are 100% mathematically true for that specific subproblem:
1. **If 2 chars don't match, they can't BOTH be in the LCS (as the last character).** We must test alternate timelines (drop one or the other) to find the true ending character.
2. **If 2 chars match, they MUST BOTH be in the LCS (as the last character).** This is the Greedy Choice Property. Lock them together, add +1, and ask `dp[i-1][j-1]` to solve the rest.
3. **2 chars are the same IF AND ONLY IF they can both be paired up in the LCS.**

## 🗑️ The LCS Leap: The Math of Deletion
Why does finding the minimum deletion cost (LeetCode 583) mathematically equal finding the Longest Common Subsequence (LCS)?
* Let $L$ be the length of the surviving identical string.
* Deletions in $S$ = `Length(S) - L`
* Deletions in $T$ = `Length(T) - L`
* **Total Deletions** = `Length(S) + Length(T) - 2L`
* **The Optimization:** $Length(S)$ and $Length(T)$ are locked fixed numbers. To make Total Deletions as *small* as possible, you must make $L$ as *large* as possible. Max $L$ is exactly the LCS.
