# Timesheet Formatter

Timesheet Formatter is a program to make the hours section of the required timesheet a little quicker.  It is written in C but doesn't use anything more complicated than a pointer. 

## Getting Started

After you clone the repository you will need to compile the timesheet.c file.  
I compile using gcc and standard C11.

```
gcc -std=c11 timesheet.c
```

If you want to name the outputed file use the -o flag, and put the desired name after the file to compile. The default output name is a.out.

***

Type the path to the output to run the program.

```
./a.out
```

After running the program generates a file name TimeSheet.txt, this is where you copy the inputed hours from.

## Sample run of the app

- The week that starts with April 5 as a Sunday.

```
Prompt 1: Please enter Sundays month(Ex January - 1):
Meaning: Please enter the month in numerical format for the Sunday of the week you worked on.
Example input: 4 //(Because it's april)
```

```
Prompt 2: Please enter Sundays, day of the month(Ex 15th - 15):
Meaning: Please enter the date for sunday for the week.
Example input: 5 //(Sunday for this week is 5th so 5).
```
```
Prompt 3: How many time blocks did you work on Sunday:
Meaning: A time block is a period of time for which you worked continuously in the day, you could've worked on multiple periods of time in a day, this is just a number of the blocks out of your day's schedule where you worked.
Example input: 0 //(Assuming I didn't work on Sunday).
```

```
Prompt 4: How many time blocks did you work on Monday:
Meaning: This will continue for the rest of the days of week until Saturday. Now assuming you did work on Monday in two different time periods, you will have the following prompts.
Example input: 2 //(Since I worked for two time blocks).
```


```
Prompt 5: Monday start time for block - 1 (Ex 8:30 - 8.50):
Meaning: Now we just enter the start time and then another prompt will ask us for hours worked for that time block and we don't need to worry about end time.
Example input: 9 //(Your input format has a range of [9, 9.0, 9:00], it shoudln't matter)
```

```
Prompt 6: Please enter hours worked (Ex 8hours 30min - 8.5):
Meaning: This is the prompt where you simply put in the hours worked since your start time.
Example input: 4 //(Like the prompt mentions, format for minutes to add them after a decimal point.)
```

```
Prompt 7: Monday start time for block - 2 (Ex 8:30 - 8.50):
Meaning: Start time for the next time block for the day if there are multiple.
Example input: 4 //(It is the same process like before.)
```

Once you reach the end which is basically saturday, the program will quit and you will have a TimeSheet.txt file available to on your machine. If you already had one before, it will be updated. You can copy that text now to where you want.
