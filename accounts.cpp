/**

Account Information System :

This is used to make the records of the customers of a Bank. This performs operations like storing data,
displaying the stored data, modifying the data and so on.

This application is used by the bank employee form makin records of the customers.

done by : V. Naveen Kumar(1601-15-733-301) and G. Sai Krishna(1601-15-733-303).
*/

#include<iostream>
#include<fstream>
#include<cstdlib>//to use the system() function
using namespace std;

class account_info
{
    private:
        char account_number[20];
        char firstName[10];
        char lastName[10];
        char mobile_no[10];
        double total_Balance;
    public:
        void read();
        void show();
        void write_file();
        void read_file();
        void search_();
        void del();
        void edit();
};

//to get the details from the customers
void account_info::read()
{

    cout<<"\nEnter Account Number: ";
    cin>>account_number;
    cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"enter mobile no. : ";
    cin>>mobile_no;
    cout<<"Enter Balance: ";
    cin>>total_Balance;
    cout<<endl;
}

//to display the details of the customers
void account_info::show()
{
    cout<<"\nAccount Number    : "<<account_number<<endl;
    cout<<"First Name        : "<<firstName<<endl;
    cout<<"Last Name         : "<<lastName<<endl;
    cout<<"Mobile Number     : "<<mobile_no<<endl;
    cout<<"Current Balance   : Rs.  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}

//to store the customer details into a file(here binary file is used to store)
void account_info::write_file()
{
    ofstream outfile;
    outfile.open("acc_data.acc", ios::binary|ios::app);
    read();
    outfile.write((char *)this, sizeof(*this));
    outfile.close();
}

//to display all customers details
void account_info::read_file()
{
    system("cls");
    int c=1;
    cout<<"\t\t*******************************************";
    cout<<"\n\t\t\t\"Account Information System\"\n"<<endl;
    cout<<"\t\t*******************************************\n\n";
    ifstream infile;
    infile.open("acc_data.acc", ios::binary);
    if(!infile)
    {
        cout<<"\nError in Opening!\n File Not Found!!"<<endl;
        return;
    }


    cout<<"\n\n****Data from file****\n\n"<<endl;
    while(!infile.eof())
    {

        if(infile.read((char*)(this), sizeof(*this))>0)
        {
            cout<<"\nRecord "<<c<<":\n";
            show();
        }
        c++;
    }
    infile.close();
}

//to search a record based on the record number
void account_info::search_()
{
    system("cls");
    cout<<"\t\t\t*******************************************";
    cout<<"\n\t\t\t\t\"Account Information System\"\n"<<endl;
    cout<<"\t\t\t*******************************************\n\n";
    int n;
    ifstream infile;
    infile.open("acc_data.acc", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    if(count<=0)
    {
        cout<<"file is empty......\n No data can be displayed\n";
        return;
    }
    cout<<"\n There is/are "<<count<<" record in the file"<<endl;
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read((char*)(this), sizeof(*this));
    show();
}

//to delete the customer details
void account_info::del()
{
    system("cls");
    cout<<"\t\t\t*******************************************";
    cout<<"\n\t\t\t\t\"Account Information System\"\n"<<endl;
    cout<<"\t\t\t*******************************************\n";
    int n;
    ifstream infile;
    infile.open("acc_data.acc", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    if(count<=0)
    {
        cout<<"file is empty......\n no data can be displayed\n";
    }
    else
    {
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("temp.acc", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read((char*)(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write((char*)(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("acc_data.acc");
    rename("temp.acc", "acc_data.acc");
    }
}

//to modify the customer details
void account_info::edit()
{
    system("cls");
    cout<<"\t\t\t*******************************************";
    cout<<"\n\t\t\t\t\"Account Information System\"\n"<<endl;
    cout<<"\t\t\t*******************************************\n\n";
    int n;
    fstream iofile;
    iofile.open("acc_data.acc", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    if(count<=0)
    {
        cout<<"\nthere are no records in the file....... \n\n";
        return;
    }
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read((char*)(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show();
    iofile.close();
    iofile.open("acc_data.acc", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read();
    iofile.write((char*)(this), sizeof(*this));
}
int main()
{
    account_info A;
    int choice;
    cout<<"\t\t\t*******************************************";
    cout<<"\n\t\t\t\t\"Account Information System\"\n"<<endl;
    cout<<"\t\t\t*******************************************\n";
    while(choice!=6)
    {
        cout<<"\nSelect one option below ";
        cout<<"\n\t1)Add record to file";
        cout<<"\n\t2)Show record from file";
        cout<<"\n\t3)Search Record in file";
        cout<<"\n\t4)Delete Record from file";
        cout<<"\n\t5)Modify Record in file";
        cout<<"\n\t6)Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                A.write_file();
                break;
            case 2:
                A.read_file();
                break;
            case 3:
                A.search_();
                break;
            case 4:
                A.del();
                break;
            case 5:
                A.edit();
                break;
            case 6:
                break;
            default:
                cout<<"\nEnter corret option(i.e, 1-6 only)\n\n";
        }
    }
    return 0;
}
