# python3
import random

def read_input():
    return (input().rstrip(), input().rstrip())

def print_occurrences(output):
    print(' '.join(map(str, output)))

def get_occurrences_naive(pattern, text):
    return [
        i
        for i in range(len(text) - len(pattern) + 1)
        if text[i:i + len(pattern)] == pattern
    ]
def poly_hash(s, prime, multiplier):
    hash_ = 0
    for c in reversed(s):
        hash_ = (hash_ * multiplier + ord(c)) % prime
    return hash_

def precompute_hashes(t, pLength, prime, multiplier):
    tLength = len(t)
    H = [0] * (tLength - pLength + 1)
    s = t[-pLength:]
    H[tLength - pLength] = poly_hash(s, prime, multiplier)
    y = 1
    for i in range(1, pLength + 1):
        y = y * multiplier % prime
    for i in reversed(range(tLength - pLength)):
        preHash = multiplier * H[i+1] + ord(t[i]) - y * ord(t[i + pLength])
        while preHash < 0:
            preHash += prime
        H[i] = preHash % prime
    return H

def get_occurrences(pattern, text):
    prime = 1000000007
    multiplier = random.randint(0, prime -1) + 1

    pHash = poly_hash(pattern, prime, multiplier)
    tHash = precompute_hashes(text, len(pattern), prime, multiplier)
    return [
        i
        for i in range(len(text) - len(pattern) + 1)
        if pHash == tHash[i] and text[i:i + len(pattern)] == pattern
    ]

if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))
