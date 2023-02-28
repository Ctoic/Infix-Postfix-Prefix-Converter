#include<iostream>
using namespace std;

class Node
{
public:
    char data;
    Node* next;

};

class Stack
{
public:
    Node* head;   //top
    Stack()
    {
        head = NULL;

    }

    bool isempty()
    {
        if (head == NULL)
        {
            return true;

        }
        else {
            return false;

        }
        return 0;

    }

    void push(char expre)
    {
        if (isempty())
        {
            Node* newnode = new Node();
            head = newnode;
            newnode->data = expre;
            newnode->next = NULL;
        }
        else
        {
            Node* newnode2 = new Node();
            newnode2->next = head;
            newnode2->data = expre;
            head = newnode2;

        }

        return;


    }
    char pop()
    {
        if (isempty())
        {
            cout << "Stack Underflow" << endl;
            return -1;

        }
        else
        {
            int temp = head->data;
            head = head->next;
            return temp;

        }
    }

    char top()
    {
        if (isempty())
        {
            return -1;

        }
        else
        {
            return head->data;

        }
    }


    void Display()
    {
        Node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data;
            temp = temp->next;

        }
        return;

    }
    // checker for braces
    bool Check_parenthesis(char brac_open, char brac_close);
    // checking wheather equal or not
    bool isvalid(char expression[100]);

    char* InfixToPostfix(char expression[]);

    // Function to verify whether an operator has higher precedence over other
    int HasHigherPrecedence(char op1, char op2);

    // Function to verify whether a character is operator symbol or not.
    bool IsOperator(char Charcter);

    // Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
    bool IsOperand(char Charcter);

    bool is_left_to_right_Associative(char oprator);

    // Function for the weight of operator for precedence check
    int weightofoperator(char oprator);

    //Now a function to evaluate the postfix function

    void Postfix_Evaluation(char expression[100]);

    // Now by checking the operators this function will operate on the operands from the stack
    int Operation(char operation, int op1, int op2);
    //check for numeric Digit
    bool IsNumericDigit(char C);

    //Now reverse function to achieve the prefix form
    char* reverse(char post[]);

    // Prefix function where operator is follwed by operands 

    void InfixToprefix(char post[]);


};

int main()
{
    Stack s;
    char* arr = new char[100];
    cout << "Enter an expression :" << endl;

    cin >> arr;
    //validity if valid ==> 1 else ==> 0
    cout << "Validity :";
    cout << s.isvalid(arr) << endl;
    if(s.isvalid(arr))
    {
        cout << "Postfix :";
        cout << s.InfixToPostfix(arr) << endl;
        cout << "Prefix :";
        s.InfixToprefix(arr);
        cout << endl;
        cout << "Evaluation :";
        s.Postfix_Evaluation(arr);
        cout << endl;
    }
    else
    {
        cout << "Invalid Expression" << endl;
    }


    return 0;

}
// Checking if the brackets are pair or not

bool Stack::Check_parenthesis(char brac_open, char brac_close)
{
    if (brac_open == '(' && brac_close == ')')
    {
        return true;

    }
    else if (brac_open == '{' && brac_close == '}')
    {
        return true;

    }
    else if (brac_open == '[' && brac_close == ']')
    {
        return true;

    }

    else
    {
        cout << " A parenthesis is missing :( " << endl;
        return false;
    }
}

// Checking if balance or not
bool Stack::isvalid(char expression[])
{
    // creating a stack
    Stack s1;


    int i = 0;
    while (expression[i] != '\0')
    {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        {
            s1.push(expression[i]);
        }

        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
        {
            if (s1.isempty() || !Check_parenthesis(s1.top(), expression[i]))
            {
                return false;

            }
            else
            {
                s1.pop();

            }

        }
        i++;
    }

    if (s1.isempty())
    {
        return true;

    }

    else
    {
        return false;
    }
}

// Function to convert a given infix charcterr array into postfix expression
char* Stack::InfixToPostfix(char expression[])
{
    // create a Stack
    Stack s1;

    int i = 0;
    int j = 0;
    char* postfix = new char[100];

    while (expression[i] != '\0')
    {
        if (IsOperator(expression[i]))
        {
            while (!s1.isempty() && HasHigherPrecedence(s1.top(), expression[i]))
            {
                postfix[j] = s1.top();
                s1.pop();
                j++;
            }
            s1.push(expression[i]);
        }

        else if (IsOperand(expression[i]))
        {
            postfix[j] = expression[i];
            if (IsOperator(expression[++i]))
            {
                postfix[++j] = ' ';
            }
            i--;
            j++;
        }

        else if (expression[i] == '(')
        {
            s1.push(expression[i]);
        }

        else if (expression[i] == ')')
        {
            while (!s1.isempty() && s1.top() != '(')
            {
                postfix[j] = s1.top();
                s1.pop();
                j++;
            }
            s1.pop();
        }
        i++;
    }

    while (!s1.isempty())
    {
        postfix[j] = s1.top();
        s1.pop();
        j++;
    }
    postfix[j] = '\0';


    return postfix;

}

// Reverse Function Char array to finally converting it to prefix 

char* Stack::reverse(char arr[])
{
    int length = 0, i = 0;
    while (arr[i] != '\0')
    {
        //calculating the length of expression
        length++;
        i++;

    }
    length--;

    i = 0;
    int l = length;

    while (i <= length / 2)
    {
        int Swap = arr[i];
        arr[i] = arr[l];
        arr[l] = Swap;
        l--;
        i++;

    }

    for (i = 0; i <= length; i++)
    {
        if (arr[i] == '(')
        {
            arr[i] = ')';

        }
        else if (arr[i] == ')')
        {
            arr[i] = '(';
        }

    }
    return arr;

}
// Now finally we will convert expression to prefix form 
void Stack::InfixToprefix(char arr[])
{
    char* Reverse = reverse(arr);
    Reverse = InfixToPostfix(Reverse);
    Reverse = reverse(Reverse);
    cout << "This prefix form is :" << Reverse << endl;

}


void Stack::Postfix_Evaluation(char expression[])
{
    Stack s1;
    int op1, op2, result = 0;

    int i = 0;
    while (expression[i] != '\0')
    {
        if (expression[i] == ' ')
        {
            i++;
        }

        else if (IsOperator(expression[i]))
        {
            op2 = s1.top();
            s1.pop();
            op1 = s1.top();
            s1.pop();

            result = Operation(expression[i], op1, op2);
            s1.push(result);
            i++;
        }
        else if (IsNumericDigit(expression[i]))
        {
            // extracting the numeric digit from the charcter arrray
            int operand = 0;

            while (expression[i] != '\0' && IsNumericDigit(expression[i]))
            {
                operand = (operand * 10) + (expression[i] - 48);
                i++;
            }
            s1.push(operand);

        }
    }

    cout << result << endl;

}

int Stack::Operation(char operation, int op1, int op2)
{
    if (operation == '+')
    {
        return op1 + op2;
    }
    else if (operation == '-')
    {
        return op1 - op2;
    }
    else if (operation == '*')
    {
        return op1 * op2;
    }
    else if (operation == '/')
    {
        return op1 / op2;
    }
    else if (operation == '%')
    {
        return op1 % op2;

    }
    else if (operation == '^')
    {
        int  power = 1;
        int i = 0;

        for (i; i < op2; i++)
        {
            power = power * op1;

        }

        return power;

    }

    else
        cout << "Unexpected Error \n";
    return -1;


}
// Checking wheather we got a numeric digit
bool Stack::IsNumericDigit(char C)
{
    if (C >= '0' && C <= '9') return true;
    return false;
}



// Check for the operand if they are Valid or Not
bool Stack::IsOperand(char charcter)
{
    if (charcter >= 48 && charcter <= 58)
    {
        return true;

    }

    else
    {
        return false;

    }
}


// Check if the given char is a an operator or Not
bool Stack::IsOperator(char charcter)
{
    if (charcter == '-' || charcter == '+' || charcter == '*' || charcter == '/' || charcter == '^' || charcter == '%')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Stack::weightofoperator(char op)
{

    int weight = -1;
    switch (op)
    {
    case '+':
    case '-':
        weight = 1;
        break;

    case '*':
    case '/':
    case '^':
        weight = 2;
        break;

    case '%':
        weight = 3;
    }
    return weight;

}


// Checking the precedence of operator

int  Stack::HasHigherPrecedence(char op1, char op2)
{
    int opr1weight = weightofoperator(op1);
    int opr2weight = weightofoperator(op2);

    if (op1 == '(')
        return false;

    if (opr1weight == opr2weight)
    {
        return true;
    }

    else if (opr1weight > opr2weight)
    {
        return true;

    }
    else
    {
        return false;

    }
}
