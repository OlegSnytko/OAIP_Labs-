#include<stdio.h>
int main()
{
	int R, L, h;
	float Sbok, Spol, V;
	printf("Input R, L, h: ");
	while (scanf_s("%d%d%d", &R, &h, &L) != 3) 
	{
	    printf("Wrong Input\n");
		printf("Try again\n");

		rewind(stdin);
	}
	Sbok = (3.14 * R * L);
	Spol = (3.14 * R * L + 3.14 * R * R);
	V = 1.0 / 3 * 3.14 * R * R * h;
	printf("Sbok= %.3f \n", Sbok);
	printf("Spol= %.3f \n", Spol);
	printf("V= %.3f \n", V);
	return 0;
}
