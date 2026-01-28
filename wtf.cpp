#include <iostream>
#include <print>
#include <algorithm>

std::string_view alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

[[nodiscard]]
inline size_t alphaVal (const char ch) {
    return ch - 'A' + 1;
}

[[nodiscard]]
std::string cascadeEncrypt (std::string_view&& pt)
{
    std::string deck = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
    std::string deck = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string pt = "";

    for (int i = 0; i < 26; ++i)
    {
        if (ct[0] == deck[i])
        {
            pt += alpha[i - 1];
            std::reverse(deck.begin(), deck.begin() + i);
            std::rotate(deck.begin(), deck.begin() + i, deck.end());
            break;
        }
    }

    for (int j = 1; j < ct.size(); ++j)
    {
        for (size_t i = 0; i < 26; ++i)
        {
            if (ct[j] == deck[i])
            {
                //std::println("{}", i);
                std::reverse(deck.begin(), deck.begin() + i);
                std::rotate(deck.begin(), deck.begin() + i, deck.end());
                pt += alpha[i - 1];
                //std::println("{}", deck);
            }
        }
    }

    return pt;
}

int main ()
{
    std::string ct = 
    "URILURQZUSVTSHMZRUGB";

    std::println("{} -> {}", ct, cascadeDecrypt(std::string_view(ct)));

    std::cin.get();
}