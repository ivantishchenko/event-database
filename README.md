# Event database in C++
Implementation of a simple database in C++. 

# Prerequisites
* Unix based system. The app was tested on Ubuntu on Ubuntu Linux 20.04 LTS and MacOS 12.4.
* Shell e.g. bash or zsh.
* GNU Compiler Collection (GCC) version 11

# Compiling and running
Compile the app:
```bash
make release

# Alternatively for debug mode
# make debug 
```

Run the app:
```bash
./build/apps/main
```

Remove all binaries:
```bash
make clean
```

# Project structure
All headers are in [**include**](include). All sources are in [**src**](src).Here is the structure of the project:
- **main.cpp** - Entry point for an app. Also runs some unit testing.
- **condition_parser.h/cpp** - Parses a condition for **Find** and **Del**. Builds an AST.
- **token.h/cpp** - Tokenizer used in ParseCondition
- **database.h/cpp** - Represents a database
- **node.h/cpp** - Represents terms of the expression
- **data.h/cpp** - Represents the dates and its utilities
- **test_runner.h/cpp** - Simple unit testing framework
- ***_test.h/cpp** - Unit tests for respective components

# Functionality
## Supported commands
Here are the commands the database supports:
- **Add date event** - adds a pair **(data, event)**
- **Print** - prints database content
- **Find condition** - outputs all records, which match the **condition**
- **Del condition** - deletes all records, which math the **condition**
- **Last date** - outputs all records, which occured after the **date**

## Conditional commands
Here are the examples of conditional commands:
- **Find date < 2021-11-06** - finds all events, which occured after 06.11.2021
- **Del event != "holiday"** - deletes all non **"holiday"** events
- **Find date >= 2021-01-01 AND date < 2021-07-01 AND event == "sport event"** - finds all **"sport event"**, which occured in the first half of 2021
- **Del date < 2021-01-01 AND (event == "holiday" OR event == "sport event")** - deletes all events **"holiday"** and **"sport event"**, which occured before 2021

If the **condition** is empty then all entries are matched.

# Commands
## Add
Adds an event.
Input:
```
Add 2021-11-07 big sport event
```
will add **(2021-11-07, big sport event)**. There will be no output.

## Del
Deletes an event. Input:
```
Add 2021-06-01 1st of June
Add 2021-07-08 8th of July
Add 2021-07-08 Someone's birthday
Del date == 2021-07-08
```

Output:
```
Removed 2 entries
```

## Print
Prints event in memory. Input:
```
Add 2021-01-01 Holiday
Add 2021-03-08 Holiday
Add 2021-1-1 New Year
Add 2021-1-1 New Year
Print
```

Output:
```
2021-01-01 Holiday
2021-01-01 New Year
2021-03-08 Holiday
```

## Find
Finds events which match a **condition**. Input:
```
Add 2021-01-01 Holiday
Add 2021-03-08 Holiday
Add 2021-01-01 New Year
Find event != "working day"
Add 2021-05-09 Holiday
```

Output
```
2021-01-01 Holiday
2021-01-01 New Year
2021-03-08 Holiday
Found 3 entries
```

## Last
Finds last event, which occured by **date**. Input:
```
Add 2021-01-01 New Year
Add 2021-03-08 Holiday
Add 2021-01-01 Holiday
Last 2020-12-31
Last 2021-01-01
Last 2021-06-01
Add 2021-05-09 Holiday
```

Output:
```
No entries
2021-01-01 Holiday
2021-03-08 Holiday
```

## Example
Input:
```
Add 2021-11-21 Tuesday
Add 2021-11-20 Monday
Add 2021-11-21 Weekly meeting
Print
Find event != "Weekly meeting"
Last 2021-11-30
Del date > 2021-11-20
Last 2021-11-30
Last 2021-11-01
```

Output:
```
2021-11-20 Monday
2021-11-21 Tuesday
2021-11-21 Weekly meeting
2021-11-20 Monday
2021-11-21 Tuesday
Found 2 entries
2021-11-21 Weekly meeting
Removed 2 entries
2021-11-20 Monday
No entries
```