// Teodor-Adrian Mirea (2017)
// University Project - Honeycomb - C

#include<stdio.h>

#define IN_SIZE 32769	//	buffer_size in fgets
#define CMAX 50
#define RMAX 30

typedef char in[IN_SIZE];
typedef int queens[6*CMAX];
typedef char mat[2*RMAX+3][2*CMAX+3];

void initialize(int [], queens, mat);
int read(in, int);
int read_columns(in , int []);	
int read_queens(in, queens, int);
int build_honeycomb(mat, queens, int, int [], char, int);
void print(mat, int, int);

int main()
{
	in input;	/*	the string which will contain every line from the input
					source (only one line per processing) */
	queens q;	/*	array which contains the positions of the queens in the
					honeycomb */
	mat honeycomb;	/*	matrix in which the honeycomb will be "drawn" and then
					printed */

	char c;		/*	character which shows how's the first honeycomb cell
					(C - lower, R - higher) */
	int v[CMAX], i, j, nr_q, max_col, max_row;

	while(fgets(input, IN_SIZE, stdin)!=NULL)
	{
		//	initialising v and q with 0 and the honeycomb with blank spaces
		initialize(v, q, honeycomb);

		max_col = 0;
		max_row = 0;

		//	reading the columns in the array v
		j = read_columns(input, v);

		/*	calculation of the number of columns and maximum number of lines
			in the honeycomb */
		i = 0;
		while(v[i] != 0)
		{
			if(v[i] >= max_row)
				max_row = v[i];
			max_col++;
			i++;
		}

		//	reading the state of the first cell (lower or higher)
		c = input[j];

		/*	reading the positions of the queens into the array q and
			setting the length of the array */
		nr_q = 0;
		if(input[j+1] == ' ')
			nr_q=read_queens(input, q, j+2);

		/*	building the honeycomb and remembering the maximum number of lines
			in the matrix which contains the honeycomb */
		max_row = build_honeycomb(honeycomb, q, max_col, v, c, nr_q);

		//	printing the honeycomb
		print(honeycomb, max_col, max_row);
	}

	return 0;
}

/*	the function initializes the elements of arrays with 0 and the honeycomb 
	matrix with blank spaces */
void initialize(int v[], queens q, mat honeycomb)
{
	int i, j;
	for(i = 0; i < CMAX; i++)
		v[i] = 0;
	for(i = 0; i < 3*CMAX; i++)
		q[i] = 0;
	for(i = 0; i <= 2*RMAX+2; i++)
		for(j = 0;j <= 2*CMAX+2; j++)
			honeycomb[i][j] = ' ';
}

/*	the function reads the number of lines for every column and puts them in
	the array v */
int read_columns(in input, int v[])
{
	int i = 0, j = 0;

	while(1)
	{
		/*	if the buffer reached the state-character for the first cell, exit
			the reading of lines */
		if(input[j] == 'R' || input[j] == 'C')
			break;
		else
		{
			//	save numbers with 2 digits if it is necesary
			if((input[j+1] - '0' >= 0) && (input[j+1] - '0' <= 9))
			{
				v[i] = (input[j] - '0') * 10 + (input[j+1] - '0');
				j += 3;	
			}
			else
			{
				v[i] = input[j] - '0';
				j += 2;
			}

			i++;
		}
	}
	return j;	//	returning the position where the state-character is
}

/*	the function reads the pairs of positions for every queen and saves them
	in the array q (even positions = column, odd positions = row) */
int read_queens(in input, queens q, int j)
{
	int i = 0;

	do
	{
		//	save numbers with 2 digits if it is necesary
		if((input[j+1] - '0' >= 0) && (input[j+1] - '0' <= 9))
		{
			q[i] = (input[j] - '0') * 10 + (input[j+1] - '0');
			j += 3;
		}
		else
		{
			q[i] = input[j] - '0';
			j += 2;
		}

		i++;
	}while(input[j] != '\n' && input[j] != '\0');

	return i;	//	returning the number of elements in the array q
}

/*	the function builds the honeycomb in its final form */
int build_honeycomb(mat honeycomb, queens q, int max_col,
						int v[], char c, int nr_q)
{
	int i, j, col, row, max_row = 0;

	/*	going through the honeycomb through the columns and marking in the
		matrix the place where a cell should be printed */
	for(j = 0; j <= max_col; j++)
	{
		/*	using mathematical calculations, the column-index of the center
			of the cell (in the final honeycomb) for every cell is
			2*read_column+1	*/
		col = 2 * j + 1;

		/*	for every line, marking until the maximum number of columns on the current
			row is excedeed */
		for( i = 0; i < v[j]; i++)
		{
			//	all the above formulas were found using mathematical calculations
			if(c == 'R')
			{
				if(j % 2 == 0)
					row = 2 * i + 1;
				else
					row = 2 * (i + 1);
			}
			else
			{
				if(j % 2 == 0)
					row = 2 * (i + 1);
				else
					row = 2 * i + 1;
			}

			honeycomb[row][col] = 'X';	//	mark the center of the cell with 'X'
		}
	}

	/*	going through the array q and marking in the matrix the place where a
		cell containing a queen exists */
	for(i = 0; i < nr_q; i += 2)
	{
		/*	using mathematical calculations, the column-index of the center
			of the cell (in the final honeycomb) for every cell which contains
			a queen is 2*read_column-1	*/
		col = 2 * q[i] - 1;

		//	all the above formulas were found using mathematical calculations
		if(c == 'R')
		{
			if(q[i] % 2 == 0)
				row = 2 * q[i+1];
			else
				row = 2 * q[i+1] - 1;
		}
		else
		{
			if(q[i] % 2 == 0)
				row = 2 * q[i+1] - 1;
			else
				row = 2 * q[i+1];
		}

		honeycomb[row][col] = 'Q';	//	mark the center of the cell with 'Q'
	}

	/*	going through the whole matrix and placing '/', '_', '\' around the
		center of the cell */
	for(i = 1; i <= 2*RMAX+1; i++)	/*	the first line (0) never contains 'X'
										or "Q" */
		for(j = 1; j <= 2*CMAX+1; j+=2)	/*	j=1 and j+=2 because only on the
											odd columns the characters 'X' and
											'Q' are found */
		{
			if(honeycomb[i][j] == 'X' || honeycomb[i][j] == 'Q')
			{
				honeycomb[i-1][j] = honeycomb[i+1][j] = '_';
				honeycomb[i][j-1] = honeycomb[i+1][j+1] = '/';
				honeycomb[i+1][j-1] = honeycomb[i][j+1] = '\\';

				/*	saving the maximum row which contained the character 'X'
					or 'Q' */
				if(i > max_row)
					max_row = i;
			}

			//	remove the character 'X' because it is not needed anymore
			if(honeycomb[i][j] == 'X')
				honeycomb[i][j] = ' ';
		}
	return max_row + 1;	/*	returning max_row+1 because this is the last line
							in the matrix which contains components of the 
							honeycomb */

}

//	the function shows the final form of the honeycomb
void print(mat honeycomb, int max_col, int max_row)
{
	int i, j;

	for(i = 0; i <= max_row; i++)
	{
		for(j= 0 ;j <= 2*max_col; j++)
			printf("%c", honeycomb[i][j]);
		printf("\n");
	}
}
