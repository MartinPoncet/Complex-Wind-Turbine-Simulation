## Wind Turbine Simulation

This program simulates the operation of a wind farm over a specified number of days.

**How to run the program:**

1. Navigate to the directory containing the program.
2. Open a terminal and type `make eolienne`.
3. Run the executable file `eolienne.exe`.

**Program usage:**

1. The program will first ask you to specify the number of days and turbines to simulate.
2. It will then open a menu that allows you to select the type of simulation you want to run.
3. All parameters of the simulation can be modified through this menu without having to access the code.
4. The results of the simulation can be displayed in the console or saved to a text file (`simulation_eoliennes.txt`).

**Program structure:**

The program consists of three modules:

* A module for simulating wind turbines.
* A module for the menu.
* A module for the wind.

There are also two structures:

* `EtatEolienne`: This structure defines the state of an individual wind turbine at a given time during the simulation.
* `Parametres`: This structure stores all the parameters of the program so that they can be modified using the menu.

**Wind enumeration:**

The program uses an enumeration called `Vent` to represent the three possible wind speeds:

* `NUL`: No wind.
* `MOYEN`: Medium wind.
* `FORT`: Strong wind.

This enumeration makes the code easier to understand, but it is not necessary.

**Simulation algorithm:**

The program simulates the operation of a wind turbine by first generating a random wind speed for each day of the simulation. It then uses this wind speed to calculate the amount of energy that the turbine can produce. The program then simulates the operation of the turbine for each day, taking into account factors such as the turbine's efficiency and maintenance costs.

**Output:**

The program can generate a text file that summarizes the results of the simulation. The file contains the following information for each day:

* The day number.
* The wind speed.
* The status of each turbine (operational or broken).
* The amount of energy produced by each turbine.
* The total energy production for the day.
* The total cost of repairs for the day.

The file also contains the total energy production and total cost of repairs for the entire simulation.

**Example:**

The following is an example of the output of the program:

Jour 0 Vent 0	Eolienne 0 +0.000000MW	
Production 0.000000	Cout 0
Jour 1 Vent 1	Eolienne 0 +0.400000MW	
Production 0.400000	Cout 0
Jour 2 Vent 1	Eolienne 0 +0.400000MW	
Production 0.800000	Cout 0
Jour 3 Vent 1	Eolienne 0 +0.400000MW	
Production 1.200000	Cout 0
Jour 4 Vent 1	Eolienne 0 +0.400000MW	
Production 1.600000	Cout 0
Jour 5 Vent 1	Eolienne 0 +0.400000MW	
Production 2.000000	Cout 0
Jour 6 Vent 2	Eolienne 0 cassée	
Production 2.000000	Cout 0
Jour 7 Vent 1	Eolienne 0 cassée 1/3	
Production 2.000000	Cout 150000

Production totale 5.200001	Cout total 150000
