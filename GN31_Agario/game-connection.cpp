#include "pch.h"
#include "game-connection.h"

#include <exception>

void GameConnection::init(){
  WSADATA wd;
  WORD winSockVersion = MAKEWORD(2, 0);
  if(WSAStartup(winSockVersion, &wd)) throw std::runtime_error("WinSock failed to initialize");
}

void GameConnection::uninit(){
  disconnect();
  WSACleanup();
}

void GameConnection::connect(const char* address, const char* playerName){
  disconnect();
  
  socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  serverAddr = {};
  serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(20250);

  unsigned long flag = 1;
	ioctlsocket(socket, FIONBIO, &flag);

  PacketClientJoin packet;
  packet.version = PROTOCOL_VERSION;
  strcpy_s(packet.name, sizeof(packet.name), playerName);
  sendPacket(packet);
}

void GameConnection::disconnect(){
  if(socket){
    // maybe send PacketClientLeave here
    closesocket(socket);
    socket = NULL;
  }
}

bool GameConnection::receivePacket(){
  if(socket == NULL) return false; // throwでもよき
  
  sockaddr_in senderAddr;
  int senderAddrLen;

  auto res = recvfrom(socket, packetBuffer, sizeof(packetBuffer), 0, reinterpret_cast<sockaddr*>(&senderAddr), &senderAddrLen);
  if(res == SOCKET_ERROR){
    int err = WSAGetLastError();
    if(err == WSAEWOULDBLOCK) return false;
    // TODO エラーハンドル
    return false;
  }
  return true;
}

PacketType GameConnection::getPacketType(){
  return *reinterpret_cast<PacketType*>(packetBuffer);
}

void GameConnection::sendBytes(const void* data, int length){
  if(socket == NULL) return; // throwでもよき
  sendto(socket, static_cast<const char*>(data), length, 0, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(sockaddr));
}
