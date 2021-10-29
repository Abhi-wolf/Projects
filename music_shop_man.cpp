#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class music
{
   private:
    char  track_id[10];
    char  name[20];
    char  category[10];
    int   year_of_release;
    int   stock_no;
    float price;
   public:
    void add_record();
    void enter_data();
    void dislpay_record();
    void show_data();
    void search_record();
    void del_record();
    void edit_record();
    int  category_type();
    void initiate();

}global;



// ************************************************* DELETE FUNCTION *****************************************************

void music :: del_record()
{
    char deltrack[10];
    cout<<"Enter track id of record to delete : ";
    cin>>deltrack;
    ifstream obj6("test.dat", ios::binary);
    ofstream obj7("new.dat", ios::binary | ios::app);
    while(obj6.read((char*)&global,sizeof(global)))
    {
        if(strcmp(global.track_id,deltrack)!=0)
        {
            obj7.write((char*)&global,sizeof(global));
        }
    }
    obj6.close();
    obj7.close();
    remove("test.dat");
    rename("new.dat","test.dat");
    cout<<"Data deleted sucessfully"<<endl;
    initiate();
}



//***************************************************** EDIT FUNCTION *****************************************************

void music :: edit_record()
{
    char trackingid[10];
    ifstream obj4("test.dat", ios::binary);
    ofstream obj5("newtest.dat", ios::binary | ios::app);
    cout<<"Enter tracking id of file to modify: ";
    cin>>trackingid;
    while(obj4.read((char*)&global,sizeof(global)))
    {
        if(strcmp(global.track_id,trackingid)==0)
          enter_data();
        obj5.write((char*)&global,sizeof(global));
    }
    obj4.close();
    obj5.close();
    remove("test.dat");
    rename("newtest.dat","test.dat");
    initiate();
  //  exit(0);

}


// ********************************************** SEARCH FUNCTION ******************************************************

void music :: search_record()
{
    ifstream obj3("test.dat",ios::binary);
    char trackid[10];
    int num2=0;
    cout<<"Enter Track ID : ";
    cin>>trackid;
    if(!obj3)
    {
        cout<<"No data in file. "<<endl;
        exit(0);
    }
    else
    {
        while(obj3.read((char*)&global,sizeof(global)))
        {
            if(strcmp(global.track_id,trackid)==0)
            {
                cout<<"Data found. "<<endl;
                show_data();
                num2++;
            }
        }
    }
    if(num2==0)
      cout<<"Data not found"<<endl;
    obj3.seekg(0);
    obj3.close();
    initiate();

}



// ********************************************** SHOW DATA FUNCTION ***************************************************

void music :: show_data()
{
   cout<<"TRACK'S ID   : "<<track_id<<endl;
   cout<<"NAME         : "<<name<<endl;
   cout<<"CATEGORY     : "<<category<<endl;
   cout<<"RELEASE DATE : "<<year_of_release<<endl;
   cout<<"STOCK NO     : "<<stock_no<<endl;
   cout<<"PRICE        : "<<price<<endl; 
   cout<<"\n";
}



// ******************************************* DISPLAY DATA FUNCTION ***************************************************
void music :: dislpay_record()
{
    ifstream obj2;
    obj2.open("test.dat", ios::in | ios::binary);
    if(!obj2)
    {
        cout<<"No data present "<<endl;
        exit(0);
    }
    obj2.read((char*)&global,sizeof(global));
    while(!obj2.eof())
    {
      show_data();
      obj2.read((char*)&global,sizeof(global));
    }
    obj2.close();
  //  exit(0);
    initiate();
}



// ******************************************** ENTER DATA FUNCTION *************************************************

void music :: enter_data()
{
    int cat;
    cout<<"--------------- Enter data -------------------"<<endl;
    cout<<"Enter Track Id :";
    cin>>track_id;
    chk:
    if(strcmp(track_id,"\0")==0)
    {
       cout<<"Trcak's Identity must be legal \n";
       goto chk;
    }
    cout<<"Enter name :";
    cin>>name;
    cout<<"Enter track's category AUDIO,VIDEO,MP3...\n";
    cat=category_type();
    if(cat == 1)
      strcpy(category,"AUDIO");
    if(cat == 2)
      strcpy(category,"VIDEO");
    if(cat == 3)
      strcpy(category,"MP3");
    if(cat == 4)
    {
       cout<<"Give category: "<<endl;
       cin>>category;
    }
    
    cout<<"Enter release date (only numbers): ";
    cin>>year_of_release;
    dte:
    if(year_of_release<1900 )
    {
        cout<<"Invalid release date. "<<"\n";
        cin>>year_of_release;
        goto dte;
    }

    cout<<"Enter no of stocks: ";
    cin>>stock_no;
    cout<<"Enter price of record: ";
    cin>>price;
}



// ******************************************* CATEGORY FUNCTION **************************************************

int music :: category_type()
{
   int cate;
   cout<<"Enter the type of category: \n";
   cout<<"1. AUDIO "<<endl;
   cout<<"2. VIDEO "<<endl;
   cout<<"3. MP3 "<<endl;
   cout<<"4. OTHER OPTIONS "<<endl;
   cin>>cate;
   return cate;
}



// ********************************************* ADD RECORD FUNCTION **********************************************

void music :: add_record()
{
    ofstream obj1;
    obj1.open("test.dat", ios::app | ios::binary);
    if(!obj1)
    {
        cout<<"Not enough space.";
        exit(0);
    }
    char ch='y';
    while(ch=='y')
    {
        global.enter_data();
        obj1.write((char*)&global,sizeof(global));
        cout<<"*******DATA ENTERED*********"<<endl;
        cout<<"Enter y to continue: ";
        cin>>ch;
        if(ch=='y' || ch=='Y')
         initiate();
    }
    obj1.close();
    //exit(0);
    
}



// ******************************************* INITIATE FUNCTION ****************************************************

void music :: initiate()
{
    int num1;
    cout<<"Enter: "<<endl;
    cout<<"1. Add Record "<<endl;
    cout<<"2. Display Record "<<endl;
    cout<<"3. Search Record "<<endl;
    cout<<"4. Edit Record "<<endl;
    cout<<"5. Delete Record "<<endl;
    //cin>>num1;
    char p='y';
    while(p=='y'  || p=='Y')
    {
        cout<<"Enter choice: ";
        cin>>num1;
    switch(num1)
    {
      case 1:
       global.add_record();
       break;
      case 2:
       global.dislpay_record();
       break;
      case 3:
       global.search_record();
       break;
      case 4:
       global.edit_record();
       break;
      case 5:
       global.del_record();
       break;
      default:
       cout<<"wrong choice"<<endl;
    }
    cout<<"Want to go to main menu press y/Y ";
    cout<<" else any other key ";
    cin>>p;
    if(p=='y' || p=='Y')
     initiate();
    else
     exit(0);
    }

}



void welcome_screen()
{
    cout<<" **************************  WELCOME TO MUSIC SHOP MANAGEMENT PROJECT  **************************"<<endl;
    cout<<"********************************  PROJECT BY ABHIJEET KUMAR  ************************************\n\n"<<endl;
}




// ***************************************** MAIN FUNCTION *******************************************************

int main()
{
    char password[10]="Singh";
    char passwd[10];
    welcome_screen();
    asd:
    cout<<"&&&&&&&&&&&&&&&  ENTER PASSWORD TO ENTER PROGRAM  &&&&&&&&&&&&&&&&"<<endl;
    cin>>passwd;
    if(strcmp(password,passwd)==0)
    {
       global.initiate();
    }
    else
    {
        cout<<"WRONG PASSWORD  TRY AGAIN "<<endl;
        goto asd;
    }

  return 0;
}