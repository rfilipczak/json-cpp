# json-cpp

Simple json single-header-file-lib for c++20.

## Features

* pretty print
* compact form

## Todo

* reading and parsing

## Requirements

* g++
* c++20
* make

## Example

```c++
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

    root["likes c++"] = Json::True{};
    root["list of finished projects"] = Json::Null{};

    root.pretty_print();

    return 0;
}
```

## Quickstart

```console
$ mkdir cmake-build-debug
$ cd cmake-build-debug
$ cmake ..
$ make
$ ./example
{
  "name": "Bob",
  "age": 44,
  "address": {
    "planet": "Earth"
  },
  "children": [
    {
      "name": "Joe",
      "age": 15
    },
    {
      "name": "Sara",
      "age": 13
    }
  ],
  "likes c++": true,
  "list of finished projects": null
}
```