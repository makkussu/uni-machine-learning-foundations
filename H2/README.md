Code for this task can be found at [this link](https://gitlab.cs.taltech.ee/mausma/iti0210-2023/-/blob/master/H2/main.c).

# Introduction

The data will be presented in a form of sections, where each section is equal to a chessboard size. 

Section will contain ten images (furter referred as samples) and statistics regarding the sample: success rate, used position and issues.

## The All Mighty Algorithm
In order to understand the results from samples, the local search [hill climbing] algorithm implementation must be explained.

Little dictionary:
* value = the amount of 'captures' a queen can perform

Each queen is positioned on **a different row in a different column**. Thus no queen can have a direct contact after initialization (meaning two queens cannot be put side-by-side).

The algorithm works the following way: 
* Find a queen with the largest value (if multiple, choose randomly)
* Move it vertically, calculate its personal value and global value for each cell.
* Save the least conflicting cell (if multiple, choose randomly)
* Move the queen to the previously saved cell

If the algorithm is stuck, after nearly five iterations it choosen a random queen and performs the same tasks as previously mentioned.

For example:\
[x x x x]\
[x q x q]\
[q x q x]\
[x x x x]\

Queens on positions (1, 1) && (2, 2) are the most valuable, as they both can capture 3 queens. Thus a random one is chosen and moved vertically until the most optimal cell is found (in this case its (0, 1) for (1,1) and (2, 3) for (2, 2)).

**NB!** Upper 2D array is the initial matrix, while the next one is the final matrix.

Tables are structures as following:
* Try: the number of sample, which can be found in the linked folder.
* Initial value: the total amount of 'captures' after initialization
* Final value: the total amount of 'captures' after moving queens.
* Difference: difference between initial and final values.
* Success rate: the amount of zeros in 'Final value' column.

## 4x4 Board
[Link to folder with screenshots](./img/4x4/)
| Try | Initial Value | Final Value  | Difference |
|-----|---------------|--------------|------------|
|   1 | 4             | 0            |      4     |
|   2 | 2             | 0            |       2    |
|   3 | 1             | 0            |       1    |
|   4 | 2             | 2            |       0    |
|   5 | 2             | 0            |       2    |
|   6 | 2             | 1            |       1    |
|   7 | 2             | 0            |       2    |
|   8 | 0             | 0            |       0    |
|   9 | 4             | 0            |       4    |
|   10| 1             | 0            |       1    |

Success rate: ~80%

## 5x5 Board
[Link to folder with screenshots](./img/5x5/)
| Try | Initial Value | Final Value  | Difference |
|-----|---------------|--------------|------------|
|   1 | 2             | 0            |      2     |
|   2 | 2             | 0            |       2    |
|   3 | 2             | 0            |       2    |
|   4 | 2             | 0            |       2    |
|   5 | 2             | 0            |       2    |
|   6 | 2             | 0            |       2    |
|   7 | 6             | 0            |       6    |
|   8 | 2             | 0            |       2    |
|   9 | 2             | 0            |       2    |
|   10| 2             | 0            |       2    |

Success rate: 100% (**Update:** I cannot confirm whether it is constant for this size)

## 6x6 Board
[Link to folder with screenshots](./img/6x6/)
| Try | Initial Value | Final Value  | Difference |
|-----|---------------|--------------|------------|
|   1 | 5             | 1            |      4     |
|   2 | 1             | 1            |       0    |
|   3 | 4             | 1            |       3    |
|   4 | 9             | 0            |       9    |
|   5 | 4             | 0            |       4    |
|   6 | 5             | 3            |       2    |
|   7 | 5             | 3            |       2    |
|   8 | 5             | 1            |       4    |
|   9 | 1            | 0            |       1    |
|   10| 4             | 0            |       4    |

Success rate: ~40%

## 7x7 Board
[Link to folder with screenshots](./img/7x7/)
| Try | Initial Value | Final Value  | Difference |
|-----|---------------|--------------|------------|
|   1 | 7             | 0            |      7     |
|   2 | 6             | 3            |       3    |
|   3 | 5             | 0            |       5    |
|   4 | 4             | 0            |       4    |
|   5 | 5             | 1            |       4    |
|   6 | 0             | 0            |       0    |
|   7 | 7             | 0            |       0    |
|   8 | 5             | 0            |       5    |
|   9 | 3             | 0            |       3    |
|   10| 3             | 2            |       1    |

Success rate: ~70%

## 8x8 Board
[Link to folder with screenshots](./img/8x8/)
| Try | Initial Value | Final Value  | Difference |
|-----|---------------|--------------|------------|
|   1 | 4             | 0            |      4     |
|   2 | 6             | 2            |       4    |
|   3 | 4             | 2            |       2    |
|   4 | 5             | 2            |       3    |
|   5 | 4             | 1            |       3    |
|   6 | 3             | 1            |       2    |
|   7 | 5            | 0            |       5    |
|   8 | 5             | 0            |       5    |
|   9 | 4             | 0            |       4    |
|   10| 6             | 1            |       5    |

Success rate: ~40%

## Issues

**Update:** I have changed one line of code and the algorithm magically works now, thus I have crossed out old 'issues'. Why did not I just remove them? Well, currently unrelated issues are still data and it shows how a little change could affect the whole result. 

1. ~~The algorithm struggles to find a ZERO-value solution. It seems as if it moves around the same queen over and over again, thus getting stuck in a cycle. Even though it quite successfully find a ONE-value solution (as shown in data).~~
2. For some reason the success rate radically changes when switching size of the board and I have absolutely no idea why :')
2. ~~The 'success rate' can be a highly subjective idea. In all samples, the 'final' version of matrix can truly be counted as *final* because every other *individual* move would not change the state of the board at all. However, if we account for ***future possibilities***, then the achieved state can be called a 'failure'. (although I would highly disagree with this, as it seems like the algorithm finds a *local maxima*)~~
3. ~~When entering large numbers such that N >= 50, the difference rate drops significantly. For example, there is a very high possibility that 51 will stay at the same value as its initial state *because* its initial state is the local maxima. It seems as if the rule 'no same column, no same row' automatically leads to the higher probability of achieving local maxima during initialization. Though I would love to be proven wrong here, as this theory makes me quite anxious :')~~
4. If N >= 200, the program is either stuck in a loop or it takes too long to calculate value for each possibility, thus it leads to `segfault`. I guess my memory manipulations overload the program as well, thus leading to its crash.