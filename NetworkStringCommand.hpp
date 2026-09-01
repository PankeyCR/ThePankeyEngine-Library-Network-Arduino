
#ifndef NetworkStringCommand_hpp
	#define NetworkStringCommand_hpp

	#include "Command.hpp"
	#include "ByteArray.hpp"
	#include "ArrayRawList.hpp"
	#include "invokeRawList.hpp"

	#if defined(pankey_Log) && (defined(NetworkStringCommand_Log) || defined(pankey_Global_Log) || defined(pankey_Network_Log))
		#include "Logger_status.hpp"
		#define NetworkStringCommandLog(status,method,mns) pankey_Log(status,"NetworkStringCommand",method,mns)
	#else
		#define NetworkStringCommandLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoNetwork{

			template<class A>
			class NetworkStringCommand : public Command<A&,const ByteArray&>{
				public:
					NetworkStringCommand(){}
					NetworkStringCommand(char a_split){m_split_char = a_split;}
					virtual ~NetworkStringCommand(){}
					
					void splitChar(char a_split){m_split_char = a_split;}

					virtual void execute(A& a_app, const ByteArray& a_message){
						NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "");
						String i_split;
						Base::ArrayRawList<String> i_command;
						for(int x = 0; x < a_message.length(); x++){
							char f_char = (char)a_message.get(x);
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "iteration:");
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", x);
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "char:");
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", f_char);
							if(f_char == m_split_char){
								NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "adding split command");
								i_command.add(i_split);
								i_split = "";
								continue;
							}
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "adding char");
							i_split += f_char;
						}
						if(i_split != ""){
							NetworkStringCommandLog(pankey_Log_StartMethod, "execute", "last addintion");
							i_command.add(i_split);
						}
						invokeAll<const Base::ArrayRawList<String>&>(m_methods, i_command);
						invokeAll<A&,const Base::ArrayRawList<String>&>(m_app_methods, a_app, i_command);
						NetworkStringCommandLog(pankey_Log_EndMethod, "execute", "");
					}

					virtual void add(InvokeFunction<const ArrayRawList<String>&> a_function){
						NetworkStringCommandLog(pankey_Log_StartMethod, "add", "InvokeFunction<const ArrayRawList<String>&>");
						m_methods.add(a_function);
						NetworkStringCommandLog(pankey_Log_EndMethod, "add", "");
					}

					virtual void add(InvokeFunction<A&,const ArrayRawList<String>&> a_function){
						NetworkStringCommandLog(pankey_Log_StartMethod, "add", "InvokeFunction<A&,const ArrayRawList<String>&>");
						m_app_methods.add(a_function);
						NetworkStringCommandLog(pankey_Log_EndMethod, "add", "");
					}

					virtual long getType()const{
						return ClassType<NetworkStringCommand<A>>::getId();
					}

					virtual bool istype(long a_type)const{
						return Command<A&,const ByteArray&>::istype(a_type) || ClassType<NetworkStringCommand<A>>::getId() == a_type;
					}

				protected:
					char m_split_char = ' ';

					Base::FunctionList<const Base::ArrayRawList<String>&> m_methods;
					Base::FunctionList<A&,const Base::ArrayRawList<String>&> m_app_methods;
			};

		}

	}

#endif