# Runoff

Implement a program that runs a runoff election, per the below.
```
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

## Specification
Complete the implementation of ```runoff.c``` in such a way that it simulates a runoff election. You should complete the implementations of the ```vot```, ```tabulate```, ```print_winner```, ```find_min```, ```is_tie```, and ```eliminate``` functions, and you should not modify anything else in ```runoff.c``` (except you may include additional header files, if you'd like).

### ```vote```
- The function takes arguments ```voter```, ```rank```, and ```name```. If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.).
- If the preference is successfully recorded, the function should return ```true```; the function should return ```false``` otherwise (if, for instance, name is not the name of one of the candidates).
- You may assume that no two candidates will have the same name.

### ```tabulate```
- The function should update the number of votes each candidate has at this stage in the runoff.
- Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.

### ```print_winner```
- If any candidate has more than half of the vote, their name should be printed to stdout and the function should return ```true```.
- If nobody has won the election yet, the function should return ```false```.

### ```find_min```
- The function should return the minimum vote total for any candidate who is still in the election.

### ```is_tie```
- The function takes an argument ```min```, which will be the minimum number of votes that anyone in the election currently has.
- The function should return ```true``` if every candidate remaining in the election has the same number of votes, and should return ```false``` otherwise.

### ```eliminate```
The function takes an argument ```min```, which will be the minimum number of votes that anyone in the election currently has.
- The function should eliminate the candidate (or candidates) who have ```min``` number of votes.