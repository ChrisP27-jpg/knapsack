# knapsack

This program emulates the knapsack problem using baseball cards and their prices. The program takes in a file that holds all the values of all baseball cards. Then it takes in another file that gives us 1 or more knapsack problems. The problem will give us how many total cards are available to buy, how much money we have to spend, and the price of buying each baseball card. This program determines which baseball cards to buy in order for the greatest resale profit and overall value. I've provided some example files.

## Usage

:$ make

:$ ./program1 -m "file with card values" -p "file with knapsack problem"

    OR ./program1 -p "file with knapsack problem" -m "file with card values"
