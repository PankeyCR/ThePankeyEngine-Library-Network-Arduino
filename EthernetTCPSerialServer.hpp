#pragma once

#include "Arduino.h"
#include "IPAddress.h"
#include "Ethernet.h"
#include "EthernetServer.h"
#include "EthernetClient.h"

#include "IP.hpp"
#include "to_CharPointer_IP.hpp"
#include "SerialServer.hpp"
#include "EthernetTCPSerialPort.hpp"

#if defined(pankey_Log) && (defined(EthernetTCPSerialServer_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define EthernetTCPSerialServerLog(status,method,mns) pankey_Log(status,"EthernetTCPSerialServer",method,mns)
#else
	#define EthernetTCPSerialServerLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			class EthernetTCPSerialServer : public pankey::Library::Network::SerialServer{	
				public:
					EthernetTCPSerialServer(const pankey::Utility::Test::CharPointer& a_name, int port):m_server(port){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "Contructor", "");
						m_name = a_name;
						m_port = port;
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					
					virtual ~EthernetTCPSerialServer(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						// m_server.stop();
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual pankey::Utility::Test::CharPointer getName(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "getName", "");
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "getName", "");
						return m_name;
					}

					virtual void begin(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "begin", "");
						m_server.begin();
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "begin", "");
					}
						
					virtual void stop(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "stop", "");
						// m_server.stop();
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "stop", "");
					}
					
					virtual pankey::Library::Network::SerialPort* accept(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "accept", "");
						EthernetClient client = m_server.accept();   // Listen for incoming clients
						if(client){
							EthernetTCPSerialServerLog(pankey_Log_StartMethod, "accept", "if(client)");
							pankey::Library::Network::SerialPort* i_port = new EthernetTCPSerialPort(client);
							IPAddress i_ip = client.remoteIP();
							IP i_port_ip = createIP(i_ip[0],i_ip[1],i_ip[2],i_ip[3]);
							i_port->setIP(i_port_ip);
							i_port->setPort(m_port);
							return i_port;
						}
						return nullptr;
					} 
					
					pankey::Library::Network::SerialPort* available(){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "available", "");
						EthernetClient client = m_server.available();   // Listen for incoming clients
						if(client){
							EthernetTCPSerialServerLog(pankey_Log_StartMethod, "available", "if(client)");
							pankey::Library::Network::SerialPort* i_port = new EthernetTCPSerialPort(client);
							IPAddress i_ip = client.remoteIP();
							IP i_port_ip = createIP(i_ip[0],i_ip[1],i_ip[2],i_ip[3]);
							i_port->setIP(i_port_ip);
							i_port->setPort(m_port);
							return i_port;
						}
						return nullptr;
					}
						
					virtual void operator=(const EthernetTCPSerialServer& a_server){
						EthernetTCPSerialServerLog(pankey_Log_StartMethod, "operator=", "server(port)");
						m_server = a_server.m_server;
						m_port = a_server.m_port;
						EthernetTCPSerialServerLog(pankey_Log_EndMethod, "operator=", "");
					}

				protected:
					EthernetServer m_server;
					int m_port = 80;
					pankey::Utility::Test::CharPointer m_name;
			};

		}

	}

}