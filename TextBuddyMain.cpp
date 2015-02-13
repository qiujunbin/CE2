//This class is used to store and retrieve the commands entered by the user in the following way:
//the user can enter the commands like "add", "delete", "display", "clear", "sort", "search" and "exit",
//Any other commands will be deem to be invalid and will be followed by an error message.
//user will be deemed to be entering inputs following commands as mentioned above.
//there will be a save function after the user exits the programme, which will save the user inputs in the user specified <filename>.txt
//initialised from the command line interface.

//The programme will be saved after user exits the program because it will keep track of the inputs that user have added and are still
//remaining in the string vector at the end of his operation. This prevents premature optimization.

//The programme will be as follow:

// Welcome to TextBuddy. <filename>.txt is ready for use
// command: add a quick brown fox
// added to <filename>.txt: "a quick brown fox"
// command: add jumped over a lazy dog
// added to <filename>.txt: "jumped over a lazy dog"
// command: add based on his instinct
// added to <filename>.txt: "based on his instinct"
// command: display
// 1. a quick brown fox
// 2. jumped over a lazy dog
// 3. based on his instinct
// command: sort
// Contents in <filename>.txt have been alphabetically sorted.
// command: display
// 1. a quick brown fox
// 2. based on his instinct
// 3. jumped over a lazy dog
// command: search instinct
// 1. based on his instinct
// Words have been found in lines present in <filename>.txt
// command: delete 1
// deleted from <textfile>.txt: "a quick brown fox"
// command: display
// 1. jumped over a lazy dog
// command: clear
// all content deleted from <textfile>.txt
// command: exit

//@author Qiu Junbin 


#include <iostream>
#include "TextBuddy.h"

using namespace std;

// These are the static variables that cannot be initialize in header file
const string TextBuddy::WELCOME_MESSAGE = "Welcome to TextBuddy. %s is ready for use";
const string TextBuddy::MESSAGE_ADDED = "added to %s: \"%s\"";
const string TextBuddy::MESSAGE_DELETED = "deleted from %s: \"%s\"";
const string TextBuddy::MESSAGE_CLEARED = "all content deleted from %s";
const string TextBuddy::MESSAGE_ERROR = "ERROR: Unrecognised command type";
const string TextBuddy::MESSAGE_PROGRAM_TERMINATION = "Press any key to terminate the program . . .";
const string TextBuddy::MESSAGE_LINE_ERROR = "ERROR: Unable to find the line specified";
const string TextBuddy::MESSAGE_IS_EMPTY = "%s is empty.";
const string TextBuddy::MESSAGE_CANNOT_DELETE = "There is no inputs to delete. Please Specify.";
const string TextBuddy::MESSAGE_CANNOT_ADD = "There is no inputs to add. Please Specify.";
const string TextBuddy::MESSAGE_SORTED = "Contents in %s have been alphabetically sorted.";
const string TextBuddy::MESSAGE_NOT_FOUND = "Words not found in any line.";
const string TextBuddy::MESSAGE_FOUND = "Words have been found in lines present in %s";

char TextBuddy::buffer[255] = "";
vector<string> TextBuddy::userInputs;


void TextBuddy::main(int argc, string argv){

	validCommandLineInterface(argc);
	initialiseUserInput(argv);
	sprintf_s(buffer, WELCOME_MESSAGE.c_str(), argv.c_str());
	showToUser(buffer);
	enterCommand(argv);

	return;
}

void TextBuddy::enterCommand(string nameOfFile){

	while (true) {
		cout << "command:" <<endl;

		string userCommand;
		getline(cin, userCommand);

		string systemMessage = executeCommand(nameOfFile, userCommand);
		saveToFile(nameOfFile);
		showToUser(systemMessage);
	}

	return;
}

string TextBuddy::executeCommand(string nameOfFile, string userCommand){

	string command = getFirstWord(userCommand);
	string restOfInput = excludeFirstWord(userCommand);
	COMMAND_TYPE typeOfCommand = determineCommandType(command);

	switch (typeOfCommand){
	case ADD :
		return addInputs(nameOfFile, restOfInput);
	case DISPLAY:
		return displayInputs(nameOfFile);
	case DELETE: 
		return deleteInputs(nameOfFile, restOfInput);
	case CLEAR:
		return clear(nameOfFile, restOfInput);
		/*
	case SORT:
		return sortAlphabetical(nameOfFile);
	case SEARCH:
		return searchWholeFile(nameOfFile, restOfInput);
		*/
	case EXIT:
		exit(0);
	default:
		showToUser(MESSAGE_ERROR);
		showToUser(MESSAGE_PROGRAM_TERMINATION);
		getchar();
		exit(EXIT_FAILURE);
	}
}

string TextBuddy::addInputs(string nameOfFile, string restOfInput){

	userInputs.push_back(restOfInput);
	sprintf_s(buffer, MESSAGE_ADDED.c_str(), nameOfFile.c_str(), restOfInput.c_str());

	return buffer;
}

string TextBuddy::displayInputs(string nameOfFile){

	if (userInputs.empty()){
		sprintf_s(buffer, MESSAGE_IS_EMPTY.c_str(), nameOfFile.c_str());
		return buffer;
	}
	else{

		ifstream readFile;
		string firstOutputLine, secondOutputLine;
		int numberOfLine = 0;

		readFile.open(nameOfFile);

		if (!readFile.eof()){
			numberOfLine = 1;
			getline(readFile, firstOutputLine);

			if (!readFile.eof()){

				for (numberOfLine = 1; getline(readFile, secondOutputLine); numberOfLine++) {

					cout << numberOfLine << ". " << firstOutputLine << endl;
					firstOutputLine = secondOutputLine;
				}
			}

			cout << numberOfLine << ". " << firstOutputLine;
		}

		readFile.close();
	}

	return "";
}

string TextBuddy::deleteInputs(string nameOfFile, string restOfInput){

	vector<string>::iterator iter = getLineNumber(nameOfFile, restOfInput);
	sprintf_s(buffer, MESSAGE_DELETED.c_str(), nameOfFile.c_str(), iter->c_str());
	userInputs.erase(iter);

	return buffer;
}

string TextBuddy::clear(string nameOfFile, string restOfInput){

	userInputs.clear();
	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), nameOfFile.c_str());

	return buffer;
}


void sort(vector<string>&nameOfVector){

	//implementing a bubble sort
	for (int i = 0; i < nameOfVector.size(); i++){
		for (int j = 1; j < nameOfVector.size(); j++){

			if (isupper(nameOfVector[j - 1][0]) || isupper(nameOfVector[j][0])){
				char convertFirstCharacter = tolower(nameOfVector[j - 1][0]);
				char convertSecondCharacter = tolower(nameOfVector[j][0]);

				if (convertFirstCharacter > convertSecondCharacter){
					string temp = nameOfVector[j - 1];
					nameOfVector[j - 1] = nameOfVector[j];
					nameOfVector[j] = temp;
				}
				else if (convertFirstCharacter - convertSecondCharacter == 0){
					if (isupper(nameOfVector[j][0]) && islower(nameOfVector[j - 1][0])){
						string temp = nameOfVector[j - 1];
						nameOfVector[j - 1] = nameOfVector[j];
						nameOfVector[j] = temp;
					}
				}
			}
			else{
				if (nameOfVector[j - 1][0] > nameOfVector[j][0]){
					string temp = nameOfVector[j - 1];
					nameOfVector[j - 1] = nameOfVector[j];
					nameOfVector[j] = temp;
				}
			}
		}
	}
}

//the search function will do a binary search with a sorted vector<string>
bool binarySearch(vector<string>&nameOfVector, string keyWord){

	sort(nameOfVector);
	size_t mid, left = 0;
	size_t right = nameOfVector.size(); // one position passed the right end
	while (left < right) {
		mid = left + (right - left) / 2;
		if (keyWord > nameOfVector[mid]){
			left = mid + 1;
		}
		else if (keyWord < nameOfVector[mid]){
			right = mid;
		}
		else {
			return true;
		}
	}

	return false;
}

bool search(vector<string>&nameOfVector, string keyWord){


	if (binarySearch(nameOfVector, keyWord)){
		return true;
	}
	else{
		//now we attempt to break the words of each string
		for (int i = 0; i < nameOfVector.size(); i++){

			unsigned int tStart = 0;
			unsigned int tEnd = 0;
			string temp = "";
			tEnd = nameOfVector[i].find_first_of(" ,;");
			while (tEnd != string::npos) {
				temp = nameOfVector[i].substr(tStart, tEnd - tStart);
				tStart = tEnd + 1; // start of a new word
				if (keyWord == temp){
					return true;
				}
				else{
					tEnd = nameOfVector[i].find_first_of(" ,;", tStart);
				}
			}
			if (tStart < nameOfVector[i].size()){
				temp = nameOfVector[i].substr(tStart);
				if (keyWord == temp){
					return true;
				}
			}
		}
	}
		return false;

}


void printVector(vector<string> nameOfVector){

	for (int i = 0; i < nameOfVector.size(); i++){
		cout << nameOfVector[i] << endl;
	}
}

//this will be the TDD for the search function present written above.
void isFound(){

	vector<string> tempVectorString;

	/*
	//this block of code will attempt to find the exact keyword and phrases provided by the user
	tempVectorString.push_back("Hi, this is a search");
	tempVectorString.push_back("Find the little brown fox");
	tempVectorString.push_back("who jump over the wall");
	tempVectorString.push_back("can you find it?");
	printVector(tempVectorString);
	string keyWord = "who jump over the wall";
	if (search(tempVectorString, keyWord)){
		cout << "The keyword who jump over the wall is found!" << endl;
	}
	else{
		cout << "The keyword who jump over the wall is not found!" << endl;
	}
	*/
	
	//this block of code will attempt to find the exact keyword and phrases provided by the user
	tempVectorString.push_back("Hi, this is a search");
	tempVectorString.push_back("Find the little brown fox");
	tempVectorString.push_back("who jump over the wall");
	tempVectorString.push_back("can you find it?");
	printVector(tempVectorString);
	string keyWord1 = "jump";
	if (search(tempVectorString, keyWord1)){
		cout << "The keyword jump is found!" << endl;
	}
	else{
		cout << "The keyword jump is not found!" << endl;
	}
	
}

// This is the TDD functions which will test the sort function written above
void checkSorted(){

	vector<string> tempVectorString;

	//this test for the sorting algorithm for the 1st alphabet

	tempVectorString.push_back("bbc");
	tempVectorString.push_back("dbc");
	tempVectorString.push_back("abc");
	tempVectorString.push_back("cbc");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);

	//this test will try to sort and solve the problem of capital letters present in the vector
	tempVectorString.push_back("BBC");
	tempVectorString.push_back("bbc");
	tempVectorString.push_back("ABC");
	tempVectorString.push_back("abc");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);

}

/*
bool isFound(string nameOfFile, string inputs){

	vector<string>::iterator iter = 
}
*/
/*
string TextBuddy::sortAlphabetical(string nameOfFile){

	//stable_sort(userInputs.begin(), userInputs.end());

	sprintf_s(buffer, MESSAGE_SORTED.c_str(), nameOfFile.c_str());
	return buffer;
}

string TextBuddy::searchWholeFile(string nameOfFile, string keyWord){

	bool searchFound = false;
	int lineNumber = 0;
	int sizeOfFile = userInputs.size();

	for (int i = 1; i <= sizeOfFile; i++){

		string linesInFile = to_string(i);
		string searchResult = searchEachLine(nameOfFile, keyWord, linesInFile);
		if (searchResult != string()){
			searchFound = true;
			++lineNumber;
			cout << lineNumber << ". " << searchResult << endl;
		}
	}

	if (searchFound){
		sprintf_s(buffer, MESSAGE_FOUND.c_str(), nameOfFile.c_str());
	}
	else{
		sprintf_s(buffer, MESSAGE_NOT_FOUND.c_str());
	}

	return buffer;

}

string TextBuddy::searchEachLine(string nameOfFile, string keyWord, string lineNumber){

	string::iterator checkLine;
	vector<string>::iterator iter = getLineNumber(nameOfFile, lineNumber);

	checkLine = search (iter->begin(), iter->end(), keyWord.begin(), keyWord.end());

	if (checkLine == iter->end() || iter->end() == iter->begin()){
		return string();
	}
	else
		return *iter;

}
*/


//this function returns the number that the user wants to delete in order for the deleteInputs function to work
vector<string>::iterator TextBuddy::getLineNumber(string nameOfFile, string userCommand){

	//declared an integer iter for comparision with stoi function later
	int iter = 1;
	for (vector<string>::iterator i = userInputs.begin(); i != userInputs.end(); i++) {
		if (iter == stoi(userCommand)) {
			return i;
		}
		else
			iter++;
	}

	sprintf_s(buffer, MESSAGE_LINE_ERROR.c_str(), nameOfFile.c_str());
	showToUser(buffer);

	return userInputs.end();
}

TextBuddy::COMMAND_TYPE TextBuddy::determineCommandType(string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "add"){
		return COMMAND_TYPE::ADD;
	}
	else if (command == "display") {
		return COMMAND_TYPE::DISPLAY;
	}
	else if (command == "delete") {
		return COMMAND_TYPE::DELETE;
	}
	else if (command == "clear") {
		return COMMAND_TYPE::CLEAR;
	}
	else if (command == "sort") {
		return COMMAND_TYPE::SORT;
	}
	else if (command == "search") {
		return COMMAND_TYPE::SEARCH;
	}
	else if (command == "exit") {
		return COMMAND_TYPE::EXIT;
	}
	else
		return COMMAND_TYPE::ERROR;
}

string TextBuddy::getFirstWord(string userCommand){

	string command = userCommand.substr(0, userCommand.find_first_of(" "));
	return command;
}

string TextBuddy::excludeFirstWord(string userCommand){

	string restOfInput = userCommand.substr(userCommand.find_first_of(" ") + 1);
	return restOfInput;
}

//function will exercise the save to file by deleting the initial one and then creating a new file
void TextBuddy::saveToFile(string nameOfFile){
	ifstream inputFile;
	ofstream outputFile;

	inputFile.open("fileToBeRenamed.txt");
	inputFile.close();
	remove(nameOfFile.c_str());
	rename("fileToBeRenamed.txt", nameOfFile.c_str());

	//input into file from vector<string>
	if (userInputs.begin() != userInputs.end()) {
		for (vector<string>::iterator i = userInputs.begin(); i != userInputs.end(); i++) {
			//ios::app All output operations are performed at the end of the file, appending the content to the current content of the file.
			outputFile.open(nameOfFile.c_str(), ios::app); 
			outputFile << *i << endl;
			outputFile.close();
		}
	}
}

void TextBuddy::initialiseUserInput(string nameOfFile){

	ifstream inputFile;
	string line;
	inputFile.open(nameOfFile);

	while (getline(inputFile, line)) {
		userInputs.push_back(line);
	}
	inputFile.close();
	return;
}

void TextBuddy::validCommandLineInterface(int argc){

	if (argc > 2) {
		showToUser(MESSAGE_ERROR);
		showToUser(MESSAGE_PROGRAM_TERMINATION);
		exit(0);
	}
}

//acts as a printing function
void TextBuddy::showToUser(string text) {

	cout << text << endl;
}


//this is the entry point of the programme. 
int main(int argc, char* argv[]){
	//check if the user have input the correct number of arguments
	//checkSorted();
	isFound();
	if (argc == 1){
		string fileName;
		cout << "Enter a file name: ";
		getline(cin, fileName);
		//TextBuddy::main(2, fileName);
	}
	else {
		//TextBuddy::main(argc, argv[1]);
	}
	return 0;
}
