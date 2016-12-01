#pragma once

struct ClientInfo;

void DoCommunicate(IAsyncResult ^ar);
bool ProcessString(ClientInfo &cinfo, array<Byte> ^ar);
bool ProcessCommand(ClientInfo &cinfo, const char *str);
