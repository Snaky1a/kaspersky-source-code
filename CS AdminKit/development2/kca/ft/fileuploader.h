/*!
 * (C) 2007 "Kaspersky Lab"
 *
 * \file fileuploader.h
 * \author ����� �����������
 * \date 2007
 * \brief ��������� ������ ������� ����� � UA
 * 
 */

#ifndef KLFT_FILEUPLOADER_H
#define KLFT_FILEUPLOADER_H

#include <std/base/klbase.h>

#include <transport/tr/transport.h>

#include <kca/ft/foldersync.h>

namespace KLFT {

	class KLSTD_NOVTABLE FileUploader
	{			
	public:

		void GetSyncFolderFile( const KLTRAP::Transport::ConnectionFullName &remoteConnection, 
			const KLTRAP::Transport::ConnectionFullName &fromConnection, 
			KLFT::FolderSync *pFolderSync,
			const std::wstring &fileName, 
			const std::wstring &operationId );

	};

} // end namespace KLFT

#endif // !defined(KLFT_FILEUPLOADER_H)