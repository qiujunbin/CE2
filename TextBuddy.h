#ifndef TEXTBUDDY_H_
#define TEXTBUDDY_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

class TextBuddy{

public:
	// These are the possible command types
	enum COMMAND_TYPE {
		ADD, DISPLAY, DELETE, CLEAR, SORT, SEARCH, EXIT, ERROR
	};

	static void main(int argc, string argv);

private:
	static const string WELCOME_MESSAGE;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_CLEARED;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_ERROR;
	static const string MESSAGE_PROGRAM_TERMINATION;
	static const string MESSAGE_LINE_ERROR;
	static const string MESSAGE_IS_EMPTY;
	static const string MESSAGE_CANNOT_DELETE;
	static const string MESSAGE_CANNOT_ADD;
	static const string MESSAGE_SORTED;
	static const string MESSAGE_NOT_FOUND;
	static const string MESSAGE_FOUND;

	static char buffer[255];
	static vector<string> userInputs;

	static void enterCommand(string nameOfFile);
	static void saveToFile(string nameOfFile);

	static string addInputs(string nameOfFile, string restOfInput);
	static string displayInputs(string nameOfFile);
	static string deleteInputs(string nameOfFile, string restOfInput);
	static string clear(string nameOfFile, string restOfInput);
	static string sortAlphabetical(string nameOfFile);

	static string searchFile(string nameOfFile, string restOfInput);
	static string searchLine(string nameOfFile, string restOfInput, string lineNumber);

	static void showToUser(string text);
	static void validCommandLineInterface(int argc);
	static void initialiseUserInput(string nameOfFile);

	static string executeCommand(string nameOfFile, string userCommand);
	static string getFirstWord(string userCommand);
	static string excludeFirstWord(string userCommand);
	static vector<string>::iterator getLineNumber(string nameOfFile, string userCommand);
	static COMMAND_TYPE determineCommandType(string command);

};

#endif