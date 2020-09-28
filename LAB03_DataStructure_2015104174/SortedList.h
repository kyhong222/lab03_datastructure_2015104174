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
	int GetNextItem(Content& data);

	/**
	*	@brief	item을 찾아서 해당 item을 반환한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	list 내에서 찾은 item이 data에 입력된다.
	*	@param	data	찾고자 하는 id가 입력된 ItemType값. 발견한 item이 리턴된다.
	*	@return	성공(발견)시 1, 실패시 0을 리턴한다.
	*/
	int Retrieve_SeqS(Content& data);

	/**
	*	@brief	id가 일치하는 item을 찾아서 해당 item을 제거한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	list 내에 해당 item이 제거된다.
	*	@param	data	제거하고자 하는 id가 입력된 ItemType값.
	*	@return	성공시 1, 실패시 0을 리턴한다.
	*/
	int Delete(Content data);

	/**
	*	@brief	id가 일치하는 list내 item을 찾아서 변경한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	배열 내에 넘겨받은 item과 id가 일치하는 값이 넘겨받은 item의 내용으로 변경된다.
	*	@param	data	교체하고자 하는 id와 레코드를 가진 ItemType값.
	*	@return	성공시 1, 실패시 0을 리턴한다.
	*/
	int Replace(Content data);

	/**
	*	@brief	이진탐색을 통해 id가 일치하는 list내 item을 찾아서 반환한다.
	*	@pre	없음.
	*	@post	배열 내에 넘겨받은 item과 id가 일치하는 값을 찾아서 data로 반환된다.
	*	@param	data	찾고자 하는 id가 입력된 ItemType값.
	*	@return	성공(발견)시 1, 실패시 0을 리턴한다.
	*/
	int Retrieve_BinaryS(Content& data);

private:
	Content m_Array[MAXSIZE];  ///< list array.
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
};

// Make list empty.
template<typename Content>
void SortedList<Content>::MakeEmpty()
{
	m_Length = 0;
}


// Get a number of records in current list.
template<typename Content>
int SortedList<Content>::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
template<typename Content>
bool SortedList<Content>::IsFull()
{
	if (m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}



// search item by using primary key

template<typename Content>
int SortedList<Content>::Add(Content inData)
{
	// List가 꽉 차있는 경우 0을 리턴
	if (IsFull())
	{
		/*MAXSIZE += 5;
		Content* temp = new Content[MAXSIZE];
		for (int i = 0; i < m_Length; i++) temp[i] = m_Array[i];
		delete[] m_Array;
		m_Array = temp;*/
		return 0;
	}
	if (m_Length == 0) {    	// List가 비어 있으면 맨 얖에 추가, length++, 1을 리턴 
		m_Array[m_Length++] = inData;
		return 1;
	}
	// 새 항목의 삽입 위치 iPos를 검색. 끝에 도달하거나 현재 item이 inData보다 크면 종료
	int iPos = 0;
	bool found = false;
	Content curItem;
	ResetList();
	iPos = GetNextItem(curItem);  // 끝에 도달하면 -1을 리턴
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
	//끝에 도달하면 iPos==-1. 이경우 맨 뒤에 추가
	if (iPos == -1) {
		// 인덱스 length에 추가, length++, 1리턴
		m_Array[m_Length++] = inData;
		return 1;
	}
	// iPost<length이면 iPos부터 length-1 사이의 모든 항목을 뒤로 한 칸씩 이동
	for (int i = m_Length; i > iPos; i--)
		m_Array[i] = m_Array[i - 1];
	// iPos에 추가,
	m_Array[iPos] = inData;
	// Length++, 1리턴
	m_Length++;
	return 1;
}



// Initialize list iterator.
template<typename Content>
void SortedList<Content>::ResetList()
{
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
template<typename Content>
int SortedList<Content>::GetNextItem(Content& data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer == m_Length)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}




//Primary key가 일치하는 item을 찾아서 반환함
template<typename Content>
int SortedList<Content>::Retrieve_SeqS(Content& data)
{
	Content CurItem;

	ResetList();	//iterator 초기화
	GetNextItem(CurItem);	//첫아이템 가져옴
	while (m_CurPointer < m_Length)	//처음부터 끝까지
	{
		switch (CurItem.Compare(data))	//입력 아이템과 현재 아이템을 비교
		{
		case EQUAL:	//일치하면
			data = CurItem;	//data에 현재 아이템을 반환
			return 1;	//성공(1)을 리턴
			break;
		case GREATER:	//현재 아이템의 Primary key가 더 크면(정렬되있으므로 나머지에 찾는게 없다)
			return 0;	//실패(0)을 리턴
			break;
		default:	//현재 아이템의 Primary key가 더 작으면
			GetNextItem(CurItem);	//다음 아이템을 가져온다.(계속 탐색)
			break;
		}
	}
	return 0; //실패시0
}



//Primary key가 일치하는 item을 찾아서 제거함
template<typename Content>
int SortedList<Content>::Delete(Content data)
{
	if (Retrieve_SeqS(data))	//Primary key가 일치하는 item을 발견한다면(1)
	{
		for (int i = m_CurPointer; i < m_Length; i++)	//현재 포인터부터 입력된 배열 끝까지 반복
			m_Array[i] = m_Array[i + 1];	//배열 뒤에걸 앞으로 하나씩 땡김
		m_Length--;	//아이템 개수를 하나 줄임
		return 1;	//성공(1)을 리턴
	}
	return 0;	//Primary key일치하는 item을 찾지 못한다면 실패(0)을 리턴
}

//Primary key가 일치하는 item의 내용을 교체시킴
template<typename Content>
int SortedList<Content>::Replace(Content data)
{
	Content tmp(data);	//입력받은 item을 백업

	if (Retrieve_SeqS(data))	//일치하는 아이템을 찾은 경우
	{
		m_Array[m_CurPointer] = tmp;	//배열에서 현재포인터가 가르키는 것을 백업했던 아이템으로 교체시킴
		return 1;	//성공(1)을 리턴
	}
	return 0;	//Primary key와 일치하는 item을 찾지 못한다면 실패(0)을 리턴
}

//Primary key가 일치하는 item을 이진탐색으로 검색해서 반환한다.
template<typename Content>
int SortedList<Content>::Retrieve_BinaryS(Content& data)
{
	if (m_Length == 0)	//만약 배열이 비었다면
		return 0;	//실패(0)을 리턴
	int low = 0;
	int high = m_Length - 1;
	int mid;
	while (1)
	{
		mid = (low + high) / 2;
		switch (m_Array[mid].Compare(data))
		{
		case EQUAL:	//현재 아이템과 입력 아이템의 Primary key가 일치한다면
			data = m_Array[mid];	//data에 발견한 값을 리턴
			return 1;	//성공(1)을 리턴
			break;
		case GREATER:	//현재 아이템의 Primary key가 입력 아이템의 Primary key보다 크다면
			if (mid <= low)	//처음 배열의 값보다 작은경우
				return 0;	//실패(0)을 리턴
			//currentPos /= 2;	//더 작은쪽 인덱스의 절반로 이동
			high = mid - 1;
			break;
		case LESS:	//현재 아이템의 Primary key가 입력 아이템의 Primary key보다 작다면
			if (mid >= high)	//마지막 배열의 값보다 큰경우
				return 0;	//실패(0)을 리턴
			//mid = (mid + m_Length) / 2;	//더 큰쪽 인덱스의 절반으로 이동
			low = mid + 1;
			break;
		}
	}
	return 0;	//호출될 일 없는 리턴(WARNING 방지용)
}
