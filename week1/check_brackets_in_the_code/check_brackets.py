# python3

from collections import namedtuple

Bracket = namedtuple("Bracket", ["char", "position"])


def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]


def find_mismatch(text):
    error_pos = 0
    opening_brackets_stack = []
    for i, next in enumerate(text):
        if next in "([{":
            # Process opening bracket, write your code here
            tmp_bracket_1 = Bracket(next, i+1)
            opening_brackets_stack.append(tmp_bracket_1)

        if next in ")]}":
            # Process closing bracket, write your code here
            if len(opening_brackets_stack) == 0:
                error_pos = i + 1
                break
            else:
                top_bracket = opening_brackets_stack.pop()
                if are_matching(top_bracket.char, next):
                    continue
                else:
                    error_pos = i + 1
                    break
    return opening_brackets_stack, error_pos


def main():
    text = input()
    mismatch, error_position = find_mismatch(text)
    # Printing answer, write your code here
    if(len(mismatch) == 0) & (error_position == 0):
        print('Success')
    else:
        if error_position == 0:
            while len(mismatch) > 1:
                mismatch.pop()
            error_position = mismatch.pop().position
        print(error_position)

if __name__ == "__main__":
    main()
