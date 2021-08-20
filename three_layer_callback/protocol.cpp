#include "protocol.h"
#include "role.h"
#include <list>


CmdMsg::CmdMsg(){}
CmdMsg::~CmdMsg(){}


CmdParseProtocol CmdParseProtocol::m_instance;
CmdParseProtocol::CmdParseProtocol(){}
CmdParseProtocol::~CmdParseProtocol(){}


UserData *CmdParseProtocol::raw2request(std::string _szInput){
    CmdMsg *pout = new CmdMsg();
    if ("exit" == _szInput){
        pout->is_frame_exit == true;
    }
    if("close" == _szInput){
        pout->output_open == false;
    }
    if("open" == _szInput){
        pout->output_open == true;
    }

    pout->echo_string = _szInput;
    return pout;
} 

std::string *CmdParseProtocol::response2raw(UserData &_oUserData){
    GET_REF2DATA(CmdMsg, output, _oUserData);
    return new std::string(output.echo_string);
} 

Irole *CmdParseProtocol::GetMsgProcessor(UserDataMsg &_oUserDataMsg){
    szInputChannelInfo = _oUserDataMsg.szInfo;
    GET_REF2DATA(CmdMsg, output, *_oUserDataMsg.poUserData);
    std::list<Irole*> role_list = ZinxKernel::Zinx_GetAllRole();
    if(output.echo_string == "exit")
    {   
        /*过滤exit_framework对象*/
        for (auto role : role_list)
        {
            if(NULL != dynamic_cast<ExitFrameworkRole *>(role))
            {
                return role;
            }
        }
    }

    if(output.echo_string == "open"||output.echo_string == "close")
    {
        /*过滤output_mng_role对象*/
		for (auto role : role_list)
		{
			if (NULL != dynamic_cast<OutputMngRole *>(role))
			{
				return role;
			}
		}
    }

    /*过滤echo_role对象*/
	for (auto role : role_list)
	{
		if (NULL != dynamic_cast<EchoRole *>(role))
		{
			return role;
		}
	}

    return nullptr;
} 

Ichannel *CmdParseProtocol::GetMsgSender(BytesMsg &_oBytes){
    if(szInputChannelInfo == "stdin_channel"){
        return ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
    }

    return ZinxKernel::Zinx_GetChannel_ByInfo(szInputChannelInfo);

} 

