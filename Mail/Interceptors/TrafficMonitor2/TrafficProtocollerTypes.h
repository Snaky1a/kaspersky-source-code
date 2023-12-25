/*
*/

#if !defined(__KL_TRAFFICPROTOCOLLERTYPES_H)
#define __KL_TRAFFICPROTOCOLLERTYPES_H

namespace TrafficProtocoller
{
	enum data_source_t
	{
		dsUnknown = 0,
		dsClient,					//!< �������� ������ - ������
		dsServer					//!< �������� ������ - ������
	};

	enum detect_code_t
	{
		dcProtocolUnknown = 0,			//!< �������� �� �������
		dcProtocolDetected,				//!< �������� �������
		dcNeedMoreInfo,					//!< �� ���������� ������ ��� ��������� ���������
		dcDataDetected,					//!< ���������� ������� �������� ������
		dcProtocolLikeDetected,			//!< ���� ���������� �� ������������ ���������
		dc_last,
	};

	inline const char *GetDataSourceStr(data_source_t ds)
	{
		switch(ds)
		{
		case dsClient:
			return "dsClient";
		case dsServer:
			return "dsServer";
		}
		return "dsUnknown";
	}
}

#define npPROTOCOL_TYPE ((tSTRING)("PROTOCOL_TYPE")) // ��� ��������� (����� ������ ��� ������� �����)


#endif  // !defined(__KL_TRAFFICPROTOCOLLERTYPES_H)
