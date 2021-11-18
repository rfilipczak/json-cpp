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
```

## Quickstart

```console
$ mkdir cmake-build-debug
$ cd cmake-build-debug
$ cmake ..
$ make
$ ./example
{
  "name": "Rafal",
  "age": 28,
  "address": {
    "planet": "Earth"
  },
  "favourite movies": [
    {
      "tile": "Magnolia",
      "year": 1999
    },
    {
      "title": "Mulholland Dr.",
      "year": 2001
    }
  ],
  "likes c++": true,
  "knows everything about programming": false,
  "list of finished projects": null
}
```
