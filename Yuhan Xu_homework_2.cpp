/* ******************************************************
 * Name: Yuhan Xu
 * Wisc ID: 9075265950
 * OS: Windows
 * IDE (or text editor): Eclipse
 * Compiler: MinGW
 * How long did the assignment take you to complete in minutes: 1h30min
 * What other resources did you consult (copy and paste links below): No
 */ // ******************************************************
// note the grading script will only allow these include files - do not add extra #includes
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// declare and initialize constant variables
const int MAX_CLASS_SIZE = 100;
const int MAX_NUMBER_OF_ASSIGNMENTS = 100;

// function declaration
// do not change these prototypes.  Add your code to the function definitions below
void Read_Grade_File(string names[MAX_CLASS_SIZE][2],
		int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int *number_of_students,
		int *number_of_assignments, const string input_filename);
void Format_Case_Of_Names(string names[MAX_CLASS_SIZE][2], const int number_of_students);
void Compute_Total_And_Percent(int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int total[],
		float percent[], int number_of_students, int number_of_assignments);
void Write_Formatted_Grades(string names[MAX_CLASS_SIZE][2], int total[], float percent[],
		const int number_of_students, const string output_filename);


// There is no need to change main. However you are encouraged to write code
// that writes data to the console to check the correctness of each of your functions as
// as you work.
int main() {
	string input_filename = "unformatted_grades.txt";
	string output_filename = "formatted_grades.txt";
	string names[MAX_CLASS_SIZE][2];
	int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS];
	int number_of_students = 0;
	int number_of_assignments = 0;
	int total[MAX_CLASS_SIZE];
	float percent[MAX_CLASS_SIZE];

	Read_Grade_File(names, scores, &number_of_students, &number_of_assignments, input_filename);
	Format_Case_Of_Names(names, number_of_students);
	Compute_Total_And_Percent(scores, total, percent, number_of_students, number_of_assignments);
	Write_Formatted_Grades(names, total, percent, number_of_students, output_filename);
	return 0;
}

// Add your code below to define these functions
// remember to add comments to each function to describe the
// 1) purpose, 2) input, and 3) output of the functions

// This function reads unformatted grade txt files
void Read_Grade_File(string names[MAX_CLASS_SIZE][2],
		int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int *number_of_students,
		int *number_of_assignments, const string input_filename) {
	ifstream infile; // use infile to read grade file

	// declare some string variables
	string word;
	string skip;
	string line;

	int count_student = 0; // create a int variable that uses to count student and initialize it to be 0

	infile.open(input_filename); // open the file called input_filename
	infile >> word >>*number_of_students; // read number_of_students using pointer
	infile >> word >>*number_of_assignments; // read number_of_assignments using pointer

	// this for loop is used to skip the third row of the unformatted text file
	for(int i=0; i<(*number_of_assignments + 3);i++){
		infile>>skip;
	}

	// use getline to read file by line
	while(getline(infile,line)){
		int count_score = 0; // create a int variable that uses to count score and initialize it to be 0
		infile>>skip; // skip some elements
		infile>>names[count_student][0]>>names[count_student][1]; // read certain entries of string names

		// while count_score is less than number_of_assignments, read in specific score(scores[count_student][count_score]) and increment count_score
		while(count_score < *number_of_assignments){
			infile>>scores[count_student][count_score];
			count_score++;
		}

		// if count_student is smaller than number_of_students-1, increment count_student
		if(count_student < (*number_of_students-1)){
			count_student++;
		}
	}

	infile.close(); // close the file after reading


}

// This function formats the case of names
void Format_Case_Of_Names(string names[MAX_CLASS_SIZE][2], const int number_of_students) {
	//looping through the number of students
	for (int i = 0; i < number_of_students; i++) {
		for (int j = 0; j < 2; j++) {
			string name = names[i][j]; //read the first and last name
			name[0] = toupper(name[0]); //change the first character to upper case

			int k = 1;
			// bring each character of name to lower case
			while (name[k]) {
				name[k] = tolower(name[k]); // bring each character of name to lower case
				k++;
			}

			names[i][j] = name; // assign name to names[i][j]

		}
	}
}

// This function computes total score and percentage
void Compute_Total_And_Percent(int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int total[],
		float percent[], int number_of_students, int number_of_assignments) {
	// loop through each student and get their score and percentage
	for (int i = 0; i < number_of_students; i++) {
		int sum = 0;
        // this for loop helps to get the sum that is the total score
		for (int j = 0; j < number_of_assignments; j++) {
			sum += scores[i][j];
		}
		total[i] = sum; //total scores
		percent[i] = (((float) sum * 10) / (float) number_of_assignments); // calculate percentage

	}

}

// This function writes formatted grade to the outFile
void Write_Formatted_Grades(string names[MAX_CLASS_SIZE][2], int total[], float percent[],
		const int number_of_students, const string output_filename) {
	ofstream outFile; // use outFile to write
	outFile.open(output_filename); // open the file named output_filename

	// write information of each student in formatted outFile
	for (int i = 0; i < number_of_students; i++) {
		string name = names[i][1] + ", " + names[i][0];
		outFile << setw(19) << left << name; // write names of each student
		outFile << setw(3) << right << total[i]; // write total score
		// write percentage to outFile
		outFile << setw(7) << right << fixed << setprecision(1) << percent[i] << endl;
	}

	outFile.close(); // close the file
}


