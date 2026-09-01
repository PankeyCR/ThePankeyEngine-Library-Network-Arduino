#pragma once

#include "SerialPort.hpp"
#include "Arduino.h"
#include "IPAddress.h"
#include "Ethernet.h"
#include "EthernetServer.h"
#include "EthernetClient.h"

#if defined(pankey_Log) && (defined(EthernetTCPSerialPortn_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define EthernetTCPSerialPortLog(status,method,mns) pankey_Log(status,"EthernetTCPSerialPort",method,mns)
#else
	#define EthernetTCPSerialPortLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			class EthernetTCPSerialPort : public pankey::Library::Network::SerialPort{	
				public:
					EthernetTCPSerialPort(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "Contructor", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~EthernetTCPSerialPort(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "Destructor", "");
						if(connected()){
							stop();
						}
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "Destructor", "");
					}

					EthernetTCPSerialPort(const EthernetTCPSerialPort& a_serialport){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "Contructor", "");
						m_client = a_serialport.m_client;
						m_ip = a_serialport.m_ip;
						m_port = a_serialport.m_port;
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					EthernetTCPSerialPort(EthernetClient a_client){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
						m_client = a_client;
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual int status(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "status", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "status", "");
						return m_client.status();
					}

					virtual int available(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "available", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "available", "");
						return m_client.available();
					}

					virtual pankey::Type::Array::Byte read(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "read", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "read", "");
						return m_client.read();
					}

					virtual int peek(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "peek", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "peek", "");
						return m_client.peek();
					}

					virtual pankey::Memory::Allocator::memory_size write(Byte a_byte){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "write", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "write", "");
						return m_client.write(a_byte);
					}
					
					virtual pankey::Memory::Allocator::memory_size print(const pankey::Type::Array::ByteArray& a_message){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "print", "");
						pankey::Memory::Allocator::memory_size i_size = 0;
						for(int x = 0; x < a_message.length(); x++){
							i_size += m_client.write(a_message.get(x));
						}
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "print", "");
						return i_size;
					}
					
					virtual pankey::Memory::Allocator::memory_size println(const pankey::Type::Array::ByteArray& a_message){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "println", "");
						pankey::Memory::Allocator::memory_size i_size = 0;
						for(int x = 0; x < a_message.length(); x++){
							i_size += m_client.write(a_message.get(x));
						}
						m_client.println();
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "println", "");
						return i_size;
					}

					virtual bool connected(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "connected", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "connected", "");
						return m_client.connected();
					}
					
					virtual bool connect(const pankey::Type::Array::ByteArray& a_ip){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "connect", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "connect", "");
						return connect(a_ip,-1);
					}
					
					virtual bool connect(const pankey::Type::Array::ByteArray& a_ip, int port){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "connect", "");
							
						IPAddress i_ip;
						if(a_ip.length() == 4){
							i_ip = IPAddress(a_ip.get(0), a_ip.get(1), a_ip.get(2), a_ip.get(3));
						}
						
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "connect", "");
						return m_client.connect(i_ip, port);
					}
					
					virtual void stop(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "stop", "");
						m_client.stop();
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "stop", "");
					}

					virtual void flush(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "flush", "");
						m_client.flush();
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "flush", "");
					}

					virtual void operator=(EthernetClient c){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "operator=", "");
						m_client = c;
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "operator=", "");
					}

					virtual void operator=(const EthernetTCPSerialPort& a_serialport){
						m_client = a_serialport.m_client;
					}

					virtual bool operator==(EthernetTCPSerialPort c){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "operator==", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "operator==", "");
						return m_client == c.m_client;
					}
					virtual bool operator!=(EthernetTCPSerialPort c){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "operator!=", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "operator!=", "");
						return m_client != c.m_client;
					}
					virtual operator bool(){
						EthernetTCPSerialPortLog(pankey_Log_StartMethod, "operator bool", "");
						EthernetTCPSerialPortLog(pankey_Log_EndMethod, "operator bool", "");
						return m_client;
					}

				protected:
					EthernetClient m_client;
			};

		}

	}

}