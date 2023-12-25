/*-----------------02.05.99 09:31-------------------
 * Project Prague                                 *
 * Subproject Object IDentifications              *
 * Author Andrew Andy Petrovitch                  *
 * Copyright (c) Kaspersky Lab                    *
 * Purpose Prague API                             *
 *                                                *
--------------------------------------------------*/

#ifndef __PR_OID_H
#define __PR_OID_H

// Object origin type constants 
// pgOBJECT_ORIGIN property

#define OID_ANY                        ((tORIG_ID)(-1))
#define OID_GENERIC_IO                 ((tORIG_ID)(0))
#define OID_PASSWORDED_EXE             ((tORIG_ID)(0x1000))         // fake ����, �������������� ��� Susupicion
#define OID_COMMAND_RELOAD_BASE        ((tORIG_ID)(0x2000))
#define OID_LOGICAL_DRIVE              ((tORIG_ID)(0x2001))			// ���������� ���� (removable, fixed...). ��������� � WindDiskIO.ppl. ���������� IO � ObjPtr. ������� ����� ���� ��������, ��������
#define OID_PHYSICAL_DISK              ((tORIG_ID)(0x2002))			// ���������� ���� (removable, fixed...). ��������� � WindDiskIO.ppl. ���������� IO � ObjPtr. ������� ����� ���� ��������, ��������
#define OID_AVP3_DOS_MEMORY            ((tORIG_ID)(0x3001))
#define OID_AVP3_BOOT                  ((tORIG_ID)(0x3002))
#define OID_AVP3_MBR                   ((tORIG_ID)(0x3003))
#define OID_MEMORY_PROCESS             ((tORIG_ID)(0x5001))			// ������ ���������. ��������� � MemScan.ppl. ���������� OS, ObjPtr, IO. ����� ���� ��������, ��������, �������
#define OID_MEMORY_PROCESS_MODULE      ((tORIG_ID)(0x5002))			// ������ ��������� � ������. ��������� � MemModSc.ppl. ���������� OS, ObjPtr, IO. ����� ���� ��������, ��������, �������
#define OID_SCRIPT_TEXT                ((tORIG_ID)(0x5004))			// ����� ������� (��������, ������� �� HTML)
#define OID_SCRIPT_VBS                 ((tORIG_ID)(0x5005))			// �������� ������������� ������� ����� ����������� ����� VBScript
#define OID_SCRIPT_VBSE                ((tORIG_ID)(0x5006))			// ����������� �������� ������������� ������� ����� ����������� ����� VBScript 
#define OID_SCRIPT_VBSH                ((tORIG_ID)(0x5007))			// ����������� ������������� ������� ����� ����������� ����� VBScript + ��������
#define OID_SCRIPT_JS                  ((tORIG_ID)(0x5008))			// �������� ������������� ������� ����� ����������� ����� JavaScript
#define OID_SCRIPT_PACKED_TEXT         ((tORIG_ID)(0x5009))			// �������������� ��� ������������ ����� (lowercase, crlf -> lf, � �.�.)
#define OID_SCRIPT_BAT                 ((tORIG_ID)(0x500A))			// �������������� ��� ������������ ����� BAT-����� (������ ����� ����������, � ����� ��������� �����������)
#define OID_SCRIPT_MIRC                ((tORIG_ID)(0x500B))			// �������������� ��� ������������ ���� MIRC/PIRCH ������� (������ ��� ����������� � INI-�����, ��������� ������� ������� � ������� ������)
#define OID_MAIL_MSG_REF               ((tORIG_ID)(0x6000))			// �������� ���������, ������������ � ���� ������ ����� Outlook(pst-����). ��������� ��� �������� �� ��� ������ ��������� �������.
#define OID_MAIL_MSG_MIME              ((tORIG_ID)(0x6001))			// �������� ��������� � MIME �������.
#define OID_MAIL_MSG_BODY              ((tORIG_ID)(0x6002))			// ����� ����(plain-body, rich-body, html-body) ��������� ��������� (������).
#define OID_MAIL_MSG_ATTACH            ((tORIG_ID)(0x6003))			// ����� ��������(attachment) ��������� ��������� (������).
#define OID_MIRA_GENERIC               ((tORIG_ID)(0x7000))			// OID_MIRA_EXE_xxx ����� - ��������� ��� ���������� ������������� ������� � �������� ������� (a-la MIRA) 
#define OID_MIRA_EXE                   ((tORIG_ID)(0x7001))			// ����������� �������� �����
#define OID_MIRA_EXE_VB_NATIVE         ((tORIG_ID)(0x7002))			// �������������� ������ �� ��������� ���������������� Visual Basic 5,6 Native Code
#define OID_MIRA_EXE_VB_PCODE          ((tORIG_ID)(0x7003))			// �������������� ������ �� ��������� ���������������� Visual Basic 5,6 PCode
#define OID_MIRA_EXE_DELPHI            ((tORIG_ID)(0x7004))			// �������������� ������ �� ��������� ���������������� Borland Delphi
#define OID_MIRA_EXE_BORLANDC_1994     ((tORIG_ID)(0x7005))			// �������������� ������ �� ��������� ���������������� Borland C++
#define OID_MIRA_EXE_MSVC              ((tORIG_ID)(0x7006))			// �������������� ������ �� ��������� ���������������� Microsoft Visual C
#define OID_REOPEN_DATA                ((tORIG_ID)(0x8000))         // ������ ��� ������� �������� �������
#define OID_QUARANTINED_OBJECT         ((tORIG_ID)(0x9000))         // ������ � ���������

#endif
