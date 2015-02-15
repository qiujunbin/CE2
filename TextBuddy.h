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
	enum commandType {
		ADD, DISPLAY, DELETE, CLEAR, SORT, SEARCH, EXIT, ERROR
	};

	static void main(int argc, string argv);

private:
	static const string MESSAGE_WELCOME;
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


	static string sort(string nameOfFile);
	static void swap(int target);
	static bool checkAnyUpper(int target);
	static bool checkSameCharacter(char firstCharacter, char secondCharacter);
	static bool upperCaseSwap(int target);
	static bool lowerCaseSwap(int target);

	static bool binarySearch(string nameOfFile, string keyWord);
	static string search(string nameOfFile, string keyWord);
	static bool seperateString(string keyWord);


	static string searchWholeFile(string nameOfFile, string restOfInput);
	static string searchEachLine(string nameOfFile, string restOfInput, string lineNumber);

	static void showToUser(string text);
	static void print(int lineNumber, string message);
	static void commandLineInterface(int argc);
	static void initialiseUserInput(string nameOfFile);
	static void getFileInputs(string nameOfFile);

	static string executeCommand(string nameOfFile, string userCommand);
	static string getFirstWord(string userCommand);
	static string excludeFirstWord(string userCommand);

	static vector<string>::iterator getLineNumber(string nameOfFile, string userCommand);
	static commandType determineCommandType(string command);

};

#endif