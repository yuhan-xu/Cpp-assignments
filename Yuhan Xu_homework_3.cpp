/* ******************************************************
 * Name: Yuhan Xu
 * Wisc ID: 9075265950
 * OS: Windows
 * IDE (or text editor):Eclipse
 * Compiler: MinGW
 * How long did the assignment take you to complete in minutes: 1 hour
 * What other resources did you consult (copy and paste links below): None
 *
 */ // ******************************************************
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int counter;

// input: none
// output: a number entered by the user
// alternative output: if the three lines that get input from the user are commmented out
// then the the function will return the next number in the sequence provided in the vector
// test_your_code_with_these_numbers. Use these numbers to duplicate the sample output
// provided in the assignment description to test your code
int Get_User_Input() {
	/* Comment the three lines in this block to test your code with the input below
	int n;
	cin >> n;
	return n;
	// */

	vector<int> test_your_code_with_these_numbers { 1, 28, 13, 43, -1, // Input_Numbers
			7,					// Print_Numbers
			2, 1, -1, 			// Safe_Insert
			7,					// Print_Numbers
			3, 2,				// Safe_Delete
			7,					// Print_Numbers
			4, 					// Sort
			7,					// Print_Numbers
			1, 49, 22, 43, 22, 19, 49, -1,	// Input_Numbers
			7,					// Print_Numbers
			5, 					// Sort_And_Remove_Duplicates
			7,					// Print_Numbers
			6,					// Sum
			0 };					// Quit

	int test_number = test_your_code_with_these_numbers[counter++];
	cout << test_number << endl;
	return test_number;
}

// This function prints out the number and position in the vector of each element. It takes a integer vector called numbers
void Print_Numbers(vector<int> numbers){

	// Print the header
	cout << "The numbers in the vector are: ";
	cout << "\n";

	// Iterate through the vector and for each entry print the position and value so that it matches the sample output
	for (int i = 0; i < numbers.size(); i++) {
		cout << "The value at position " << "[" << i << "]" << " is " << numbers[i] << endl;
	}
}

// Clear the vector of numbers, request that the user enter a number or -1 to quit, get the number from the user using
// the Get_User_Input function, add it to the end of the vector, and keep requesting the user enter an integer until
// they enter a -1. It takes one parameter by reference: a vector of integers
void Input_Numbers(vector<int>& numbers){
	numbers.clear(); // Clear the vector of numbers

	cout << "Please enter a number or -1 to quit: "; // request that the user enter a number or -1 to quit
	int num = Get_User_Input(); // call Get_User_Input function to get the number
	if(num != -1) // if num is not -1, add to the end of the vector
		numbers.push_back(num);


	while (num != -1) // keep requesting the user enter an integer until they enter a -1
	{
	    cout << "Please enter a number or -1 to quit: ";
	    num = Get_User_Input(); // call Get_User_Input function
	    if(num != -1) { // if num is not -1, add to the end of the vector
	    	numbers.push_back(num);
	    }

	}


}

// This method implements a "safe" variation on insertion. It takes one parameter by reference: the vector of integers.
void Safe_Insert(vector<int>& numbers){
	cout << "Enter the index where you would like to insert a number: "; //  first prompts the user to enter the index where they would like to insert the new number
	int index = Get_User_Input(); // Use the function Get_User_Input to read this index

	cout << "Enter the the number to be inserted: "; // prompts the user to indicate the number to be inserted
	int num = Get_User_Input(); // Use the function Get_User_Input to read this number

	if(index < 0){ // If the given index is negative, insert the integer into position 0
		numbers.insert(numbers.begin(),num);
	} else if (index > numbers.size()){ // If the given index is greater than the size of the vector, insert the integer at the end of the vector.
		numbers.insert(numbers.end(),num);
	} else{ // Otherwise insert the integer at the index provided by the user
		numbers.insert(numbers.begin()+index,num);
	}

}

// This method implements implement a "safe" variation on deletion. It takes one parameter by reference: the vector of integers.
void Safe_Delete(vector<int>& numbers){
	cout << "Enter the index where you would like to delete a number: "; // Prompt the user to enter the index of the number to be deleted
	int index = Get_User_Input(); // Use Get_User_Input to read the index

	// Remove the number at the given index if valid
	if(index >= 0 && index <= numbers.size()-1){
		numbers.erase(numbers.begin()+index);
	}

	// If the given index is negative, remove the integer at index 0
	if(index < 0){
		numbers.erase(numbers.begin());
	}

	// If the given index is greater than the size of the vector, remove the last integer in the vector
	if(index > numbers.size()){
		numbers.erase(numbers.end());
    }

	// If the vector is empty, make no changes to the vector
	if(numbers.empty()){
		return;
	}
}

// This function sorts the numbers in ascending order. It takes one parameter by reference: the vector of integers
void Sort_Numbers(vector<int>& numbers){
	sort(numbers.begin(), numbers.end()); // use sort from C++ library to sort numbers
}

// This function sorts the numbers in ascending order and removes duplicate numbers. It takes one parameter by reference
void Sort_And_Remove_Duplicates(vector<int>& numbers){
	Sort_Numbers(numbers); // call Sort_Numbers function first to sort numbers vector

	// for each number in the vector, if it is equal to the previous number, erase it
	for(int i=1;i<numbers.size();i++){
		// check if ith element in numbers is equal to i-1st element in numbers
		if(numbers[i] == numbers[i-1]){
			numbers.erase(numbers.begin()+i); // if they are the same, erase ith element
		}
	}

}

// This function computes and returns the sum of the numbers in the vector
int Sum(vector<int> numbers){
	int sum = 0; // create an int variable called sum and initialize it to be 0

	for (auto n : numbers) // for each element in numbers, sum them together
	    sum += n;

	return sum; // return the sum

}

// #### DO ALL OF YOUR WORK ABOVE THIS LINE!!! ###
// #### We will copy and paste everything above into the grading script for testing
int main() {
	counter = 0;
	vector<int> numbers;
	int total = 0;
	int choice = 1;

	cout << "0. Quit" << endl;
	cout << "1. Input_Numbers" << endl;
	cout << "2. Safe_Insert" << endl;
	cout << "3. Safe_Delete" << endl;
	cout << "4. Sort_Numbers" << endl;
	cout << "5. Sort_And_Remove_Duplicates" << endl;
	cout << "6. Sum" << endl;
	cout << "7. Print_Numbers" << endl << endl;

	while (choice) {
		cout << "Choose one of the menu options: ";
		choice = Get_User_Input();

		switch (choice) {
		case 0:
			break;
		case 1:
			Input_Numbers(numbers);
			break;
		case 2:
			Safe_Insert(numbers);
			break;
		case 3:
			Safe_Delete(numbers);
			break;
		case 4:
			Sort_Numbers(numbers);
			break;
		case 5:
			Sort_And_Remove_Duplicates(numbers);
			break;
		case 6:
			total = Sum(numbers);
			cout << "The total is " << total << endl;
			break;
		case 7:
			Print_Numbers(numbers);
			break;
		default:
			break;
		}
		cout << endl;
	}

	return 0;
}



/* Sample Run using the test_your_code_with_these_numbers in Get_User_Input
0. Quit
1. Input_Numbers
2. Safe_Insert
3. Safe_Delete
4. Sort_Numbers
5. Sort_And_Remove_Duplicates
6. Sum
7. Print_Numbers

Choose one of the menu options: 1
Please enter a number or -1 to quit: 28
Please enter a number or -1 to quit: 13
Please enter a number or -1 to quit: 43
Please enter a number or -1 to quit: -1

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is 28
The value at position [1] is 13
The value at position [2] is 43

Choose one of the menu options: 2
Enter the index where you would like to insert a number: 1
Enter the the number to be inserted: -1

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is 28
The value at position [1] is -1
The value at position [2] is 13
The value at position [3] is 43

Choose one of the menu options: 3
Enter the index where you would like to delete a number: 2

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is 28
The value at position [1] is -1
The value at position [2] is 43

Choose one of the menu options: 4

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is -1
The value at position [1] is 28
The value at position [2] is 43

Choose one of the menu options: 1
Please enter a number or -1 to quit: 49
Please enter a number or -1 to quit: 22
Please enter a number or -1 to quit: 43
Please enter a number or -1 to quit: 22
Please enter a number or -1 to quit: 19
Please enter a number or -1 to quit: 49
Please enter a number or -1 to quit: -1

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is 49
The value at position [1] is 22
The value at position [2] is 43
The value at position [3] is 22
The value at position [4] is 19
The value at position [5] is 49

Choose one of the menu options: 5

Choose one of the menu options: 7
The numbers in the vector are:
The value at position [0] is 19
The value at position [1] is 22
The value at position [2] is 43
The value at position [3] is 49

Choose one of the menu options: 6
The total is 133

Choose one of the menu options: 0

*/



