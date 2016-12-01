#pragma once

struct ClientInfo;

struct Room
{
	char name[CHAT_DATA_BUF];
	list<ClientInfo *> users;
	ClientInfo *master;

	explicit Room(const char *n = "default");
	~Room();

	void AddUser(ClientInfo *user);
	void RemoveUser(ClientInfo *user);

	void BroadCastString(const char *str);
};
