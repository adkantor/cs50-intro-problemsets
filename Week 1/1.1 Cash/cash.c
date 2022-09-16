// The program first asks the user how much change is owed and then prints the minimum number of coins with which that change can be made.
// Assume coins available are quarters (25c), dimes (10c), nickels (5c), and pennies (1c)

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // ask input
    float dollar_owed;
    do
    {
        dollar_owed = get_float("Change owed: ");
    }
    while (dollar_owed < 0);
    // convert to cents
    int cents_owed = round(dollar_owed * 100);
    
    // get quarters needed
    int quarters = cents_owed / 25;
    cents_owed = cents_owed % 25;
    // get dimes needed
    int dimes = cents_owed / 10;
    cents_owed = cents_owed % 10;
    // get nickels needed
    int nickels = cents_owed / 5;
    cents_owed = cents_owed % 5;
    // get pennies needed
    int pennies = cents_owed;

    // total number of coins needed
    int coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);
}
