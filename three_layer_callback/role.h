#include <zinx.h>
#include <vector>
#include <list>


class EchoRole:public Irole
{
public:
    EchoRole();
    virtual ~EchoRole();

	virtual bool Init() override;
	virtual UserData *ProcMsg(UserData &_poUserData) override;
	virtual void Fini() override;
};


class ExitFrameworkRole:public Irole
{
	virtual bool Init() override;
	virtual UserData *ProcMsg(UserData &_poUserData) override;
	virtual void Fini() override;
};


class OutputMngRole:public Irole
{
    Ichannel *m_channel = NULL;
	virtual bool Init() override;
	virtual UserData *ProcMsg(UserData &_poUserData) override;
	virtual void Fini() override;
};




