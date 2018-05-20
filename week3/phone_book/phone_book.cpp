#include <iostream>
#include <vector>
#include <string>

struct Query{
    std::string procedure, name;
    int number; 
};

std::vector<Query> readQueries(){
    int n;
    std::cin >> n;
    std::vector<Query> queries(n);
    for (int i = 0; i < n; i++){
        std::cin >> queries[i].procedure;
        if (queries[i].procedure == "add"){
            std::cin >> queries[i].number;
            std::cin >> queries[i].name;
        }
        else{
            std::cin >> queries[i].number;
        }
    }
    return queries;
}

std::vector<std::string> processQueries(std::vector<Query> queries){
    std::vector<std::string> response;
    std::vector<Query> contacts(10000000);
    for (int i = 0; i < queries.size(); i++){
        if (queries[i].procedure == "add"){
            contacts[queries[i].number] = queries[i];
        }
        else if (queries[i].procedure == "find"){
            if (contacts[queries[i].number].name != ""){
                response.push_back(contacts[queries[i].number].name);
            }
            else{
                response.push_back("not found");
            }
        }
        else if (queries[i].procedure == "del"){
            contacts[queries[i].number].number = 0;
            contacts[queries[i].number].name = "";
        }
        else{
            std::cout << "wrong procedure, please only choose find, add or del" << std::endl;
        }
    }
    return response;
}


void readResponse(std::vector<std::string> response){
    for (auto const& res: response){
        std::cout << res << std::endl;
    }
}

int main(){
    readResponse(processQueries(readQueries()));
    return 0;
}