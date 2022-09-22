#include<stdio.h>

int main()
{
	float a, b, c;

	printf("Enter the sides of the triangle: ");
	while (scanf_s("%f %f %f", &a, &b, &c) != 3) 
	{
		printf("Invalid entry\n");
		printf("Enter the sides of the triangle again: ");
		rewind(stdin);
	}
	if (a == b || a == c || b == c)
	{
		printf("Triangle isosceles");
		
	}
	else 
	{
		printf("Triangle non-isosceles");
    }


	return 0;
}