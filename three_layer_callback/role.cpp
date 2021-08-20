#include "role.h"
#include "channel.h"
#include "protocol.h"


/* details for class EchoRole */
EchoRole::EchoRole(){}
EchoRole::~EchoRole(){}
void EchoRole::Fini(){}
bool EchoRole::Init(){return true; }

UserData * EchoRole::ProcMsg(UserData &_poUserData){
    GET_REF2DATA(CmdMsg, input, _poUserData);
    std::string echo_string = input.echo_string;
    CmdMsg *pout = new CmdMsg();
    pout->echo_string = echo_string;
    ZinxKernel::Zinx_SendOut(*pout, *(CmdParseProtocol::get_instance()));
    return nullptr;
}


/* details for class ExitFrameworkRole */
bool ExitFrameworkRole::Init() { return true;}
void ExitFrameworkRole::Fini() {}

UserData *ExitFrameworkRole::ProcMsg(UserData &_poUserData) {
    GET_REF2DATA(CmdMsg, cmd, _poUserData);
    if(cmd.is_frame_exit){
        ZinxKernel::Zinx_Exit();
    }
    return nullptr;
}


/* details for class OutputMngRole */
bool OutputMngRole::Init() { return true;}
void OutputMngRole::Fini() {}

UserData *OutputMngRole::ProcMsg(UserData &_poUserData) {
    GET_REF2DATA(CmdMsg, cmd, _poUserData);
    
    if(NULL == m_channel)
    {
        m_channel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
    }

    if(cmd.output_open == true)
    {
        ZinxKernel::Zinx_Add_Channel(*m_channel);
    }
    else
    {
        ZinxKernel::Zinx_Del_Channel(*m_channel);
    }
}

