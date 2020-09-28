#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum RelationType
{
	LESS,
	GREATER,
	EQUAL
};

class Content
{
public:
	// constructor
	Content()
	{
		fileName = "";
		createAt = "";
		relatedPeople = "";
		eventName = "";
		description = "";
		contentType = 0;
		kindOf = 0;
	}

	//destructor
	~Content() {}

	// property getters
	// returns that property
	string getFileName() { return fileName; }
	string getCreateAt() { return createAt; }
	string getRelatedPeople() { return relatedPeople; }
	string getEventName() { return eventName; }
	string getDescription() { return description; }
	int getContentType() { return contentType; }
	int getKindOf() { return kindOf; }

	// property setters
	// params : data to set
	// post : set property as data
	void setFileName(string data) { fileName = data; }
	void setCreateAt(string data) { createAt = data; }
	void setRelatedPeople(string data) { relatedPeople = data; }
	void setEventName(string data) { eventName = data; }
	void setDescription(string data) { description = data; }
	void setContentType(int data) { contentType = data; }
	void setKindOf(int data) { kindOf = data; }

	// set property 'name' from KB to add, delete, retrieve, etc
	void SetNameFromKB()
	{
		string name;
		cout << "\tFile name : ";
		cin >> name;

		setFileName(name);
	}

	// set records with properties params
	// params : datas to set
	// post : set records as params
	void setRecord(
			string fileName,
			string createAt,
			string relatedPeople,
			string eventName,
			string description,
			int contentType,
			int kindOf)
	{
		setFileName(fileName);
		setCreateAt(createAt);
		setRelatedPeople(relatedPeople);
		setEventName(eventName);
		setDescription(description);
		setContentType(contentType);
		setKindOf(kindOf);
	}

	// get record for link
	// it used to insert favicon and event to store only necessory properties
	// return : simple Content origins Content
	Content getRecordForLink()
	{
		Content Link;
		Link.setFileName(fileName);
		Link.setCreateAt(createAt);
		Link.setContentType(contentType);

		return Link;
	}

	// display records
	void displayRecord();

	// display records for simple Content(link)
	void displayRecordForLink();

	// set record from KB
	// it used to add record on master list
	void setRecordFromKB();

	// set record from KB for simple record
	// it used to add record on favicon, event list
	void setRecordFromKBForLink();

	// read contents from file
	int ReadDataFromFile(ifstream &fin);

	// write contents to file
	int WriteDataToFile(ofstream &fout);

	// read contents from file for simple records
	int ReadDataFromFileForLink(ifstream &fin);

	// write contents to file for simple records
	int WriteDataToFileForLink(ofstream &fout);

	// compare with fileName to sort in list
	RelationType Compare(const Content &data);

	// compare with createAt to use favicon.rearrange()
	RelationType CompareByCreateAt(const Content &data);

	// compare with contentType to use favicon.rearrange()
	RelationType CompareByType(const Content &data);

protected:
	string fileName;
	string createAt;
	string relatedPeople;
	string eventName;
	string description;

	int contentType;
	int kindOf;
};