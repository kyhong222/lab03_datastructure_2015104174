#include"Event.h"

int Event::AddItem() {
	Content temp;
	temp.SetNameFromKB();

	if (MasterList->Retrieve_BinaryS(temp)) {
		temp = temp.getRecordForLink();
		MCList.Add(temp);
		MCLength++;
		return 1;
	}
	else {
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

int Event::DeleteItem() {
	Content temp;
	temp.SetNameFromKB();

	if (MCList.Delete(temp)) { 
		MCLength--; 
		return 1;
	}
	else {
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

int Event::RetriveItem() {
	Content temp;
	temp.SetNameFromKB();
	if (MCList.Retrieve_BinaryS(temp)) {
		temp.displayRecord();
		return 1;
	}
	else {
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

void Event::DisplayItems() {
	Content temp;
	cout << endl;
	cout << "\n\tMC list in event(Link)" << endl;

	// list의 모든 데이터를 화면에 출력
	MCList.ResetList();
	int length = MCLength;
	int curIndex = MCList.GetNextItem(temp);
	while (curIndex < length && curIndex != -1)
	{
		temp.displayRecordForLink();
		curIndex = MCList.GetNextItem(temp);
	}
}


void Event::DisplayItemsDetailed() {
	Content temp;
	cout << endl;
	cout << "\n\tMC list in event" << endl;

	// list의 모든 데이터를 화면에 출력
	MCList.ResetList();
	int length = MCLength;
	int curIndex = MCList.GetNextItem(temp);
	while (curIndex < length && curIndex != -1)
	{
		MasterList->Retrieve_BinaryS(temp);
		temp.displayRecord();
		curIndex = MCList.GetNextItem(temp);
	}
}

void Event::setEventFromKB() {
	string nameData, descriptionData;

	cout << "\t Event name : ";
	cin >> nameData;

	cout << "\t Event description : ";
	cin >> descriptionData;

	name = nameData;
	description = descriptionData;
}

void Event::getCommand() {
	while (1)
	{
		cout << endl << endl;
		cout << "\tEvent name : " << name << endl;
		cout << "\tEvent description : " << description << endl;
		cout << "\t---ID -- Command ----- " << endl;
		cout << "\t   1 : Add content on event list" << endl;
		cout << "\t   2 : Delete content on event list" << endl;
		cout << "\t   3 : Retrive content by fileName" << endl;
		cout << "\t   4 : Display item on event list" << endl;
		cout << "\t   5 : Display item on event list detailed" << endl;
		cout << "\t   6 : Set empty event list" << endl;
		cout << "\t   7 : Get event list from file" << endl;
		cout << "\t   8 : Put event list to file " << endl;
		cout << "\t   9 : Set event data" << endl;
		cout << "\t   0 : Quit" << endl;

		cout << endl << "\t Choose a Command--> ";

		int m_Command;
		cin >> m_Command;

		switch (m_Command)
		{
		case 1:		// read a record and add to list.
			AddItem();
			break;
		case 2:		//delete
			DeleteItem();
			break;
		case 3:		//replace
			RetriveItem();
			break;
		case 4:		//search by filename.
			DisplayItems();
			break;
		case 5:		// display all the records in list on screen.
			DisplayItemsDetailed();
			break;
		case 6:		// make empty list.
			MCList.MakeEmpty();
			name = "untitled";
			description = "no-description";
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 9:
			setEventFromKB();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// Open a file by file descriptor as an input file.
int Event::OpenInFile(string fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Event::OpenOutFile(string fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_OutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Event::ReadDataFromFile()
{
	int index = 0;
	Content data;	// 읽기용 임시 변수

	string filename;
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return 0;

	// 이벤트 정보 추가
	m_InFile >> name >> description;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!m_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFileForLink(m_InFile);
		MCList.Add(data);
	}
	MCLength = MCList.GetLength();
	m_InFile.close();	// file close

	// 현재 list 출력
	//DisplayAllItem();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Event::WriteDataToFile()
{
	Content data;	// 쓰기용 임시 변수

	string filename;
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	// 이벤트 정보 추가
	m_OutFile << name << endl
		<< description << endl;

	// list 포인터를 초기화
	MCList.ResetList();

	// list의 모든 데이터를 파일에 쓰기
	int length = MCLength;
	int curIndex = MCList.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFileForLink(m_OutFile);
		curIndex = MCList.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}