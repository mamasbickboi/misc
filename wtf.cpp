#include <iostream>
#include <print>
#include <algorithm>

std::string_view alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

[[nodiscard]]
size_t alphaVal (const char ch) {
    return ch - 'A' + 1;
}

[[nodiscard]]
std::string cascadeEncrypt (std::string_view&& pt)
{
    //can change this to the initial state
    std::string deck = alpha.data();

    std::string ct = "";

    for (const char& ch : pt)
    {
        std::reverse(deck.begin(), deck.begin() + alphaVal(ch));
        std::rotate(deck.begin(), deck.begin() + alphaVal(ch), deck.end());

        ct += deck.front();
    }

    return ct;
}

[[nodiscard]]
std::string cascadeDecrypt (std::string_view&& ct)
{
    //can change this to the initial state
    std::string deck = alpha.data();
    std::string pt = "";

    size_t idx;

    for (const char& ch : ct)
    {
        idx = deck.find(ch);
        std::reverse(deck.begin(), deck.begin() + idx);
        std::rotate(deck.begin(), deck.begin() + idx, deck.end());
        pt += alpha[idx - 1];
    }

    return pt;
}

int main ()
{
    std::string ct = "URILURQZUSVTSHMZRUGB";

    std::println("{} -> {}", ct, cascadeDecrypt(std::string_view(ct)));

    std::cin.get();
}