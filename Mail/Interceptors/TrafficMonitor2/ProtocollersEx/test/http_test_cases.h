/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	http_test_cases.h
*		\brief	�������� ������ ��� http traffic monitor-�
*		
*		\author ��������� �������
*		\date	27.04.2005 11:44:51
*		
*		
*/		
#pragma once
#include <string>
///////////////////////////////////////////////////////////////////////////////
namespace http
{
bool test_chunk_parser(char const* begin, char const* end);
/**
 * \breif - ��������, ����������� ���������������� �������������� �������� ������ � �������
 *			�� �������������� ������ ��������� http
 *	begin - ������ ������
 *	end   - ����� ������
 *	\result - ���������� true ���� ���� ������� �������. � ������� ��������� ���������� �
 *			  ���������� ��������������.
 */
bool test_detect_traffic(char const* begin, char const* end);
/**
 * \brief - ���������� ��������, �� ���� ����������� ��������� ����� ������,
 *			������� �������� ����������� ��������� http, � ���������� ����������
 *			������ �������� ������ ������ �� ������ � �������� �� ���������� �
 *			����. ������ �� ������ ����������� ������� ������������� ������. 
 *	begin - ������ ������
 *	end   - ����� ������
 *  out   - ��� ��������� ����� ��� ����������� ������ http
 *	\result - ���������� true ���� ���� ������� ������� � � ����� �� �������� ������.
 */
bool test_full_packet_traffic(char const* begin, char const* end, std::string const& out);
/**
 * \breif - �������� �� �������� ����� � ���������� ��������� ����������.
 *			� ����� �������� ��������� test_full_packet_traffic
 */
bool test_async_full_packet_traffic(char const* begin, char const* end, std::string const& out);
//!
void xoring_file(std::string const& fname, std::string const& out);
//!
bool test_processor(char const* begin, char const* end);
//!
bool test_processor(std::list<std::string> const& l);
}//namespace http
///////////////////////////////////////////////////////////////////////////////