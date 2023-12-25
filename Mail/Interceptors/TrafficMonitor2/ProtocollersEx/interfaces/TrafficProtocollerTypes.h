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
		dc_last,
	};
}

#endif  // !defined(__KL_TRAFFICPROTOCOLLERTYPES_H)
