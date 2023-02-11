#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>
#include <float.h>
#include <regex>
using std::string;
using std::endl;
using std::cout;

template <typename T>
void cast_char(T value)
{
    char out_c;

    std::ios::fmtflags flags = cout.flags();
    try
    {
        if (value < 0 || value > 127)
            throw std::string("char: impossible");
        if (std::isnan(value))
            throw std::string("char: impossible");
        out_c = static_cast<char>(value);
        if (out_c > ' ' && out_c <= '~')
            cout << "char: '" << out_c << "'" <<  endl;
        else if ((0 <= out_c && out_c <= ' ') || out_c == 127)
            throw std::string("char: Not displayable");
        else
            throw std::string("char: impossible");
    }
    catch (std::string &e)
    {
        cout << std::setiosflags(flags);
        cout << e << endl;
    }
    cout << std::setiosflags(flags);
}

template <typename T>
void cast_int(T value)
{
    int out_i;

    std::ios::fmtflags flags = cout.flags();
    try
    {
        if (std::isnan(value))
            throw std::exception();
        out_i = static_cast<int>(value);
        if (out_i == INT_MIN && (std::fabs((T)INT_MIN - value) > DBL_EPSILON))
            throw std::exception();
        cout << std::dec << "int: " << out_i << endl;
    }
    catch (std::exception &e)
    {
        cout << std::setiosflags(flags);
        cout << "int: impossible" << endl;
    }
    cout << std::setiosflags(flags);
}

template <typename T>
void cast_float(T value)
{
    float out_f;
    std::stringstream ss;

    std::ios::fmtflags flags = cout.flags();
    try
    {
        out_f = static_cast<float>(value);

        ss << std::fixed << std::setprecision(5) << "float: " << out_f;
        string out = ss.str();
        size_t pos = out.find(".", 0);
        if (pos != string::npos)
        {
            for(int i=0; i<4;i++)
            {
                if (out[out.length() - 1] == '0')
                    out.pop_back();
            }
        }
        cout << out << "f" << endl;
    }
    catch (std::exception &e)
    {
        cout << std::setiosflags(flags);
        cout << "float: impossible" << endl;
    }
    cout << std::setiosflags(flags);
}

template <typename T>
void cast_double(T value)
{
    double out_d;
    std::stringstream ss;

    std::ios::fmtflags flags = cout.flags();
    try
    {
        out_d = static_cast<double>(value);
        ss << std::fixed << std::setprecision(5) << "double: " << out_d;
        string out = ss.str();
        size_t pos = out.find(".", 0);
        if (pos != string::npos)
        {
            for(int i=0; i<4;i++)
            {
                if (out[out.length() - 1] == '0')
                    out.pop_back();
            }
        }
        cout << out << endl;
    }
    catch (std::exception &e)
    {
        cout << std::setiosflags(flags);
        cout << "double: impossible" << endl;
    }
    cout << std::setiosflags(flags);
}

bool check_char(string str)
{
    char c;
    if (str.length() != 1)
        return (false);
    c = static_cast<char>(str.c_str()[0]);
    if (c < 0 || c > 127)
        return (false);
    cast_char(c);
    cast_int(c);
    cast_float(c);
    cast_double(c);
    cout << endl;
    return (true);
}

bool check_float(string str)
{
    float f;

    try
    {
        float ftmp = static_cast<float>(INT_MAX);
        f = static_cast<float>(stof(str));
        if (ftmp == f)
        {
            return (false);
        }
    }
    catch (std::exception &e)
    {
        return (false);
    }
    cast_char(f);
    cast_int(f);
    cast_float(f);
    cast_double(f);
    cout << endl;
    return (true);
}

bool check_double(string str)
{
    double d;

    try
    {
        d = static_cast<double>(stod(str));
    }
    catch (std::exception &e)
    {
        return (false);
    }
    cast_char(d);
    cast_int(d);
    cast_float(d);
    cast_double(d);
    cout << endl;
    return (true);
}

bool check_int(string str)
{
    int i;

    if (str.find(".", 0) != string::npos)
        return (false);
    if (str.find("f", 0) != string::npos)
        return (false);
    try
    {
        i = static_cast<int>(stoi(str));
        if (i == INT_MIN)
            return (false);
    }
    catch (std::exception &e)
    {
        return (false);
    }
    cast_char(i);
    cast_int(i);
    cast_float(i);
    cast_double(i);
    cout << endl;
    return (true);
}


void cast_test(string str)
{
    if (check_int(str))
        return ;
    if (check_float(str))
        return ;
    if (check_double(str))
        return ;
    if (check_char(str))
        return ;
    cout << "char: impossible" << endl;
    cout << "int: impossible" << endl;
    cout << "float: impossible" << endl;
    cout << "double: impossible" << endl;
    cout << endl;
}

int main(int argc, char **argv)
{
    string tmp;
    string substr;
    size_t pos;

    float f = 100000.123f;

    cout << "f:" << f << endl;
    f = 1000000.123f;
    cout << "f:" << f << endl;

    if (argc < 2)
    {
        cout << "Error:Argument is nothing" << endl;
        return (0);
    }
    for (int i = 1; i< argc ; i++)
    {
        tmp = string(argv[i]);
        pos = 0;

        do 
        {
            pos = tmp.find(" ", 0);
            if (pos == string::npos)
            {
                if (tmp == " " || tmp == "")
                    break ;
                cast_test(tmp);
                break ;
            }
            else
            {
                cast_test(tmp.substr(0, pos));
                tmp = tmp.substr(pos + 1);
            }
        } while ((pos != string::npos));
    }
}
