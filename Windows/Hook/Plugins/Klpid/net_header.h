#define ETH_HEADER_LENGTH	0xE

#define ETH_P_LOOP	0x0060		/* Ethernet Loopback packet	*/
#define ETH_P_ECHO	0x0200		/* Ethernet Echo packet		*/
#define ETH_P_PUP	0x0400		/* Xerox PUP packet		*/
#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/
#define ETH_P_X25	0x0805		/* CCITT X.25			*/
#define ETH_P_ARP	0x0806		/* Address Resolution packet	*/
#define	ETH_P_BPQ	0x08FF		/* G8BPQ AX.25 Ethernet Packet	[ NOT AN OFFICIALLY REGISTERED ID ] */
#define ETH_P_DEC       0x6000          /* DEC Assigned proto           */
#define ETH_P_DNA_DL    0x6001          /* DEC DNA Dump/Load            */
#define ETH_P_DNA_RC    0x6002          /* DEC DNA Remote Console       */
#define ETH_P_DNA_RT    0x6003          /* DEC DNA Routing              */
#define ETH_P_LAT       0x6004          /* DEC LAT                      */
#define ETH_P_DIAG      0x6005          /* DEC Diagnostics              */
#define ETH_P_CUST      0x6006          /* DEC Customer use             */
#define ETH_P_SCA       0x6007          /* DEC Systems Comms Arch       */
#define ETH_P_RARP      0x8035		/* Reverse Addr Res packet	*/
#define ETH_P_ATALK	0x809B		/* Appletalk DDP		*/
#define ETH_P_AARP	0x80F3		/* Appletalk AARP		*/
#define ETH_P_IPX	0x8137		/* IPX over DIX			*/
#define ETH_P_IPV6	0x86DD		/* IPv6 over bluebook		*/
#define ETH_P_PPP_DISC	0x8863		/* PPPoE discovery messages     */
#define ETH_P_PPP_SES	0x8864		/* PPPoE session messages	*/
#define ETH_P_ATMMPOA	0x884c		/* MultiProtocol Over ATM	*/
#define ETH_P_ATMFATE	0x8884		/* Frame-based ATM Transport*/

#pragma pack(1)
typedef struct _ETH_HEADER {
	UCHAR	dstMac[6];	/* destination eth addr	*/
	UCHAR	srcMac[6];	/* source ether addr	*/
	USHORT	Type;		/* packet type ID field	*/
} ETH_HEADER, *PETH_HEADER;

typedef struct	_IP_HEADER {	
	UCHAR	Ihl		: 4;
	UCHAR	Version : 4;
	
	UCHAR	TypeOfService;
	USHORT	TotalLength;
	USHORT  Identification;
	USHORT	Flg_FragOffs;
	UCHAR	TimeToLive;
	UCHAR	Protocol;
	USHORT	HeaderChecksum;
	ULONG	srcIP;
	ULONG	dstIP;	
} IP_HEADER, *PIP_HEADER;

typedef struct _TCP_HEADER {
	USHORT	srcPort;
	USHORT	dstPort;
	ULONG	SeqNumber;
	ULONG	AckNumber;

	USHORT	res1:4;
	USHORT	DataOffset:4;
	USHORT	fin:1;
	USHORT	syn:1;
	USHORT	rst:1;
	USHORT	psh:1;
	USHORT	ack:1;
	USHORT	urg:1;
	USHORT	ece:1;
	USHORT	cwr:1;
	
	USHORT	Window;
	USHORT	CheckSum;
	USHORT	UrgPointer;
} TCP_HEADER, *PTCP_HEADER;

typedef struct _UDP_HEADER {
	USHORT	srcPort;
	USHORT	dstPort;
	USHORT	Length;
	USHORT	CheckSum;
} UDP_HEADER, *PUDP_HEADER;


#define SESSION_REQUEST         0x81
#define SESSION_MESSAGE         0x00

#define SMB_NEGOTIATE_PROTOCOL  0x72
#define SMB_SESSION_SETUP_ANDX  0x73
#define SMB_TREE_CONNECT_ANDX   0x75
#define SMB_COM_TRANSACTION     0x25

typedef struct _SMB_HEADER
{
	UCHAR	server_component[4];
	UCHAR	command;
	UCHAR	error_class;
	UCHAR	reserved1;
	USHORT	error_code;
	UCHAR	flags;
	USHORT	flags2;
	UCHAR	reserved2[12];
	USHORT	tree_id;
	USHORT	proc_id;
	USHORT	user_id;
	USHORT	mpex_id;
} SMB_HEADER, *PSMB_HEADER;

typedef struct _TRANSACTION_REQUEST
{
	/* wct: word count */
	UCHAR	wct;
	USHORT	total_param_cnt;
	USHORT	total_data_cnt;
	USHORT	max_param_cnt;
	USHORT	max_data_cnt;
	UCHAR	max_setup_cnt;
	UCHAR	reserved1;
	USHORT	flags;
	ULONG	timeout;
	USHORT	reserved2;
	USHORT	param_cnt;
	USHORT	param_offset;
	USHORT	data_cnt;
	USHORT	data_offset;
	UCHAR	setup_count;
	UCHAR	reserved3;
	/* bcc: byte count */
	USHORT bcc;
} TRANSACTION_REQUEST, *PTRANSACTION_REQUEST;

typedef struct _SMB_PARAMETERS
{
	USHORT	function_code;
	UCHAR	param_descriptor[6];
	UCHAR	return_descriptor[7];
	USHORT	detail_level;
	USHORT	recv_buffer_len;
} SMB_PARAMETERS, *PSMB_PARAMETERS;


typedef struct NBT_PACKET 
{
	UCHAR	type;
	UCHAR	flags;
	USHORT	length;
	UCHAR	called[34];
	UCHAR	calling[34];
} NBT_PACKET, *PNBT_PACKET;

#define ICMP_ECHOREPLY		0	/* Echo Reply			*/
#define ICMP_DEST_UNREACH	3	/* Destination Unreachable	*/
#define ICMP_SOURCE_QUENCH	4	/* Source Quench		*/
#define ICMP_REDIRECT		5	/* Redirect (change route)	*/
#define ICMP_ECHO		8	/* Echo Request			*/
#define ICMP_TIME_EXCEEDED	11	/* Time Exceeded		*/
#define ICMP_PARAMETERPROB	12	/* Parameter Problem		*/
#define ICMP_TIMESTAMP		13	/* Timestamp Request		*/
#define ICMP_TIMESTAMPREPLY	14	/* Timestamp Reply		*/
#define ICMP_INFO_REQUEST	15	/* Information Request		*/
#define ICMP_INFO_REPLY		16	/* Information Reply		*/
#define ICMP_ADDRESS		17	/* Address Mask Request		*/
#define ICMP_ADDRESSREPLY	18	/* Address Mask Reply		*/

typedef struct _ICMP_HEADER {
	UCHAR	Type;
	UCHAR	Code;
	USHORT	CheckSum;
	union 
	{
		struct 
		{
			USHORT	Id;
			USHORT	Sequence;
		} echo;
		struct
		{
			ULONG	Address;
			ULONG	enh_hdr;
		} redirect;


	}	Params;	
} ICMP_HEADER, *PICMP_HEADER;
#pragma pack()
