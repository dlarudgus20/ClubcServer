#pragma once

struct ClientInfo;

void LoginProcess(ClientInfo &cinfo, array<Byte> ^ar);
void FinallyProcess(ClientInfo &cinfo);

void AllBroadCastString(const char *str);
