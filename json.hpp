#ifndef JSON_H
#define JSON_H

#include <string>
#include <variant>
#include <vector>
#include <concepts>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>


namespace Json
{
    using Key = std::string;
    using String = std::string;
    using Number = double;

    struct True_ {};
    struct False_ {};
    struct Null_ {};

    static const True_ True{};
    static const False_ False{};
    static const Null_ Null{};

    class Object; // forward declare needed for recursive dependency

    class Data
    {
    private:
        enum class Type
        {
            String,
            Number,
            Object,
            True,
            False,
            Null
        };

        // recursive dependency helper
        template<typename T>
        struct recursive_wrapper
        {
            std::vector<T> t;

            explicit recursive_wrapper(const T& _t)
            {
                t.emplace_back(std::move(_t));
            }

            friend std::ostream& operator<<(std::ostream& out, const recursive_wrapper& wrapper)
            {
                out << wrapper.t.front();
                return out;
            }
        };

        using Variant = std::variant<std::monostate, String, Number, recursive_wrapper<Object>>;

        Variant variant;
        Type type;

    public:
        Data& operator=(const String& str)
        {
            type = Type::String;
            variant = str;
            return *this;
        }

        template<typename T>
        requires std::floating_point<T> || std::integral<T>
        Data& operator=(const T& number)
        {
            type = Type::Number;
            variant = static_cast<Number>(number);
            return *this;
        }

        Data& operator=(const Object& obj)
        {
            type = Type::Object;
            variant = recursive_wrapper<Object>(obj);
            return *this;
        }

        Data& operator=(const True_& _true [[maybe_unused]])
        {
            type = Type::True;
            return *this;
        }

        Data& operator=(const False_& _false [[maybe_unused]])
        {
            type = Type::False;
            return *this;
        }

        Data& operator=(const Null_& _null [[maybe_unused]])
        {
            type = Type::Null;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const Data& data)
        {
            switch (data.type)
            {
                case Type::String:
                    out << std::quoted(std::get<String>(data.variant));
                    break;
                case Type::Number:
                    out << std::get<Number>(data.variant);
                    break;
                case Type::Object:
                    out << std::get<recursive_wrapper<Object>>(data.variant);
                    break;
                case Type::True:
                    out << "true";
                    break;
                case Type::False:
                    out << "false";
                    break;
                case Type::Null:
                    out << "null";
                    break;
                default:
                    assert(0 && "unreachable");
            }
            return out;
        }
    }; // class Data

    class Value
    {
    private:
        std::vector<Data> values;
        bool isArray{false};
    public:
        Value()
        {
            values.resize(1);
        }

        template<typename T>
        Value& operator=(const T& t)
        {
            values.at(0) = t;
            return *this;
        }

        Data& operator[](std::size_t index)
        {
            isArray = true;
            values.resize(index + 1);
            return values.at(index);
        }

        friend std::ostream& operator<<(std::ostream& out, const Value& value)
        {
            if (value.isArray)
                out << '[';
            for (std::size_t i = 0; const auto& data: value.values)
            {
                out << data << ((++i != value.values.size()) ? "," : "");
            }
            if (value.isArray)
                out << ']';
            return out;
        }
    }; // class Value


    class Object
    {
    private:
        std::vector<std::pair<Key, Value>> values;

    public:
        Object& operator+=(const Object& other)
        {
            for (const auto& value: other.values)
            {
                this->values.emplace_back(value);
            }
            return *this;
        }

        Value& operator[](const Key& key)
        {
            if (auto found = std::ranges::find_if(values, [key](const auto& v) -> bool {
                    return (v.first == key);
            }); found != std::end(values))
            {
                return found->second;
            }
            else
            {
                values.resize(values.size() + 1);
                values.at(values.size() - 1).first = key;
                return values.at(values.size() - 1).second;
            }
        }

        friend std::ostream& operator<<(std::ostream& out, const Object& obj)
        {
            out << '{';
            for (std::size_t i = 0; const auto& val: obj.values)
            {
                out << std::quoted(val.first) << ':' << val.second << ((++i != obj.values.size()) ? "," : "");
            }
            out << '}';
            return out;
        }

        [[nodiscard]] std::string compact() const
        {
            std::ostringstream oss;
            oss << *this;
            return oss.str();
        }

        void pretty_print() const
        {
            std::string compact = this->compact();

            std::ostringstream result;
            int current_level = 0;

            auto intend = [&current_level, &result]() {
                for (int i = 0; i < current_level; ++i)
                    result << "  ";
            };

            char previous{};
            std::ranges::for_each(compact, [&result, &current_level, &previous, intend](char c) {
                if (c == '{')
                {
                    if (previous != ':')
                        intend();
                    result << '{' << '\n';
                    ++current_level;
                }
                else if (c == '}')
                {
                    result << '\n';
                    --current_level;
                    intend();
                    result << '}';
                }
                else if (c == '[')
                {
                    result << '[' << '\n';
                    ++current_level;
                }
                else if (c == ']')
                {
                    result << '\n';
                    --current_level;
                    intend();
                    result << ']';
                }
                else if (c == ':')
                {
                    result << ':' << ' ';
                }
                else if (c == ',')
                {
                    result << ',' << '\n';
                }
                else if (c == '"' && (previous == ',' || previous == '{'))
                {
                    intend();
                    result << '"';
                }
                else
                {
                    if (previous == ',' || previous == '{' || previous == '[')
                        intend();
                    result << c;
                }
                previous = c;
            });

            std::cout << result.str() << '\n';
        }
    }; // class Object

} // namespace Json

#endif //JSON_H
