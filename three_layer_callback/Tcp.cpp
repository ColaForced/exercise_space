#include "Tcp.h"
#include "protocol.h"


MyTcpData::MyTcpData(int _fd):ZinxTcpData(_fd){}

MyTcpData::~MyTcpData(){}

AZinxHandler*MyTcpData:: GetInputNextStage(BytesMsg & _oInput){
    return CmdParseProtocol::get_instance();
}


ZinxTcpData *MyTcpConnectFact::CreateTcpDataChannel(int _fd){
    return new MyTcpData(_fd);
}
