#pragma once

#include "Arduino.h"
#include "IPAddress.h"

#include <EthernetUdp.h>

#include "ArrayRawMap.hpp"
#include "IP.hpp"
#include "to_CharPointer_IP.hpp"
#include "SerialServer.hpp"
#include "MessageSerialPort.hpp"

#if defined(pankey_Log) && (defined(UDPSerialServer_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define UDPSerialServerLog(status,method,mns) pankey_Log(status,"UDPSerialServer",method,mns)
#else
	#define UDPSerialServerLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			class UDPSerialServer : public SerialServer{	
				public:
					UDPSerialServer(const pankey::Utility::Test::CharPointer& a_name, int a_port):m_port(a_port){
						UDPSerialServerLog(pankey_Log_StartMethod, "Contructor", "server");
						m_name = a_name;
						UDPSerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					
					virtual ~UDPSerialServer(){
						UDPSerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						UDPSerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual pankey::Utility::Test::CharPointer getName(){
						UDPSerialServerLog(pankey_Log_StartMethod, "getName", "");
						UDPSerialServerLog(pankey_Log_EndMethod, "getName", "");
						return m_name;
					}
				
					virtual void send(const pankey::Type::Array::IP& a_ip, int a_port, const pankey::Type::Array::ByteArray& a_message){
						UDPSerialServerLog(pankey_Log_StartMethod, "send", "");
						IPAddress i_ip(a_ip.get(0), a_ip.get(1), a_ip.get(2), a_ip.get(3));
						Udp.beginPacket(i_ip, a_port);
						for(int x = 0; x < a_message.length(); x++){
							pankey::Type::Array::Byte f_byte = a_message.get(x);
							Udp.write(f_byte);
							// UDPSerialServerLog(pankey_Log_Statement, "send", "Byte: ");
							// UDPSerialServerLog(pankey_Log_Statement, "send", f_byte);
						}
						// Udp.print(a_message);
						UDPSerialServerLog(pankey_Log_EndMethod, "send", "");
						Udp.endPacket();
					}
				
					virtual void begin(){
						UDPSerialServerLog(pankey_Log_StartMethod, "begin", "");
						UDPSerialServerLog(pankey_Log_Statement, "begin", "Port: ");
						UDPSerialServerLog(pankey_Log_Statement, "begin", m_port);
						Udp.begin(m_port);
						UDPSerialServerLog(pankey_Log_EndMethod, "begin", "");
					}
					
					pankey::Library::Network::SerialPort* available(){
						// UDPSerialServerLog(pankey_Log_StartMethod, "available", "");
						// UDPSerialServerLog(pankey_Log_EndMethod, "available", "");
						return m_ports.removeFirst();
					}

					virtual void update(){
						// UDPSerialServerLog(pankey_Log_StartMethod, "update", "");
						int packetSize = Udp.parsePacket();
						if (packetSize) {
							UDPSerialServerLog(pankey_Log_Statement, "update", "packetSize: ");
							UDPSerialServerLog(pankey_Log_Statement, "update", packetSize);
							IPAddress i_remote = Udp.remoteIP();
							pankey::Type::Array::IP i_ip = createIP(i_remote[0], i_remote[1], i_remote[2], i_remote[3]);
							int i_port = Udp.remotePort();
							pankey::Type::Array::ByteArray i_message;
							while(Udp.available() > 0){
								pankey::Type::Array::Byte f_value = (pankey::Type::Array::Byte)Udp.read();
								i_message.add(f_value);
							}
							UDPSerialServerLog(pankey_Log_Statement, "update", "IP: ");
							UDPSerialServerLog(pankey_Log_Statement, "update", i_ip);
							UDPSerialServerLog(pankey_Log_Statement, "update", "Port: ");
							UDPSerialServerLog(pankey_Log_Statement, "update", i_port);
							UDPSerialServerLog(pankey_Log_Statement, "update", "Message: ");
							UDPSerialServerLog(pankey_Log_Statement, "update", i_message);
							pankey::Library::Network::SerialPort* i_serial_port = new MessageSerialPort(i_message);
							i_serial_port->setIP(i_ip);
							i_serial_port->setPort(i_port);
							m_ports.addPointer(i_serial_port);
						}
						// UDPSerialServerLog(pankey_Log_EndMethod, "update", "");
					}

				protected:

					EthernetUDP Udp;
					pankey::DataStructure::List::ArrayRawPointerList<pankey::Library::Network::SerialPort> m_ports = pankey::DataStructure::List::ArrayRawPointerList<pankey::Library::Network::SerialPort>(10, false, true);
					pankey::Utility::Test::CharPointer m_name;
					int m_port = 102;

			};

		}

	}

}