#include"Content.h"

void Content::displayRecord() {
	cout << endl;
	cout << "\tFile name : " << fileName << endl;
	cout << "\tCreate at : " << createAt << endl;
	cout << "\tRelated people : " << relatedPeople << endl;
	cout << "\tEvent name : " << eventName << endl;
	cout << "\tDescription : " << description << endl;
	cout << "\tContent type : ";
	switch (contentType)
	{
	case 1:
		cout << "photo";
		break;
	case 2:
		cout << "panorama";
		break;
	case 3:
		cout << "video";
		break;
	default:
		cout << "unknown";
		break;
	}
	cout << endl;
	cout << "\tKind of : ";
	switch (kindOf)
	{
	case 1:
		cout << "people";
		break;
	case 2:
		cout << "place";
		break;
	case 3:
		cout << "stuff";
		break;
	case 4:
		cout << "video";
		break;
	default:
		cout << "unknown";
		break;
	}
	cout << endl;
	cout << "--------------------------------" << endl;
}

void Content::displayRecordForLink() {
	cout << endl;
	cout << "\tFile name : " << fileName << endl;
	cout << "\tCreate at : " << createAt << endl;
	cout << "\tContent type : ";
	switch (contentType)
	{
	case 1:
		cout << "photo";
		break;
	case 2:
		cout << "panorama";
		break;
	case 3:
		cout << "video";
		break;
	default:
		cout << "unknown";
		break;
	}
	cout << endl;
	cout << "--------------------------------" << endl;
}

void Content::setRecordFromKB() {
	cout << "\tFile name : ";
	cin >> fileName;

	cout << "\tCreate at : ";
	cin >> createAt;

	cout << "\tRelated people : ";
	cin >> relatedPeople;

	cout << "\tEvent name : ";
	cin >> eventName;

	cout << "\tDescription : ";
	cin >> description;

	cout << "\tContent type(1.photo 2.panorama 3.video) : ";
	cin >> contentType;

	cout << "\tKind of(1.people 2.place 3.stuff 4.video) : ";
	cin >> kindOf;
}

void Content::setRecordFromKBForLink() {
	cout << "\tFile name : ";
	cin >> fileName;

	cout << "\tCreate at : ";
	cin >> createAt;

	cout << "\tContent type(1.photo 2.panorama 3.video) : ";
	cin >> contentType;
}

// Read a record from file.
int Content::ReadDataFromFile(ifstream& fin)
{
	fin >> fileName;
	fin >> createAt;
	fin >> relatedPeople;
	fin >> eventName;
	fin >> description;
	fin >> contentType;
	fin >> kindOf;

	return 1;
};

// Write a record into file.
int Content::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << fileName << " ";
	fout << createAt << " ";
	fout << relatedPeople << " ";
	fout << eventName << " ";
	fout << description << " ";
	fout << contentType << " ";
	fout << kindOf << " ";

	return 1;
}

// Read a record from file.
int Content::ReadDataFromFileForLink(ifstream& fin)
{
	fin >> fileName;
	fin >> createAt;
	fin >> contentType;

	return 1;
};

// Write a record into file.
int Content::WriteDataToFileForLink(ofstream& fout)
{
	fout << endl;
	fout << fileName << " ";
	fout << createAt << " ";
	fout << contentType << " ";

	return 1;
}


// Compare two itemtypes.
RelationType Content::Compare(const Content &data)
{
	if (this->fileName > data.fileName)
		return GREATER;
	else if (this->fileName < data.fileName)
		return LESS;
	else
		return EQUAL;
}

// Compare two itemtypes.
RelationType Content::CompareByCreateAt(const Content &data)
{
	if (this->createAt > data.createAt)
		return GREATER;
	else if (this->createAt < data.createAt)
		return LESS;
	else
		return EQUAL;
}

// Compare two itemtypes.
RelationType Content::CompareByType(const Content &data)
{
	if (this->contentType > data.contentType)
		return GREATER;
	else if (this->contentType < data.contentType)
		return LESS;
	else
		return EQUAL;
}