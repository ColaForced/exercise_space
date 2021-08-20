#include "zinx.h"
#include <string>
#include <vector>


class StdInChannel:public Ichannel
{
    public:
        StdInChannel();
        virtual ~StdInChannel();
	
        virtual bool Init() override;
        virtual bool ReadFd(std::string & _input) override;
        virtual bool WriteFd(std::string & _output) override;
        virtual void Fini() override;
        virtual int GetFd() override;
        virtual std::string GetChannelInfo() override;
        virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};


class StdOutChannel:public Ichannel
{
    public:
        StdOutChannel();
        ~StdOutChannel();
    
        virtual bool Init() override;
        virtual bool ReadFd(std::string & _input) override;
        virtual bool WriteFd(std::string & _output) override;
        virtual void Fini() override;
        virtual int GetFd() override;
        virtual std::string GetChannelInfo() override;
        virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};


class TimerChannel:public Ichannel
{
private:
    int m_fd = -1;

public:
    TimerChannel();
	virtual ~TimerChannel();
    virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};


class TimeOutTask {
public:
	virtual void proc_timeout() = 0;
	int m_count = 0;
	int time_out = 0;
};


class TimeOutDeliever:public AZinxHandler
{
private:
    TimeOutDeliever();
    virtual ~TimeOutDeliever();
    static TimeOutDeliever *m_single;

    std::vector<std::list<TimeOutTask *> > m_wheel;
    int cur_pos = 0;

public:
    static TimeOutDeliever *get_instance();
    virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;

	/*提供任务队列的添加删除函数*/
	void register_task(int _sec, TimeOutTask *_task);
	void unregister_task(TimeOutTask *_task);

};



