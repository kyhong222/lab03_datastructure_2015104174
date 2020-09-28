#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "SortedList.h"
#include "Content.h"

using namespace std;

#define MAXSIZE 10

class Favicon {
public:
	// constructor
	Favicon() {
		MCLength = 0;
	}

	// destructor
	Favicon() {}

	// add item in favicon's MCList with fileName as simple record
	int AddItem();

	// delete item in favicon's MCList with fileName as simple record
	int DeleteItem();

	// retrive item in favicon's MCList with fileName
	int RetriveItem();

	// display items as simple record
	void DisplayItems();

	// display items as detailed record
	void DisplayItemsDetailed();

	// rearrange items & display
	void rearrange();

	// it used for access master list on application
	void setMasterList(SortedList<Content>* masterList) { MasterList = masterList; }

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
	int MCLength;					///< MC length

	ifstream m_InFile;				///< input file descriptor.
	ofstream m_OutFile;				///< output file descriptor.

	SortedList<Content> MCList;		///< MC list
	SortedList<Content>* MasterList;///< master list pointer
};
