#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    int error_pos = 0;    
    std::stack <Bracket> opening_brackets_stack;

    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        
        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket tmp_bracket_1 = Bracket(next, position + 1);
            opening_brackets_stack.push(tmp_bracket_1);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()){
                error_pos = position + 1;
                break;
            }   
            else{
                Bracket top_bracket = opening_brackets_stack.top();
                opening_brackets_stack.pop();
                if (top_bracket.Matchc(next)){
                    continue;
                }   
                else{
                    error_pos = position + 1;
                    break;
                } 
            }
                 
        }
    }
    // Printing answer, write your code here
    if (opening_brackets_stack.empty() && error_pos == 0){
        std::cout << "Success" << std::endl;
    }
    else {
        // for the situation "(((", error_pos are not changed, 
        // but opening_brackets_stack are not empty
        if (error_pos == 0)
        {   
            while (opening_brackets_stack.size() > 1){
                opening_brackets_stack.pop();
            }
            error_pos = opening_brackets_stack.top().position;
        }
        std::cout << error_pos << std::endl;
    }
    return 0;
}
