# Resolution Method

## The Algorithm
I won't include explanation for `simple_resolution_solver()` function, as it has been copied from the task description. `resolve` is what interests us the most:

First of all, `resolve` takes a `current` and `clause` values, and combines them into a set, 
thus removing any possible duplicates. Then it goes through each element in a set and checks 
whether it has an opposite of itself (basically if 'A' has '-A' in dataset). If such 'contradiction' 
is found, it removes both of the elements from the dataset and returns it as is.

Later on, `simple_resolution_solver` checks whether the list is empty or not. 
If it is, contradiction is found and it return `True`. In every other situation `False` is returned.

## Data

The following table presents a database with very basic queries:

| KB             | Query      | Expected Data Output           | Expected Conclusion | Program Conclusion | Notes                                                      |
|----------------|------------|--------------------------------|---------------------|--------------------|------------------------------------------------------------|
| A v B          | A v -B     | A                              | False               | False              | A is left, thus no  contradiction is found                 |
| A v B v -C     | A v C      | A v B                          | False               | False              | Same as before                                             |
| A v B v -C v D | A v C v -D | A v B v (-C v C) \|\| (-D v D) | False               | False              | Although tautology is present,  A and B are left untouched |
| D              | -D         | Empty                          | True                | True               | Contradiction is found,  no elements are left              |
| A v -B         | A v -C v D | Both remain unchanged          | False               | False              | KB and query are unrelated to each other                   |

Unicorn KB + queries database:

KB-CNF type program accepts: [["-mythical", "immortal"], ["mythical", "mammal"], ["-immortal", "horned"], ["-mammal", "horned"], ["horned", "magical"]]

| Query     | Expected Conclusion | Program Conclusion | Notes                                                                            |
|-----------|---------------------|--------------------|----------------------------------------------------------------------------------|
| -magical  | True                | True               | This is a clear contradiction. No matter the result, the unicorn must be magical |
| -mythical | False               | False              | It can be a mammal, thus no contradictions are here                              |
| -horned   | True                | True               | Same as the first one: no matter the result, the unicorn will be horned          |

## Forward Chaining as incomplete logic method
Forward Chaining, as its name implies, is literally a **chain of forward thinking** or 
deductive/inductive analysis (I apologize, I cannot remember which is which :(  ).
It **requires** foundation to stand on, meaning facts must be present. If we draw a parallel
between egg and unicorn problems, the difference is clear:

Egg problem literally states that egg is fragile, it has liquid inside and might fall down. Later on,
conclusions are made according to this base.

Unicorn problem, however, does not imply anything. It just makes statements without any basis but
facts could be drawn from those statements (as per horning and magical, which are always true). 
The forward chaining algorithm struggles without a foundation to stand on, thus failing to resolve
the task.
