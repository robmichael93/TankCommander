/*
 *   A wrapper for C++ sockets on Unix and Windows
 *   Copyright (C) 2001 
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PracticalSocket.h"
#include <iostream>

#ifdef WIN32
  #include <winsock.h>         // for socket(), connect(), send(), and recv()
  typedef int socklen_t;
#else
  #include <sys/types.h>       // for socket(), connect(), send(), and recv()
  #include <sys/socket.h>      // for socket(), connect(), send(), and recv()
  #include <netdb.h>           // for gethostbyname()
  #include <arpa/inet.h>       // for sockaddr_in and inet_addr()
  #include <unistd.h>          // for close()
#endif

#include <errno.h>

using namespace std;

// Socket Code

Socket::Socket() { 
  sockDesc = -1;      // Mark this socket as unconnected.
}

Socket::~Socket() {  
  close();
}

void Socket::close() {
  // If the socket is open, close it.
  if (isOpen()) {
    #ifdef WIN32
      ::closesocket(sockDesc);
    #else
      ::close(sockDesc);
    #endif
    sockDesc = -1;
  }
}

bool Socket::isOpen() {
  return sockDesc >= 0;
}

bool Socket::getLocalIP(char address[], int addrLen) {
  struct sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sockDesc, (struct sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    return false;
  } else {
    char *tmp = inet_ntoa(addr.sin_addr);
    if ((strlen(tmp) + 1) > addrLen) {
      return false;
    } else {
      strcpy(address, tmp);
    }
  }
  return true;
}

bool Socket:: getLocalPort(unsigned short &port) {
  struct sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sockDesc, (struct sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    return false;
  } else {
    port = ntohs(addr.sin_port);
  }
  return true;
}

bool Socket::getForeignIP(char address[], int addrLen) {
  struct sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sockDesc, (struct sockaddr *) &addr,(socklen_t *) &addr_len) < 0) {
    return false;
  } else {
    char *tmp = inet_ntoa(addr.sin_addr);
    if ((strlen(tmp) + 1) > addrLen) {
      return false;
    } else {
      strcpy(address, tmp);
    }
  }
  return true;
}

bool Socket::getForeignPort(unsigned short &port) {
  struct sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sockDesc, (struct sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    return false;
  } else {
    port = ntohs(addr.sin_port);
  }
  return true;
}

bool Socket::resolveName(char name[], unsigned long &address) {
  struct hostent *host;

  if ((host = gethostbyname(name)) == NULL) {
    return false;
  }

  address = *((unsigned long *) host->h_addr_list[0]);
  return true;
}

void Socket::dieWithError(char *message) {
  cerr << strerror(errno) << ": " << message << endl;
  exit(1);
}

#ifdef WIN32
void Socket::startUp() {
   WORD wVersionRequested;
   WSADATA wsaData;

   wVersionRequested = MAKEWORD(2, 0);                  // Request Winsock v2.0 
   if (WSAStartup(wVersionRequested, &wsaData) != 0) {  // Load Winsock DLL 
     cerr << "WSAStartup() failed" << endl;
     exit(1);
   }
}

void Socket::cleanUp() {
  if (WSACleanup() != 0) {
    cerr << "WSACleanup() failed" << endl;
    exit(1);
  }
}
#endif

// Socket Code

bool TCPSocket::open(char *host, unsigned short port) {
  // Make a new socket.
  if ((sockDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "Cannot create TCPSocket" << endl;
    return false;
  }

  // Get the address of the requested host.
  struct sockaddr_in sin;
  memset((char *) &sin, 0, sizeof(sin)); 
  sin.sin_family = AF_INET;
  unsigned long int addr = 0;

  if (resolveName(host, addr)) {
    sin.sin_addr.s_addr = addr;
  } else {
    cerr << "Cannot get host information for server " << host << endl;
    close();
    return false;
  }
  sin.sin_port = htons(port);
  
  // Try to connect to the given port.
  if (connect(sockDesc, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    close();
    cerr << "Cannot connect to " << host << " on port " << port << endl;
    return false;
  }

  return true;
}

bool TCPSocket::send(const void *buffer, int count) { 
  return (::send(sockDesc, (const char*) buffer, count, 0) != -1);
}

int TCPSocket::recv(void *buffer, int count) {
  return ::recv(sockDesc, (char *) buffer, count, 0);
}

// TCPServerSocket Code

bool TCPServerSocket::open(unsigned short port) {
  // Make a new, unconnected socket
  if ((sockDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "Cannot create TCPServerSocket" << endl;
    return false;
  }

  // Bind the socket to its port.
  struct sockaddr_in sin;
    
  memset((char *)&sin, 0, sizeof(sin));

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);

  if (bind(sockDesc, (sockaddr *)&sin, sizeof(sockaddr_in)) < 0) {
    cerr << "Cannot Bind TCP to port " << port << endl;
    close();
    return false;
  }

  // Listen for new connections on this socket
  if (listen(sockDesc, 5) < 0) {
    cerr << "Cannot Listen on TCPServerSocket" << endl;
    close();
    return false;
  }
  return true;
}

bool TCPServerSocket::accept(TCPSocket &sock) { 
  // Return false if the TCPServerSocket is not connected
  if (!isOpen()) {
     return false;
  }

  // Fill in the socket for the new connection
  sock.sockDesc = ::accept(sockDesc, NULL, 0);

  // Return true on success.
  return sock.sockDesc >= 0;
}

// UDPSocket Code

bool UDPSocket::open(unsigned short port) {
  // Make a new socket.
  if ((sockDesc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    cerr << "Cannot create socket" << endl;
    return false;
  }

  // Connect the socket to its port.
  struct sockaddr_in sin;
    
  memset((char *)&sin, 0, sizeof(sin));

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);
    
  if (bind(sockDesc, (sockaddr *)(&sin), sizeof(sockaddr_in)) < 0) {
    cerr << "Cannot Bind UDP Socket to " << port << endl;
    close();
    return false;
  }

  return true;
}

bool UDPSocket::connect(char *host, unsigned short port) {
  struct sockaddr_in sin;
  memset((char *) &sin, 0, sizeof(sin)); 
  sin.sin_family = AF_INET;
  unsigned long int addr = 0;

  if (resolveName(host, addr)) {
    sin.sin_addr.s_addr = addr;
  } else {
    cerr << "Cannot get host information for server " << host << endl;
    close();
    return false;
  }
  sin.sin_port = htons(port);
  
  // Try to connect to the given port.
  if (::connect(sockDesc, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    cerr << "Cannot connect to " << host << " on port " << port << endl;
    return false;
  }

  return true;
}

bool UDPSocket::disconnect() {
  struct sockaddr_in sin;

  // Try to disconnect
  if (::connect(sockDesc, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    cerr << "Cannot disconnect" << endl;
    return false;
  }

  return true;
}

bool UDPSocket::send(char *host, unsigned short port, void const *buffer, int count) {
  // Get the address of the requested host.
  // Since each datagram could be for a different destination, 
  // we have to figure this out for each call.
  struct sockaddr_in sin;
  memset((char *) &sin, 0, sizeof(sin));
  int addr = inet_addr(host);
  sin.sin_addr.s_addr = addr;
  if(addr != -1) {
    sin.sin_family = AF_INET;
  } else {
    struct hostent *hostp = gethostbyname(host);
      
    if (hostp) {
      sin.sin_family = hostp->h_addrtype;
      sin.sin_addr.s_addr = *((unsigned long *)hostp->h_addr_list[0]);
    } else {
      cerr << "Cannot get host information for server " << host << endl;
      close();
      return false;
    }
  }
  sin.sin_port = htons(port);
  
  // Write out the whole buffer as a single message.
  return send(sin, buffer, count);
}

bool UDPSocket::send(struct sockaddr_in sockAddr, void const *buffer, int count) {
  sendto(sockDesc, (char *) buffer, count, 0, (sockaddr *) &sockAddr, sizeof(sockAddr));
  return true;
}

int UDPSocket::recv(void *buffer, int count, struct sockaddr_in &clntAddr, 
    unsigned int &addrLen) {
  return recvfrom(sockDesc, (char *) buffer, count, 0, 
    (struct sockaddr *)&clntAddr, (socklen_t *) &addrLen);
}

int UDPSocket::recv(void *buffer, int count) {
  return ::recv(sockDesc, (char *) buffer, count, 0);
}

