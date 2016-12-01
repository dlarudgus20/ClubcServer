#pragma once

struct ClientInfo;

bool OnStart();
bool OnStop();
bool OnPause();
bool OnContinue();

bool InitService();
bool CleanupService();
