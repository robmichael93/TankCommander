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

#ifndef __PRACTICALSOCKET_INCLUDED__
#define __PRACTICALSOCKET_INCLUDED__

#include <string>  // for strerror()

using namespace std;

/**
 *   Socket super class
 */
class Socket {
public:
  /**
   *   Create a socket
   */
  Socket();
  
  /**
   *   Destroy the socket
   */
  ~Socket();

  /**
   *   Close this socket
   */
  void close();

  /**
   *   Return true if this socket is open.
   *   @return return true on success
   */
  bool isOpen();

  /**
   *   Get the local IP address
   *   @param address local IP address destination
   *   @param addrLen maximum length of address
   *   @return true if successful
   */
  bool getLocalIP(char address[], int addrLen);

  /**
   *   Get the local port
   *   @param port port to return
   *   @return true if successful
   */
  bool getLocalPort(unsigned short &port);

  /**
   *   Get the foreign IP address
   *   @param address foreign IP address destination
   *   @param addrLen maximum length of address
   *   @return true if successful
   */ 
  bool getForeignIP(char address[], int addrLen);

  /**
   *   Get the foreign port
   *   @param port port to return
   *   @return true if successful
   */
  bool getForeignPort(unsigned short &port);

  /**
   *   Takes the name of the host and returns the available host
   *   information from the naming service, including the host's internet
   *   address.
   *   @param name name to resolve
   *   @param address address to return
   *   @return true if successful
   */
  static bool resolveName(char name[], unsigned long &address);

  /**
   *   Prints the system and given error message
   */
  static void dieWithError(char *message);

  #ifdef WIN32
  /**
   *   Wrapper functions for WSAStartup() for Win32
   */
  static void startUp();

  /**
   *   Wrapper functions for WSACleanup() for Win32
   */
  static void cleanUp();
  #endif

private:
  // Prevent the user from trying to use value semantics on this object.
  Socket(Socket const &sock);
  void operator=(Socket const &sock);

protected:
  int sockDesc;      // Socket descriptor
};

class TCPServerSocket;

/**
 *   TCP socket wrapper class for communication with other TCP sockets
 */
class TCPSocket : public Socket {
public:
  /**
   *   Try to establish a socket connection with the given host and
   *   port.  Return true if the connection is successfully opened.
   *   @param host host name, can be either IP or domain name
   *   @param port port number
   *   @return return true on success
   */
   bool open(char *host, unsigned short port);

  /**
   *   Write the given sequence of bytes over this socket connection.
   *   buffer is a pointer to the first byte to be written and
   *   count is the number of bytes to be written.
   *   @returns true if the write is successful
   *   @param buffer the memory address of the bytes to be written
   *   @param count the number of bytes to be written
   */
  bool send(const void *buffer, int count);

  /**
   *   Read up to count bytes data from this socket.  The given buffer 
   *   is where the data will be placed.
   *   @return the actual number of bytes read
   *   @param buffer the buffer address to receive the data
   *   @param the maximum number of bytes to read
   */
  int recv(void *buffer, int count);

  friend TCPServerSocket;
};

/**
 *   TCP socket wrapper class for servers
 */
class TCPServerSocket : public Socket {
public:
  /**
   *   Initialize this TCPServerSocket to accept connections on the given
   *   port.  
   *   @param port the port number
   *   @return true if the server socket is opened successfully
   */
  bool open(unsigned short port);

  /**
   *   Wait for a new connection on this TCPServerSocket's port.
   *   Initialize the given socket as a socket for talking over the
   *   new connection.
   *   @param sock socket for the new connection
   *   @return true if success
   */
  bool accept(TCPSocket &sock);
};

/**
  *   UDP socket wrapper class
  */
class UDPSocket : public Socket{
public:
  /**
   *   Create a socket and bind it to the given port.
   *   @param port port number
   *   @return return true on success
   */
  bool open(unsigned short port);

  /**
   *   Set foreign address and port
   *   @param host address of host to connect to
   *   @param port port of host to connect to
   *   @return return true on success
   */
  bool connect(char *host, unsigned short port);

  /**
   *   Unset foreign address and port
   *   @return return true on success
   */
  bool disconnect();

  /**
   *   Write the given sequence of bytes over this socket connection.
   *   buffer is a pointer to the first byte to be written and
   *   count is the number of bytes to be written.  
   *   @returns true if the write is successful
   *   @param host the name or dotted-quad notation for a host
   *   @param port port number
   *   @param buffer the memory address of the bytes to be written
   *   @param count the number of bytes to be written
   */
  bool send(char *host, unsigned short port, void const *buffer, int count);

   /**
   *   Write the given sequence of bytes over this socket connection.
   *   buffer is a pointer to the first byte to be written and
   *   count is the number of bytes to be written.  
   *   @returns true if the write is successful
   *   @param sockAddr the address structure of the host
   *   @param buffer the memory address of the bytes to be written
   *   @param count the number of bytes to be written
   */
  bool send(struct sockaddr_in sockAddr, void const *buffer, int count);

  /**
   *   Read read up to count bytes data from this socket.  The given buffer 
   *   is where the data will be placed.
   *   @return the actual number of bytes read
   *   @param buffer the buffer address to receive the data
   *   @param count the maxium number of bytes to read
   *   @param addr the address structure for the origin of a packet
   *   @param addrLen the size of the address structure(addr)
   */
  int recv(void *buffer, int count, struct sockaddr_in &, unsigned int &);

  /**
   *   Read read up to count bytes data from this socket.  The given buffer 
   *   is where the data will be placed.
   *   @return the actual number of bytes read
   *   @param buffer the buffer address to receive the data
   *   @param count the maxium number of bytes to read
   */
  int recv(void *buffer, int count);
};

#endif

