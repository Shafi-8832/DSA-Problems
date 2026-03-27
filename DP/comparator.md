# comparators_and_sorting.md

## ⚖️ Custom Comparators: The "Student ID" Analogy
When you have a basic `vector<int>`, C++'s `std::sort` knows exactly what to do (because $2 < 5$). 

But when you hand it a custom `struct` (like `job` with `start_time`, `finish_time`, and `value`), the compiler completely panics. It doesn't know which field makes one job "less" than another. Should it sort by value? By start time? 

A **custom comparator** is just you acting as the boss and telling the compiler exactly which field to look at to determine the timeline order.

## 🛑 The `<` vs `<=` Trust Issue (Strict Weak Ordering)
You must **ALWAYS** use strictly `<` (less than) in C++ comparators. Never use `<=` (less than or equal to).

* **The Trap:** Thinking `<=` is safer or necessary for jobs that finish at the exact same time.
* **The Physical Reality:** C++ sorting algorithms require a mathematical rule called **Strict Weak Ordering**. One of the absolute rules of this math is that if you compare an item to itself (or an identical item), the answer *must* be `false`.
* **The Crash:** If you use `<=`, and two jobs finish at the exact same time, the comparator returns `true`. The C++ `std::sort` engine gets confused, thinks the items are out of order, tries to swap them, checks again, gets `true` again, and can completely crash your program with a Segmentation Fault or out-of-bounds memory error.

If `a.finish_time == b.finish_time`, they are tied. Neither one is strictly "less" than the other. Therefore, returning `false` is the mathematically correct answer.

```cpp
// The Flawless Comparator for Weighted Interval Scheduling
bool compareFinish(const job& a, const job& b) {
    // MUST be strictly '<' to prevent C++ sorting engine crashes!
    return a.finish_time < b.finish_time; 
}