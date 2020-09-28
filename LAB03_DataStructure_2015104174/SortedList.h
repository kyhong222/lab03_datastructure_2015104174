#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Content.h"

#define MAXSIZE 10

/**
*	array based simple unsorted list.
*/
template <typename Content>
class SortedList
{
public:
	/**
	*	default constructor.
	*/
	SortedList()
	{
		m_Length = 0;
		m_CurPointer = 0;
	}

	/**
	*	destructor.
	*/
	~SortedList() {}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(Content data);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(Content &data);

	/**
	*	@brief	item�� ã�Ƽ� �ش� item�� ��ȯ�Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ������ ã�� item�� data�� �Էµȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��. �߰��� item�� ���ϵȴ�.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int Retrieve_SeqS(Content &data);

	/**
	*	@brief	id�� ��ġ�ϴ� item�� ã�Ƽ� �ش� item�� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ���� �ش� item�� ���ŵȴ�.
	*	@param	data	�����ϰ��� �ϴ� id�� �Էµ� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Delete(Content data);

	/**
	*	@brief	id�� ��ġ�ϴ� list�� item�� ã�Ƽ� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� �Ѱܹ��� item�� �������� ����ȴ�.
	*	@param	data	��ü�ϰ��� �ϴ� id�� ���ڵ带 ���� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Replace(Content data);

	/**
	*	@brief	����Ž���� ���� id�� ��ġ�ϴ� list�� item�� ã�Ƽ� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� ã�Ƽ� data�� ��ȯ�ȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int Retrieve_BinaryS(Content &data);

private:
	Content m_Array[MAXSIZE]; ///< list array.
	int m_Length;							///< number of elements in list.
	int m_CurPointer;					///< iterator pointer.
};

// Make list empty.
template <typename Content>
void SortedList<Content>::MakeEmpty()
{
	m_Length = 0;
}

// Get a number of records in current list.
template <typename Content>
int SortedList<Content>::GetLength()
{
	return m_Length;
}

// Check capacity of list is full.
template <typename Content>
bool SortedList<Content>::IsFull()
{
	if (m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}

// search item by using primary key

template <typename Content>
int SortedList<Content>::Add(Content inData)
{
	// List�� �� ���ִ� ��� 0�� ����
	if (IsFull())
	{
		/*MAXSIZE += 5;
		Content* temp = new Content[MAXSIZE];
		for (int i = 0; i < m_Length; i++) temp[i] = m_Array[i];
		delete[] m_Array;
		m_Array = temp;*/
		return 0;
	}
	if (m_Length == 0)
	{ // List�� ��� ������ �� �A�� �߰�, length++, 1�� ����
		m_Array[m_Length++] = inData;
		return 1;
	}
	// �� �׸��� ���� ��ġ iPos�� �˻�. ���� �����ϰų� ���� item�� inData���� ũ�� ����
	int iPos = 0;
	bool found = false;
	Content curItem;
	ResetList();
	iPos = GetNextItem(curItem); // ���� �����ϸ� -1�� ����
	while (iPos > -1 && !found)
	{
		switch (curItem.Compare(inData))
		{
		case EQUAL:
			//	cout << " %%% same item exist in the list %%%\n";
			return 0;
		case GREATER:
			found = true;
			break;
		case LESS:
			iPos = GetNextItem(curItem);
			break;
		}
	}
	//���� �����ϸ� iPos==-1. �̰�� �� �ڿ� �߰�
	if (iPos == -1)
	{
		// �ε��� length�� �߰�, length++, 1����
		m_Array[m_Length++] = inData;
		return 1;
	}
	// iPost<length�̸� iPos���� length-1 ������ ��� �׸��� �ڷ� �� ĭ�� �̵�
	for (int i = m_Length; i > iPos; i--)
		m_Array[i] = m_Array[i - 1];
	// iPos�� �߰�,
	m_Array[iPos] = inData;
	// Length++, 1����
	m_Length++;
	return 1;
}

// Initialize list iterator.
template <typename Content>
void SortedList<Content>::ResetList()
{
	m_CurPointer = -1;
}

// move list iterator to the next item in list and get that item.
template <typename Content>
int SortedList<Content>::GetNextItem(Content &data)
{
	m_CurPointer++;								// list pointer ����
	if (m_CurPointer == m_Length) // end of list�̸� -1�� ����
		return -1;
	data = m_Array[m_CurPointer]; // ���� list pointer�� ���ڵ带 ����

	return m_CurPointer;
}

//Primary key�� ��ġ�ϴ� item�� ã�Ƽ� ��ȯ��
template <typename Content>
int SortedList<Content>::Retrieve_SeqS(Content &data)
{
	Content CurItem;

	ResetList();										//iterator �ʱ�ȭ
	GetNextItem(CurItem);						//ù������ ������
	while (m_CurPointer < m_Length) //ó������ ������
	{
		switch (CurItem.Compare(data)) //�Է� �����۰� ���� �������� ��
		{
		case EQUAL:				//��ġ�ϸ�
			data = CurItem; //data�� ���� �������� ��ȯ
			return 1;				//����(1)�� ����
			break;
		case GREATER: //���� �������� Primary key�� �� ũ��(���ĵ������Ƿ� �������� ã�°� ����)
			return 0;		//����(0)�� ����
			break;
		default:								//���� �������� Primary key�� �� ������
			GetNextItem(CurItem); //���� �������� �����´�.(��� Ž��)
			break;
		}
	}
	return 0; //���н�0
}

//Primary key�� ��ġ�ϴ� item�� ã�Ƽ� ������
template <typename Content>
int SortedList<Content>::Delete(Content data)
{
	if (Retrieve_SeqS(data)) //Primary key�� ��ġ�ϴ� item�� �߰��Ѵٸ�(1)
	{
		for (int i = m_CurPointer; i < m_Length; i++) //���� �����ͺ��� �Էµ� �迭 ������ �ݺ�
			m_Array[i] = m_Array[i + 1];								//�迭 �ڿ��� ������ �ϳ��� ����
		m_Length--;																		//������ ������ �ϳ� ����
		return 1;																			//����(1)�� ����
	}
	return 0; //Primary key��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

//Primary key�� ��ġ�ϴ� item�� ������ ��ü��Ŵ
template <typename Content>
int SortedList<Content>::Replace(Content data)
{
	Content tmp(data); //�Է¹��� item�� ���

	if (Retrieve_SeqS(data)) //��ġ�ϴ� �������� ã�� ���
	{
		m_Array[m_CurPointer] = tmp; //�迭���� ���������Ͱ� ����Ű�� ���� ����ߴ� ���������� ��ü��Ŵ
		return 1;										 //����(1)�� ����
	}
	return 0; //Primary key�� ��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

//Primary key�� ��ġ�ϴ� item�� ����Ž������ �˻��ؼ� ��ȯ�Ѵ�.
template <typename Content>
int SortedList<Content>::Retrieve_BinaryS(Content &data)
{
	if (m_Length == 0) //���� �迭�� ����ٸ�
		return 0;				 //����(0)�� ����
	int low = 0;
	int high = m_Length - 1;
	int mid;
	while (1)
	{
		mid = (low + high) / 2;
		switch (m_Array[mid].Compare(data))
		{
		case EQUAL:						 //���� �����۰� �Է� �������� Primary key�� ��ġ�Ѵٸ�
			data = m_Array[mid]; //data�� �߰��� ���� ����
			return 1;						 //����(1)�� ����
			break;
		case GREATER:			//���� �������� Primary key�� �Է� �������� Primary key���� ũ�ٸ�
			if (mid <= low) //ó�� �迭�� ������ �������
				return 0;			//����(0)�� ����
			//currentPos /= 2;	//�� ������ �ε����� ���ݷ� �̵�
			high = mid - 1;
			break;
		case LESS:				 //���� �������� Primary key�� �Է� �������� Primary key���� �۴ٸ�
			if (mid >= high) //������ �迭�� ������ ū���
				return 0;			 //����(0)�� ����
			//mid = (mid + m_Length) / 2;	//�� ū�� �ε����� �������� �̵�
			low = mid + 1;
			break;
		}
	}
	return 0; //ȣ��� �� ���� ����(WARNING ������)
}
