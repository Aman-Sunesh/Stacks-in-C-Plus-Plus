#include <iostream>
#include <stack>
#include "prelab5.h"
#include "payload.h"


using namespace std;

int precedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0; 
}

int polish(const string& exp)
{
    stack<int> s;
    int n = exp.length();

    for (int i = 0; i < n; i++)
    {
        if (isdigit(exp[i]))
        {
            s.push(exp[i] - '0');  // Convert exp[i] to an integer and push in the stack
        }

        else if ((exp[i] == '+') || (exp[i] == '-') || (exp[i] == '*') 
                || (exp[i] == '/') || (exp[i] == '%'))
        {
            if (s.size() < 2)
            {
                throw runtime_error("Error! Invalid Expression");
            }

            int val2 = s.top();
            s.pop();

            int val1 = s.top();
            s.pop();

            if (isspace(exp[i])) 
            {
                continue;
            }

            if (exp[i] == '+')
            {
                s.push(val1 + val2);
            }

            else if (exp[i] == '-')
            {
                s.push(val1 - val2);
            }

            else if (exp[i] == '*')
            {
                s.push(val1 * val2);
            }

            else if (exp[i] == '/')
            {
                if (val2 == 0)
                {
                    throw runtime_error("Error! Division by Zero");
                }

                s.push(val1 / val2);
            }

            else if (exp[i] == '%')
            {
                if (val2 == 0)
                {
                    throw runtime_error("Error! Division by Zero");
                }

                s.push(val1 % val2);
            }
        }
    }

    // At this point, the stack should only have one element, which is the result;
    if (s.size() != 1)
    {
        throw runtime_error("Error! Invalid Postfix Expression");
    }

    return s.top();
}


string translate(const string& exp)
{
    stack<char> s;
    int n = exp.length();
    string result;

    for (int i = 0; i < n; i++)
    {
        if (isspace(exp[i])) 
        {
            continue;
        }

        if (isdigit(exp[i]))
        {
            result += exp[i];
        }

        else if (exp[i] == '(')
        {
            s.push(exp[i]);
        }

        else if (exp[i] == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                result += s.top();
                s.pop();
            }

            if (!s.empty() && s.top() == '(')
            {
                s.pop(); // We remove '(', but do not append it to the result
            }
        }

        else if ((exp[i] == '+') || (exp[i] == '-') || (exp[i] == '*') 
                || (exp[i] == '/') || (exp[i] == '%'))
        {
            while (!s.empty() && precedence(s.top()) >= precedence(exp[i]))
            {
                result += s.top();
                s.pop();
            }

            s.push(exp[i]);
        }
    }

    while (!s.empty())
    {
        result += s.top();
        s.pop();
    }

    return result;
}