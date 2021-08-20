#include <zinx.h>
#include <string>


class CmdMsg: public UserData
{
public:
    CmdMsg();
    virtual ~CmdMsg();
	bool is_frame_exit = false;
	bool output_open = true;
	std::string echo_string;
};



class CmdParseProtocol:public Iprotocol
{
private:
    CmdParseProtocol();
    static CmdParseProtocol m_instance;
    std::string szInputChannelInfo;

public:
    static CmdParseProtocol *get_instance(){return &m_instance;}
    virtual ~CmdParseProtocol();

    virtual UserData *raw2request(std::string _szInput) override;
    virtual std::string *response2raw(UserData &_oUserData) override;
    virtual Irole *GetMsgProcessor(UserDataMsg &_oUserDataMsg) override;
    virtual Ichannel *GetMsgSender(BytesMsg &_oBytes) override;
};
