Code for this task can be found at [this link](https://gitlab.cs.taltech.ee/mausma/iti0210-2023/-/blob/master/H1/main.py).

The data will be presented as a table to facilitate
a comparison of the data.

|   300x300    | Time  | Iterations | Step length |
|--------------|-------|------------|-------------|
| BFS          | 143ms |      47233 |         555 |
| GBFS(Greedy) | 13ms  |       2325 |         831 |
| A*           | 39ms  |       8202 |         555 |


|   600x600    | Time  | Iterations | Step length |
|--------------|-------|------------|-------------|
| BFS          | 567ms |     197804 |        1248 |
| GBFS(Greedy) | 53ms  |      10895 |        2356 |
| A*           | 239ms |      60468 |        1248 |

|   900x900    | Time  | Iterations | Step length |
|--------------|-------|------------|-------------|
| BFS          | 1327ms|     450414 |        1844 |
| GBFS(Greedy) | 62ms  |      12771 |        3088 |
| A*           | 384ms |      93995 |        1844 |