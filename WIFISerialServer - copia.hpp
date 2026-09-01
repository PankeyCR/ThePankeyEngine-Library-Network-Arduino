
#ifndef WIFISerialServer_hpp
	#define WIFISerialServer_hpp

	#include "SerialServer.hpp"
	#include "WIFISerialPort.hpp"

	#include "WiFi.h"

	#if defined(pankey_Log) && (defined(WIFISerialServer_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
		#include "Logger_status.hpp"
		#define WIFISerialServerLog(status,method,mns) pankey_Log(status,"WIFISerialServer",method,mns)
	#else
		#define WIFISerialServerLog(status,method,mns)
	#endif
	
	namespace pankey{

		namespace ArduinoNetwork{

			class WIFISerialServer : public Network::SerialServer<String,String>{	
				public:
					WIFISerialServer():server(80){
						WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(80)");
						WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					WIFISerialServer(int port):server(port){
						WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(port)");
						WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					WIFISerialServer(const WIFISerialServer& a_wifi_server){
						WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(port)");
						server = a_wifi_server.server;
						m_name = a_wifi_server.m_name;
						m_port = a_wifi_server.m_port;
						WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					
					virtual ~WIFISerialServer(){
						WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.stop();
						WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void begin(){
						WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.begin();
						WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void stop(){
						WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.stop();
						WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual Base::unique_ptr<SerialPort> accept(){
						WIFISerialServerLog(pankey_Log_StartMethod, "accept", "");
						#if pankey_Generic_Hardware == pankey_Generic_Esp32_Hardware
							WIFISerialServerLog(pankey_Log_Statement, "accept", "pankey_GENERIC_ESP32");
							WiFiClient client = server.accept();   // Listen for incoming clients
							if(client){
								obj<SerialPort> i_port = WIFISerialPort(client,"ethernet");
								WIFISerialServerLog(pankey_Log_EndMethod, "accept", "if(client)");
								return i_port;
							}
						#endif 
						#if pankey_Generic_Hardware == pankey_Generic_Esp8266_Hardware
							WIFISerialServerLog(pankey_Log_Statement, "accept", "pankey_GENERIC_ESP8266");
							WiFiClient client = server.available();
							if(client){
								obj<SerialPort> i_port = WIFISerialPort(client,"ethernet");
								WIFISerialServerLog(pankey_Log_EndMethod, "accept", "if(client)");
								return i_port;
							}
						#endif 
						WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
						return nullptr;
					} 
					
					virtual obj<SerialPort> available(){
						WIFISerialServerLog(pankey_Log_StartMethod, "available", "");
						WiFiClient client = server.available();   // Listen for incoming clients
						if(client){
							obj<SerialPort> i_port = WIFISerialPort(client,"ethernet");
							WIFISerialServerLog(pankey_Log_EndMethod, "available", "if(client)");
							return i_port;
						}
						WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
						return nullptr;
					}
					
					virtual WiFiServer getServer(){
						return server;
					}
					
					virtual void operator=(const WIFISerialServer& a_wifi_server){
						WIFISerialServerLog(pankey_Log_StartMethod, "operator=", "server(port)");
						server = a_wifi_server.server;
						m_name = a_wifi_server.m_name;
						m_port = a_wifi_server.m_port;
						WIFISerialServerLog(pankey_Log_EndMethod, "operator=", "");
					}

				protected:
					WiFiServer server;
			};

		}

	}

#endif