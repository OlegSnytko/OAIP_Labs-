#include<stdio.h>
#include<math.h>
int main()
{
	int userChoice;
	float circleArea, squareArea;
	printf("Choose the case: \n");
	printf("1 - a circle in a square \n");
    printf("2 - a square in circle \n");
	while (scanf_s("%d", &userChoice) != 1 || (userChoice != 1 && userChoice != 2)) 
	{
		printf("Error input\n\n");
		printf("Choose the case: \n");
		rewind(stdin);
		
	}

	printf("Input Area: ");
	while (scanf_s("%f %f", &circleArea, &squareArea) != 2)
	{
		printf("Error: input a number ");
		rewind(stdin);
	}
	
	if (userChoice == 1)
	{
		if (2 * sqrt(circleArea / 3.14) < sqrt(squareArea)) {
			printf("Circle fits into a square");
		}

		else
		{
			printf("Circle doesn't fit the square ");
		}
	}
	else if (userChoice == 2)
	{
		if (sqrt(2 * circleArea / 3.14) > sqrt(squareArea)) {
			printf("Square fits into a circle");
		}
		else
		{
			printf("Square doesn't fit the circle");
		}
	}
	return 0;
}

	