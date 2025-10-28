page 184

5.3.1. Minimum-Comparison Sorting

Merge insertion.

A pleasant generalization of the method above has been discovered by Lester Ford, Jr. and Selmer Johnson. Since it involves some aspects of merging and some aspects of insertion, we shall call it merge insertion. For example, consider the problem of sorting 21 elements. We start by comparing the ten pairs K1 : K2, K3: K4, ... , K19: K20; then we sort the ten larger elements of the pairs, using merge insertion. As a result we obtain the configuration analogous to (5)·

Picture 7.

Main chain (sorted a's):  a1 → a2 → a3 → a4 → a5 → ...
                          ↑    ↑    ↑    ↑    ↑
Smaller elements (b's):   b1   b2   b3   b4   b5   ...

-----
Перший виклик
sort([5, 7, 6, 8, 9, 10, 1, 4, 2, 3])  // 10 елементів
├─ Створює пари: (5,7), (6,8), (9,10), (1,4), (2,3)
└─ merge_sort(pairs) // 5 пар
   ├─ Витягує larger: [7, 8, 10, 4, 3]
   └─ sort([7, 8, 10, 4, 3])  // Рекурсивний виклик

Другий виклик
sort([7, 8, 10, 4, 3])  // 5 елементів
├─ Створює пари: (7,8), (10,4)→(4,10), unpaired=3
└─ merge_sort(pairs) // 2 пари
   ├─ Витягує larger: [8, 10]
   └─ sort([8, 10])  // Рекурсивний виклик

Третій виклик
sort([8, 10])  // 2 елементи
└─ Base case: [8, 10] (вже відсортовано)
-----

Main chain (a's):     [3,  4,  7,  8,  10]  ← Відсортовані larger елементи
Smaller elements(b's): [2,  1,  5,  6,  9]   ← Відповідні smaller елементи
                       ↑   ↑   ↑   ↑   ↑
Співвідношення:       b1≤a1 b2≤a2 b3≤a3 b4≤a4 b5≤a5 ✓
______

The next step is to insert b3 among {b1 , a1, a2}, then b2 among the other elements less than a2; we arrive at the configuration:

Picture 8.

Main chain (a's):      [2,   3,    4,    7,  8,  10]  ← Відсортовані елементи + b1
Smaller elements(b's): [1,   5,    6,    9]           ← Відповідні smaller елементи
                       ↑     ↑     ↑     ↑
Співвідношення:       b1≤a1 b2≤a2 b3≤a3 b4≤a4

Let us call the upper-line elements the main chain. We can insert b5 into its proper place in the main chain, using three comparisons (first comparing it to c4, then c 2 or c 6 , etc.); then b4 can be moved into the main chain in three more steps, leading to:

Picture 9.

The next step is crucial; is it clear what to do? We insert bu (not b7 ) into the main chain, using only four comparisons. Then b10 , b9 , b8 , b7 , b6 (in this order)
can also be inserted into their proper places in the main chain, using at most four comparisons each.

A careful count of the comparisons involved here shows that the 21 elements have been sorted in at most 10+ S(lO) + 2 + 2 + 3 + 3 +4+ 4+4 +4+ 4+4 = 66 steps.

Since

2 to the power of 65 < 21! < 2 to the power of 66,

we also know that no fewer than 66 would be possible in any event; hence

S(21) = 66.

(Binary insertion would have required 74 comparisons.)

In general, merge insertion proceeds as follows for n elements:
i) Make pairwise comparisons of [n/2] disjoint pairs of elements. (If n is odd, leave one element out.)
ii) Sort the [n/2] larger numbers, found in step (i), by merge insertion.
iii) Name the elements a1, a2, ... , a[n/2], b1, b2, ... , b[n/2] as in (Picture 7), where a1 <= a2 ... <=> a[n/2] and bi <= i for 1 <= i <= [n/2]; call b1 and the a's the "main chain". Insert the remaining b's into the main chain, using binary
insertion, in the following order, leaving out all bj for j > [n/2]:

Picture 11:
b3,b2; b5,b4; b11,b10,...,b6; ...; btk,btk-1, ... ,btk-1+1; ....

We wish to define the sequence (t1, t2, t3, t4, ... ) = (1, 3, 5, 11, ... ), which appears in (11), in such a way that each of btk1  btk-1, ... , btk-1+1 can be inserted into the main chain with at most k comparisons. Generalizing (7), (8), and (g), we obtain the diagram:

(diagram)

where the main chain up to and including atk-1 contains 2tk-1 + (tk - tk-1 - 1) elements.
This number must be less than 2 to the power of k; our best bet is to set it equal to 2k - 1, so that:

Picture 12.

tk-1 + tk = 2 to the power of k.

(Continuation.)
