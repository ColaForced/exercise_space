#pragma once
#include <ZinxTCP.h>

class MyTcpData:public ZinxTcpData
{
public:
    MyTcpData(int _fd);
    virtual ~MyTcpData();
    virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};


class MyTcpConnectFact:public IZinxTcpConnFact
{
    virtual ZinxTcpData *CreateTcpDataChannel(int _fd) override;
};