#ifndef _ClubcChatSockApi_h__
#define _ClubcChatSockApi_h__

#ifdef _CLUBCHATSOCK_DLL
#define _CLUBCCHATSOCK_API extern "C" __declspec(dllexport)
#else
#define _CLUBCCHATSOCK_API extern "C" __declspec(dllimport)
#endif

/* 한번에 보낼 수 있는 데이터 최대치 */
#define CHAT_DATA_BUF 1024

/* 소켓 자료형 */
typedef struct { int _unused; } *HClubcChatSock;

/* utf-8 자료형
 * 이 타입이 사용된 곳은 utf-8을 사용합니다. */
typedef char char_utf8;

/* ClubcChatSockEvent
 * Event핸들러에서 이벤트 종류를 구분하는 데 쓰여집니다.
 * 이 값에 따라 param의 의미가 달라집니다. */
typedef enum
{
	/* 접속자 리스트가 바뀔때 발생.
	 * param : 사용되지 않음 */
	CLUBCSOCKEVENT_UPDATE_CNTLIST,
	/* 접속자가 추가될때 발생.
	 * param : 추가된 접속자의 닉네임(const char *) */
	CLUBCSOCKEVENT_ADD_CNTLIST,
	/* 접속자가 나갈때 발생.
	 * param : 나간 접속자의 닉네임(const char *) */
	CLUBCSOCKEVENT_REMOVE_CNTLIST,

	/* 방 리스트가 바뀔때 발생.
	 * param : 사용되지 않음 */
	CLUBCSOCKEVENT_UPDATE_ROOMLIST,
	/* 방이 추가될때 발생.
	 * param : 추가된 방의 닉네임(const char *) */
	CLUBCSOCKEVENT_ADD_ROOMLIST,
	/* 방이 제거될때 발생.
	 * param : 제거된 방의 닉네임(const char *) */
	CLUBCSOCKEVENT_REMOVE_ROOMLIST

} ClubcChatSockEvent;

/* Receive 핸들러
 * nErrorCode가 0이 아니고 str가 NULL일 경우 - OnReceive Error
 * nErrorCode가 0이고 str가 NULL일 경우 - Receive Error */
typedef void (*ClubcSockReceiveHandler)(HClubcChatSock sock, const char_utf8 *str, int nErrorCode);
/* Close 핸들러 
 * nErrorCode가 0이 아니고 str가 NULL일 경우 - OnClose Error */
typedef void (*ClubcSockCloseHandler)(HClubcChatSock sock, int nErrorCode);
/* Connect 핸들러 */
typedef void (*ClubcSockConnectHandler)(HClubcChatSock sock);
/* Event 핸들러 */
typedef void (*ClubcSockEventHandler)(HClubcChatSock sock, ClubcChatSockEvent e, void *param);
/* RoomExt 핸들러 */
typedef void (*ClubcSockRoomExtHandler)(HClubcChatSock sock);

/* 소켓 생성 */
/* 서버의 주소와 각 핸들러, 아이디/비밀번호/UserData를 인수로 받습니다. */
/* UserData는 사용자가 임의로 쓸 수 있는 변수입니다. 필요 없을 시엔 NULL을 전달하십시오.*/
_CLUBCCHATSOCK_API HClubcChatSock CreateClubcChatSock(
	const wchar_t *Server,
	ClubcSockReceiveHandler pfnOnReceive, ClubcSockCloseHandler pfnOnClose,
	ClubcSockConnectHandler pfnOnConnect, ClubcSockEventHandler pfnOnEvent,
	ClubcSockRoomExtHandler pfOnRoomExt,
	const char_utf8 *id, const char_utf8 *pw, void *UserData);
/* 소켓 해제 */
_CLUBCCHATSOCK_API void DeleteClubcChatSock(HClubcChatSock sock);

/* 문자열 Send */
_CLUBCCHATSOCK_API int SendStringClubcChatSock(HClubcChatSock sock, const char_utf8 *str);

/* 닉네임 구하기 */
_CLUBCCHATSOCK_API const char_utf8 *GetMyNicknameClubcChatSock(HClubcChatSock sock);

/* 접속자 리스트 구하기
 * 접속자 리스트는 \n(개행)으로 구분합니다.
 * 예 : Person1\nPerson2\nPerson3\n... */
_CLUBCCHATSOCK_API void GetConnectListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size);

/* 연결되있는지 여부를 확인합니다.
 * 리턴형은 진위형(TRUE/FALSE)입니다. */
_CLUBCCHATSOCK_API int IsConnectedClubcChatSock(HClubcChatSock sock);

/* UserData 조작 함수 */
_CLUBCCHATSOCK_API void SetUserDataClubcChatSock(HClubcChatSock sock, void *UserData);
_CLUBCCHATSOCK_API void *GetUserDataClubcChatSock(HClubcChatSock sock);

/* 방 시스템 확장 활성화
 * 이 함수 호출 후 CLUBCSOCKEVENT_UPDATE_ROOMLIST 이벤트가 처음 발생한 후부터 방 시스템 확장을 사용할 수 있습니다. */
_CLUBCCHATSOCK_API void EnableRoomExtClubcChatSock(HClubcChatSock sock);

/* 방 리스트 구하기
 * 방 시스템 확장이 활성화되어야 합니다.
 * 방 리스트는 \n(개행)으로 구분합니다.
 * 예 : Room1\nRoom2\nRoom3\n...*/
_CLUBCCHATSOCK_API void GetRoomListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size);

/* 방 입장/변경 */
_CLUBCCHATSOCK_API void ChangeRoomClubcChatSock(HClubcChatSock sock, const char_utf8 *room);

#endif /* _ClubcChatSockApi_h__ */