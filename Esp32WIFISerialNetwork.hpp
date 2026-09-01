
#ifndef Esp32WIFISerialNetwork_hpp
	#define Esp32WIFISerialNetwork_hpp

	#include "SerialNetwork.hpp"
	#include "NewLinePortProtocol.hpp"
	#include "Esp32WIFISerialServer.hpp"
	#include "ArrayRawPointerMap.hpp"
	#include "ArrayRawPointerList.hpp"

	#if defined(pankey_Log) && (defined(Esp32WIFISerialNetwork_Log) || defined(pankey_Global_Log) || defined(pankey_Network_Log))
		#include "Logger_status.hpp"
		#define Esp32WIFISerialNetworkLog(status,method,mns) pankey_Log(status,"Esp32WIFISerialNetwork",method,mns)
	#else
		#define Esp32WIFISerialNetworkLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoNetwork{

			template<class P, class A, class... Args>
			class Esp32WIFISerialNetwork : public Network::SerialNetwork<A,Args...>{	
				public:	
					Esp32WIFISerialNetwork(){
						m_diconnection.setOwner(false);
					}
					virtual ~Esp32WIFISerialNetwork(){}
					
					virtual void instantSend(const Base::ByteArray& a_message){
						for(int x = 0; x < m_ports.length(); x++){
							auto f_port = m_ports.getKeyPointerByIndex(x);
							auto f_protocol = m_ports.getValuePointerByIndex(x);
							if(f_port == nullptr || f_protocol == nullptr){
								continue;
							}
							f_protocol->InstantBroadcastMessage(*f_port, a_message);
						}
					}

					virtual void instantSend(const Base::ByteArray& a_ip, const Base::ByteArray& a_message){
						for(int x = 0; x < m_ports.length(); x++){
							auto f_port = m_ports.getKeyPointerByIndex(x);
							auto f_protocol = m_ports.getValuePointerByIndex(x);
							if(f_port == nullptr || f_protocol == nullptr){
								continue;
							}
							if(f_port->getIP() != a_ip){
								continue;
							}
							f_protocol->InstantPrivateMessage(*f_port, a_message);
						}
					}
					
					virtual bool isConnected(const Base::ByteArray& a_ip){return false;}
				
					virtual void connect() {}
					
					virtual void connect(const Base::ByteArray& a_ip) {}
						
					virtual void disconect() {}
					
					virtual void disconect(const Base::ByteArray& a_ip) {}
					
					virtual bool ping(const Base::ByteArray& a_ip){
						return false;
					}

					virtual long getType()const{
						Esp32WIFISerialNetworkLog(pankey_Log_StartMethod, "getType", "");
						Esp32WIFISerialNetworkLog(pankey_Log_EndMethod, "getType", "");
						return Base::ClassType<Esp32WIFISerialNetwork<P,A,Args...>>::getId();
					}

					virtual bool istype(long a_type)const{
						Esp32WIFISerialNetworkLog(pankey_Log_StartMethod, "istype", "");
						Esp32WIFISerialNetworkLog(pankey_Log_EndMethod, "istype", "");
						return Network::SerialNetwork<A,Args...>::istype(a_type) || Base::ClassType<Esp32WIFISerialNetwork<P,A,Args...>>::getId() == a_type;
					}

					virtual void initializeState(A& app){
						m_server.begin();
					}

					virtual void updateState(A& a_app, Args... a_values){
						auto i_port = m_server.accept();
						if(i_port != nullptr){
							m_ports.addPointers(i_port.get(), new P());
							i_port.release();
						}
						for(int x = 0; x < m_ports.length(); x++){
							auto f_port = m_ports.getKeyPointerByIndex(x);
							auto f_protocol = m_ports.getValuePointerByIndex(x);
							if(f_port == nullptr || f_protocol == nullptr){
								continue;
							}
							if(!f_port->connected()){
								m_diconnection.addPointer(f_port);
								continue;
							}
							if(f_port->available() > 0){
								Base::ByteArray f_read = f_protocol->Read(*f_port);
								if(f_read.isEmpty()){
									continue;
								}
								this->DeliverMessage(a_app, f_port->getIP(), f_read);
							}
							this->SendMessages(*f_port, *f_protocol);
						}
						if(!m_diconnection.isEmpty()){
							for(int x = 0; x < m_diconnection.length(); x++){
								auto f_port = m_diconnection.getPointerByIndex(x);
								m_ports.destroyByKeyPointer(f_port);
							}
							m_diconnection.reset();
						}
					}
					
				protected:
					Esp32WIFISerialServer m_server;
					Base::ArrayRawPointerMap<Network::SerialPort,Network::PortProtocol> m_ports;
					Base::ArrayRawPointerList<Network::SerialPort> m_diconnection;
					
			};

		}

	}

#endif