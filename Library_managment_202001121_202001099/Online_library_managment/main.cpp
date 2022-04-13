#include <iostream>
#include <string>
using namespace std;

struct management
{
    string name;
    string password;
    string book;
    int days_left;
    int exist;
    management *next;
    bool logedin = false;
};

struct books
{
    string name;
    books *next;
    bool free;
};

class library_data
{
public:
    management *data;
    books *names;
    int size = 26;
    library_data()
    {
        names = new books[26];
        for (int i = 0; i < 26; i++)
        {
            names[i].free = 1;
            names[i].next = NULL;
            names[i].name = "0";
            // names[i].number = i+1;
        }
        names[13].name = "ABCD"; // int(A) % 26 = 13
        names[14].name = "BCDE";
        names[15].name = "CDEF";
        names[16].name = "DEFG";

        data = new management[26];
        for (int i = 0; i < size; i++)
        {
            data[i].exist = 0;
        }
        // inserting the names of books:
    }
    void insert_new_customer(); //done
    int hash_function(char);    // done
    void loan_book(string);     // done
    void return_book(string);   //done
    bool book_free(string);     //done
    void login();               //done
    void show_details();        //done
    void book_returned(string); //done
    void new_book(string name); // yet to be done
    void logged_out(string);
};
/*class personal_management : private library_data
{
public:
    void login();
    void loan_book();
    void show_details();
    void return_book();
};*/
void library_data ::book_returned(string book_name)
{
    int i = hash_function(book_name[0]);
    if (names[i].name == book_name)
    {
        if (names[i].free == 0)
        {

            names[i].free = 1;
        }
    }
    else
    {
        books *temp = names[i].next;
        while (temp != NULL)
        {
            if (temp->name == book_name)
            {
                if (temp->free == 0)
                {
                    temp->free = 1;
                    return;
                }

                return;
            }
        }
    }
}
bool library_data ::book_free(string book_name)
{
    int i = hash_function(book_name[0]);
    if (names[i].name == book_name)
    {
        if (names[i].free == 1)
        {
            names[i].free = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        books *temp = names[i].next;
        while (temp != NULL)
        {
            if (temp->name == book_name)
            {
                if (temp->free == 1)
                {
                    return true;
                }
                else
                    return false;
            }
        }
        if (temp == NULL)
        {
            return false;
        }
    }
    return true;
}
void library_data ::new_book(string name)
{
    /* string name;
    cout << "name of book not present in library: ";
    cin >> name; */
    int i = hash_function(name[0]);
    if (names[i].name == "0")
    {
        names[i].name = name;
    }
    else
    {
        books *book_new;
        book_new->name = name;
        book_new->next = names[i].next;
        names[i].next = book_new;
    }
}
void library_data ::return_book(string name)
{
    int i = hash_function(name[0]);
    if (data[i].name == name)
    {
        if (data[i].book == "null")
        {
            cout << "no book to be returned\n";
        }
        else
        {
            cout << "do you want to return the book titled: " << data[i].book << ". Press 1 to confirm and 0 to cancel\n";
            int check;
            cin >> check;
            if (check)
            {
                data[i].book == "null";
                book_returned(data[i].book);
                if (book_free(data[i].book))
                {
                    cout << "returned " << data[i].book << endl;
                    data[i].book = "null";
                }
            }
            else
            {
                cout << "No returning book query generated\n";
            }
        }
    }
    else
    {
        management *temp = data[i].next;
        while (temp != NULL)
        {
            if (temp->book == name)
            {
                break;
            }
            temp = temp->next;
        }
        if (temp->book == "null")
        {
            cout << "no book to be returned\n";
        }
        else if (temp == NULL)
        {
            cout << "NO user found\n";
        }
        else
        {
            cout << "do you want to return the book titled: " << temp->book << ". Press 1 to confirm and 0 to cancel\n";
            int check;
            cin >> check;
            if (check)
            {
                temp->book == "null";
                book_returned(temp->book);
                if (book_free(temp->book))
                {
                    cout << "returned " << temp->book << endl;
                    temp->book = "null";
                }
            }
        }
    }
}
void library_data ::login()
{
    cout << "user name: ";
    string first;
    cin >> first;
    int i = hash_function(first[0]); // hashfunction will return value so that we can "instantly" find the username;
    //cout << "name of user found: "<<data[i].name;
    //cout<<"\ngoing in the condition check of login(); function\n";
    if (first == data[i].name) // if the first data at the ith hashmap is the user we're looking for
    {
        string password;
        cout << "user found!\n";
        cout << "enter your password: ";
        cin >> password;

        int j = 5;
        while (j > 0 && (password != data[i].password)) // giving 5 chances to the user to enter the correct password
        {
            cout << "Wrong password " << j-- << " chances left\nEnter password: ";
            /* cout << "correct password:..." << data[i].password << "...\n";
            cout << "you entered: ......." << password << "...\n"; */
            cin >> password;
        }
        j--; // if password entered for 5th time will be wrong, i will be 0, now i-- will make it -1 if the password was wrong for the fifth time as well, else it will be atleast 0 (last chance me match hoga to i = 1, i-- => i = 0)
        if (j == -1)
        {
            cout << "max chances reached\nTry next time!\n";
            data[i].logedin = false; // the function calling to check if the user is loged in or not will know if to show the details or not
            return;
        }
        else
        {
            cout << "Sucessfully loged in\n";
            data[i].logedin = true; // the function will get true, that password was correct
            return;
        }
    }

    else // if the user info at the first position of the hasmap is not the user we are searching for
    {
        //cout <<"entering the elsee of login\n";
        management *temp = data[i].next;
        //cout <<"made a iterating management node\n";
        while (temp != NULL)
        {
            //cout<<"in the while loop\n";
            //cout<<"name is: "<<temp->name<<endl;
            if (temp->name == first)
                break;
            temp = temp->next; // untill we get the user, or we reached the end, we'll move to the nextt node
        }
        if (temp->name != first)
        {
            cout << "No user found! check your username\n";
            data[i].logedin = false; // if temp's name is not first => we didnt find the user, so there exist no data.
            return;
        }
        else
        { // case if the user name was matched at some not other than the first one.
            cout << "Enter your password " << first << " : ";
            string password;
            cin >> password;
            int i = 5;
            while (i > 0 && (password != temp->password))
            {
                cout << "Wrong password " << i-- << " chances left\nEnter password: ";
                cin >> password;
            }
            // same conditions are repeated.
            i--;
            if (i == -1)
            {
                cout << "max chances reached\nTry next time!\n";
                return;
                // temp->logedin = false;
            }
            else
            {
                cout << "Sucessfully loged in\n";
                temp->logedin = true;
                return;
            }
        }
    }
}
void library_data ::loan_book(string first)
{
    int i = hash_function(first[0]);
    if (data[i].name == first)
    {
        if (data[i].logedin) // only if the user is loged in
        {
            if (data[i].book == "null") // "null" here means no books on load through the account
            {
                cout << "no book on loan\nEnter book name to take on loan: ";
                string book_name;
                cin >> book_name;
                if (book_free(book_name)) // the user doesnot has any book pending and is set to get the book if the library has the book free
                {
                    cout << "book will be delivered in a day\n";
                    data[i].book = book_name;
                    cout << data[i].book << "is to be delivered\n";
                }
                else
                {
                    cout << "book already on loan, please check after some time\n";
                }
            }
            else
            {
                cout << "please return " << data[i].book << " before loaning another book\n";
            }
        }
    }
    else // SIMILAR CODE, JUST ITERATING TILL WE MATCH WITH THE NAME OR REACH THE  END OF THE LIST....
    {
        // cout <<"entered the else\n";
        management *temp = data[i].next;
        while (temp != NULL)
        {
            if (temp->name == first)
            {
                //       cout <<"breaking cause name found\n";
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {
            cout << "wrong user name\n";
        }
        else if (temp->name == first)
        {
            // cout <<"came to the perfect place\n";
            if (temp->book == "null")
            {
                cout << "no book on loan\nEnter book name to take on loan: ";
                string book_name;
                cin >> book_name;
                if (book_free(book_name))
                {
                    cout << "book will be delivered in a day\n";
                    temp->book = book_name;
                }
                else
                {
                    cout << "book already on loan, please check after some time\n";
                }
            }
        }
    }
}
int library_data ::hash_function(char c)
{
    if (int(c) > 90)
        c = c - 32;
    return ((int(c)) % 26);
}
void library_data ::insert_new_customer()
{
    string first;
    cout << "Enter your user name: ";
    cin >> first;

    int i = hash_function(first[0]);
    if (data[i].exist == 0)
    {
        data[i].name = first;
        data[i].book = "null";
        //data[i].days_left = -1;
        data[i].exist = 1;
        cout << "Enter password for future: ";
        cin >> data[i].password;
        data[i].next = NULL;
    }
    else
    {
        management *temp = new management;
        temp->name = first;
        temp->book = "null";
        // temp->days_left = -1;
        temp->exist = 1;
        cout << "Enter password for future: ";
        cin >> temp->password;
        temp->next = data[i].next;
        data[i].next = temp;
    }
}
void library_data ::show_details()
{
    cout << "Second sequrity check for your username\nEnter your username: ";
    string first;
    cin >> first;
    int i = hash_function(first[0]);
    cout <<"\n\n----------------------------------------------------\n";
    if (data[i].name == first)
    {
        if (data[i].logedin)
        {
            cout << "Here are your details:\n";
            cout << "username: " << data[i].name << endl;
            if (data[i].book == "null")
            {
                cout << "NO book taken\n";
            }
            else
            {
                cout << "Book taken: " << data[i].book << endl;
                //cout << "time to return book: " << data[i].days_left << endl;
            }
            cout << "That is all for the information to show!\n";
        }
        else
        {
            cout << "Not loged in using this username\n";
        }
    }
    else
    {
        management *temp = data[i].next;
        while (temp != NULL)
        {
            if (temp->name == first)
            {
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {
            cout << "no user found with the name\n";
        }
        else if (temp->book == "null")
        {
            cout << "Here are your details:\n";
            cout << "username: " << temp->name << endl;
            cout << "No book on loan from this user\n";
        }
        else
        {
            cout << "Here are your details:\n";
            cout << "username: " << temp->name << endl;
            cout << "book on loan: " << temp->book << endl;
            //cout << "days left to return: " << temp->days_left << endl;
        }

    }
    cout << "\n\n----------------------------------------------------\n";
}
void library_data ::logged_out(string first)
{
    int i = hash_function(first[0]);
    if (data[i].name == first)
    {
        if (data[i].logedin)
        {
            data[i].logedin = false;
            cout << "successfully logged out\n";
        }
        else
        {
            cout << "user has not loged in yet\n";
        }
    }
    else
    {
        int j = 0;
        management *temp = data[i].next;
        while (temp != NULL)
        {
            if (temp->name == first)
                break;
            j++;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "No user found\n";
        }
        else
        {
            temp->logedin = false;
            cout << "successfully logged out\n";
        }
    }
}
int main()
{
    library_data h;
    int option, i = 1;

    cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout <<"\t\t\t\t\t****         *****   ***********    ***********      *********     ***********   ****      ****\n";
    cout <<"\t\t\t\t\t****         *****   ***      ***   ***      ***    **       **    ***      ***   ****    **** \n";
    cout <<"\t\t\t\t\t****         *****   ***      ***   ***      ***   ***       ***   ***      ***    ****  ****  \n";
    cout <<"\t\t\t\t\t****         *****   ***      ***   ***      ***   ***       ***   ***      ***     ********   \n";
    cout <<"\t\t\t\t\t****         *****   ***********    ***********    *************   ***********        ****     \n";
    cout <<"\t\t\t\t\t****         *****   ***      ***   ***    **      ***       ***   ***    **          ****     \n";
    cout <<"\t\t\t\t\t**********   *****   ***      ***   ***     ***    ***       ***   ***     ***        ****     \n";
    cout <<"\t\t\t\t\t**********   *****   ***********    ***      ***   ***       ***   ***      ***       ****     \n";
    system("pause");
    system("cls");
    while (1)
    {
        if (i == 1)
        {
            i++;
            cout << "Press 1 if you are new coustomer\n";
        }
        else
        {
            cout << "Press 1 if you are new coustomer\n";
            cout << "Press 2 for login window\n";
            cout << "Press 3 for loaning a book\n";
            cout << "Press 4 for returning the book\n";
            cout << "Press 5 to view your details\n";
            cout << "Press 6 to log out\n";
            cout << "Press 7 to suggesting book\n";
            cout << "Pess 8 to exit the programm\n";
            // cout << "Press 6 to see if a book is free or not\n";
        }
        string name;
        cout << "Enter the choice: ";
        cin >> option;
        system("CLS");

        switch (option)
        {
        case 1:
            h.insert_new_customer();
            cout << "SUCCESSFULLY REGISTERED\n";
            break;
        case 2:
            h.login();
            break;
        case 3:
            cout << "Username: ";
            cin >> name;
            h.loan_book(name);
            break;
        case 4:
            cout << "Username: ";
            cin >> name;
            h.return_book(name);
            break;
        case 5:
            h.show_details();
            break;
        //case 6:
        //    cout << "name of book to be checked\n";
        //    cin >> name;
        //    h.book_free(name);;
        //    break;
        case 6:
            cout << "Username: ";
            cin >> name;
            h.logged_out(name);
            cout << "Logged out succesfully\n";
            break;
        case 7:
            cout << "Books suggestion : ";
            cin >> name;
            cout << "book will be made available in few time\nThanks for the help!\n";
            break;
        case 8:
            cout << "Exiting the program\nThanks for using.\n";
            system("pause");
            exit(0);
            break;

        default:
            cout << "Not a valid choice\n";
            break;
        }
        system("pause");
        system("CLS");
    }
}
