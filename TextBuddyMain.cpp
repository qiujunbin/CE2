//This class is used to store and retrieve the commands entered by the user in the following way:
//the user can enter the commands like "add", "delete", "display", "clear" and "exit".
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
// command: display
// 1. a quick brown fox
// 2. jumped over a lazy dog
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

static void displayLine(int i, string outputLine){

	cout << i << ". " << outputLine << endl;
}

//this is the entry point of the programme. 
int main(int argc, char* argv[]){
	//check if the user have input the correct number of arguments

	if (argc == 1){
		string fileName;
		cout << "Enter a file name: ";
		getline(cin, fileName);
		TextBuddy::main(2, fileName);
	}
	else {
		TextBuddy::main(argc, argv[1]);
	}
	return 0;
}
