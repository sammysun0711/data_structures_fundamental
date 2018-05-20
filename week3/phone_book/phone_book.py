# python3
class Query:
    def __init__(self, query):
        self.procedure = query[0]
        self.number = int(query[1])
        if self.procedure == "add":
            self.name = query[2]

def ReadQueries():
    n = int(input())
    return [Query(input().split()) for i in range(n)]

def ProcessQueries(queries):
    response = []
    contacts = [None for i in range(0, 10000000)]
    for query in queries:
        if query.procedure == "add":
            contacts[query.number] = query
        elif query.procedure == "find":
            if contacts[query.number] != None:
                response.append(contacts[query.number].name)
            else:
                response.append("not found")
        elif query.procedure == "del":
            contacts[query.number] = None
        else:
            print("wrong procedure, please only chosse find, add or del")
    return response

def ReadResponse(response):
    for res in response:
        print(res)

if __name__ == '__main__':
    ReadResponse(ProcessQueries(ReadQueries()))
