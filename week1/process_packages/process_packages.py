# python3

from collections import namedtuple

Request = namedtuple("Request", ["arrived_at", "time_to_process"])
Response = namedtuple("Response", ["was_dropped", "started_at"])


class Buffer:
    def __init__(self, size):
        self.size = size
        self.finish_time = []

    def process(self, request):
        # write your code here
        if len(self.finish_time) == 0:
            self.finish_time.append(request.arrived_at + request.time_to_process)
            #print("Buffer (queue of finish_time_) is empty, push new process in queue and process it intermediately")
            return Response(False, request.arrived_at)
        else:
            if request.arrived_at >= self.finish_time[0]:
                finish_time_back = self.finish_time[len(self.finish_time) - 1]
                if request.arrived_at <= finish_time_back:
                    #print("arrival_time of request is latter than finish_time of first process in queue. But early than last process in queue")
                    self.finish_time.append(finish_time_back + request.time_to_process)
                    self.finish_time.pop(0)
                    return Response(False, finish_time_back)
                else:
                    #print("arrival_time of request is latter than finish_time of first process in queue. and latter than last process in queue")
                    self.finish_time.append(request.arrived_at + request.time_to_process)
                    self.finish_time.pop(0)
                    return Response(False, request.arrived_at)
            else:
                if len(self.finish_time) < self.size:
                    finish_time_back = self.finish_time[len(self.finish_time) - 1]
                    #print("arrival_time of request is early than finish_time of first process in queue. But there is still space in buffer, message will not be dropped")
                    self.finish_time.append(finish_time_back + request.time_to_process)
                    return Response(False, finish_time_back)
                else:
                    #print("arrival_time of request is early than finish_time of first process in queue. And there is no space in buffer, message will be dropped")
                    return Response(True, -1)

def process_requests(requests, buffer):
    responses = []
    for request in requests:
        responses.append(buffer.process(request))
    return responses


def main():
    buffer_size, n_requests = map(int, input().split())
    requests = []
    for _ in range(n_requests):
        arrived_at, time_to_process = map(int, input().split())
        requests.append(Request(arrived_at, time_to_process))

    buffer = Buffer(buffer_size)
    responses = process_requests(requests, buffer)

    for response in responses:
        print(response.started_at if not response.was_dropped else -1)


if __name__ == "__main__":
    main()
