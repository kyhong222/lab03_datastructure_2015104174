#include "Favicon.h"

int Favicon::AddItem()
{
	Content temp;
	temp.SetNameFromKB();

	if (MasterList->Retrieve_BinaryS(temp))
	{
		temp = temp.getRecordForLink();
		MCList.Add(temp);
		MCLength++;
		return 1;
	}
	else
	{
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

int Favicon::DeleteItem()
{
	Content temp;
	temp.SetNameFromKB();

	if (MCList.Delete(temp))
	{
		MCLength--;
		return 1;
	}
	else
	{
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

int Favicon::RetriveItem()
{
	Content temp;
	temp.SetNameFromKB();
	if (MCList.Retrieve_BinaryS(temp))
	{
		temp.displayRecord();
		return 1;
	}
	else
	{
		cout << "\tThere is no item like that" << endl;
		return 0;
	}
}

void Favicon::DisplayItems()
{
	Content temp;
	cout << endl;
	cout << "\n\tMC list in event(Link)" << endl;

	// list�� ��� �����͸� ȭ�鿡 ���
	MCList.ResetList();
	int length = MCLength;
	int curIndex = MCList.GetNextItem(temp);
	while (curIndex < length && curIndex != -1)
	{
		temp.displayRecordForLink();
		curIndex = MCList.GetNextItem(temp);
	}
}

void Favicon::DisplayItemsDetailed()
{
	Content temp;
	cout << endl;
	cout << "\n\tMC list in event" << endl;

	// list�� ��� �����͸� ȭ�鿡 ���
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

void Favicon::rearrange()
{
	int command;
	cout << "\tarrange to(1.name 2.create time 3.content type) : ";
	cin >> command;
	if (command == 1)
	{
		this->DisplayItems();
	}
	else if (command == 2)
	{
		Content newArray[MAXSIZE];

		Content temp;
		MCList.ResetList();
		for (int i = 0; i < MCLength; i++)
		{
			MCList.GetNextItem(temp);
			newArray[i] = temp;
		}

		for (int i = 0; i < MCLength; i++)
		{
			for (int j = 0; j < MCLength - 1 - i; j++)
			{
				if (newArray[j].CompareByCreateAt(newArray[j + 1]))
				{
					temp = newArray[j];
					newArray[j] = newArray[j + 1];
					newArray[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < MCLength; i++)
		{
			newArray[i].displayRecordForLink();
		}
	}
	else if (command == 3)
	{
		Content newArray[MAXSIZE];

		Content temp;
		MCList.ResetList();
		for (int i = 0; i < MCLength; i++)
		{
			MCList.GetNextItem(temp);
			newArray[i] = temp;
		}

		for (int i = 0; i < MCLength; i++)
		{
			for (int j = 0; j < MCLength - 1 - i; j++)
			{
				if (newArray[j].CompareByType(newArray[j + 1]))
				{
					temp = newArray[j];
					newArray[j] = newArray[j + 1];
					newArray[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < MCLength; i++)
		{
			newArray[i].displayRecordForLink();
		}
	}
	else
	{
		cout << "\tinvalid command" << endl;
	}
	return;
}

void Favicon::getCommand()
{
	while (1)
	{
		cout << endl
				 << endl;
		cout << "\t---ID -- Command ----- " << endl;
		cout << "\t   1 : Add content on favicon list" << endl;
		cout << "\t   2 : Delete content on favicon list" << endl;
		cout << "\t   3 : Retrive content by fileName" << endl;
		cout << "\t   4 : Display item on favicon list" << endl;
		cout << "\t   5 : Display item on favicon list detailed" << endl;
		cout << "\t   6 : Make empty favicon list" << endl;
		cout << "\t   7 : Get favicon list from file" << endl;
		cout << "\t   8 : Put favicon list to file " << endl;
		cout << "\t   9 : Rearrange favicon list" << endl;
		cout << "\t   0 : Quit" << endl;

		cout << endl
				 << "\t Choose a Command--> ";

		int m_Command;
		cin >> m_Command;

		switch (m_Command)
		{
		case 1: // read a record and add to list.
			AddItem();
			break;
		case 2: //delete
			DeleteItem();
			break;
		case 3: //replace
			RetriveItem();
			break;
		case 4: //search by filename.
			DisplayItems();
			break;
		case 5: // display all the records in list on screen.
			DisplayItemsDetailed();
			break;
		case 6: // make empty list.
			MCList.MakeEmpty();
			break;
		case 7: // load list data from a file.
			ReadDataFromFile();
			break;
		case 8: // save list data into a file.
			WriteDataToFile();
			break;
		case 9:
			rearrange();
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
int Favicon::OpenInFile(string fileName)
{
	m_InFile.open(fileName); // file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_InFile)
		return 0;
	else
		return 1;
}

// Open a file by file descriptor as an output file.
int Favicon::OpenOutFile(string fileName)
{
	m_OutFile.open(fileName); // file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_OutFile)
		return 0;
	else
		return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Favicon::ReadDataFromFile()
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
		data.ReadDataFromFileForLink(m_InFile);
		MCList.Add(data);
	}

	MCLength = MCList.GetLength();
	m_InFile.close(); // file close

	// ���� list ���
	//DisplayAllItem();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Favicon::WriteDataToFile()
{
	Content data; // ����� �ӽ� ����

	string filename;
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	MCList.ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
	int length = MCLength;
	int curIndex = MCList.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFileForLink(m_OutFile);
		curIndex = MCList.GetNextItem(data);
	}

	m_OutFile.close(); // file close

	return 1;
}