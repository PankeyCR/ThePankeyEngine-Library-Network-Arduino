#pragma once

#include <Ethernet.h>
#include <SPI.h>
#include "CharPointer.hpp"
#include "to_CharPointer_String.hpp"
#include "to_CharPointer_Mac.hpp"

#if defined(pankey_Log) && (defined(ETHERNETConnection_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
	#include "Logger_status.hpp"
	#define ETHERNETConnectionLog(status,method,mns) pankey_Log(status,"ETHERNETConnection",method,mns)
#else
	#define ETHERNETConnectionLog(status,method,mns)
#endif

namespace pankey{

	namespace Library{

		namespace Network{

			namespace Arduino{

				struct ETHERNETConnection{

					void connect(IPAddress a_ip, IPAddress a_gateway, IPAddress a_subnet, int CS_pin, byte* mac){
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "IPAddress");
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "a_ip");
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", a_ip);
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "a_gateway");
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", a_gateway);
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "a_subnet");
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", a_subnet);
						
						Ethernet.init(CS_pin);
						Ethernet.begin(mac, a_ip, a_gateway, a_subnet);
						
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "connected");
					}

					void connect(const pankey::Utility::Test::CharPointer& a_ip, const pankey::Utility::Test::CharPointer& a_gateway, const pankey::Utility::Test::CharPointer& a_subnet, const pankey::Utility::Test::CharPointer& a_mac){
						ETHERNETConnectionLog(pankey_Log_StartMethod, "connect", "CharPointer");
						
						IPAddress i_ip;
						i_ip.fromString( pankey::Type::Array::Arduino::toString(a_ip) );
						
						IPAddress i_gateway;
						i_gateway.fromString( pankey::Type::Array::Arduino::toString(a_gateway) );
						
						IPAddress i_subnet;
						i_subnet.fromString( pankey::Type::Array::Arduino::toString(a_subnet) );

						pankey::Type::Array::Mac i_mac = pankey::Type::Array::toMAC(a_mac);
						byte* i_byte_mac = (byte*)i_mac.getArrayPointer();
						
						connect(i_ip, i_gateway, i_subnet, 10, i_byte_mac);
						ETHERNETConnectionLog(pankey_Log_EndMethod, "connect", "");
					}

					void halt_Until_Is_Connected(){
						ETHERNETConnectionLog(pankey_Log_StartMethod, "halt_Until_Is_Connected", "");
						while (Ethernet.linkStatus() != LinkON) {
							ETHERNETConnectionLog(pankey_Log_StartMethod, "halt_Until_Is_Connected", ".");
							// System::sleep(1000);
							delay(1000);
						}
						ETHERNETConnectionLog(pankey_Log_EndMethod, "halt_Until_Is_Connected", "");
					}

					void halt_Until_Is_Connected(float a_time){
						ETHERNETConnectionLog(pankey_Log_StartMethod, "halt_Until_Is_Connected", "");
						long i_time_limit = 1000 * a_time;
						long i_start_time = millis();
						while ((millis() - i_start_time) < i_time_limit) {
							ETHERNETConnectionLog(pankey_Log_StartMethod, "halt_Until_Is_Connected", ".");
							// Watchdog::feed();
							if(Ethernet.linkStatus() != LinkON){
								return;
							}
						}
						ETHERNETConnectionLog(pankey_Log_EndMethod, "halt_Until_Is_Connected", "");
					}


					bool hasEthernetLAN(){
						return Ethernet.linkStatus() == LinkON;
					}

				};

			}

		}

	}

}
