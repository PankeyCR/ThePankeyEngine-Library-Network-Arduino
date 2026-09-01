
#ifndef ArduinoNetworkCommands_hpp
	#define ArduinoNetworkCommands_hpp

	#include "ByteArray.hpp"
	#include "ArrayPointerHelper.hpp"
	#include "CharArrayHelper.hpp"

	#if defined(pankey_Log) && (defined(ArduinoNetworkCommands_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoIO_Log))
		#include "Logger_status.hpp"
		#define ArduinoNetworkCommandsLog(status,method,mns) pankey_Log(status,"ArduinoNetworkCommands",method,mns)
	#else
		#define ArduinoNetworkCommandsLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoIO{

			template<class A>
			void ArduinoNetworkCommands(A& a_app, const Base::ByteArray& a_ip, int a_port, const Base::ByteArray& a_message){
				CharArray i_ip = getIP(a_ip);
				CharArray i_message = toCharArray(a_message);
				println(i_ip);
				Serial.println(a_port);
				println(i_message);
				auto i_split = split(i_message, ' ');
				
				if(i_split.length() == 1){
					CharArray i_command_1 = i_split.get(0);
					println(i_command_1);
				}
				
				if(i_split.length() == 2){
					CharArray i_command_1 = i_split.get(0);
					CharArray i_command_2 = i_split.get(1);
					println(i_command_1);
					println(i_command_2);
				}
			}

		}

	}

#endif