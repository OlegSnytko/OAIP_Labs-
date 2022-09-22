#include<stdio.h>

int main()
{
	float a, b, c;

	printf("Enter the sides of the triangle:");
	scanf_s("%f %f %f", &a, &b, &c);
	if (a == b || a == c || b == c)
	{
		printf("Triangle isosceles ");
		
	}
	else {
		printf("Triangle non-isosceles");

	}


	return 0;
}