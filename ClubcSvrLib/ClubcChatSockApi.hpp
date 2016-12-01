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

// ���ӽ����̽�
namespace IkhPrograms
{
	// utf-8 ǥ�� ���ڿ�
	// �� Ÿ���� ���� ���� utf-8�� ����մϴ�.
	typedef std::string string_utf8;

	// ���� Ŭ������ ClubcChatSockApi.h�� �Լ����� Ȱ���ϴ� ���� �����ݴϴ�.
	class CClubcChatSock
	{
	private:
		// HClubcChatSock�� ��� ���� ����ü�Դϴ�.
		// m_pSock ������ ��� ������ ����ŵ�ϴ�.
		struct SClubcChatSock
		{
			// HClubcChatSock
			HClubcChatSock sock;
			// ���� ī��Ʈ�Դϴ�.
			unsigned RefCount;

			// ������ ����Ʈ
			// OnEvent���� ������
			std::list<string_utf8> m_ConnectList;

			// �� ����Ʈ
			// OnEvent���� ������
			std::vector<string_utf8> m_RoomList;

			// �� Ȯ�� Ȱ��ȭ ����
			bool bUseRoomExt;

			// �������Դϴ�.
			explicit SClubcChatSock(unsigned ref = 0) : RefCount(ref), bUseRoomExt(false) { }
		};
	public:
		// ���� Ŭ�����Դϴ�.
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
					return "ClubcChatSock ���� ����";
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
		// SClubcChatSock�� ����Ű�� �������Դϴ�.
		// �ʱ�ȭ���� ���� �ÿ� NULL�̸� �ʱ�ȭ�� new�� �����Ҵ�˴ϴ�.
		SClubcChatSock *m_pSock;

		// Receive/Close/Connect �ڵ鷯�Դϴ�.
		// UserData�� this �����Ͱ� ������ �װ͵��� �̿��� OnReceive/OnClose/OnConnect �����Լ��� ȣ���մϴ�.
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
		// Receive �ڵ鷯
		// nErrorCode�� 0�� �ƴϰų� str�� NULL�̸� �����Դϴ�.
		virtual void OnReceive(const char_utf8 *str, int nErrorCode) { }
		// Close �ڵ鷯
		// nErrorCode�� 0�� �ƴϸ� �����Դϴ�.
		virtual void OnClose(int nErrorCode) { }
		// Connect�ڵ鷯
		virtual void OnConnect() { }
		// RoomExt �ڵ鷯
		// �� Ȯ���� Ȱ��ȭ�Ǹ� ȣ��˴ϴ�.
		virtual void OnRoomExt() { }
		// Event�ڵ鷯
		// �������� ��� �� �Լ��� ���� ȣ���ؾ���
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
		// Ŭ���� ����ڰ� �����Ӱ� �� �� �ִ� �����Դϴ�.
		void *m_UserData;

		// �������Դϴ�.
		CClubcChatSock() : m_pSock(NULL) { }
		CClubcChatSock(const wchar_t *Server, const char_utf8 *id, const char_utf8 *pw, void *UserData = NULL) : m_pSock(NULL)
		{
			Create(Server, id, pw, UserData);
		}
		// ���� ������. m_pSock�� NULL�� �ƴҰ�� ���� ī��Ʈ�� ������ŵ�ϴ�.
		CClubcChatSock(const CClubcChatSock &other)
		{
			m_pSock = other.m_pSock;
			if(m_pSock != NULL)
			{
				m_pSock->RefCount++;
			}
		}

		// �ʱ�ȭ �ڵ�
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

		// �ı����Դϴ�.
		virtual ~CClubcChatSock()
		{
			if(m_pSock != NULL)
			{
				Close();
			}
		}

		// Cleanup �ڵ�
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

		// ���ڿ��� ������ �Լ��Դϴ�.
		int SendString(const char_utf8 *str)
		{
			assert(this != NULL && m_pSock != NULL);
			return SendStringClubcChatSock(m_pSock->sock, str);
		}

		// �г����� ���ϴ� �Լ��Դϴ�.
		const char_utf8 *GetMyNickname()
		{
			assert(this != NULL && m_pSock != NULL);
			return GetMyNicknameClubcChatSock(m_pSock->sock);
		}

		// ������ ����Ʈ ���ڿ��� ���ϴ� �Լ��Դϴ�.
		// �� �Լ� ��� GetConnectList�� ����Ͻʽÿ�.
		// ���ڿ� ���� ���� ������ ClubcChatSockApi.h ����
		string_utf8 GetConnectListStr()
		{
			char buf[CHAT_DATA_BUF];
			assert(this != NULL && m_pSock != NULL);
			GetConnectListClubcChatSock(m_pSock->sock, buf, sizeof(buf) / sizeof(buf[0]));
			return buf;
		}

		// ������ ����Ʈ�� ���ϴ� �Լ��Դϴ�.
		// �� ����Ʈ�� CClubcChatSock::OnEvent()�� ���� �����˴ϴ�.
		const std::list<string_utf8> &GetConnectList()
		{
			assert(this != NULL && m_pSock != NULL);
			return m_pSock->m_ConnectList;
		}

		// �� ����Ʈ ���ڿ��� ���ϴ� �Լ��Դϴ�.
		// �� �Լ� ��� GetRoomList�� ����Ͻʽÿ�.
		// ���ڿ� ���� ���� ������ ClubcChatSockApi.h ����
		string_utf8 GetRoomListStr()
		{
			char buf[CHAT_DATA_BUF];
			assert(this != NULL && m_pSock != NULL);
			GetRoomListClubcChatSock(m_pSock->sock, buf, sizeof(buf) / sizeof(buf[0]));
			return buf;
		}

		// �� ����Ʈ�� ���ϴ� �Լ��Դϴ�.
		// �� ����Ʈ�� CClubcChatSock::OnEvent()�� ���� �����˴ϴ�.
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

		// ������ ��������� true�� ��ȯ�մϴ�.
		bool IsConnected()
		{
			assert(this != NULL);
			return m_pSock != NULL && IsConnectedClubcChatSock(m_pSock->sock);
		}

		// �� Ȯ���� ����ϸ� true�� ��ȯ�մϴ�.
		bool IsUseRoomExt()
		{
			assert(this != NULL && m_pSock != NULL);
			return m_pSock->bUseRoomExt;
		}

		// ������ ���������� true�� ��ȯ�մϴ�.
		bool IsInited()
		{
			assert(this != NULL);
			return m_pSock != NULL;
		}
	};
};

#endif // ClubcChatSockApi_h__
