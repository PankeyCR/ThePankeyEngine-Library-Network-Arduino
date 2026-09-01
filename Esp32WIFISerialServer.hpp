#pragma once

#include "SerialServer.hpp"
#include "SerialPort.hpp"
#include "Esp32WIFISerialPort.hpp"
#include "arduinoByteArrayHelper.hpp"

#include "WiFi.h"

#if defined(pankey_Log) && (defined(Esp32WIFISerialServer_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define Esp32WIFISerialServerLog(status,method,mns) pankey_Log(status,"Esp32WIFISerialServer",method,mns)
#else
	#define Esp32WIFISerialServerLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			namespace Arduino{

				class Esp32WIFISerialServer : public Network::SerialServer{	
					public:
						Esp32WIFISerialServer():m_server(80){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(80)");
							m_port = 80;
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
						}
						Esp32WIFISerialServer(int a_port):m_server(a_port){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(a_port)");
							m_port = a_port;
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
						}
						Esp32WIFISerialServer(const Esp32WIFISerialServer& a_wifi_server){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "");
							m_server = a_wifi_server.m_server;
							m_port = a_wifi_server.m_port;
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
						}
						
						virtual ~Esp32WIFISerialServer(){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
							m_server.stop();
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
						}

						virtual void begin(){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "begin", "");
							m_server.begin();
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "begin", "");
						}
						
						virtual void stop(){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "stop", "");
							m_server.stop();
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "stop", "");
						}
						
						virtual Network::SerialPort* accept(){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "accept", "");
							WiFiClient client = m_server.accept();   // Listen for incoming clients
							if(client){
								Network::SerialPort* i_port = new Esp32WIFISerialPort(client);
								IPAddress i_ip = client.remoteIP();
								i_port->setIP(getByteArrayIP(i_ip));
								i_port->setPort(m_port);
								// Serial.println(i_ip);
								// println(getByteArrayIP(i_ip));
								Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "if(client)");
								return i_port;
							}
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
							return nullptr;
						} 
						
						virtual Network::SerialPort* available(){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "available", "");
							WiFiClient client = m_server.available();   // Listen for incoming clients
							if(client){
								Network::SerialPort* i_port = new Esp32WIFISerialPort(client);
								IPAddress i_ip = client.remoteIP();
								i_port->setIP(getByteArrayIP(i_ip));
								i_port->setPort(m_port);
								Esp32WIFISerialServerLog(pankey_Log_EndMethod, "available", "if(client)");
								return i_port;
							}
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
							return nullptr;
						}
						
						virtual void operator=(const Esp32WIFISerialServer& a_wifi_server){
							Esp32WIFISerialServerLog(pankey_Log_StartMethod, "operator=", "server(port)");
							m_server = a_wifi_server.m_server;
							m_port = a_wifi_server.m_port;
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "operator=", "");
						}

					protected:
						WiFiServer m_server;
						int m_port = 80;
				};

			}

		}

	}

}