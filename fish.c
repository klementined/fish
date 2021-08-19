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
	long startTime = 0; //게임 시작 시간
	long totalElapsedTime = 0; //총 경과 시간
	long prevElapsedTime = 0; //직전 경과 시간 (최근에 물을 준 시간 간격)

	int num; //몇번 어항에 물을 줄 것인지, 사용자 입력
	initData();

	cursor = arrayFish; //cursor [0].. cursor[1]

	startTime = clock(); //현재 시각을 millisecond 단위로 변환
	while (1)
	{
		printfFishes();
		printf("which fish bowl would you water? ");
		scanf("%d", &num);

		//입력값 체크
		if (num < 1 || num>6)
		{
			printf("\nthe input number is invalid\n");
			continue;
		}

		//총 경과 시간
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		printf("total elapsed time : %ld seconds\n", totalElapsedTime);

		//직전에 물을 준 시간 (마지막으로 물 준 시간) 이후로 흐른 시간
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("pervious elapsed time: %ld seconds\n", prevElapsedTime);

		//어항의 물을 감소 (증발)
		decreaseWater(prevElapsedTime);

		//사용자가 입력한 어항에 물을 준다
		//1. 어항의 물이 0이면? 물을 주지 않는다 이미 물고기 죽음
		if (cursor[num - 1] <= 0)
		{
			printf("fish %d already died :(... we are not giving water\n", num);
		}
		//2. 어항의 물이 0이 아닌 경우? 물을 준다! 100을 넘지 않는지 체크
		else if (cursor[num - 1] + 1 <= 100)
		{
			printf("giving water to fish bowl %d\n\n", num);
			cursor[num - 1] += 1;
		}

		//레벨업을 할건지 확인 (레벨업은 20초마다 한번씩 수행)
		if (totalElapsedTime / 20 > level - 1)
		{
			//레벨업
			level++;
			printf("*** LEVEL UP!!! ==level %d -> level %d== ***\n\n", level - 1, level);

			//최종 레벨 : 5
			if (level == 5)
			{
				printf("\n\YOU WIN! You reached the highest level. shutting down...\n\n");
				exit(0);
			}
		}

		//모든 물고기가 죽었는지 확인
		if (checkFishAlive() == 0)
		{
			//물고기 dead
			printf("all fish died :(...\n");
		}

		else
		{
			//한마리라도 살음
			printf("the fish is/are still alive!\n"); 
		}
		prevElapsedTime = totalElapsedTime;
		//10포 -> 15 초 (5초: prevElapsesdTime -> 15초) -> 25초 (10초..?)
	}

return 0;
}

void initData()
{
	level = 1;
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] = 100; //어항의 물 높이 (0~100)
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
		arrayFish[i] -= (level * 3 * (int)elapsedTime); //3: 난이도 조정을 위한 값
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
