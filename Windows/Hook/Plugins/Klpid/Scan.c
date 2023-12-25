BOOLEAN	CheckTcpScan(PSTAT_ELEMENT	Element)
{
	ULONG	ListSize;
	ListSize = GetListCount(&Element->TcpPortList);
	// ���� ������ � ����� ������, ��� �������� � ���������� - ��� ������������ !
	if (ListSize >= AttackOptions.MaxOpenedTcpPorts)
		return TRUE;
	return FALSE;
}

BOOLEAN	CheckUdpScan(PSTAT_ELEMENT	Element)
{	
	ULONG	ListSize;
	ListSize = GetListCount(&Element->UdpPortList);
	// ���� ������ � ����� ������, ��� �������� � ���������� - ��� ������������ !
	if (ListSize >= AttackOptions.MaxOpenedUdpPorts)
		return TRUE;
	return FALSE;	
}
