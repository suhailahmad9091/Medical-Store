#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<ctime>

using namespace std;

int z=0;

class item
{
    int id, price, quantity, day, month, year;
    char name[30];
public:
  void purchase_item();
  void display_item(int);
  void add_item();
  void update_quantity(int);
  void modify_item();
  void delete_item();
  void view_sale();
  int get_id();
  char* get_name();
  int get_quantity();
}i;

int item::get_id()
{
    return id;
}

char* item::get_name()
{
    return name;
}

int item::get_quantity()
{
    return quantity;
}

void item::update_quantity(int n)
{
    quantity = quantity - n ;
}

void item::add_item()
{
    system("cls");

    id = z+1;

    time_t currenttime = time(0);
    tm *ltm=localtime(&currenttime);

    day=ltm->tm_mday;
    month=1+ltm->tm_mon;
    year=1900+ltm->tm_year;

    cout<<"\n%%%%%%%%%%         Add Item       %%%%%%%%%%";

    int flag=0;

    do
    {
        cout<<"\n\nEnter the name of item : ";
        fflush(stdin);
        gets(name);

        int l=strlen(name);
        if(l>1)
        {
            int alpha=0,space=0;
            for(int i=0;name[i]!='\0';i++)
            {
                if(isalpha(name[i]))
                alpha++;
                else if(name[i]==' ')
                space++;
            }
            if( (alpha==l && space==0) || (alpha==l-1 && space==1) )
            flag=1;
        }
        if(flag!=1)
            cout<<"\nEnter character only.....";
    }while(flag!=1);

    flag=0;
    cout<<"\n\nEnter price of item : ";
    while(!(cin>>price))
    {
        cout<<"\nEnter integer only.....";

        cout<<"\n\nEnter price of item : ";
        cin.clear();
        cin.ignore(100,'\n');
    }

    flag=0;
    cout<<"\n\nEnter quantity of item : ";
    while(!(cin>>quantity))
    {
        cout<<"\nEnter integer only.....";

        cout<<"\n\nEnter quantity of item : ";
        cin.clear();
        cin.ignore(100,'\n');
    }

    cout<<"\n\n==  Item added successfully  ==\n";
}

void item::display_item(int flag)
{
    if(flag == 1) {
        cout<<"\n     Item id is : "<<id;
        cout<<"\n\n     Item name is : "<<name;
        cout<<"\n\n     Item Price is : "<<price;
        cout<<"\n\n     Item Quantity is : "<<quantity;
        cout<<"\n\n     Date is : "<<day<<"-"<<month<<"-"<<year;
    }
    else {
        cout<<"\n     Medicine Name : "<<name;
        cout<<"\n\n     Medicine Price : "<<price;
    }
}

void item::delete_item()
{

system("cls");
int x=0,n;

cout<<"\n%%%%%%%%%%         Delete Item       %%%%%%%%%%";

cout<<"\n\nEnter the id of item to delete : ";
cin>>n;

ifstream file("item.dat");
ofstream temp("temp.dat");

while(file.read((char*)&i,sizeof(i)))
{
if(get_id()==n)
{
x=1;
cout<<"\n\nDeleted item details are given below.....\n";
display_item(1);
cout<<endl;
}
else
temp.write((char*)&i,sizeof(i));
}

file.close();
temp.close();
remove("item.dat");
rename("temp.dat","item.dat");

if(x==0)
{
    cout<<"\n\nItem id does not match with any item.....\n";
}

}

void item::modify_item()
{

system("cls");

int pos,x=0,n;

cout<<"\n%%%%%%%%%%         Update Item       %%%%%%%%%%";

cout<<"\n\nEnter the id of item to update : ";
cin>>n;

fstream file("item.dat",ios::in|ios::out);

while(!file.eof())
{
    pos=file.tellg();
    file.read((char*)&i,sizeof(i));
    if(get_id()==n)
    {
        x=1;
        break;
    }
}

if(x==1)
{
    int choice, flag=0;

    cout<<"\nItem Found.....\n";

    cout<<"\nPress 1 for updating name";
    cout<<"\nPress 2 for updating price";
    cout<<"\nPress 3 for updating quantity";

    cout<<"\n\nEnter your choice : ";
    cin>>choice;

    if(choice==1)
    {
        do
        {
        cout<<"\n\nEnter the name of item : ";
        fflush(stdin);
        gets(name);

        int l=strlen(name);
        if(l>1)
        {
        int alpha=0,space=0;
        for(int i=0;name[i]!='\0';i++)
        {
        if(isalpha(name[i]))
        alpha++;
        else if(name[i]==' ')
        space++;
        }
        if( (alpha==l && space==0) || (alpha==l-1 && space==1) )
        flag=1;
        }
        if(flag!=1)
        cout<<"\nEnter character only.....";
        }while(flag!=1);
    }

    else if(choice==2)
    {
        cout<<"\nEnter the price of item : ";
        while(!(cin>>price))
        {
            cout<<"\nEnter integer only.....";

            cout<<"\n\nEnter the price of item : ";
            cin.clear();
            cin.ignore(100,'\n');
        }
    }

    else if(choice==3)
    {
        cout<<"\nEnter the quantity of item : ";
        while(!(cin>>quantity))
        {
            cout<<"\nEnter integer only.....";

            cout<<"\n\nEnter the quantity of item : ";
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
    else
    {
        cout<<"\nYour choice is wrong.....";
    }

    if(choice==1 || choice==2 ||choice==3)
    {

    cout<<"\n%%%%%%%%%%  Item Updated Successfully   %%%%%%%%%%\n";

    file.seekg(pos);
    file.write((char*)&i,sizeof(i));
    }

}

if(x==0)
   cout<<"\n\nItem not found.....\n";

file.close();

}

int orderID = 1000;

void item::purchase_item()
{
    system("cls");

    int flag=0, pos, n;
    char x[30];

    cout<<"\n%%%%%%%%%%%         Make an Order       %%%%%%%%%%%";

    cout<<"\n\nEnter the name of medicine : ";
    fflush(stdin);
    gets(x);

    fstream file("item.dat");
    while(!file.eof())
    {
        pos=file.tellg();

        file.read((char*)&i,sizeof(i));

        if(strcmpi(get_name(),x) == 0)
        {
            flag=1;
            break;
        }
    }

    if(flag==0)
    {
        cout<<"\n\nMedicine with the given name is not available.....\n";
    }
    else
    {
        cout<<"\nHow many medicine you want to order : ";
        cin>>n;

        if(n>get_quantity())
            cout<<"\n\nSufficient quantity is not present.....\n";
        else
        {
            cout<<"\n\nOrder was Successfull, \nPress any key to get order receipt.....";
            getch();
            system("cls");

            cout<<"\n\n##########################################";
            cout<<"\n#              Order Receipt             #";
            cout<<"\n##########################################";
            cout<<"\n\n         Order ID : "<<orderID+1;
            cout<<"\n\n         Medicine Name : "<<name;
            cout<<"\n\n         Medicine Price : "<<price;
            cout<<"\n\n         Medicine Quantity : "<<n;
            cout<<"\n\n         Total Amount : "<<price*n;
            cout<<"\n\n         Order Date : "<<day<<"-"<<month<<"-"<<year;
            cout<<"\n\n##########################################\n\n";

            update_quantity(n);

            file.seekg(pos);
            file.write((char*)&i,sizeof(i));

            ofstream temp("sale.txt",ios::app);
            temp<<"    Order ID : "<<orderID+1;
            temp<<"\n\n    Item ID : "<<id;
            temp<<"\n\n    Item Name : "<<name;
            temp<<"\n\n    Item Price : "<<price;
            temp<<"\n\n    Item Quantity : "<<n;
            temp<<"\n\n    Total Amount : "<<price*n;
            temp<<"\n\n    Order Date : "<<day<<"-"<<month<<"-"<<year;
            temp<<"\n\n............................................\n\n";

            temp.close();

            file.close();
        }
    }

}

void item::view_sale()
{
    system("cls");

    char c;
    int flag=0;

    ifstream temp("sale.txt");
    while(temp)
    {
        if(flag==0)
        {
            cout<<"\n@@@@@@@@@@@         Sale of Items       @@@@@@@@@@\n\n\n";
            flag=1;
        }

        temp.get(c);
        cout<<c;
    }
    temp.close();

    if(flag==0)
    {
        cout<<"\n\nNo Sale is done till now.....\n\n";
    }
}

int main()
{
    int choice,ch1;
    char ch2='y',ch3='y', ch4='y', user_name[30], password[30];

    do
    {
    system("cls");
    cout<<"\n==  WELCOME TO MEDICAL STORE  ==";
    cout<<"\n\n\t1. Customer";
    cout<<"\n\n\t2. Admin";
    cout<<"\n\n\t3. Exit";

    cout<<"\n\n\nEnter your choice : ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            do
            {
                system("cls");
                cout<<"\n==  WELCOME CUSTOMER  ==";
                cout<<"\n\n1. Purchase Medicine";
                cout<<"\n\n2. See Medicine List";
                cout<<"\n\n3. Exit";

                cout<<"\n\n\nEnter your choice : ";
                cin>>ch1;

                if(ch1==1)
                {
                    i.purchase_item();
                }

                else if(ch1==2)
                {
                int x=0;

                system("cls");

                ifstream file("item.dat");
                while(file.read((char*)&i,sizeof(i)))
                {
                    if(x==0)
                    {
                        cout<<"\n@@@@@@@@@@    Medicine List    @@@@@@@@@@\n";
                        x=1;
                    }

                i.display_item(0);
                cout<<"\n\n.............................................\n";
                }
                file.close();

                if(x==0)
                {
                system("cls");
                cout<<"\n\nNo item found.....\n\n";
                }

                }

                else if(ch1==3)
                {
                    cout<<"\nSuccessfully exited from customer menu.....";
                    break;
                    ch2='n';
                }

                if(ch2!='n')
                {
                    cout<<"\n\nWant to go back to customer menu (y/n) : ";
                    cin>>ch2;
                }

                }while(ch2=='y');
                break;

        case 2:
                system("cls");
                cout<<"\nEnter user name : ";
                fflush(stdin);
                gets(user_name);

                    int j;
                    cout<<"\nEnter the password : ";

                    for(j=0;j<16;j++)
                    {
                        password[j]=getch();

                        if(password[j]==13)
                            break;
                        else
                            cout<<"*";
                    }

                    password[j]='\0';

                if(strcmp(user_name,"admin")==0 && strcmp(password,"12345")==0)
                {
                do
                {
                system("cls");
                cout<<"\n==  WELCOME ADMIN  ==";
                cout<<"\n\n1. Add Item";
                cout<<"\n\n2. See Item List";
                cout<<"\n\n3. Modify Item";
                cout<<"\n\n4. Delete Item";
                cout<<"\n\n5. View Sales";
                cout<<"\n\n6. Exit";

                cout<<"\n\n\nEnter your choice : ";
                cin>>ch1;

                if(ch1==1)
                {

                fstream file;

                file.open("item.dat",ios::in);
                while(file.read((char*)&i,sizeof(i)))
                {
                z=i.get_id();
                }
                file.close();

                file.open("item.dat",ios::app);
                i.add_item();
                file.write((char*)&i,sizeof(i));
                file.close();

                }

                else if(ch1==2)
                {
                int x=0;

                system("cls");

                ifstream file("item.dat");
                while(file.read((char*)&i,sizeof(i)))
                {
                    if(x==0)
                    {
                        cout<<"\n@@@@@@@@@@    All Items    @@@@@@@@@@\n";
                        x=1;
                    }

                i.display_item(1);
                cout<<"\n\n.............................................\n";
                }
                file.close();

                if(x==0)
                {
                system("cls");
                cout<<"\n\nNo item found.....\n\n";
                }

                }

                else if(ch1==3)
                    i.modify_item();
                else if(ch1==4)
                    i.delete_item();
                else if(ch1==5)
                    i.view_sale();
                else if(ch1==6)
                {
                    cout<<"\nSuccessfully exited from admin menu.....";
                    break;
                    ch2='n';
                }

                if(ch2!='n')
                {
                    cout<<"\n\nWant to go back to admin menu (y/n) : ";
                    cin>>ch2;
                }

              }while(ch2=='y');
            }
            else
                cout<<"\n\nUsername and password is invalid.....\n";
            break;

        case 3:
            exit(0);
        }

        cout<<"\n\nWant to go back to main menu (y/n) : ";
        cin>>ch3;

    }while(ch3=='y');
}


