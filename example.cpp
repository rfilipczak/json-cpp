#include "./json.hpp"


int main()
{
    Json::Object root;
    root["name"] = "Bob";
    root["age"] = 44;

    Json::Object address;
    address["planet"] = "Earth";

    root["address"] = address;

    Json::Object joe;
    joe["name"] = "Joe";
    joe["age"] = 15;

    Json::Object sara;
    sara["name"] = "Sara";
    sara["age"] = 13;

    root["children"][0] = joe;
    root["children"][1] = sara;

    root["likes c++"] = Json::True;
    root["list of finished projects"] = Json::Null;
    root["placeholder"] = Json::False;

    root.pretty_print();

    return 0;
}
