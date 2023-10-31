# Forward Chaining

## The Algorithm
The algorithm does not include any complex logic. Here are very simple steps it follows:

1. Take the clause. If premise count is zero, compare it with query.
2. If it is not the query, then go through every single clause
3. Remove itself from other clauses, thus lowering 'inferred' value
4. If a clause with query-like value has no premises remaining, True is returned

## Input / Output
Example of input:

```
clauses = [
    ([], 'fragile'),
    ([], 'falls down'),
    ([], 'contains liquid'),
    (['falls down', 'fragile'], 'breaks'),
    (['breaks', 'contains liquid'], 'makes a mess'),
    (['spoiled', 'breaks'], 'smells')
]
```

Basically, program takes a list of sets as an input, where premises go first and conclusion goes in the end. 

Output is basically True/False values the program emits.

## Results for queries A to C
Starting data for each query:

| Clause     | Symbol | Premise    | Count | Inferred |
|------------|--------|------------|-------|----------|
| Fragile    | F      | NIL        | 0     | F        |
| Falls Down | FD     | NIL        | 0     | F        |
| Liquid     | L      | NIL        | 0     | F        |
| Breaks     | B      | F, FD      | 2     | F        |
| Mess       | M      | B, L       | 2     | F        |
| Smells     | S      | Spoiled, B | 2     | F        |

Query A final data:

Query: Breaks

| Clause     | Symbol | Premise    | Count | Inferred |
|------------|--------|------------|-------|----------|
| Fragile    | F      | NIL        | 0     | T        |
| Falls Down | FD     | NIL        | 0     | T        |
| Liquid     | L      | NIL        | 0     | T        |
| Breaks     | B      | ~~F~~, ~~FD~~      | 0     | **Returned**        |
| Mess       | M      | B, ~~L~~       |2     | F        |
| Smells     | S      | Spoiled, B | 2     | F        |

Query B final data:

Query: Makes a mess

| Clause     | Symbol | Premise    | Count | Inferred |
|------------|--------|------------|-------|----------|
| Fragile    | F      | NIL        | 0     | T        |
| Falls Down | FD     | NIL        | 0     | T        |
| Liquid     | L      | NIL        | 0     | T        |
| Breaks     | B      | ~~F~~, ~~FD~~      | 0     | T        |
| Mess       | M      | ~~B~~, ~~L~~       | 0     | **Returned**        |
| Smells     | S      | Spoiled, ~~B~~ | 1     | F        |

Query C final data:

Query: Smells

| Clause     | Symbol | Premise    | Count | Inferred |
|------------|--------|------------|-------|----------|
| Fragile    | F      | NIL        | 0     | T        |
| Falls Down | FD     | NIL        | 0     | T        |
| Liquid     | L      | NIL        | 0     | T        |
| Breaks     | B      | ~~F~~, ~~FD~~      | 0     | T        |
| Mess       | M      | ~~B~~, ~~L~~       | 0     | T        |
| Smells     | S      | Spoiled, ~~B~~ | 1     | F        |
