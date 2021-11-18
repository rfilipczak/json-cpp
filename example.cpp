#include "./json.hpp"

int main()
{
    Json::Object root;
    root["name"] = "Rafal";
    root["age"] = 28;

    Json::Object address;
    address["planet"] = "Earth";
    root["address"] = address;

    Json::Object movie0;
    movie0["tile"] = "Magnolia";
    movie0["year"] = 1999;

    Json::Object movie1;
    movie1["title"] = "Mulholland Dr.";
    movie1["year"] = 2001;

    root["favourite movies"][0] = movie0;
    root["favourite movies"][1] = movie1;

    Json::Object trivia;
    trivia["likes c++"] = Json::True;
    trivia["knows everything about programming"] = Json::False;
    trivia["list of finished projects"] = Json::Null;

    root += trivia;

    root.pretty_print();

    return 0;
}
