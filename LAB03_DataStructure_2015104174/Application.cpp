#include "Application.h"

// Program driver.
void Application::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1: // read a record and add to list.
			AddItem();
			break;
		case 2: //delete
			DeleteItem();
			break;
		case 3: //replace
			ReplaceItem();
			break;
		case 4: //search by filename.
			SearchById_SequenS();
			break;
		case 5: // display all the records in list on screen.
			DisplayAllItem();
			break;
		case 6: // make empty list.
			m_List.MakeEmpty();
			break;
		case 7: // load list data from a file.
			ReadDataFromFile();
			break;
		case 8: // save list data into a file.
			WriteDataToFile();
			break;
		case 9: // go to favicon menu
			faviconList.getCommand();
			break;
		case 10: // go to event menu
			eventList.getCommand();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl
			 << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add content on master list" << endl;
	cout << "\t   2 : Delete content on master list" << endl;
	cout << "\t   3 : Replace content by fileName" << endl;
	cout << "\t   4 : Search content by fileName" << endl;
	cout << "\t   5 : Print all on screen" << endl;
	cout << "\t   6 : Make empty list" << endl;
	cout << "\t   7 : Get master list from file" << endl;
	cout << "\t   8 : Put master list to file " << endl;
	cout << "\t   9 : Go to Favicon Menu " << endl;
	cout << "\t   10 : Go to Event Menu " << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl
			 << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// Add new record into list.
int Application::AddItem()
{
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (m_List.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	Content item;

	item.setRecordFromKB();
	m_List.Add(item);

	return 1;
}

//filename���� item�� ã�� ����Ѵ�.
int Application::SearchById_SequenS()
{
	Content item;
	item.SetNameFromKB(); //name�Է¹޴´�.

	if (m_List.Retrieve_SeqS(item)) //0�� �ƴϸ�(ã����)
	{
		cout << "<============ Item FOUND !==========>" << endl;
		item.displayRecord(); //�ش� item�� ����Ѵ�.
		cout << "<====================================>" << endl;
		return 1; //����(1)�� ����
	}
	cout << "<======== ITEM Not Found!==========>" << endl;
	return 0; //����(0)�� ����
}

//id�� item�� ã�Ƽ� �����Ѵ�.
int Application::DeleteItem()
{
	int pre = m_List.GetLength(); //���� item������ �޾ƿ´�.
	Content item;
	item.SetNameFromKB();

	m_List.Delete(item);

	if (pre > m_List.GetLength()) //���� item�������� ���� item������ �������� ���ż���
	{
		cout << "<========DELETE SUCCESS !===========>" << endl;
		return 1;
	}

	cout << "<========DELETE FAIL !=======>" << endl;
	return 0;
}

//�ش� id�� item�� �����Ѵ�.
int Application::ReplaceItem()
{
	Content item;
	item.setRecordFromKB(); //Ű����κ��� ������ �Է¹���

	m_List.Replace(item); //�ش� item�� id�� ��ġ�ϴ� ���� ã�� �ٲ۴�.
	//this->DisplayAllItem();
	return 0;
}

// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	Content data;

	cout << "\n\tCurrent list" << endl;

	// list�� ��� �����͸� ȭ�鿡 ���
	m_List.ResetList();
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.displayRecord();
		curIndex = m_List.GetNextItem(data);
	}
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(string fileName)
{
	m_InFile.open(fileName); // file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_InFile)
		return 0;
	else
		return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(string fileName)
{
	m_OutFile.open(fileName); // file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_OutFile)
		return 0;
	else
		return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	Content data; // �б�� �ӽ� ����

	string filename;
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!m_InFile.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close(); // file close

	// ���� list ���
	//DisplayAllItem();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	Content data; // ����� �ӽ� ����

	string filename;
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	m_List.ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close(); // file close

	return 1;
}

// ����Ʈ���� �ش� id�� ���� item�� ã�´�.
int Application::SearchByID_BinaryS()
{
	Content item;

	item.SetNameFromKB();							 //id�� �Է¹޴´�
	if (m_List.Retrieve_BinaryS(item)) //����Ž���� �����ߴٸ�
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		item.displayRecord();
		cout << "<====================================>" << endl;
		return 1; //����(1)�� ��ȯ
	}
	//�߰� ���ҽ�
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0; //����(0)�� ��ȯ
}
