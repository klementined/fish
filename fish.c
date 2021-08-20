#include <stdio.h>
#include <time.h>

int level;
int arrayFish[6];
int* cursor;

void initData();
void printfFishes();
void decreaseWater(long elapsedTime);
int checkFishAlive();

int main(void)
{
	long startTime = 0; //game start time
	long totalElapsedTime = 0; //total elapsed time
	long prevElapsedTime = 0; //previous elapsed time (time gap between the previous watered time and current time) 

	int num; //user input of which bowl to water
	initData();

	cursor = arrayFish; //cursor [0].. cursor[1]

	startTime = clock(); //change time to millisecond 
	while (1)
	{
		printfFishes();
		printf("which fish bowl would you water? ");
		scanf("%d", &num);

		//check input
		if (num < 1 || num>6)
		{
			printf("\nthe input number is invalid\n");
			continue;
		}

		//total elapsed time
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		printf("total elapsed time : %ld seconds\n", totalElapsedTime);
		
		//calculate previous watered time 
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("pervious elapsed time: %ld seconds\n", prevElapsedTime);

		//decrease water
		decreaseWater(prevElapsedTime);

		//give water to the fishbowl of input number
		//1. If water level is 0? the fish is already dead, do not water
		if (cursor[num - 1] <= 0)
		{
			printf("fish %d already died :(... we are not giving water\n", num);
		}
		//2. If water level isn't 0? water fish & check if water level is not over 100
		else if (cursor[num - 1] + 1 <= 100)
		{
			printf("giving water to fish bowl %d\n\n", num);
			cursor[num - 1] += 1;
		}

		//check for level up (level up in every 20 seconds)
		if (totalElapsedTime / 20 > level - 1)
		{
			//level up
			level++;
			printf("*** LEVEL UP!!! ==level %d -> level %d== ***\n\n", level - 1, level);

			//final level : 5
			if (level == 5)
			{
				printf("\n\YOU WIN! You reached the highest level. shutting down...\n\n");
				exit(0);
			}
		}

		//check if fish died or not
		if (checkFishAlive() == 0)
		{
			//if all fish are dead
			printf("all fish died :(...\n");
		}

		else
		{
			//if at least one fish is alive
			printf("the fish is/are still alive!\n"); 
		}
		prevElapsedTime = totalElapsedTime;
		//10 secs -> 15 secs (5 secs: prevElapsesdTime -> 15 secs) -> 25 secs (10 secs..?)
	}

return 0;
}

void initData()
{
	level = 1;
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] = 100; //water level of each fish bowl (1~100)
	}
}

void printfFishes()
{
	printf("%3dst %3dnd %3drd %3dth %3dth %3dth\n", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++)
	{
		printf(" %4d ", arrayFish[i]);
	}
	printf("\n\n");
}

void decreaseWater(long elapsedTime)
{
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] -= (level * 3 * (int)elapsedTime); //3 is to change the difficulty of the game (higher number = harder)
		if (arrayFish[i] < 0)
		{
			arrayFish[i] = 0;
		}
	}
}

int checkFishAlive()
{
	for (int i = 0; i < 6; i++)
	{
		if (arrayFish[i] > 0)
			return 1;
	}
	return 0;
}
