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
const string TextBuddy::MESSAGE_WELCOME = "Welcome to TextBuddy. %s is ready for use";
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
vector<string> TextBuddy::foundInputs;

/*
void TextBuddy::main(int argc, string argv){

	commandLineInterface(argc);
	initialiseUserInput(argv);
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv.c_str());
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
	commandType typeOfCommand = determineCommandType(command);

	switch (typeOfCommand){
	case ADD :
		return addInputs(nameOfFile, restOfInput);
	case DISPLAY:
		return displayInputs(nameOfFile);
	case DELETE: 
		return deleteInputs(nameOfFile, restOfInput);
	case CLEAR:
		return clear(nameOfFile, restOfInput);
	case SORT:
		return sort(nameOfFile);
	case SEARCH:
		return search(nameOfFile, restOfInput);
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
		getFileInputs(nameOfFile);
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

void TextBuddy::getFileInputs(string nameOfFile){

	ifstream readFile;
	string firstOutputLine, secondOutputLine;

	readFile.open(nameOfFile);

	if (!readFile.eof()){
		int numberOfLine = 1;
		getline(readFile, firstOutputLine);

		for (numberOfLine = 1; getline(readFile, secondOutputLine); numberOfLine++) {

			print(numberOfLine, firstOutputLine);
			firstOutputLine = secondOutputLine;
		}

		print(numberOfLine, firstOutputLine);
	}

	readFile.close();
}
*/
/*

string TextBuddy::sort(string nameOfFile){

	//implementing a bubble sort
	for (int i = 0; i < userInputs.size(); i++){
		for (int j = 1; j < userInputs.size(); j++){

			if (checkAnyUpper(j)){
				char firstCharacter = tolower(userInputs[j - 1][0]);
				char secondCharacter = tolower(userInputs[j][0]);

				if (firstCharacter > secondCharacter){
					swap(j);
				}
				else if (checkSameCharacter(firstCharacter, secondCharacter)){
					if (upperCaseSwap(j)){
						swap(j);
					}
				}
			}
			else{
				if (lowerCaseSwap(j)){
					swap(j);
				}
			}
		}
	}
	sprintf_s(buffer, MESSAGE_SORTED.c_str(), nameOfFile.c_str());
	return buffer;
}

string TextBuddy::search(string nameOfFile, string keyWord){

	bool searchResult = false;
	if (binarySearch(nameOfFile, keyWord)){
		searchResult = true;
	}
	else{
		//now we attempt to break the words of each string
		searchResult = seperateString(keyWord);
	}

	if (searchResult){
		printSearchResult();
		foundInputs.clear(); //ready vector for next command
		sprintf_s(buffer, MESSAGE_FOUND.c_str(), nameOfFile.c_str());
	}
	else{
		sprintf_s(buffer, MESSAGE_NOT_FOUND.c_str());
	}

	return buffer;

}

void TextBuddy::swap(int target){

	string temp = userInputs[target - 1];
	userInputs[target - 1] = userInputs[target];
	userInputs[target] = temp;
}

bool TextBuddy::checkAnyUpper(int target){

	return (isupper(userInputs[target - 1][0]) || isupper(userInputs[target][0]));
}

bool TextBuddy::checkSameCharacter(char firstCharacter, char secondCharacter){
	
	if (firstCharacter - secondCharacter == 0){
		return true;
	}
	else{
		return false;
	}
}

bool TextBuddy::upperCaseSwap(int target){

	return (isupper(userInputs[target][0]) && islower(userInputs[target - 1][0]));
}

bool TextBuddy::lowerCaseSwap(int target){

	return (userInputs[target - 1][0] > userInputs[target][0]);
}


bool TextBuddy::binarySearch(string nameOfFile, string keyWord){

	size_t mid, left = 0;
	size_t right = userInputs.size(); // one position passed the right end
	while (left < right) {
		mid = left + (right - left) / 2;
		if (keyWord > userInputs[mid]){
			left = mid + 1;
		}
		else if (keyWord < userInputs[mid]){
			right = mid;
		}
		else {
			foundInputs.push_back(userInputs[mid]);
			return true;
		}
	}

	return false;
}

bool TextBuddy::seperateString(string keyWord){
	
	for (int i = 0; i < userInputs.size(); i++){

		unsigned int tStart = 0;
		unsigned int tEnd = 0;
		string temp = "";
		tEnd = userInputs[i].find_first_of(" ,;");
		while (tEnd != string::npos) {
			temp = userInputs[i].substr(tStart, tEnd - tStart);
			tStart = tEnd + 1; // start of a new word
			if (keyWord == temp){
				foundInputs.push_back(userInputs[i]);
			}
			else{
				tEnd = userInputs[i].find_first_of(" ,;", tStart);
			}
		}
		if (tStart < userInputs[i].size()){
			temp = userInputs[i].substr(tStart);
			if (keyWord == temp){
				foundInputs.push_back(userInputs[i]);
			}
		}
	}
	if (foundInputs.size() != 0){
		return true;
	}
	else{
		return false;
	}

}
*/


/*
void swap(vector<string>& tempVectorString, int target){

	string temp = tempVectorString[target - 1];
	tempVectorString[target - 1] = tempVectorString[target];
	tempVectorString[target] = temp;
}

bool checkAnyUpper(vector<string> tempVectorString, int target){

	return (isupper(tempVectorString[target - 1][0]) || isupper(tempVectorString[target][0]));
}

bool checkSameCharacter(char firstCharacter, char secondCharacter){

	if (firstCharacter - secondCharacter == 0){
		return true;
	}
	else{
		return false;
	}
}

bool upperCaseSwap(vector<string> tempVectorString, int target){

	return (isupper(tempVectorString[target][0]) && islower(tempVectorString[target - 1][0]));
}

bool lowerCaseSwap(vector<string> tempVectorString, int target){

	return (tempVectorString[target - 1][0] > tempVectorString[target][0]);
}


void sort(vector<string>& tempVectorString){

	//implementing a bubble sort
	for (size_t i = 0; i < tempVectorString.size(); i++){
		for (size_t j = 1; j < tempVectorString.size(); j++){

			if (checkAnyUpper(tempVectorString, j)){
				char firstCharacter = tolower(tempVectorString[j - 1][0]);
				char secondCharacter = tolower(tempVectorString[j][0]);

				if (firstCharacter > secondCharacter){
					swap(tempVectorString, j);
				}
				else if (checkSameCharacter(firstCharacter, secondCharacter)){
					if (upperCaseSwap(tempVectorString, j)){
						swap(tempVectorString, j);
					}
				}
			}
			else{
				if (lowerCaseSwap(tempVectorString, j)){
					swap(tempVectorString, j);
				}
			}
		}
	}
	cout << "Sort function is executed" << endl;
}

bool isSorted(vector<string> nameOfVector) {

	bool sorted = true;
	for (size_t i = 0; i < nameOfVector.size() - 1; i++) {
		if (tolower(nameOfVector[i][0]) > tolower(nameOfVector[i + 1][0])){
			sorted = false;
		}
	}
	return sorted;
}
*/


void print(int lineNumber, string message){

	cout << lineNumber << ". " << message << endl;
}

void printSearchResult(vector<string> tempFoundVectorString){
	int iter = 1;
	for (vector<string>::iterator i = tempFoundVectorString.begin(); i != tempFoundVectorString.end(); i++, iter++){
		print(iter, *i);
	}
}

void printVector(vector<string> nameOfVector){

	for (size_t i = 0; i < nameOfVector.size(); i++){
		cout << nameOfVector[i] << endl;
	}
}


bool binarySearch(vector<string> tempVectorString, vector<string>& tempFoundVectorString, string keyWord){

	size_t mid, left = 0;
	size_t right = tempVectorString.size(); // one position passed the right end
	while (left < right) {
		mid = left + (right - left) / 2;
		if (keyWord > tempVectorString[mid]){
			left = mid + 1;
		}
		else if (keyWord < tempVectorString[mid]){
			right = mid;
		}
		else {
			tempFoundVectorString.push_back(tempVectorString[mid]);
			return true;
		}
	}

	return false;
}

bool seperateString(vector<string> tempVectorString, vector<string>& tempFoundVectorString, string keyWord){

	for (size_t i = 0; i < tempVectorString.size(); i++){

		unsigned int tStart = 0;
		unsigned int tEnd = 0;
		string temp = "";
		tEnd = tempVectorString[i].find_first_of(" ,;");
		while (tEnd != string::npos) {
			temp = tempVectorString[i].substr(tStart, tEnd - tStart);
			tStart = tEnd + 1; // start of a new word
			if (keyWord == temp){
				tempFoundVectorString.push_back(tempVectorString[i]);
			}
			else{
				tEnd = tempVectorString[i].find_first_of(" ,;", tStart);
			}
		}
		if (tStart < tempVectorString[i].size()){
			temp = tempVectorString[i].substr(tStart);
			if (keyWord == temp){
				tempFoundVectorString.push_back(tempVectorString[i]);
			}
		}
	}
	if (tempFoundVectorString.size() != 0){
		return true;
	}
	else{
		return false;
	}

}

bool search(vector<string> tempVectorString, vector<string>& tempFoundVectorString, string keyWord){

	bool searchResult = false;
	if (binarySearch(tempVectorString, tempFoundVectorString, keyWord)){
		searchResult = true;
	}
	else{
		//now we attempt to break the words of each string
		searchResult = seperateString(tempVectorString, tempFoundVectorString, keyWord);
	}

	if (searchResult){
		printSearchResult(tempFoundVectorString);
		tempFoundVectorString.clear(); //ready vector for next command
	}
	else{
		cout << "Not found"; 
	}
	return searchResult;

}

//this will be the TDD for the search function present written above.
void isFound(){
	vector<string> tempVectorString;
	vector<string> tempFoundVectorString;

	/*
	//test 1
	//this block of code will attempt to find the a single alphabets provided by the user
	tempVectorString.push_back("H");
	tempVectorString.push_back("F");
	tempVectorString.push_back("w");
	tempVectorString.push_back("c");
	printVector(tempVectorString);
	string keyWord = "w";

	if (search(tempVectorString, tempFoundVectorString, keyWord)){		//if code passes
		cout << "The alphabet 'w' is found!" << endl;
	}
	else{																//if code fails
		cout << "The alphabet 'w' is not found! hence case 1 failed" << endl;
	}
	*/

	/*
	//test 2
	//this block of code will attempt to find the exact keyword and phrases provided by the user
	tempVectorString.push_back("Hi, this is a search");
	tempVectorString.push_back("Find the little brown fox");
	tempVectorString.push_back("who jump over the wall");
	tempVectorString.push_back("can you find it?");
	printVector(tempVectorString);
	string keyWord = "who jump over the wall";

	if (search(tempVectorString, tempFoundVectorString, keyWord)){		//if code passes
		cout << "The keyword who jump over the wall is found!" << endl;
	}
	else{																//if code fails
		cout << "The keyword who jump over the wall is not found! hence case 2 failed" << endl;
	}
	*/

	//test 3
	//this block of code will attempt to find the exact keyword and phrases provided by the user
	tempVectorString.push_back("Hi, this is a search");
	tempVectorString.push_back("Find the little brown fox");
	tempVectorString.push_back("who jump over the wall");
	tempVectorString.push_back("can you find it?");
	printVector(tempVectorString);
	string keyWord = "jump";
	if (search(tempVectorString, tempFoundVectorString, keyWord)){	//if code passes
		cout << "The keyword jump is found!" << endl;
	}
	else{															//if code fails
		cout << "The keyword jump is not found! hence case 3 failed" << endl;
	}
}


/*
// This is the TDD functions which will test the sort function written above
void checkSorted(){

	vector<string> tempVectorString;

	//test 1
	//this test for the sorting algorithm for the 1st alphabet (doesnt test for the presence of capital letter)
	tempVectorString.push_back("b");
	tempVectorString.push_back("d");
	tempVectorString.push_back("a");
	tempVectorString.push_back("c");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);
	
	if (isSorted){
		cout << "The inputs are sorted based on 1st alphabet" << endl;
	}
	else{
		cout << "The inputs are not sorted based on 1st alphabet, test 1 failed" << endl;
	}

	//test 2
	//this test for the sorting algorithm for the subsequent alphabets (doesnt test for the presence of capital letter)
	tempVectorString.push_back("bbc");
	tempVectorString.push_back("dbc");
	tempVectorString.push_back("abc");
	tempVectorString.push_back("cbc");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);
	if (isSorted){
		cout << "The inputs are sorted based on alphabet" << endl;
	}
	else{
		cout << "The inputs are not sorted based on alphabet, test 2 failed" << endl;
	}

	//test 3
	//this test for the sorting algorithm for the 1st alphabet (doesnt test for the presence of capital letter)
	tempVectorString.push_back("B");
	tempVectorString.push_back("b");
	tempVectorString.push_back("A");
	tempVectorString.push_back("a");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);

	if (isSorted){
		cout << "The inputs are sorted based on 1st alphabet" << endl;
	}
	else{
		cout << "The inputs are not sorted based on 1st alphabet, test 3 failed" << endl;
	}

	//test 4
	//this test will try to sort and solve the problem of capital letters present in the vector
	//this bunch of inputs will arrange the code according to ABC,abc,BBC,bbc as the correct inputs.
	tempVectorString.push_back("BBC");
	tempVectorString.push_back("bbc");
	tempVectorString.push_back("ABC");
	tempVectorString.push_back("abc");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);

	if (isSorted){
		cout << "The inputs are sorted based on alphabet" << endl;
	}
	else{
		cout << "The inputs are not sorted based on alphabet, test 4 failed" << endl;
	}

	//test 5
	//this test will try to sort and solve the problem of capital letters present in the vector
	tempVectorString.push_back("This is a test input");
	tempVectorString.push_back("we would be able to know the truth");
	tempVectorString.push_back("the tester will carry on to code till its right");
	tempVectorString.push_back("how about this?");
	printVector(tempVectorString);
	sort(tempVectorString);
	cout << "After sorting:" << endl;
	printVector(tempVectorString);

	if (isSorted){
		cout << "The inputs are sorted based on alphabet" << endl;
	}
	else{
		cout << "The inputs are not sorted based on alphabet, test 5 failed" << endl;
	}
}
*/

/*

vector<string>::iterator TextBuddy::getLineNumber(string nameOfFile, string userCommand){

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

TextBuddy::commandType TextBuddy::determineCommandType(string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "add"){
		return commandType::ADD;
	}
	else if (command == "display") {
		return commandType::DISPLAY;
	}
	else if (command == "delete") {
		return commandType::DELETE;
	}
	else if (command == "clear") {
		return commandType::CLEAR;
	}
	else if (command == "sort") {
		return commandType::SORT;
	}
	else if (command == "search") {
		return commandType::SEARCH;
	}
	else if (command == "exit") {
		return commandType::EXIT;
	}
	else
		return commandType::ERROR;
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

void TextBuddy::commandLineInterface(int argc){

	if (argc > 2) {
		showToUser(MESSAGE_ERROR);
		showToUser(MESSAGE_PROGRAM_TERMINATION);
		exit(0);
	}
}

void TextBuddy::showToUser(string text) {

	cout << text << endl;
}

void TextBuddy::printSearchResult(){
	int iter = 1;
	for (vector<string>::iterator i = foundInputs.begin(); i != foundInputs.end(); i++, iter++){
		print(iter, *i);
	}
}

void TextBuddy::print(int lineNumber, string message){

	cout << lineNumber << ". " << message << endl;
}

*/

//this is the entry point of the programme. 
int main(){
//int main(int argc, char* argv[]){
	//check if the user have input the correct number of arguments
	
	//checkSorted();

	isFound();
	system("pause");
	/*
	if (argc == 1){
		string fileName;
		cout << "Enter a file name: ";
		getline(cin, fileName);
		//TextBuddy::main(2, fileName);
	}
	else {
		//TextBuddy::main(argc, argv[1]);
	}
	*/
	return 0;
}