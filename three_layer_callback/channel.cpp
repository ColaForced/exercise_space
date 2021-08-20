#include "channel.h"
#include <iostream>
#include <sys/timerfd.h>

using namespace std;

/* details for class StdInChannel */

StdInChannel::StdInChannel(){}
StdInChannel::~StdInChannel(){}

bool StdInChannel::Init(){
    return true;
}

bool StdInChannel::ReadFd(std::string & _input){
    cin>>_input;
    return true;
}

bool StdInChannel::WriteFd(std::string & _output){
    return false;
}

void StdInChannel::Fini(){}

int StdInChannel::GetFd(){
    return 0;
}

std::string StdInChannel::GetChannelInfo(){
    return "stdin channel";
}

AZinxHandler * StdInChannel::GetInputNextStage(BytesMsg & _oInput){
    // 待实现

}



/* details for class StdOutChannel */

StdOutChannel::StdOutChannel(){}
StdOutChannel::~StdOutChannel(){}

bool StdOutChannel::Init(){
    return true;
}

bool StdOutChannel::ReadFd(std::string & _input){
    return false;
}

bool StdOutChannel::WriteFd(std::string & _output){
    cout<<_output<<endl;
    return true;
}

void StdOutChannel::Fini(){}

int StdOutChannel::GetFd(){
    return 1;
}

std::string StdOutChannel::GetChannelInfo(){
    return "stdout channel";
}

AZinxHandler * StdOutChannel::GetInputNextStage(BytesMsg & _oInput){
    return nullptr;
}



/* details for class TimerChannel */
TimerChannel::TimerChannel(){}
TimerChannel::~TimerChannel(){}

bool TimerChannel::Init() {
    bool bRet = false;
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(fd >= 0)
    {
        m_fd = fd;
        struct itimerspec period = { {1,0}, {0,1}};
        if(0 == timerfd_settime(m_fd, 0, &period, NULL))
        {
            bRet = true;
        }
        else
        {
            close(m_fd);
            m_fd = -1;
        }
    }
    return bRet;
}

bool TimerChannel::ReadFd(std::string & _input) {
    bool bRet = false;
    char buff[8];
    if(sizeof(buff) == read(m_fd, buff, sizeof(buff)))
    {
        _input.append(buff,sizeof(buff));
        bRet = true;
    }
    return bRet;
}

bool TimerChannel::WriteFd(std::string & _output) {
    return false;
}

void TimerChannel::Fini() {
    if(m_fd >= 0) close(m_fd);
}

int TimerChannel::GetFd() {
    return m_fd;
}

std::string TimerChannel::GetChannelInfo() {
    return "timerfd" + m_fd;
}

AZinxHandler* TimerChannel::GetInputNextStage(BytesMsg & _oInput) {
    return TimeOutDeliever::get_instance(); 
}






TimeOutDeliever::TimeOutDeliever(){
    for(int i=0; i<10; i++)
    {
        std::list<TimeOutTask*> tmp;
        m_wheel.push_back(tmp);
    }
}

TimeOutDeliever::~TimeOutDeliever(){}

TimeOutDeliever* TimeOutDeliever::m_single = NULL;

TimeOutDeliever *TimeOutDeliever::get_instance(){
    if(m_single==NULL)
    {
        m_single = new TimeOutDeliever();
    }
    return m_single;
}

IZinxMsg * TimeOutDeliever::InternelHandle(IZinxMsg & _oInput){
    GET_REF2DATA(BytesMsg, timeout_count, _oInput);

	/*强转8个字节的首地址无符号整数的指针*/
	unsigned long *pcont = (unsigned long *)timeout_count.szData.data();

	for (int i = 0; i < *pcont; i++)
	{
		std::list<TimeOutTask *> tmp_list;
		/*遍历当前刻度所对应的list，减计数1*/
		for (auto itr = m_wheel[cur_pos].begin(); itr != m_wheel[cur_pos].end(); )
		{
			/*若计数减为0了，则要调用处理函数，重置计数*/
			if ((*itr)->m_count <= 0)
			{
				/*超时了，暂存本次超时的任务节点*/
				tmp_list.push_back((*itr));
				/*要摘掉,后边重新添加*/
				itr = m_wheel[cur_pos].erase(itr);
				
			}
			else
			{
				/*减计数*/
				(*itr)->m_count--;
				itr++;
			}
		}
		/*调用超时任务的处理函数，重新添加超时任务到时间轮*/
		for (auto ptask : tmp_list)
		{
			ptask->proc_timeout();
			register_task(ptask->time_out, ptask);
		}
		/*刻度向后移动一格*/
		cur_pos++;
		cur_pos %= m_wheel.size();
		/*循环超时次数次*/
	}	

	/*没有下一个环节*/
	return nullptr;
}

AZinxHandler * TimeOutDeliever::GetNextHandler(IZinxMsg & _oNextMsg){
    return nullptr;
}

/*提供任务队列的添加删除函数*/
void TimeOutDeliever::register_task(int _sec, TimeOutTask *_task){
    /*计算任务所在格子*/
	int dest_grid = _sec % m_wheel.size() + cur_pos;
	dest_grid %= m_wheel.size();
	/*计算剩余计数*/
	_task->m_count = _sec / m_wheel.size();
	_task->time_out = _sec;

	/*添加参数_task对象到对应格子的list里*/
	m_wheel[dest_grid].push_back(_task);
}


void TimeOutDeliever::unregister_task(TimeOutTask *_task){
    /*遍历所有刻度*/
	for (auto &grid : m_wheel)
	{
		bool find = false;
		/*遍历该刻度对应的list---》删除*/
		for (auto ptask : grid)
		{
			if (ptask == _task)
			{
				grid.remove(_task);
				find = true;
				break;
			}
		}
		if (true == find)
		{
			break;
		}
	}
}



