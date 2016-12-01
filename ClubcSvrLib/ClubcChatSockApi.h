#ifndef _ClubcChatSockApi_h__
#define _ClubcChatSockApi_h__

#ifdef _CLUBCHATSOCK_DLL
#define _CLUBCCHATSOCK_API extern "C" __declspec(dllexport)
#else
#define _CLUBCCHATSOCK_API extern "C" __declspec(dllimport)
#endif

/* �ѹ��� ���� �� �ִ� ������ �ִ�ġ */
#define CHAT_DATA_BUF 1024

/* ���� �ڷ��� */
typedef struct { int _unused; } *HClubcChatSock;

/* utf-8 �ڷ���
 * �� Ÿ���� ���� ���� utf-8�� ����մϴ�. */
typedef char char_utf8;

/* ClubcChatSockEvent
 * Event�ڵ鷯���� �̺�Ʈ ������ �����ϴ� �� �������ϴ�.
 * �� ���� ���� param�� �ǹ̰� �޶����ϴ�. */
typedef enum
{
	/* ������ ����Ʈ�� �ٲ� �߻�.
	 * param : ������ ���� */
	CLUBCSOCKEVENT_UPDATE_CNTLIST,
	/* �����ڰ� �߰��ɶ� �߻�.
	 * param : �߰��� �������� �г���(const char *) */
	CLUBCSOCKEVENT_ADD_CNTLIST,
	/* �����ڰ� ������ �߻�.
	 * param : ���� �������� �г���(const char *) */
	CLUBCSOCKEVENT_REMOVE_CNTLIST,

	/* �� ����Ʈ�� �ٲ� �߻�.
	 * param : ������ ���� */
	CLUBCSOCKEVENT_UPDATE_ROOMLIST,
	/* ���� �߰��ɶ� �߻�.
	 * param : �߰��� ���� �г���(const char *) */
	CLUBCSOCKEVENT_ADD_ROOMLIST,
	/* ���� ���ŵɶ� �߻�.
	 * param : ���ŵ� ���� �г���(const char *) */
	CLUBCSOCKEVENT_REMOVE_ROOMLIST

} ClubcChatSockEvent;

/* Receive �ڵ鷯
 * nErrorCode�� 0�� �ƴϰ� str�� NULL�� ��� - OnReceive Error
 * nErrorCode�� 0�̰� str�� NULL�� ��� - Receive Error */
typedef void (*ClubcSockReceiveHandler)(HClubcChatSock sock, const char_utf8 *str, int nErrorCode);
/* Close �ڵ鷯 
 * nErrorCode�� 0�� �ƴϰ� str�� NULL�� ��� - OnClose Error */
typedef void (*ClubcSockCloseHandler)(HClubcChatSock sock, int nErrorCode);
/* Connect �ڵ鷯 */
typedef void (*ClubcSockConnectHandler)(HClubcChatSock sock);
/* Event �ڵ鷯 */
typedef void (*ClubcSockEventHandler)(HClubcChatSock sock, ClubcChatSockEvent e, void *param);
/* RoomExt �ڵ鷯 */
typedef void (*ClubcSockRoomExtHandler)(HClubcChatSock sock);

/* ���� ���� */
/* ������ �ּҿ� �� �ڵ鷯, ���̵�/��й�ȣ/UserData�� �μ��� �޽��ϴ�. */
/* UserData�� ����ڰ� ���Ƿ� �� �� �ִ� �����Դϴ�. �ʿ� ���� �ÿ� NULL�� �����Ͻʽÿ�.*/
_CLUBCCHATSOCK_API HClubcChatSock CreateClubcChatSock(
	const wchar_t *Server,
	ClubcSockReceiveHandler pfnOnReceive, ClubcSockCloseHandler pfnOnClose,
	ClubcSockConnectHandler pfnOnConnect, ClubcSockEventHandler pfnOnEvent,
	ClubcSockRoomExtHandler pfOnRoomExt,
	const char_utf8 *id, const char_utf8 *pw, void *UserData);
/* ���� ���� */
_CLUBCCHATSOCK_API void DeleteClubcChatSock(HClubcChatSock sock);

/* ���ڿ� Send */
_CLUBCCHATSOCK_API int SendStringClubcChatSock(HClubcChatSock sock, const char_utf8 *str);

/* �г��� ���ϱ� */
_CLUBCCHATSOCK_API const char_utf8 *GetMyNicknameClubcChatSock(HClubcChatSock sock);

/* ������ ����Ʈ ���ϱ�
 * ������ ����Ʈ�� \n(����)���� �����մϴ�.
 * �� : Person1\nPerson2\nPerson3\n... */
_CLUBCCHATSOCK_API void GetConnectListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size);

/* ������ִ��� ���θ� Ȯ���մϴ�.
 * �������� ������(TRUE/FALSE)�Դϴ�. */
_CLUBCCHATSOCK_API int IsConnectedClubcChatSock(HClubcChatSock sock);

/* UserData ���� �Լ� */
_CLUBCCHATSOCK_API void SetUserDataClubcChatSock(HClubcChatSock sock, void *UserData);
_CLUBCCHATSOCK_API void *GetUserDataClubcChatSock(HClubcChatSock sock);

/* �� �ý��� Ȯ�� Ȱ��ȭ
 * �� �Լ� ȣ�� �� CLUBCSOCKEVENT_UPDATE_ROOMLIST �̺�Ʈ�� ó�� �߻��� �ĺ��� �� �ý��� Ȯ���� ����� �� �ֽ��ϴ�. */
_CLUBCCHATSOCK_API void EnableRoomExtClubcChatSock(HClubcChatSock sock);

/* �� ����Ʈ ���ϱ�
 * �� �ý��� Ȯ���� Ȱ��ȭ�Ǿ�� �մϴ�.
 * �� ����Ʈ�� \n(����)���� �����մϴ�.
 * �� : Room1\nRoom2\nRoom3\n...*/
_CLUBCCHATSOCK_API void GetRoomListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size);

/* �� ����/���� */
_CLUBCCHATSOCK_API void ChangeRoomClubcChatSock(HClubcChatSock sock, const char_utf8 *room);

#endif /* _ClubcChatSockApi_h__ */