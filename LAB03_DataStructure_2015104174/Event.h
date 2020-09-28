#pragma once
#include<iostream>
#include<string>
#include "SortedList.h"
#include "Content.h"

using namespace std;

class Event {
public:
	// constructor
	Event() {
		name = "untitled";
		description = "no-description";
		MCLength = 0;
	}

	// destructor
	~Event() {
	}

	// add item in event's MCList with fileName as simple record
	int AddItem();

	// delete item in event's MCList with fileName as simple record
	int DeleteItem();

	// retrive item in event's MCList with fileName
	int RetriveItem();

	// display items as simple record
	void DisplayItems();

	// display items as detailed record
	void DisplayItemsDetailed();

	// it used for access master list on application
	void setMasterList(SortedList<Content>* masterList) { MasterList = masterList; }

	// it used for set event's name & description
	void setEventFromKB();

	// calling event menus
	void getCommand();

	// read event from file
	int ReadDataFromFile();

	// write event to file
	int WriteDataToFile();

	// read event from file with filename
	int OpenInFile(string filename);

	// write event to file with filename
	int OpenOutFile(string filename);

protected:
	string name;					///< event name
	string description;				///< event description
	int MCLength;					///< MC length

	ifstream m_InFile;				///< input file descriptor.
	ofstream m_OutFile;				///< output file descriptor.
	
	SortedList<Content> MCList;		///< MC list
	SortedList<Content>* MasterList;///< master list pointer
};