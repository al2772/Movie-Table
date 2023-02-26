/* Adam Lewandowski
 * aclewandowsk
*/

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

/*Takes the array given and moves everything to the
 * right of the index given by start and shifts it to
 * the left
 */
void Shift_Array(char str[], int start, int size){
	// loop through array and swap current index
	// with the next index
        for (int i = start; i < size; i++){
                str[i] = str[i+1];
        }
        return;
}

/* Loops through the given array to increment size
 * until the end of the array is reached. Returns the
 * correct size of the array.
 */
int Get_Size(char str[]){
	int i = 0;
	int size = 0;
	// loop through array until '\0' is found
	while(str[i] != '\0'){
		size++;
		i++;
	}

	return size+1;
}

/* This function takes a string as input and removes
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */
void Clean_Whitespace(char str[]){
	// get the size of the array
	int size = Get_Size(str);

	// loop through array and test for whitespace
	  for (int i = 0; i < size-1; i++){
                if (str[i] == '\t' || str[i] == '\n'){
		// call Shift_Array to shift indexes left
                	Shift_Array(str, i, size);
        }
		if (str[i] == '\0' && str[i-1] == ' '){
			Shift_Array(str, i, size);
		}
		while(str[i] == ' ' && str[i+1] == ' '){
			Shift_Array(str, i, size);
		}
    }

    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */
void Fix_Case(char str[]) {
	int size = Get_Size(str);

    for (int i = 0; i < size-1; i++){
	// make sure first char is upper case
	if (i == 0 && str[i] >  90){
          str[i] = str[i] -  32;
        }
	// make sure first letters are upper case
	else if (i != 0 && str[i] == ' ' && str[i+1] > 90){
          str[i+1] = str[i+1] - 32;
        }
	// make sure interior charcters are lower case
 	else if (i != 0 && str[i-1] != ' ' && str[i] != ' ' && str[i] < 90){
          str[i] = str[i]  + 32;
        }

    }
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    int result = atoi(str);

    return result;
}

/*removes the elements of a char array until
 * the index indicated by end is reached
 */
void Remove_Elements(char str[], int end, int size){
	// loop through the array
        for (int i = 0; i < end; i++){
                str[i] = str[i+1];
        }
	for (int j = 0; j < size; j++){
		str[j] = str[j+1];
	}
        return;
}

/* this function takes the name of a 
* director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
  */
void Director_Last_Name(char str[]) {
    int size = Get_Size(str);
    // loop through array and remove elements
    // before the last name
    for (int i = size; i >= 0; i--){
	    if (str[i] == ' '){
		    Remove_Elements(str, i, size);
	    }
    }
    return;
    }

/* this function takes the a string and returns
* the floating point equivalent
 */
float String_To_Rating(char str[]) {
	  float result = atof(str);

    return result;
}

/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000
*/
long long String_To_Dollars(char str[])  {
    int size = Get_Size(str);
    
    Clean_Whitespace(str);

    long result = atoll(str);
    int count = 0;
    for (int i = 0; i < size; i++){
	if (str[i] == 'k' || str[i] == 'K'){
		count = 1;
	}
    }

    for (int i = 0; i < size; i++){
	if (str[i] == 'M' || str[i] == 'm'){
		count = 2;
	}
    }
    

	if (count == 1){
		result = result * 1000;
	}
	if (count == 2){
		result = result * 1000000;
	}

    return result;
}
/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
	int j = 0;
	// begin loop to iterate through each row
	for(int row = 0; row < num_movies; row++){
	j = 0;
	// loop through to first comma for title
	while (csv[row][j] != ','){
		// get title and add
		// it to the titles array
		titles[row][j] = csv[row][j];
		j++;
	}
	
	Clean_Whitespace(titles[row]);
	Fix_Case(titles[row]);
	
	j++;
	
	// loop to next comma
	char temp[1024];
	int k = 0;
	while(csv[row][j] != ','){
		// get year and  add it to years array
		// convert string to year number
		temp[k] = csv[row][j];
		k++;
		j++;
	}

	years[row] = String_To_Year(temp);
	
	j++;

	// loop to next comma
	while (csv[row][j] != ','){
		// get
		// runtime to add to runtime
		// char array
		j++;
	}
	
	j++;

	// loop to next comma
	int index = 0;
	while(csv[row][j] != ','){
		// get directors name to add
		// to directors array
		directors[row][index] = csv[row][j];
		j++;
		index++;
	}
	
	Clean_Whitespace(directors[row]);
	Director_Last_Name(directors[row]);
	Fix_Case(directors[row]);

	j++;

	// loop to next comma
	char temp2[1024];
	int t = 0;
	while(csv[row][j] != ','){
		// clean whitespace an turn rating
		// into a float
		temp2[t] = csv[row][j];
		t++;
		j++;
	}
	
	ratings[row] = String_To_Rating(temp2);
	
	j++;

	// loop to next newline
	char temp3[1024];
	int r = 0;
	while(csv[row][j] != '\n'){
		// clean whitespace and get
		// dollars as a long long
		temp3[r] = csv[row][j];
		r++;
		j++;
	}
	
	dollars[row] = String_To_Dollars(temp3);

	
	}

    return;
}

/* This function prints a well formatted table of
 * the movie data
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is
larger, left justified, first letter of each word upper case, remaining letters
lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10
(which ever is longer), left justified, only last name, first letter upper case,
remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or
10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char
directors[10][1024], float ratings[10], long long dollars[10]) {
	
	int title_length = 7;
	for (int i = 0; i <= num_movies; i++){
		Clean_Whitespace(titles[i]);
		if (Get_Size(titles[i]) > title_length){
			title_length = Get_Size(titles[i]) + 2;	
			}
	}


	int directors_length = 10;
	for (int i = 0; i <= num_movies; i++){
		Clean_Whitespace(directors[i]);
		if (Get_Size(directors[i]) > directors_length){
			directors_length = Get_Size(directors[i]) + 2;
			}
	}

	// print the first row of labels for each column
        printf("%-3s","Id");
        printf("%-*s", title_length, "Title");
        printf("%-6s", "Year");
        printf("%-*s", directors_length, "Director");
        printf("%6s%11s\n", "Rating", "Revenue");



	// loop to add each element to each row base on num_movies
	for (int i = 0; i < num_movies; i++){
		printf("%-3d", i+1);
		printf("%-*s", title_length, titles[i]);
		printf("%-6d", years[i]);
		printf("%-*s", directors_length, directors[i]);
		printf("%6.1f%11lld\n", ratings[i], dollars[i]);
	}
		

    return;
}
