#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using std::string;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}

std::vector<int> get_occurrences_naive(const Data& input) {
	const string& s = input.pattern, t = input.text;
	std::vector<int> ans;
	for (size_t i = 0; i + s.size() <= t.size(); ++i) {
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	}
	return ans;
}

long long poly_hash(const string& s, int prime, int multiplier) {
    unsigned long long hash = 0;
    for (long long i = static_cast<long long> (s.size())-1; i>=0; --i){
        hash = (hash * multiplier + s[i]) % prime;
    }
    return hash;
}

std::vector<long long> precompute_hashes(const std::string& text, int length_pattern,
                                   int prime, int multiplier){
    int length_text = text.size();
    std::vector<long long> H(length_text - length_pattern + 1);
    std::string s = text.substr(length_text - length_pattern, length_pattern);
    H[length_text - length_pattern] = poly_hash(s, prime, multiplier);
    long long y = 1;
    for (int i = 1; i<= length_pattern; i++){
        y = y * multiplier % prime;
    }
    for (int i = length_text - length_pattern - 1; i >=0; i--){
        long long preHash = multiplier * H[i+1] + text[i] - y * text[i + length_pattern];
        while (preHash < 0){
            preHash += prime;
        }
        H[i] = preHash % prime;
    }
    return H;
}


bool are_equal(const std::string& s1, const std::string s2){
    if (s1.size() != s2.size()){
        return false;
    }
    for (int i= 0; i < s1.size(); i++){
        if (s1[i] != s2[i]){
            return false;
        }
    }
    return true;
}

std::vector<int> get_occurrences(const Data& input){
    static const int prime = 1000000007;
    static const int multiplier = std::rand() % (prime - 1) + 1;
    std::vector<int> positions;
    const string& t = input.text, s = input.pattern;

    long long pHash = poly_hash(s, prime, multiplier);
    std::vector<long long> tHash = precompute_hashes(t, s.size(), prime, multiplier);
    for (size_t i = 0; i + s.size() <= t.size(); i++){
        if (pHash != tHash[i])
            continue;
        if (are_equal(t.substr(i, s.size()), s))
            positions.push_back(i);
    }
    return positions;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	print_occurrences(get_occurrences(read_input()));
	return 0;
}