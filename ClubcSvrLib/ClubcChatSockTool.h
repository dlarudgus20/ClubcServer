#pragma once

void ReceiveHandler(CInterClubcChatSock *pSock, int nErrorCode);
void CloseHandler(CInterClubcChatSock *pSock, int nErrorCode);

void OnStrReceive(CInterClubcChatSock *pSock, const char *str, int nErrorCode);
