#ifndef ClubcChatSockApi_h__
#define ClubcChatSockApi_h__

#include <stdio.h>
#include <assert.h>

#include <algorithm>
#include <exception>
#include <string>
#include <vector>
#include <list>

#include "ClubcChatSockApi.h"

// 네임스페이스
namespace IkhPrograms
{
	// utf-8 표준 문자열
	// 이 타입이 사용된 곳은 utf-8을 사용합니다.
	typedef std::string string_utf8;

	// 다음 클래스는 ClubcChatSockApi.h의 함수들을 활용하는 예를 보여줍니다.
	class CClubcChatSock
	{
	private:
		// HClubcChatSock을 담기 위한 구조체입니다.
		// m_pSock 포인터 멤버 변수가 가리킵니다.
		struct SClubcChatSock
		{
			// HClubcChatSock
			HClubcChatSock sock;
			// 참조 카운트입니다.
			unsigned RefCount;

			// 접속자 리스트
			// OnEvent에서 관리됨
			std::list<string_utf8> m_ConnectList;

			// 방 리스트
			// OnEvent에서 관리됨
			std::vector<string_utf8> m_RoomList;

			// 방 확장 활성화 여부
			bool bUseRoomExt;

			// 생성자입니다.
			explicit SClubcChatSock(unsigned ref = 0) : RefCount(ref), bUseRoomExt(false) { }
		};
	public:
		// 예외 클래스입니다.
		class CClubcChatSockException : public std::exception
		{
		public:
			enum ExceptionKind { ERR_CREATE };
		private:
			ExceptionKind m_ExceptionKind;
			CClubcChatSockException(ExceptionKind k) : m_ExceptionKind(k) { }
		public:
			virtual const char *what() const
			{
				switch(m_ExceptionKind)
				{
				case ERR_CREATE:
					return "ClubcChatSock 생성 에러";
				}
				return NULL;
			}
			virtual ExceptionKind GetExceptionKind()
			{
				return m_ExceptionKind;
			}

			friend CClubcChatSock;
		};
	private:
		// SClubcChatSock을 가리키는 포인터입니다.
		// 초기화되지 않을 시엔 NULL이며 초기화시 new로 동적할당됩니다.
		SClubcChatSock *m_pSock;

		// Receive/Close/Connect 핸들러입니다.
		// UserData엔 this 포인터가 있으며 그것들을 이용해 OnReceive/OnClose/OnConnect 가상함수를 호출합니다.
		static void ReceiveHandler(HClubcChatSock sock, const char_utf8 *str, int nErrorCode)
		{
			((CClubcChatSock *)GetUserDataClubcChatSock(sock))->OnReceive(str, nErrorCode);
		}
		static void CloseHandler(HClubcChatSock sock, int nErrorCode)
		{
			((CClubcChatSock *)GetUserDataClubcChatSock(sock))->OnClose(nErrorCode);
		}
		static void ConnectHandler(HClubcChatSock sock)
		{
			((CClubcChatSock *)GetUserDataClubcChatSock(sock))->OnConnect();
		}
		static void EventHandler(HClubcChatSock sock, ClubcChatSockEvent e, void *param)
		{
			((CClubcChatSock *)GetUserDataClubcChatSock(sock))->OnEvent(e, param);
		}
		static void RoomExtHandler(HClubcChatSock sock)
		{
			((CClubcChatSock *)GetUserDataClubcChatSock(sock))->OnRoomExt();
		}
	protected:
		// Receive 핸들러
		// nErrorCode가 0이 아니거나 str가 NULL이면 에러입니다.
		virtual void OnReceive(const char_utf8 *str, int nErrorCode) { }
		// Close 핸들러
		// nErrorCode가 0이 아니면 에러입니다.
		virtual void OnClose(int nErrorCode) { }
		// Connect핸들러
		virtual void OnConnect() { }
		// RoomExt 핸들러
		// 방 확장이 활성화되면 호출됩니다.
		virtual void OnRoomExt() { }
		// Event핸들러
		// 재정의할 경우 이 함수를 먼저 호출해야함
		virtual void OnEvent(ClubcChatSockEvent e, void *param)
		{
			switch(e)
			{
			case CLUBCSOCKEVENT_ADD_CNTLIST:
				m_pSock->m_ConnectList.push_back((const char *)param);
				break;
			case CLUBCSOCKEVENT_REMOVE_CNTLIST:
				m_pSock->m_ConnectList.remove((const char *)param);
				break;
			case CLUBCSOCKEVENT_UPDATE_CNTLIST:
				{
					string_utf8 str, cntlst = GetConnectListStr();
					m_pSock->m_ConnectList.clear();
					unsigned pos = 0;
					while(pos < cntlst.length())
					{
						str = cntlst.substr(pos, cntlst.find('\n', pos) - pos);
						if (str.length() != 0)
						{
							if(str[str.length() - 1] == '\n')
							{
								str.erase(str.length() - 1);
							}
							m_pSock->m_ConnectList.push_back(str);
						}
						pos += str.length() + 1;
					}
					break;
				}

			case CLUBCSOCKEVENT_ADD_ROOMLIST:
				m_pSock->m_RoomList.push_back((const char *)param);
				break;
			case CLUBCSOCKEVENT_REMOVE_ROOMLIST:
				m_pSock->m_RoomList.erase(find(m_pSock->m_RoomList.begin(), m_pSock->m_RoomList.end(), (const char *)param));
				break;
			case CLUBCSOCKEVENT_UPDATE_ROOMLIST:
				{
					string_utf8 str, rmlst = GetRoomListStr();
					m_pSock->m_RoomList.clear();
					unsigned pos = 0;
					while(pos < rmlst.length())
					{
						str = rmlst.substr(pos, rmlst.find('\n', pos) - pos);
						if (str.length() != 0)
						{
							if(str[str.length() - 1] == '\n')
							{
								str.erase(str.length() - 1);
							}
							m_pSock->m_RoomList.push_back(str);
						}
						pos += str.length() + 1;
					}

					if (!m_pSock->bUseRoomExt)
					{
						m_pSock->bUseRoomExt = true;
					}
					break;
				}
			}
		}
	public:
		// 클래스 사용자가 자유롭게 쓸 수 있는 변수입니다.
		void *m_UserData;

		// 생성자입니다.
		CClubcChatSock() : m_pSock(NULL) { }
		CClubcChatSock(const wchar_t *Server, const char_utf8 *id, const char_utf8 *pw, void *UserData = NULL) : m_pSock(NULL)
		{
			Create(Server, id, pw, UserData);
		}
		// 복사 생성자. m_pSock이 NULL이 아닐경우 참조 카운트를 증가시킵니다.
		CClubcChatSock(const CClubcChatSock &other)
		{
			m_pSock = other.m_pSock;
			if(m_pSock != NULL)
			{
				m_pSock->RefCount++;
			}
		}

		// 초기화 코드
		void Create(const wchar_t *Server, const char_utf8 *id, const char_utf8 *pw, void *UserData = NULL)
		{
			assert(this != NULL);
			m_UserData = UserData;
	
			if(m_pSock != NULL)
			{
				Close();
			}
			m_pSock = new SClubcChatSock;

			m_pSock->sock = CreateClubcChatSock(Server,
				ReceiveHandler, CloseHandler, ConnectHandler, EventHandler, RoomExtHandler, id, pw, this);
			if(m_pSock->sock == NULL)
			{
				delete m_pSock;
				m_pSock = NULL;
				throw CClubcChatSockException(CClubcChatSockException::ERR_CREATE);
			}
		}

		// 파괴자입니다.
		virtual ~CClubcChatSock()
		{
			if(m_pSock != NULL)
			{
				Close();
			}
		}

		// Cleanup 코드
		void Close()
		{
			assert(this != NULL && m_pSock != NULL);
			if(m_pSock->RefCount == 0)
			{
				DeleteClubcChatSock(m_pSock->sock);
				delete m_pSock;
			}
			else
			{
				m_pSock->RefCount--;
			}
		}

		// 문자열을 보내는 함수입니다.
		int SendString(const char_utf8 *str)
		{
			assert(this != NULL && m_pSock != NULL);
			return SendStringClubcChatSock(m_pSock->sock, str);
		}

		// 닉네임을 구하는 함수입니다.
		const char_utf8 *GetMyNickname()
		{
			assert(this != NULL && m_pSock != NULL);
			return GetMyNicknameClubcChatSock(m_pSock->sock);
		}

		// 접속자 리스트 문자열을 구하는 함수입니다.
		// 이 함수 대신 GetConnectList를 사용하십시오.
		// 문자열 포멧 관련 도움말은 ClubcChatSockApi.h 참조
		string_utf8 GetConnectListStr()
		{
			char buf[CHAT_DATA_BUF];
			assert(this != NULL && m_pSock != NULL);
			GetConnectListClubcChatSock(m_pSock->sock, buf, sizeof(buf) / sizeof(buf[0]));
			return buf;
		}

		// 접속자 리스트를 구하는 함수입니다.
		// 이 리스트는 CClubcChatSock::OnEvent()에 의해 관리됩니다.
		const std::list<string_utf8> &GetConnectList()
		{
			assert(this != NULL && m_pSock != NULL);
			return m_pSock->m_ConnectList;
		}

		// 방 리스트 문자열을 구하는 함수입니다.
		// 이 함수 대신 GetRoomList를 사용하십시오.
		// 문자열 포멧 관련 도움말은 ClubcChatSockApi.h 참조
		string_utf8 GetRoomListStr()
		{
			char buf[CHAT_DATA_BUF];
			assert(this != NULL && m_pSock != NULL);
			GetRoomListClubcChatSock(m_pSock->sock, buf, sizeof(buf) / sizeof(buf[0]));
			return buf;
		}

		// 방 리스트를 구하는 함수입니다.
		// 이 리스트는 CClubcChatSock::OnEvent()에 의해 관리됩니다.
		const std::vector<string_utf8> &GetRoomList()
		{
			assert(this != NULL && m_pSock != NULL);
			return m_pSock->m_RoomList;
		}

		void EnableRoomExt()
		{
			assert(this != NULL && m_pSock != NULL);
			EnableRoomExtClubcChatSock(m_pSock->sock);
		}

		void ChangeRoom(const char_utf8 *room)
		{
			assert(this != NULL && m_pSock != NULL);
			ChangeRoomClubcChatSock(m_pSock->sock, room);
		}

		// 소켓이 연결됬으면 true를 반환합니다.
		bool IsConnected()
		{
			assert(this != NULL);
			return m_pSock != NULL && IsConnectedClubcChatSock(m_pSock->sock);
		}

		// 방 확장을 사용하면 true를 반환합니다.
		bool IsUseRoomExt()
		{
			assert(this != NULL && m_pSock != NULL);
			return m_pSock->bUseRoomExt;
		}

		// 소켓이 생성됬으면 true를 반환합니다.
		bool IsInited()
		{
			assert(this != NULL);
			return m_pSock != NULL;
		}
	};
};

#endif // ClubcChatSockApi_h__
