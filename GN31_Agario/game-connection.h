#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <wchar.h>

#include "packet.h"

class GameConnection{
public:
  void init();
  void uninit();
  // ソケットがあるかを返す
  // (実装がUDPなのでネーミングが若干🤔)
  bool isConnected();
  // ソケットを作成
  void connect(const char* address, const char* playerName);
  // ソケットを破棄
  void disconnect();
  // パケットを受信し、できたかを返す
  bool receivePacket();
  // 最後に受信したパケットの種類を返す
  PacketType getPacketType();
  // 最後に受信したパケットを返す
  template<class T>
  T& getPacket(){
    return *reinterpret_cast<T*>(packetBuffer);
  }
  // パケットを送信
  template<class T>
  void sendPacket(const T& packet){
    sendBytes(&packet, sizeof(packet));
  }
private:
  SOCKET socket = NULL;
  sockaddr_in serverAddr{};
  char packetBuffer[65507];
  void sendBytes(const void* data, int length);
};
