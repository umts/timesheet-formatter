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

## Usage

- The first thing it will ask you is the month. Input the month number and not the name.
- Now enter the date for sunday of the week, and just the day of the month nothing else.
- Now you can go on with entering your time blocks starting Sunday until Saturday.
- It asks you for hours given to respective timeblocks in order.
- Once you're done, the program will quit and you can see the formatted timesheet in a textfile!









