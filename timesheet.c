//************************ Included libraries *************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//************************ Constants **********************************************************

const char* full_days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* abbreviated_days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

//************************ Prototypes *********************************************************

void Deal_With_Min(int *a, float *b, float *c);
char* End_Time(float *hours_worked, float *start_time);
void output_month_day_hours(FILE* output, const char* day, int* month, int* day_num, float* hours_worked);
void output_hour_blocks(FILE* output, float* hours_worked, int* start_time_hours, float* start_time_minutes, float* start_time);
float** gather_hours(int day_num, float* start_time, float* hours_worked, int* num_of_blocks, float* total_hours_worked);
void increment_month_and_day(int* month_num,int* day_num);
void memory_cleanup(FILE* output, int* month_num, int* day_num, float** block_starting_times, int* num_of_blocks);

//*********************** Main **************************************************************** 

int main()
{
  //variables
  float start_time = 0.0;
  float hours_worked = 0.0;
  float total_hours_worked = 0;
  int num_of_blocks = 0;
  float** block_starting_times;
  
  int *month_num = malloc(sizeof(int));
  int *day_num = malloc(sizeof(int));
  int day_of_week_num = 0;
  
  int start_time_hours;
  float start_time_minutes;
  
  int hours_worked_hours;
  int hours_worked_minutes;  

  FILE *output;
  output = fopen("TimeSheet.txt","w");
  
  puts("Please enter Sundays month(Ex January - 1): ");
  scanf("%d", month_num);
  puts("Please enter Sundays, day of the month(Ex 15th - 15): ");
  scanf("%d", day_num);
  
while(day_of_week_num < 7)
  {
    int block_output_tracker = 0;
    block_starting_times = gather_hours(day_of_week_num, &start_time, &hours_worked, &num_of_blocks, &total_hours_worked);
    output_month_day_hours(output, abbreviated_days[1], month_num, day_num, &total_hours_worked); 

    while(block_output_tracker < num_of_blocks)
    {
      start_time = block_starting_times[block_output_tracker][0];
      hours_worked = block_starting_times[block_output_tracker][1]; 

      Deal_With_Min(&start_time_hours, &start_time_minutes, &start_time);  
      output_hour_blocks(output, &hours_worked, &start_time_hours, &start_time_minutes, &start_time); 
      block_output_tracker++;
    }

    increment_month_and_day( month_num, day_num);
    fprintf(output,"\n");
    day_of_week_num += 1;
  }

  memory_cleanup(output, month_num, day_num, block_starting_times, &num_of_blocks);
}

//************* Start of Functions ************************************************************ 

//parses hours entered to get minutes
void Deal_With_Min(int *start_time_hours, float *start_time_minutes, float *start_time)
{
  *start_time_hours = *start_time;
  *start_time_minutes = *start_time - *start_time_hours;
  *start_time_minutes = *start_time_minutes * 60;
  if (*start_time_minutes == 0)
    {start_time_minutes = 00;}
}

//calculates and formats end time 
char* End_Time(float *hours_worked, float *start_time)
{
  float end = *hours_worked + *start_time;
  int end_hours = end;
  float end_minutes = (end - end_hours) * 60;
  static char end_time[20];

  end_hours = end_hours % 12;

  if (end_hours == 0 && *start_time != 0)
    {end_hours += 12;}
  if (end_minutes == 0)
  {
    snprintf(end_time, 10, "%d:00", end_hours);
  }
  else
  {
    snprintf(end_time, 10, "%d:%d", end_hours, (int)end_minutes);
  }
  return end_time;
}

//outputs
void output_month_day_hours(FILE* output, const char* day, int* month, int* day_num, float* total_hours_worked)
{
    fprintf(output,"%s %d/%d %.2f ", day, *month, *day_num, *total_hours_worked);
    *total_hours_worked = 0.0;
}

//outputs
void output_hour_blocks(FILE* output, float* hours_worked, int* start_time_hours, float* start_time_minutes, float* start_time)
{
  if((int) *start_time_minutes == 0)
  {
    fprintf(output,"(%d:00 - %s)", *start_time_hours, End_Time(hours_worked, start_time));
  }
  else
  {
    fprintf(output,"(%d:%d - %s)", *start_time_hours, (int)*start_time_minutes, End_Time(hours_worked, start_time));
  }
}

//prompts and gathers the worked hours
float** gather_hours(int day_num, float* start_time, float* hours_worked, int* num_of_blocks, float* total_hours_worked)
{
  printf("How many time blocks did you work on %s: ", full_days[day_num]);
  scanf("%d", num_of_blocks);

  float** block_starting_times = (float**)malloc(sizeof(float *) * *num_of_blocks);

  for(int i = 0; i < *num_of_blocks; i++)
  {
    block_starting_times[i] = (float*)malloc(sizeof(float) * 2);
  }

  if (*num_of_blocks > 0)
  {
    int current_block = 1;
    while (current_block <= *num_of_blocks)
    {
      printf("%s start time for block - %d (Ex 8:30 - 8.50): \n", full_days[day_num], current_block);
      scanf("%f", start_time);
      puts("Please enter hours worked (Ex 8hours 30min - 8.5): ");
      scanf("%f", hours_worked);
      
      *total_hours_worked += *hours_worked;
      block_starting_times[current_block - 1][0] = *start_time;
      block_starting_times[current_block - 1][1] = *hours_worked;
      current_block++;
    }
  }
  
  *start_time = (float)0.0;
  *hours_worked = (float)0.0;
  

  return block_starting_times;
}

//month day increments
void increment_month_and_day(int* month_num, int* day_num)
{
  //30 days has september, april, june, and november...
  if (*month_num == 4 || *month_num == 6 || *month_num == 9 || *month_num == 11)
  {
    if (*day_num == 30)
    {
      *day_num = 1;
      *month_num += 1;
    }
    else
      {*day_num  += 1;}
  }
  // all the rest have 31...
  else if (*month_num == 1 || *month_num == 3 || *month_num == 5 || *month_num == 7 || *month_num == 10 || *month_num == 12)
  {
    if (*day_num == 31)
    {
      *day_num = 1;
      *month_num += 1;
    }
    else
      {*day_num += 1;}
  }
  //except for february which has 28 and.....Oh noes this doesn't account for leap years 
  else
  {
    if (*day_num == 28)
    {
      *day_num = 1;
      *month_num += 1;
    }
    else
      {*day_num += 1;}
  }
}

//frees memory
void memory_cleanup(FILE* output, int* month_num, int* day_num, float** block_starting_times, int* num_of_blocks)
{
  fclose(output);
  free(month_num);
  free(day_num); 
  
  for(int i = 0; i < *num_of_blocks; i++)
  {
    free(block_starting_times[i]);
  }

  free(block_starting_times);
}
