// Copyright Epic Games, Inc. All Rights Reserved.


#include "DataGameModeBase.h"
#include "Socket.h"
#include <iostream>
#include <string>
using namespace std;

#define PORT	4000
#define PACKED_SIZE 1024
#define SERVER_IP	"192.168.0.178"

void ADataGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	_Sock = new Socket;

	_Sock->InitSocket();

	_Sock->ConnectSocket();

	_Sock->SendSocket();

	_Sock->ReciveSocket();

}
