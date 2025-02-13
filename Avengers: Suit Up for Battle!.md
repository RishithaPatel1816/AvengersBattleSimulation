# Code Explanation: Avengers Battle Simulation

This document provides a detailed explanation of the C++ code for the Avengers Battle Simulation project. The code is structured around three main classes: `QNS` (Quantum Nanotech Suit), `Avenger`, and `Battle`.

## 1. Class: QNS (Quantum Nanotech Suit)

### Purpose
The `QNS` class represents the Quantum Nanotech Suit worn by the Avengers. It manages the suit's attributes and behavior, such as power level, durability, energy storage, and heat level.

### Attributes
-   `powerLevel` (private, int): The suit's attack strength. Default value: 1000. Represented as P.
-   `durability` (private, int): Armor strength against attacks. Default value: 500. Represented as D.
-   `energyStorage` (private, int): Stores absorbed energy from enemy attacks. Default value: 300. Represented as E.
-   `heatLevel` (private, int): Increases with overuse; if too high, the suit shuts down. Default value: 0. Represented as H.

### Methods

#### Constructors
-   `QNS()`: Default constructor. Initializes all attributes with safe defaults (P=1000, D=500, E=300, H=0).
-   `QNS(int p, int d, int e, int h)`: Parameterized constructor. Initializes `powerLevel`, `durability`, `energyStorage`, and `heatLevel` with given values, applying constraints.
    -   `powerLevel` is capped at 5000.
    -   `heatLevel` is never negative.
-   `QNS(const QNS & q)`: Copy constructor. Duplicates another `QNS` instance.

#### Operator Overloading
-   `void operator+(const QNS &q)`: Overloads the addition operator (+). Used for suit upgradation and to power boost the suit.
    -   Formula: (P1, D1, E1, H1) + (P2, D2, E2, H2) = (P1 + E2, D1 + D2, E1 + P2, H1)
    -   `powerLevel` increases by `q.energyStorage`.
    -   `durability` increases by `q.durability`.
    -   `energyStorage` increases by `q.powerLevel`.
    -   `powerLevel` is capped at 5000.
-   `void operator-(int x)`: Overloads the subtraction operator (-). Simulates damage from an attack, reducing durability and increasing heat.
    -   Formula: (P, D, E, H) - X = (P, D - X, E + X, H + X)
    -   `durability` decreases by `x`.
    -   `energyStorage` increases by `x`.
    -   `heatLevel` increases by `x`.
-   `void operator*(int x)`: Overloads the multiplication operator (\*). Activates Power Boost mode, amplifying attack strength but raising heat.
    -   Formula: (P, D, E, H) \* X = (P + (P \* X) / 100), D, E + 5X, H + X)
    -   `powerLevel` increases by `(P * X) / 100`.
    -   `energyStorage` increases by `5 * x`.
    -   `heatLevel` increases by `x`.
    -   `powerLevel` is capped at 5000.
-   `void operator/(int x)`: Overloads the division operator (/). Activates the cooling system, reducing heat by transferring energy to durability.
    -   Formula: (P, D, E, H) / X = (P, D + X, E, H - X)
    -   `durability` increases by `x`.
    -   `heatLevel` decreases by `x`.
    -   `heatLevel` is never negative.
-   `bool operator==(QNS & q)`: Overloads the equality operator (==). Compares suits based on `powerLevel` and `durability`.
    -   Returns `true` if both `powerLevel` and `durability` are the same.
-   `bool operator<(const QNS & q)`: Overloads the less than operator (<). Compares suit effectiveness in battles.
    -   Returns `true` if the sum of `powerLevel` and `durability` is less than the other suit's sum.

#### Function Overloading
-   `void boostPowerbyFactor(int factor)`: Boosts power by a factor, increasing overheating risk. Uses the `*` operator.
-   `void boostPower(const QNS & othersuit)`: Transfers energy from another suit to boost durability. Uses the `+` operator.

#### Getters
-   `int getP()`: Returns `powerLevel`.
-   `int getD()`: Returns `durability`.
-   `int getE()`: Returns `energyStorage`.
-   `int getH()`: Returns `heatLevel`.

## 2. Class: Avenger

### Purpose
The `Avenger` class represents an Avenger equipped with a Quantum Suit. It manages the Avenger's attributes and actions during the battle.

### Attributes
-   `name` (private, string): The Avenger's name (e.g., "Iron Man", "Thor").
-   `suit` (private, QNS): The quantum suit they wear.
-   `attackStrength` (private, int): Determines the amount of damage this Avenger can make to an opponent.

### Methods
-   `Avenger(string avName, QNS avSuit, int strength)`: Constructor. Assigns values to the attributes.
-   `void attack(Avenger& enemy)`: Damages the enemy's durability by a factor of `attackStrength`.
-   `void damage(int x)`: Reduces the suit's durability and increases heat after an attack by x
-    `void resetDurability(int x)`: repairs durability of the suit by factor x.
-   `bool upgradeSuit(QNS & q)`: Transfers power from a new suit to the current suit. Uses the `+` operator.
-   `void assignSuit(QNS & q)`: Assigns a new suit to the avenger
-   `void repair(int x)`: Restores some durability to their suit by cooling down the suit by factor `x`. Uses the `/` operator.
-   `void printStatus()`: Displays the Avenger's suit details in the format "<Avenger\_Name> <P> <D> <E> <H>".
-   `int getdur()`: Returns durability of the suit
-   `int getpow()`: returns powerlevel of the suit
-   `string getName()`: return name of avenger.
    `int getHeat()`: returns heat level of the avenger

## 3. Class: Battle

### Purpose
The `Battle` class simulates battles between Avengers and enemies. It manages the list of participants, records battle events, and determines the battle's outcome.

### Attributes
-   `heroes` (private, vector<Avenger>): List of Avengers (heroes).
-   `enemies` (private, vector<Avenger>): List of Enemies (villains).
-   `weapons`(private, queue<QNS>) queue of suits
-   `battleLog` (private, vector<string>): Records the battle events in a list.

### Methods

#### Core Battle Logic
-   `void startBattle(string s, Battle & b)`: Runs the battle simulation based on input commands.
    -   Commands include: `Attack`, `Repair`, `BoostPowerByFactor`, `BoostPower`, `AvengerStatus`, `Upgrade`, `PrintBattleLog`, and `BattleStatus`.

#### Support Functions

-   `void printBattleLog()`: Shows battle history by printing each element in `battleLog`.
-   `int Result()`: Sums the power and durability of all heroes and enemies currently in battle, then returns:
    -   `1` if the sum of the Avengers is greater.
    -   `-1` if the sum of the enemies is greater.
    -   `0` in case of a tie.
-   `void createsuit(int p,int d,int e,int h)`: Creates a new suit
-   `void createhero()`: creates a new hero
-   `void createenemy()`: creates a new enemy
-   `void attackof2(string n1,string n2)`: Function to manage attack
-   `void repair(string n,int x)`: Used to manage repair of the suit
-   `pair<int,int> getAvenger(string n)`: This function is used to get the avenger
-   `void boostpower(string s,int x)`: this function is used to boostpower by factor
-   `void printAvengersuit(string s)`: to ptint the suit status of avenger
-   `void upgradesuit(string s)`: upgrading the suit if extra suits are left
-   `void boostparam(string a,int p,int d,int e, int h)`: used to boost suit from other parametrs

#### Helper Functions
*  `pair<int, int> getAvenger(string n)`: Retrieves an avenger 

## Main Function
The `main` function initializes the battle simulation.
1.  Takes input for the number of suits, heroes, and enemies.
2.  Creates suits, heroes, and enemies based on the input.
3.  Starts the battle by calling the `startBattle` method with relevant battle commands.

This structured explanation should provide a clear understanding of each class and its role in the Avengers Battle Simulation.
