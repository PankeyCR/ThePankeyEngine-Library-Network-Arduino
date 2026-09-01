
#ifndef Esp32WIFIConnection_hpp
	#define Esp32WIFIConnection_hpp
	
	#include "ArrayRawList.hpp"

	#include "ArrayPointer.hpp"
	#include "Mac.hpp"
	#include "arduinoStringHelper.hpp"
	#include "WiFi.h"
	#include <esp_wifi.h>

	#if defined(pankey_Log) && (defined(Esp32WIFIConnection_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
		#include "Logger_status.hpp"
		#define Esp32WIFIConnectionLog(status,method,mns) pankey_Log(status,"Esp32WIFIConnection",method,mns)
	#else
		#define Esp32WIFIConnectionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoNetwork{
		
			void initializeWIFI(String a_mac, String a_ip, String a_gateway, String a_subnet, String a_dns, String a_name, String a_pasword){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "initializeWIFI", "");

				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "mac");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_mac);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_dns);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "name");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_name);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "pasword");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", a_pasword);

				Base::Mac i_mac = pankey::toMAC(a_mac);
				IPAddress i_ip = toIPAddress(a_ip);
				IPAddress i_gateway = toIPAddress(a_gateway);
				IPAddress i_subnet = toIPAddress(a_subnet);
				IPAddress i_dns = toIPAddress(a_dns);

				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", i_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", i_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", i_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", i_dns);
				
				WiFi.mode(WIFI_STA);
				WiFi.setSleep(false);
				
				esp_wifi_set_mac(WIFI_IF_STA, i_mac.getArrayPointer());

				if(!WiFi.config(i_ip, i_gateway, i_subnet, i_dns)) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "STA Failed to configure");
				}

				WiFi.begin(a_name.c_str(), a_pasword.c_str());

				if(WiFi.status() == WL_CONNECTED) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "connected");
				}else{
					Esp32WIFIConnectionLog(pankey_Log_Statement, "initializeWIFI", "fail to connect");
				}

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "initializeWIFI", "");
			}

			void configWIFI(String a_mac, String a_ip, String a_gateway, String a_subnet, String a_dns){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "configWIFI", "");

				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "mac");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_mac);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_dns);

				Base::Mac i_mac = pankey::toMAC(a_mac);
				IPAddress i_ip = toIPAddress(a_ip);
				IPAddress i_gateway = toIPAddress(a_gateway);
				IPAddress i_subnet = toIPAddress(a_subnet);
				IPAddress i_dns = toIPAddress(a_dns);

				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_dns);
				
				WiFi.mode(WIFI_STA);
				WiFi.setSleep(false);
				
				esp_wifi_set_mac(WIFI_IF_STA, i_mac.getArrayPointer());

				if(!WiFi.config(i_ip, i_gateway, i_subnet, i_dns)) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "STA Failed to configure");
				}

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "configWIFI", "");
			}

			void configWIFI(String a_mac){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "configWIFI", "");

				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "mac");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_mac);

				Base::Mac i_mac = pankey::toMAC(a_mac);
				
				WiFi.mode(WIFI_STA);
				WiFi.setSleep(false);
				
				esp_wifi_set_mac(WIFI_IF_STA, i_mac.getArrayPointer());

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "configWIFI", "");
			}

			void configWIFI(String a_ip, String a_gateway, String a_subnet, String a_dns){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "configWIFI", "");

				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", a_dns);

				IPAddress i_ip = toIPAddress(a_ip);
				IPAddress i_gateway = toIPAddress(a_gateway);
				IPAddress i_subnet = toIPAddress(a_subnet);
				IPAddress i_dns = toIPAddress(a_dns);

				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "ip");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_ip);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "gateway");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_gateway);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "subnet");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_subnet);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "dns");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", i_dns);

				if(!WiFi.config(i_ip, i_gateway, i_subnet, i_dns)) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "configWIFI", "STA Failed to configure");
				}

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "configWIFI", "");
			}

			void connectWIFI(String  name, String pasword){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "connectWIFI", "");

				Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", "name");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", name);
				Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", "pasword");
				Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", pasword);
					
				WiFi.begin(name.c_str(), pasword.c_str());

				if(WiFi.status() == WL_CONNECTED) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", "connected");
				}else{
					Esp32WIFIConnectionLog(pankey_Log_Statement, "connectWIFI", "fail to connect");
				}

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "connectWIFI", "");
			}

			void disconnectWIFI(){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "disconnectWIFI", "");
					
				WiFi.disconnect();

				if(WiFi.status() != WL_CONNECTED) {
					Esp32WIFIConnectionLog(pankey_Log_Statement, "disconnectWIFI", "disconnected");
				}else{
					Esp32WIFIConnectionLog(pankey_Log_Statement, "disconnectWIFI", "fail to disconnect");
				}

				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "disconnectWIFI", "");
			}

			bool hasWIFIConnection(){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "hasWIFIConnection", "");
				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "hasWIFIConnection", "");
				return WiFi.status() != WL_CONNECTED;
			}

			void haltUntilWIFIConnection(){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIConnection", "");
				while (WiFi.status() != WL_CONNECTED) {
					Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIConnection", ".");
					delay(1000);
				}
				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "haltUntilWIFIConnection", "");
			}

			void haltUntilWIFIConnection(float a_time){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIConnection", "");
				long i_time_limit = 1000 * a_time;
				long i_start_time = millis();
				while ((millis() - i_start_time) < i_time_limit) {
					Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIConnection", ".");
					// Watchdog::feed();
					if(WiFi.status() == WL_CONNECTED){
						return;
					}
				}
				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "haltUntilWIFIConnection", "");
			}

			void haltUntilWIFIDisconnection(){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIDisconnection", "");
				while (WiFi.status() == WL_CONNECTED) {
					Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIDisconnection", ".");
					delay(1000);
				}
				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "haltUntilWIFIDisconnection", "");
			}

			void haltUntilWIFIDisconnection(float a_time){
				Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIDisconnection", "");
				long i_time_limit = 1000 * a_time;
				long i_start_time = millis();
				while ((millis() - i_start_time) < i_time_limit) {
					Esp32WIFIConnectionLog(pankey_Log_StartMethod, "haltUntilWIFIDisconnection", ".");
					// Watchdog::feed();
					if(WiFi.status() != WL_CONNECTED){
						return;
					}
				}
				Esp32WIFIConnectionLog(pankey_Log_EndMethod, "haltUntilWIFIDisconnection", "");
			}

			bool hasWifiLAN(){
				return WiFi.status() == WL_CONNECTED;
			}

			void printWIFI(Stream* port){
				if(port == nullptr){
					return;
				}
				if(WiFi.status() == WL_CONNECTED){
					port->println("WIFI connected");
				}else{
					port->println("WIFI disconnected");
				}
				port->print("WIFI ip: ");
				port->println(WiFi.localIP());
			}

			void WIFICommands(const Base::ArrayRawList<String>& a_commands){

			}

		}

	}

#endif
