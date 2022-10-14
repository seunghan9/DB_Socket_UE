// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "windows/AllowWindowsPlatformTypes.h"
#include "windows/prewindowsapi.h"

#pragma comment(lib, "ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include "Runtime/Core/Public/Math/Vector.h"
#include "CoreMinimal.h"

#include "windows/PostWindowsApi.h"
#include "windows/HideWindowsPlatformTypes.h"

/**
 * 
 */
class DATA_API Socket
{
public:
	Socket();
	~Socket();

	// ���� �ʱ�ȭ ���� ���� 2.2 ����
	bool InitSocket();

	// ���� ����
	bool CreatSocket();

	// ���� ���ε�
	bool BindSocket(const char* _BindIP, int _BindPort);

	// ���� ���·� ����
	bool ListenSocket();

	// �������� Ŭ���̾�Ʈ ���� ����
	bool AcceptSocket();

	// Ŭ���̾�Ʈ���� ������ ����
	bool ConnectSocket(const char* _ServerIP, int _ConnectPort);

	// ������ ����
	bool SendSocket();

	// ������ ����
	bool ReciveSocket();

	SOCKET _Socket;

	SOCKET _SocketConnected;

	SOCKET _ServerSocket;

};