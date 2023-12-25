/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file SubscriptionIterator.h
 * \author ����� �����������
 * \date 2002
 * \brief ��������� ������ ��������� ��������
 * 
 */

#ifndef KLEV_SUBSCIRPTION_ITERATOR_H
#define KLEV_SUBSCIRPTION_ITERATOR_H

namespace KLEV {

	class Subscription;

	class SubscriptionIterator
	{
		public:

			virtual ~SubscriptionIterator() {}
			
			/*!
				\brief ������������� �������� �� ������ ������
			*/
			virtual void Reset() = 0;

			/*!
				\brief ���������� ������� �������� � ��������� �������� �� ��������� 
					� ������ ��������
			*/
			virtual Subscription *Next() = 0;

	};

} // namespace KLEV


#endif // KLEV_SUBSCIRPTION_ITERATOR_H
