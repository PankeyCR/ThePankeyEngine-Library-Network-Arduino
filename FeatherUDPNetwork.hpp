
#ifndef UDPNetwork_hpp
#define UDPNetwork_hpp
#define UDPNetwork_AVAILABLE

#include "MessageCommand.hpp"
#include "SerialListenerState.hpp"
#include "AppState.hpp"
#include "Message.hpp"
#include "PrimitiveMap.hpp"
#include "Pair.hpp"
#include <EthernetUdp.h>

#ifdef UDPNetwork_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define UDPNetworkLog(location,method,type,mns) ame_Log(this,location,"UDPNetwork",method,type,mns)
#else
	#ifdef UDPNetwork_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define UDPNetworkLog(location,method,type,mns) ame_LogDebug(this,location,"UDPNetwork",method,type)
	#else
		#define UDPNetworkLog(location,method,type,mns) 
	#endif
#endif

namespace sgsv{

using namespace ame;

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_BaseAppState
*/
class UDPNetwork : public AppState{	
    public:	
		UDPNetwork(){}
		UDPNetwork(int c_port) : m_port(c_port){}
		UDPNetwork(int c_port, SerialListenerState<sgsv::MessageCommand>* l) : m_port(c_port){listenerState = l;}
		virtual ~UDPNetwork(){}

		virtual void setPort(int a_port){
			m_port = a_port;
		}

		virtual int getPort(){
			return m_port;
		}

		virtual void udpSend(IPAddress a_ip, int a_port, Note a_message){
			// a_message.copyToExternPointer(m_send, ' ', UDP_TX_PACKET_MAX_SIZE);
			Udp.beginPacket(a_ip, a_port);
			// Udp.write(m_send, UDP_TX_PACKET_MAX_SIZE);
			char ReplyBuffer[] = "acknowledged";
			// Udp.write(ReplyBuffer);
			Udp.print(a_message);
			Udp.endPacket();
		}
		
		virtual void instantSend(Note a_message){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Note* f_note = m_ports.getKeyByPosition(x);
				Pair<IPAddress,int>* f_pair = m_ports.getByPosition(x);
				if(f_note == nullptr || f_pair == nullptr){
					continue;
				}
				if(f_pair->key == nullptr || f_pair->value == nullptr){
					continue;
				}
				IPAddress f_ip = *f_pair->key;
				int f_port = *f_pair->value;
				this->udpSend(f_ip, f_port, a_message);
			}
		}
		
		virtual void instantSend(ByteArray a_message){}

		virtual void instantSend(Note a_name, Note a_message){
			Pair<IPAddress,int>* i_pair = m_ports.getByLValue(a_name);
			if(i_pair->key == nullptr || i_pair->value == nullptr){
				return;
			}
			IPAddress i_ip = *i_pair->key;
			int i_port = *i_pair->value;
			this->udpSend(i_ip, i_port, a_message);
		}

		virtual void instantSend(Note a_name, ByteArray a_message){}
		
		virtual void send(Note a_message){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Note* f_note = m_ports.getKeyByPosition(x);
				Pair<IPAddress,int>* f_pair = m_ports.getByPosition(x);
				if(f_note == nullptr || f_pair == nullptr){
					continue;
				}
				if(f_pair->key == nullptr || f_pair->value == nullptr){
					continue;
				}
				IPAddress f_ip = *f_pair->key;
				int f_port = *f_pair->value;
				this->udpSend(f_ip, f_port, a_message);
			}
		}
		
		virtual void send(ByteArray a_message){}

		virtual void send(Note a_name, Note a_message){
			Pair<IPAddress,int>* i_pair = m_ports.getByLValue(a_name);
			if(i_pair->key == nullptr || i_pair->value == nullptr){
				return;
			}
			IPAddress i_ip = *i_pair->key;
			int i_port = *i_pair->value;
			this->udpSend(i_ip, i_port, a_message);
		}

		virtual void send(Note a_name, ByteArray a_message){}
		
		virtual bool isConnected(Note a_name){return false;}
    
		virtual void connect() {}
		
		virtual void connect(Note a_name) {}
		    
		virtual void disconect() {}
		
		virtual void disconect(Note a_name) {}
		
		virtual bool ping(Note a_name){
			return false;
		}
		
		virtual void initialize(Application *app){
			UDPNetworkLog(ame_Log_StartMethod, "initializeState", "println", "");
			UDPNetworkLog(ame_Log_Statement, "initializeState", "println", "Port:");
			UDPNetworkLog(ame_Log_Statement, "initializeState", "println", m_port);
			Serial.println("udp initialize");
			Udp.begin(m_port);
			UDPNetworkLog(ame_Log_EndMethod, "initializeState", "println", "");
		}
		
		virtual void update(float tpc){
			//UDPNetworkLog(ame_Log_StartMethod, "updateState", "println", "");
			if(listenerState == nullptr){
				//Serial.println("listenerState == nullptr");
				return;
			}
			int packetSize = Udp.parsePacket();
			if (packetSize) {
				//Serial.println("udp packetSize");
				UDPNetworkLog(ame_Log_Statement, "updateState", "println", "packetSize");
				UDPNetworkLog(ame_Log_Statement, "updateState", "println", packetSize);
				IPAddress i_remote = Udp.remoteIP();
				int i_port = Udp.remotePort();
				int i_id = this->getPortId(i_remote);
				// if(i_id == -1){
				// 	Serial.println("udp i_id == -1");
				// 	Serial.println(i_remote);
				// 	UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "i_id == -1");
				// 	return;
				// }
				// Udp.read(m_read, UDP_TX_PACKET_MAX_SIZE);
				// Note i_text;
				// i_text.addLocalArrayPointer(m_read, UDP_TX_PACKET_MAX_SIZE);

				//Serial.println("udp Message");
				Note i_text;
				while(Udp.available() > 0){
					i_text += (char)Udp.read();
				}
				//Serial.println(i_text);
				if(i_text.charAt(i_text.length() - 1) == '\n'){
					i_text = i_text.substring(0,i_text.length() - 1);
				}

				sgsv::MessageCommand* i_message = new sgsv::MessageCommand();
				int i_size = getSplitSize(i_text, ' ');
				//Serial.println(i_size);
				if(i_size >= 1){
					Note i_t = split(i_text, 0, ' ');
					//Serial.println(i_t);
					i_message->addMessage(i_t);
				}
				if(i_size >= 2){
					Note i_t = split(i_text, 1, ' ');
					//Serial.println(i_t);
					i_message->addMessage(i_t);
				}
				if(i_size >= 3){
					Note i_t = split(i_text, 2, ' ');
					//Serial.println(i_t);
					i_message->addMessage(i_t);
				}
				if(i_size >= 4){
					Note i_t = split(i_text, 3, ' ');
					//Serial.println(i_t);
					i_message->addMessage(i_t);
				}
				
				i_message->setId(i_id);
				listenerState->addMail(i_message);
				//Serial.println("udp listener enviando mensaje");
				UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "packetSize");
			}
			//UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "");
		}

		virtual void addPort(const Note& a_name, IPAddress a_ip, int a_port){
			m_ports.addPointer(a_name, new Pair<IPAddress,int>(new IPAddress(a_ip), new int(a_port), true));
		}

		virtual void removePort(const Note& a_name, IPAddress a_ip, int a_port){
			m_ports.removeByLValue(a_name);
		}

		virtual int getPortId(IPAddress a_ip){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Pair<IPAddress,int>* f_pair = m_ports.getByPosition(x);
				if(f_pair == nullptr){
					continue;
				}
				if(f_pair->key == nullptr || f_pair->value == nullptr){
					continue;
				}
				IPAddress f_ip = *f_pair->key;
				if(f_ip == a_ip){
					return x;
				}
			}
			return -1;
		}

		virtual int getPortId(IPAddress a_ip, int a_port){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Pair<IPAddress,int>* f_pair = m_ports.getByPosition(x);
				if(f_pair == nullptr){
					continue;
				}
				if(f_pair->key == nullptr || f_pair->value == nullptr){
					continue;
				}
				IPAddress f_ip = *f_pair->key;
				int f_port = *f_pair->value;
				if(f_ip == a_ip && f_port == a_port){
					return x;
				}
			}
			return -1;
		}
		
	protected:
		unsigned int m_port = 101;
		char m_read[UDP_TX_PACKET_MAX_SIZE];
		char m_send[UDP_TX_PACKET_MAX_SIZE];

		EthernetUDP Udp;

		PrimitiveMap<Note,Pair<IPAddress,int>> m_ports;

		SerialListenerState<sgsv::MessageCommand>* listenerState = nullptr;
};

}

#endif