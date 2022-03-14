# fillit

Hive Helsinki's first pair project which objective is to code a program to find the smallest possible square with the tetriminoes given.

## Idea:

1. Before any dynamic memory allocations we made primary checks to validate the map. If one of the check fails the program outputs an error message and exits.
2. After validating a map the program chops it into smaller pieces to be fed to the algorithm later on.
3. Recursive algorithm that will try to fit each piece into the given minimun sized map.
4. On successful insertion of all tetriminoes the program will print the result.
5. Free all allocated memory before exiting the program.

## Status

- ✅ Completed on **07/03/2022**
- ✅ Score: **100/100**
- ✅ Retires: **1** after one peer evaluation. Found an edge case where an invalid map was accepted as valid.
