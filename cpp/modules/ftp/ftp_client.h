/********************************************************************
  Filename:    ftp_client.h
  Author:      
  Created:     
  Description:

*********************************************************************/
#ifndef    PLATFORM_FTP_CLIENT_HPP_  
#define    PLATFORM_FTP_CLIENT_HPP_  

#include <stdio.h>  

#include <string>  
#include <sstream>  
#include <iostream>  

//#include <ace/OS.h>  
#include <ace/OS_main.h>  
#include <ace/Reactor.h>  
#include <ace/SOCK_Acceptor.h>  
#include <ace/SOCK_Connector.h>  
#include <ace/SOCK_Stream.h>  
#include <ace/Acceptor.h>  
#include <ace/Connector.h>  
#include "platform/modules/ftp/ftp_def.hpp"



#define MAX_CONN_TIMEOUT_SECOND      3 /*TCP connection timeout in second.*/  
#define MAX_CONN_TIMEOUT_MILLISECOND 0 /*TCP connection timeout in ms.*/  

#define MAX_RECV_TIMEOUT_SECOND      1 /*TCP connection timeout in second.*/  
#define MAX_RECV_TIMEOUT_MILLISECOND 0 /*TCP connection timeout in ms.*/  

#define MAX_BUFSIZE 1024  

/************************************************************************/  
/* ACE库实现FTP功能，支持发送和接受文件                                 */  
/************************************************************************/ 
namespace ubp
{
	namespace platform
	{
		namespace ftp
		{

class FTPClient  
{  
public:  
	FTPClient(const std::string &remote_ip, const u_short remote_port,  
		const std::string &user_name, const std::string &pass_word,  
		int os_type = OS_DEFAULT);  
	virtual ~FTPClient();  

	bool LogoIn();  
	bool LogoOut();  

	bool GetSysInfo();  
	bool Noop();  

	bool ChangeLocalDir(const std::string &dirname);  
	bool ChangeRemoteDir(const std::string &dirname);  

	bool PutFile(const std::string &filename);  
	bool GetFile(const std::string &filename);  

	bool List(std::string &pathlist, const std::string &pathname = "");  
	bool NList(std::string &pathlist, const std::string &pathname = "");  

	bool ReName(const std::string &srcname, const std::string &dstname);  

private:  
	bool Recv(std::string &response);  
	bool Send(const std::string &command);  

	std::string    user_name_, pass_word_;  
	ACE_INET_Addr  remote_addr_;  
	ACE_SOCK_Connector connector_;  
	ACE_SOCK_Stream    peer_;  

	int os_type_;  

/*
public:  
	enum  
	{  
		OS_DEFAULT = 0,  
		OS_LINUX   = 1,  
		OS_WIN32   = 2,  
		OS_AIX     = 3,  
		OS_HP_UNIX = 4,  
		OS_SUNOS   = 5  
	};
*/
};  

}//namespace ftp
}//namespace platform
}//namespace ubp

#endif // PLATFORM_FTP_CLIENT_HPP_
