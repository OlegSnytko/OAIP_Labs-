#include<stdio.h>
int main()
{
	float number;
	int userChoice;
	printf("Enter unit of measure: \n1- Dm\n2- Km\n3- M\n4- MM\n5- Sm\n");
	scanf_s("%d", &userChoice);
	if (userChoice < 1 || userChoice > 5)
	{
		printf("Error: wrong number.");
		return 0;
	}
	printf("Enter the number:\n");
	scanf_s("%f", &number);
	if (userChoice == 1)
	{
		number /= 10;
	}
	else if (userChoice == 2)
	{
		number *= 1000;
	}
	else if (userChoice == 3)
	{
		number *= 1;
	}
	else if (userChoice == 4)
	{
		number /= 1000;
	}
	else if (userChoice == 5)
	{
		number /= 100;
	}

	printf("Number in meters = %f\n", number);



	return 0;
}


