#include <stdio.h>
#include "assignment_2.h"
#include <stdlib.h>

static void check_adj(int x, int a[][x]);//checks adjacent sets in the matrix and does the comparisions
static void check_nonadj(int x, int a[][x]);//checks for non adjacent sets in the matrix and does the comparisions
static void print_col(int n, int x, int a[][x]);//prints the column specified
static void clear_col(int n, int x, int a[][x]);//clears the column specified
static int num_col(int x, int a[][x]);//checks the number of columns occupied
static int col_num(int n, int x, int a[][x]);//finds the number of the column occupied
static int pivot_only(int x, int a[][x]);//returns true if there is nothing occupied below the pivots
static int row_num(int x, int a[][x]);//returns row number of the elements occupied below the pivot elements
static int log_2n(int l);//returns the log base of the power 2 for a particular value
static int sec_max(int n, int x, int a[][x]);//finds the second largest number

void find_second_greatest(int *numbers, int length)
{
	int x = log_2n(length);
	x++;
	int a[x][x];
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			a[i][j] = -1;
		}
	}
	for (int i = 0; i < length; i++)
	{
		if (a[0][0] == -1)
		{

			a[0][0] = numbers[i];
		}
		else
		{
			a[1][0] = numbers[i];
			check_adj(x, a);
		}
	}
	check_nonadj(x, a);
	int f=col_num(0, x, a);
	int ans=sec_max(f, x, a);
	printf("\n%d\n", ans);	
}

void check_adj(int x, int a[][x])
{
	int n = row_num(x, a);
	if (n == -1)
		return;
	if (n == 1)
	{
		printf("%d x %d =", a[0][0], a[1][0]);
		if (a[0][0] < a[1][0])
		{
			int temp = a[0][0];
			a[0][0] = a[1][0];
			a[1][0] = temp;
		}
		printf(" %d %d \n", a[0][0], a[1][0]);
	}
	while (pivot_only(x, a))
	{
		int n = row_num(x, a);
		if (a[0][n] == -1)
		{

			for (int i = 0; i <= n; i++)
			{
				a[i][n] = a[i][n - 1];
			}
			clear_col(n - 1, x, a);
			break;
		}
		if (a[0][n - 1] >= a[0][n])
		{
			print_col(n, x, a);
			printf(" x ");
			print_col(n - 1, x, a);
			printf(" = ");
			int m;
			for (m = n + 1; m > 1; m--)
			{
				a[m][n] = a[m - 1][n - 1];
			}
			a[1][n] = a[0][n];
			a[0][n] = a[0][n - 1];
			clear_col(n - 1, x, a);
			print_col(n, x, a);
			printf("\n");
		}
		else
		{
			print_col(n, x, a);
			printf(" x ");
			print_col(n - 1, x, a);
			printf(" = ");
			int m;
			for (m = n + 1; m > 1; m--)
			{
				a[m][n] = a[m - 1][n];
			}
			a[1][n] = a[0][n - 1];
			clear_col(n - 1, x, a);
			print_col(n, x, a);
			printf("\n");
		}
	}
}

void print_col(int n, int x, int a[][x])
{
	for (int i = 0; i < x; i++)
	{
		if (a[i][n] != -1)
		{
			printf("%d ", a[i][n]);
		}
	}
}
void check_nonadj(int x, int a[][x])
{
	while (num_col(x, a) != 1)
	{
		int m = col_num(0, x, a);
		if (m == x - 1)
		{
			return;
		}
		int n = col_num(m + 1, x, a);

		if (a[0][m] >= a[0][n] && m != n - 1)
		{
			print_col(m, x, a);
			printf(" x ");
			print_col(n, x, a);
			printf(" = ");
			int temp = a[0][n];
			int k;
			for (k = m + 1; k > 1; k--)
			{
				a[k][m + 1] = a[k - 1][m];
			}
			a[1][m + 1] = temp;
			a[0][m + 1] = a[0][m];
			clear_col(m, x, a);
			clear_col(n, x, a);
			print_col(m + 1, x, a);
			printf("\n");
		}
		else if (a[0][m] >= a[0][n] && m == n - 1)
		{

			print_col(m, x, a);
			printf(" x ");
			print_col(n, x, a);
			printf(" = ");
			int k;
			for (k = n; k > 1; k--)
			{
				a[k][n] = a[k - 1][m];
			}
			a[1][n] = a[0][n];
			a[0][n] = a[0][m];
			clear_col(m, x, a);
			print_col(n, x, a);
			printf("\n");
		}
		else if (a[0][m] < a[0][n]&&a[0][n+1]==-1)
		{
			print_col(m, x, a);
			printf(" x ");
			print_col(n, x, a);
			printf(" = ");
			int k;
			for (k = n + 1; k > 1; k--)
			{
				a[k][n + 1] = a[k - 1][n];
			}
			a[1][n + 1] = a[0][m];
			a[0][n + 1] = a[0][n];
			clear_col(m, x, a);
			clear_col(n, x, a);
			print_col(n + 1, x, a);
			printf("\n");
		}
		else if (a[0][m] < a[0][n]&&a[0][n+1]!=-1)
		{
			print_col(m, x, a);
			printf(" x ");
			print_col(n, x, a);
			printf(" = ");
			int k;
			for (k = n + 1; k > 1; k--)
			{
				a[k][n] = a[k - 1][n];
			}
			a[1][n] = a[0][m];
			a[0][n] = a[0][n];
			clear_col(m, x, a);			
			print_col(n, x, a);
			printf("\n");
			check_adj(x,a);			
		}
	}
}

void clear_col(int n, int x, int a[][x])
{
	for (int i = 0; i < x; i++)
	{
		a[i][n] = -1;
	}
}

int num_col(int x, int a[][x])
{
	int s = 0;
	for (int i = 0; i < x; i++)
	{
		if (a[0][i] != -1)
		{
			s++;
		}
	}
	return s;
}

int col_num(int n, int x, int a[][x])
{
	for (int i = n; i < x; i++)
	{
		if (a[0][i] != -1)
		{
			return i;
		}
	}
	return -1;
}

int pivot_only(int x, int a[][x])
{
	for (int i = 1; i < x; i++)
	{
		if (a[i][i - 1] != -1)
		{
			return 1;
		}
	}
	return 0;
}

int row_num(int x, int a[][x])
{

	for (int i = 1; i < x; i++)
	{
		if (a[i][i - 1] != -1)
		{
			return i;
		}
	}
	return -1;
}

int log_2n(int l)
{
	int k = 1;
	int i = 2;
	while (i < l)
	{
		i *= 2;
		k++;
	}
	if (i == l)
		return k;
	if (i > l)
	{
		return k;
	}
}

int sec_max(int n, int x, int a[][x])
{
	int m=-1;
	for(int i=1;i<x;i++)
	{
		if(m<a[i][n])
		{
			m=a[i][n];
		}
	}
	return m;
}
