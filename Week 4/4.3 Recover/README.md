# Recover

Implement a program that recovers JPEGs from a forensic image, per the below.
```
$ ./recover card.raw
```

## Specification
Implement a program called ```recover``` that recovers JPEGs from a forensic image.
- Implement your program in a file called ```recover.c``` in a directory called ```recover```.
- Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
- If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return ```1```.
- If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return ```1```.
- Your program, if it uses ```malloc```, must not leak any memory.
- When executed, your program should recover every one of the JPEGs from ```card.raw```, storing each as a separate file in your current working directory. Your program should number the files it outputs by naming each ```###.jpg```, where ```###``` is three-digit decimal number from ```000``` on up. (Befriend ```sprintf```.) You need not try to recover the JPEGs' original names.