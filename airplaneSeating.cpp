//***********************************************************************
// Author: Osvaldo 
// 
// This is a program that can be used to assign seats for a commercial 
// airplane has 13 rows, with six seats in each row. 
// Rows 1 and 2 are first class, rows 3 through 7 are business class, 
// and rows 8 through 13 are economy class.
// After the user is done assigning seats, the computer than displays
// free and taken seats on a table-like format.
//************************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int NUMBER_OF_ROWS = 13; // Stores number of row on plane and
const int NUMBER_OF_SEATS_PER_ROW = 6; // store number of seats per row

// This variables store the indexes of where
// each seating class begins and ends (the indexes)
const int FIRST_CLASS_ROW_BEGIN = 0;
const int FIRST_CLASS_ROW_END = 1;
const int BUS_CLASS_ROW_BEGIN = 2;
const int BUS_CLASS_ROW_END = 6;
const int ECON_CLASS_ROW_BEGIN = 7;
const int ECON_CLASS_ROW_END = 12;

// Data type to be used as index of the seating
// postions (out of 6) in each row when calling the main
// array
enum rowLetter { A, B, C, D, E, F, G }; 

// Function prototypes
void introProgram();
void setSeatsEmpty(bool seats[][NUMBER_OF_SEATS_PER_ROW], int noOfSeats);
void firstClass(bool seat[][NUMBER_OF_SEATS_PER_ROW]);
rowLetter inputSeatPos(char letra);
void enterSeat(int& num, char& let, int x, int y);
void businessClass(bool seat[][NUMBER_OF_SEATS_PER_ROW]);
void econClass(bool seat[][NUMBER_OF_SEATS_PER_ROW]);
bool addMoreSeat();
void seatDisplay(bool seat[][NUMBER_OF_SEATS_PER_ROW], int noOfrows);
void seatPortionDisplay(bool seat[][NUMBER_OF_SEATS_PER_ROW], int x, int y);

int main()
{
	// This array stores false when seat is free, and true
	// when seat is taken
	bool taken[NUMBER_OF_ROWS][NUMBER_OF_SEATS_PER_ROW]; 

	char seatClass;
	bool moreSeats = true;

	introProgram();
	setSeatsEmpty(taken, NUMBER_OF_ROWS);

	do
	{

		do
		{
			do
			{
				cout << endl;
				cout << "Enter the desired seat class ('f' for first "
					<< "class\n 'b' for business class, 'e' for "
					<< " economy class): ";
				cin >> seatClass;
				cout << endl;

			} while ((seatClass != 'f' && seatClass != 'F') &&
				(seatClass != 'B' && seatClass != 'b') &&
				(seatClass != 'e' && seatClass != 'E'));

			switch (seatClass)
			{
			case 'f':
			case 'F':
				firstClass(taken);
				break;
			case 'B':
			case 'b':
				businessClass(taken);
				break;
			case 'e':
			case 'E':
				econClass(taken);
				break;
			}

			moreSeats = addMoreSeat();

		} while (moreSeats != false);

		moreSeats == true;

		cout << endl;

		seatDisplay(taken, NUMBER_OF_ROWS);
		moreSeats = addMoreSeat();
		
	} while (moreSeats != false); // Exits when user decides to finalize and quit program

}

// This function introduces the program to the user
void introProgram()
{
	cout << setw(40) << " Welcome to Airplane "
		<< "Seating Arrangement Program";
	cout << endl << endl;
	cout << "Airplane's specifications:\n\nThis airplane has "
		<< NUMBER_OF_ROWS << " rows, with "
		<< NUMBER_OF_SEATS_PER_ROW << " (A, B, C, D, E, F) "
		<< "seats \nin each row. Rows 1 and 2 are first class, rows 3"
		<< " through\n7 are business class, and rows 8 through 13"
		<< " are economy \nclass.";
	cout << endl << endl;
}

// This function initializes taken array to false (indicates that the
// the seats are free
void setSeatsEmpty(bool seats[][NUMBER_OF_SEATS_PER_ROW], int noOfSeats)
{
	int counter1;
	rowLetter counter2;

	for (counter1 = 0; counter1 < noOfSeats; counter1++)
		for (counter2 = A; counter2 < G; counter2 = static_cast<rowLetter> (counter2 + 1))
			seats[counter1][counter2] = false;
}

// This function lets the user enter the seat the
// passenger desires
void enterSeat(int& num, char& let, int x, int y)
{
	do
	{
		cout << "Enter desired row number and seat "
			<< "position (example: 2C)\n"
			<< "(enter row number within range of"
			<< " seating class & seat positions from"
			<< " A to F: ";
		cin >> num >> let;
		cout << endl;

	// This loop only exists when the user enters a valid seat
	// The row number entered has to be within the chosen seating class range
	// (for example, if the user has chosen first class, then
	// the the row has to be either '1' or '2'). The seating
	// position within the row has to be between A to F.
	} while ((num < x + 1  || num > y + 1 ) || ((let != 'A' &&    
		let != 'a') && (let != 'B' && let != 'b') && (let != 'C'
			&& let != 'c') && (let != 'D' && let != 'd') &&
		(let != 'E' && let != 'e') && (let != 'F' && let != 'f')));
}

// This function converts the user input letter
// into a valid seating positon (array position
rowLetter inputSeatPos(char letra)
{
	switch (letra)
	{
	case 'A':
	case 'a':
		return A;
		break;
	case 'B':
	case 'b':
		return B;
		break;
	case 'C':
	case 'c':
		return C;
		break;
	case 'D':
	case 'd':
		return D;
		break;
	case 'E':
	case 'e':
		return E;
		break;
	case 'F':
	case 'f':
		return F;
		break;

	}
}

// This function determines if the user wants to 
// enter more seats or not
bool addMoreSeat()
{
	char symbol;

	cout << "Enter '#' to book more seats"
		<< " OR press any other key to finalize: ";
	cin >> symbol;

	if (symbol == '#')
		return true;
	else
		return false;
}

// This function allows the user to enter seats in the first class
void firstClass(bool seat[][NUMBER_OF_SEATS_PER_ROW])
{
	int rowNum;
	char letter;
	rowLetter seatP;
	bool seatPValid = false; // becomes true when seat has been saved
	char cancelSeat;
	
	do
	{
		enterSeat(rowNum, letter, FIRST_CLASS_ROW_BEGIN, FIRST_CLASS_ROW_END);

		seatP = inputSeatPos(letter);

		if (seat[rowNum - 1][seatP] != true)
		{
			seat[rowNum - 1][seatP] = true;
			seatPValid = true;
			cout << "SEAT SAVED";
			cout << endl << endl;
		}
		else
		{
			cout << "Seat " << rowNum
				<< letter << " is taken\n";
			cout << endl;

			seatPortionDisplay(seat, FIRST_CLASS_ROW_BEGIN, FIRST_CLASS_ROW_END);

			cout << "Enter '#' to cancel OR press any other key to try again: ";
			cin >> cancelSeat;
			cout << endl << endl;
		}

	// Loop exits when the seat chosen by user has been saved
	// or when user decides to cancel entering seat
	} while (seatPValid != true && cancelSeat != '#');

}

// This function allows the user to enter seats in the business class
void businessClass(bool seat[][NUMBER_OF_SEATS_PER_ROW])
{
	int rowNum;
	char letter;
	rowLetter seatP;
	bool seatPValid = false; // becomes true when seat has been saved
	char cancelSeat;

	do
	{
		enterSeat(rowNum, letter, BUS_CLASS_ROW_BEGIN, BUS_CLASS_ROW_END);

		seatP = inputSeatPos(letter);

		if (seat[rowNum - 1][seatP] != true)
		{
			seat[rowNum - 1][seatP] = true;
			seatPValid = true;
			cout << "SEAT SAVED";
			cout << endl << endl;
		}
		else
		{
			cout << "Seat " << rowNum 
				<< letter << " is taken\n";
			cout << endl;
			
			seatPortionDisplay(seat, BUS_CLASS_ROW_BEGIN, BUS_CLASS_ROW_END);

			cout << "Enter '#' to cancel OR press any other key to try again: ";
			cin >> cancelSeat;
			cout << endl << endl;
		}

		// Loop exits when the seat chosen by user has been saved
		// or when user decides to cancel entering seat
	} while (seatPValid != true && cancelSeat != '#');

}

// This function allows the user to enter seats in the economy class
void econClass(bool seat[][NUMBER_OF_SEATS_PER_ROW])
{
	int rowNum;
	char letter;
	rowLetter seatP;
	bool seatPValid = false; // becomes true when seat has been saved
	char cancelSeat;

	do
	{
		enterSeat(rowNum, letter, ECON_CLASS_ROW_BEGIN, ECON_CLASS_ROW_END);

		seatP = inputSeatPos(letter);

		if (seat[rowNum - 1][seatP] != true)
		{
			seat[rowNum - 1][seatP] = true;
			seatPValid = true;
			cout << "SEAT SAVED";
			cout << endl << endl;
		}
		else
		{
			cout << "Seat " << rowNum
				<< letter << " is taken\n";
			cout << endl;
			
			seatPortionDisplay(seat, ECON_CLASS_ROW_BEGIN, ECON_CLASS_ROW_END);
			
			cout << "\nEnter '#' to cancel OR press any other key to try again: ";
			cin >> cancelSeat;
			cout << endl << endl;
		}

		// Loop exits when the seat chosen by user has been saved
		// or when user decides to cancel entering seat
	} while (seatPValid != true && cancelSeat != '#');

}

// This function is called to ouput (in a table like format) free and taken seats  
// of the current seating class when the user tries a seat that has already been taken
void seatDisplay(bool seat[][NUMBER_OF_SEATS_PER_ROW], int noOfrows)
{
	int counter1;
	rowLetter counter2;
	string symbol1;

	cout << setw(22) << "A" << setw(11) << "B" << setw(11) << "C"
		<< setw(11) << "D" << setw(11) << "E" << setw(11) << "F";
	cout << endl << endl;

	for (counter1 = 0; counter1 < noOfrows; counter1++)
	{
		cout << setw(13) << " " << "Row " << left << setw(4) << counter1 + 1;

		for (counter2 = A; counter2 < G; counter2 = static_cast<rowLetter>(counter2 + 1))
		{
			if (seat[counter1][counter2] != true)
				symbol1 = "*";
			else
				symbol1 = "X";
			cout << setw(11) << symbol1;
		}
		cout << endl << endl;
	}

	cout << right << setw(100) << "'*' -- free seats" <<endl;
	cout << setw(101) << "'X' -- seats taken";
	cout << endl << endl;
}

// This function ouput all the seats (free and taken seats) in table like
// format
void seatPortionDisplay(bool seat[][NUMBER_OF_SEATS_PER_ROW], int x, int y)
{
	int counter1;
	rowLetter counter2;
	string symbol1;

	cout << setw(22) << "A" << setw(11) << "B" << setw(11) << "C"
		<< setw(11) << "D" << setw(11) << "E" << setw(11) << "F";
	cout << endl << endl;

	for (counter1 = x; counter1 <= y; counter1++)
	{
		cout << setw(13) << " " << "Row " << left << setw(4) << counter1 + 1;

		for (counter2 = A; counter2 < G; counter2 = static_cast<rowLetter>(counter2 + 1))
		{
			if (seat[counter1][counter2] != true)
				symbol1 = "*";
			else
				symbol1 = "X";
			cout << setw(11) << symbol1;
		}
		cout << endl << endl;
	}

	cout << right << setw(100) << "'*' -- free seats" << endl;
	cout << setw(101) << "'X' -- seats taken";
	cout << endl << endl;
}