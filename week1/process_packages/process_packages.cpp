#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here
        Response response(false, -1);
        if (finish_time_.empty() && size_ > 0){
            response.dropped = false;
            response.start_time = request.arrival_time;
            finish_time_.push(request.arrival_time + request.process_time);
            //std::cout << "Buffer (queue of finish_time_) is empty, push new process in queue and process it intermediately" << std::endl;
            return response;
        }
        else {
            if (request.arrival_time >= finish_time_.front()){
                response.dropped = false;
                if (request.arrival_time <= finish_time_.back()){
                    response.start_time = finish_time_.back();
                    finish_time_.push(finish_time_.back() + request.process_time);
                    //std::cout << "arrival_time of request is latter than finish_time of first process in queue. But early than last process in queue" << std::endl;                    
                }
                else{
                    response.start_time = request.arrival_time;
                    //std::cout << "arrival_time of request is latter than finish_time of first process in queue. and latter than last process in queue" << std::endl;
                    finish_time_.push(request.arrival_time + request.process_time);
                }
                //finish_time_.push(finish_time_.back() + request.process_time);
                finish_time_.pop();
                return response;
           }
            else {
                if (finish_time_.size() < size_){
                    response.dropped = false;
                    response.start_time = finish_time_.back();
                    finish_time_.push(finish_time_.back() + request.process_time);
                    //std::cout << "arrival_time of request is early than finish_time of first process in queue. But there is still space in buffer, message will not be dropped" << std::endl;
                    return response;
                }
                else {
                    response.dropped = true;
                    //std::cout << "arrival_time of request is early than finish_first of last process in queue. And there is no space in buffer, message will be dropped" << std::endl;
                    return response;
                }
            }
        }
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
