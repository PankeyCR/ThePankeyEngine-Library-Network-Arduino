#pragma once

#include "Byte.hpp"
#include "MemorySize.hpp"
#include "MemorySize.hpp"
#include "IPAddress.h"
#include "SerialPort.hpp"

#if defined(pankey_Log) && (defined(USBSerialPortn_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define USBSerialPortLog(status,method,mns) pankey_Log(status,"USBSerialPort",method,mns)
#else
	#define USBSerialPortLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			namespace Arduino{

				class USBSerialPort : public pankey::Library::Network::SerialPort{	
					public:
						USBSerialPort(){
							USBSerialPortLog(pankey_Log_StartMethod, "Contructor", "");
							m_serial = &Serial;
							USBSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
						}
						USBSerialPort(Stream* a_stream){
							USBSerialPortLog(pankey_Log_StartMethod, "Contructor", "");
							m_serial = a_stream;
							USBSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
						}

						virtual ~USBSerialPort(){
							USBSerialPortLog(pankey_Log_StartMethod, "Destructor", "");
							if(this->connected()){
								this->stop();
							}
							USBSerialPortLog(pankey_Log_EndMethod, "Destructor", "");
						}
						
						USBSerialPort(const USBSerialPort& a_serialport){
							USBSerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
							m_serial = a_serialport.m_serial;
							m_ip = a_serialport.m_ip;
							USBSerialPortLog(pankey_Log_EndMethod, "Contructor", "");
						}

						// virtual pankey::Type::Array::ByteArray getIP(){return pankey::getByteArrayIP(m_serial->remoteIP());}

						virtual int status(){
							USBSerialPortLog(pankey_Log_StartMethod, "status", "");
							// return m_serial->status();
							USBSerialPortLog(pankey_Log_EndMethod, "status", "");
							return 0;
						}

						virtual int available(){
							USBSerialPortLog(pankey_Log_StartMethod, "available", "");
							USBSerialPortLog(pankey_Log_EndMethod, "available", "");
							return m_serial->available();
						}

						virtual pankey::Type::Array::Byte read(){
							USBSerialPortLog(pankey_Log_StartMethod, "read", "");
							USBSerialPortLog(pankey_Log_EndMethod, "read", "");
							return (Byte)m_serial->read();
						}

						virtual int peek(){
							USBSerialPortLog(pankey_Log_StartMethod, "peek", "");
							USBSerialPortLog(pankey_Log_EndMethod, "peek", "");
							return m_serial->peek();
						}

						virtual pankey::Memory::Allocator::memory_size write(Byte a_byte){
							USBSerialPortLog(pankey_Log_StartMethod, "write", "");
							USBSerialPortLog(pankey_Log_EndMethod, "write", "");
							return m_serial->write((int)a_byte);
						}
						
						virtual pankey::Memory::Allocator::memory_size print(const pankey::Type::Array::ByteArray& a_message){
							USBSerialPortLog(pankey_Log_StartMethod, "print", "");
							pankey::Memory::Allocator::memory_size i_size = 0;
							for(int x = 0; x < a_message.length(); x++){
								i_size += m_serial->write(a_message.get(x));
							}
							USBSerialPortLog(pankey_Log_EndMethod, "print", "");
							return i_size;
						}
						
						virtual pankey::Memory::Allocator::memory_size println(const pankey::Type::Array::ByteArray& a_message){
							USBSerialPortLog(pankey_Log_StartMethod, "println", "");
							pankey::Memory::Allocator::memory_size i_size = 0;
							for(int x = 0; x < a_message.length(); x++){
								i_size += m_serial->write(a_message.get(x));
							}
							m_serial->println();
							USBSerialPortLog(pankey_Log_EndMethod, "println", "");
							return i_size;
						}

						virtual bool connected(){
							USBSerialPortLog(pankey_Log_StartMethod, "connected", "");
							USBSerialPortLog(pankey_Log_EndMethod, "connected", "");
							return true;
						}
						
						virtual bool connect(const pankey::Type::Array::ByteArray& a_ip){
							USBSerialPortLog(pankey_Log_StartMethod, "connect", "");
							USBSerialPortLog(pankey_Log_EndMethod, "connect", "");
							return connect(a_ip, -1);
						}
						
						virtual bool connect(const pankey::Type::Array::ByteArray& a_ip, int port){
							USBSerialPortLog(pankey_Log_StartMethod, "connect", "");
							USBSerialPortLog(pankey_Log_EndMethod, "connect", "");
							return false;
						}

						virtual void flush(){
							USBSerialPortLog(pankey_Log_StartMethod, "flush", "");
							m_serial->flush();
							USBSerialPortLog(pankey_Log_EndMethod, "flush", "");
						}

						virtual void operator=(const USBSerialPort& a_serialport){
							m_serial = a_serialport.m_serial;
						}

						virtual bool operator==(const USBSerialPort& a_serialport){
							return m_serial == a_serialport.m_serial;
						}

						virtual bool operator!=(const USBSerialPort& a_serialport){
							return m_serial != a_serialport.m_serial;
						}

						virtual operator bool(){
							return true;
						}

					protected:
						Stream* m_serial;
				};

			}

		}

	}

}