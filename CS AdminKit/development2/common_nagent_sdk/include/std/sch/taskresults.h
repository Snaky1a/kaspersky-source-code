/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskResults.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ����������� ���������� ������ 
 *        ��� ������� �������-�������������.
 *
 */


#ifndef KLSCH_TASKRESULTS_H
#define KLSCH_TASKRESULTS_H

namespace KLSCH {

/*!
 * \brief ���������� ���������� ������.
 *
 * ������ ����� ������������ ��� ��������� � �������� ���������� ���������� ������.
 * ��� ����������� ����� ����������� ����������� ���������� ������ 
 * ������ ������ ������������ ���� ����� �� ������ TaskResults.
 */ 
    

    class TaskResults 
	{ 

	public:
		virtual ~TaskResults() {};

		/*
			\brief ���������� ����� �������

			������ ����� ������ ���� ���������� � ������������ ������.

			\return ���������� ��������� �� ����� ��������� ������
		*/
		virtual TaskResults *Clone() = 0;

	};

}

#endif // KLSCH_TASKRESULTS_H
