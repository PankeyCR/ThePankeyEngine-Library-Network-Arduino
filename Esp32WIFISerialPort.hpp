
#ifndef Esp32WIFISerialPort_hpp
	#define Esp32WIFISerialPort_hpp

	#include "arduinoByteArrayHelper.hpp"
	#include "arduinoStringHelper.hpp"
	#include "ArduinoMemorySize.hpp"
	#include "IPAddress.h"
	#include "SerialPort.hpp"
	#include "WiFi.h"

	#if defined(pankey_Log) && (defined(Esp32WIFISerialPortn_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
		#include "Logger_status.hpp"
		#define Esp32WIFISerialPortLog(status,method,mns) pankey_Log(status,"Esp32WIFISerialPort",method,mns)
	#else
		#define Esp32WIFISerialPortLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoNetwork{

			class Esp32WIFISerialPort : public Network::SerialPort{	
				public:
					Esp32WIFISerialPort(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Esp32WIFISerialPort(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Destructor", "");
						if(this->connected()){
							this->stop();
						}
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					Esp32WIFISerialPort(const Esp32WIFISerialPort& a_serialport){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
						m_client = a_serialport.m_client;
						m_ip = a_serialport.m_ip;
						m_port = a_serialport.m_port;
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Esp32WIFISerialPort(WiFiClient a_client){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
						m_client = a_client;
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					// virtual Base::ByteArray getIP(){return pankey::getByteArrayIP(m_client.remoteIP());}

					virtual int status(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "status", "");
						// return m_client.status();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "status", "");
						return 0;
					}

					virtual int available(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "available", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "available", "");
						return m_client.available();
					}

					virtual Byte read(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "read", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "read", "");
						return (Byte)m_client.read();
					}

					virtual int peek(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "peek", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "peek", "");
						return m_client.peek();
					}

					virtual Base::memory_size write(Byte a_byte){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "write", chr);
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "write", "");
						return m_client.write((int)a_byte);
					}
					
					virtual Base::memory_size print(const Base::ByteArray& a_message){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "print", "");
						Base::memory_size i_size = 0;
						for(int x = 0; x < a_message.length(); x++){
							i_size += m_client.write(a_message.get(x));
						}
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "print", "");
						return i_size;
					}
					
					virtual Base::memory_size println(const Base::ByteArray& a_message){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "println", "");
						Base::memory_size i_size = 0;
						for(int x = 0; x < a_message.length(); x++){
							i_size += m_client.write(a_message.get(x));
						}
						m_client.println();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "println", "");
						return i_size;
					}

					virtual bool connected(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connected", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connected", "");
						return m_client.connected();
					}
					
					virtual bool connect(const Base::ByteArray& a_ip){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connect", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connect", "");
						return connect(a_ip, -1);
					}
					
					virtual bool connect(const Base::ByteArray& a_ip, int port){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connect", "");
						
						IPAddress i_ip;
						if(a_ip.length() == 4){
							i_ip = IPAddress(a_ip.get(0), a_ip.get(1), a_ip.get(2), a_ip.get(3));
						}
						
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connect", "");
						return m_client.connect(i_ip, port);
					}
					
					virtual void stop(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "stop", "");
						m_client.stop();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "stop", "");
					}

					virtual void flush(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "flush", "");
						m_client.flush();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "flush", "");
					}

					virtual void operator=(const Esp32WIFISerialPort& a_serialport){
						m_client = a_serialport.m_client;
					}

					virtual bool operator==(const Esp32WIFISerialPort& a_serialport){
						return m_client == a_serialport.m_client;
					}

					virtual bool operator!=(const Esp32WIFISerialPort& a_serialport){
						return m_client != a_serialport.m_client;
					}

					virtual operator bool(){
						return m_client;
					}

				protected:
					WiFiClient m_client;
			};

		}

	}

#endif