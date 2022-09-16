# The program first asks the user how much change is owed and then prints the minimum number of coins with which that change can be made.
# Assume coins available are quarters (25c), dimes (10c), nickels (5c), and pennies (1c)

from cs50 import get_float

# ask input
dollar_owed = -1
while dollar_owed < 0:
    dollar_owed = get_float("Change owed: ")

# convert to cents
cents_owed = round(dollar_owed * 100)

# get quarters needed
quarters = cents_owed // 25
cents_owed = cents_owed % 25
# get dimes needed
dimes = cents_owed // 10
cents_owed = cents_owed % 10
# get nickels needed
nickels = cents_owed // 5
cents_owed = cents_owed % 5
# get pennies needed
pennies = cents_owed

# total number of coins needed
coins = quarters + dimes + nickels + pennies
print(f"{coins}")