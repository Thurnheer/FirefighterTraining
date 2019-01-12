#ifndef PIPE_HPP
#define PIPE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class pipe
{
public:
    class receiving
    {
    public:
        receiving(pipe* that, T& toReceive)
            : that_(that), toReceive_(toReceive)
        {}
        receiving(receiving&& other)
            : that_(other.that_), toReceive_(other.toReceive_)
        {
            other.that_ = nullptr;
        }
        operator bool()
        {
            auto from = that_;
            that_ = nullptr;
            return from && from->try_receveive(toReceive_);
        }
        ~receiving()
        {
            if(that_)
                that_->receive(toReceive_);
        }
    private:
        pipe* that_;
        T& toReceive_;
    };
    void send(T const& t){
        std::lock_guard<std::mutex> guard(m_);
        fifo_.push(t);
        nonEmpty_.notify_all();
    }

    void receive(T& t)
    {
        std::lock_guard<std::mutex> guard(m_);
        nonEmpty_.wait(m_, [this]{
            return !fifo_.empty();
        });
        t = fifo_.front();
        fifo_.pop();
    }

    bool tryReceive(T& t){
        bool received = false;
        if(m_.try_lock())
        {
            std::lock_guard<std::mutex> guard(m_, std::adopt_lock);
            if(!fifo_.empty())
            {
                t = fifo_.front();
                fifo_.pop();
                received = true;
            }
        }
        return received;
    }

    void operator<<(T const& t) {
        send(t);
    }

    receiving operator>>(T& t) {
        return receiving(this, t);
    }

private:
    std::mutex m_;
    std::condition_variable_any nonEmpty_;
    std::queue<T> fifo_;
};

#endif // PIPE_HPP
