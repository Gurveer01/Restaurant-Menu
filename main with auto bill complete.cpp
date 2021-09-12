#include<fstream>
#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<string.h>
using namespace std;

class menu
{
public:
    int itemcode;
    char itemname[20];
    float price;
    friend void searchbycode();
    friend void searchbyname();
    friend void removeitem();
    friend void updateitem();
public:
    void accept()
    {
        cout<<endl<<"Enter Item Code :";
        cin>>itemcode;
        cout<<endl<<"Enter Item Name :";
        cin>>itemname;
        cout<<endl<<"Enter Price :";
        cin>>price;
    }
    void display()
    {
        cout<<endl<<setw(2)<<itemcode<<setw(25)<<itemname<<setw(15)<<price;
    }
};
menu obj;

class bill
{
    public:
    int billno,icode,qty;
    float price,subtotal;
    char date[15],cname[50],iname[50];
    friend void printbillbyno();
    void prebill()
    {
        cout<<endl<<"Enter Date :";
        cin>>date;
        cout<<endl<<"Enter Customer Name :";
        cin>>cname;
    }

    void cart()
    {
        while(1)
        {
            cout<<endl<<"Enter Icode :";
            cin>>icode;
            fstream rd;
            rd.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
            rd.seekg(0,ios::end);
            int s=rd.tellg();
            int count=s/sizeof(obj);
            rd.seekg(0,ios::beg);
            int flag=0;
            for (int i=1;i<=count;i++)
            {
                rd.read((char*)&obj,sizeof(obj));
                if(obj.itemcode==icode)
                {
                    price=obj.price;
                    strcpy(iname,obj.itemname);
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                cout<<endl<<"Enter Quantity :";
                cin>>qty;
                subtotal=price*qty;
                break;
            }
            else
            {
                cout<<endl<<"Invalid item code";
                break;
            }
        }
    }
};
bill obj2;

void printbill(int n)
{
    float amount=0;
    fstream rd;
    rd.open("d:\\c++ projects\\vmm restaurant menu project\\bill.txt",ios::in);
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";

    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int c=s/sizeof(obj2);
    rd.seekg(0,ios::beg);

    for(int i=1;i<=c;i++)
    {
        rd.read((char*)&obj2,sizeof(obj2));
        if(obj2.billno==n)
        {
            cout<<endl<<"Dated: "<<setw(5)<<obj2.date<<"\t\t Customer Name :"<<setw(5)<<obj2.cname<<"\t\t Bill Number  "<<obj2.billno;
            cout<<endl<<"**************************************************************************************";
            cout<<endl<<"\t\t\t\t Welcome to My Restaurant";
            cout<<endl<<"**************************************************************************************";
            cout<<endl<<"S No."<<"\t\t"<<setw(10)<<"Item Name"<<"\t"<<setw(15)<<"Price"<<setw(10)<<"Quantity"<<setw(12)<<"Subtotal"<<endl;
            break;
        }
    }
    rd.seekg(0,ios::beg);
    int i=1;
    for(int j=1;j<=c;j++)
    {
        rd.read((char*)&obj2,sizeof(obj2));
        if(obj2.billno==n)
        {
            cout<<endl<<i<<"\t\t"<<setw(10)<<obj2.iname<<"\t"<<setw(15)<<obj2.price<<setw(10)<<obj2.qty<<setw(12)<<obj2.subtotal;
            i++;
            amount=amount+obj2.subtotal;
        }
    }
    cout<<endl<<endl<<"\t\t\t\t\t\tAmount :"<<amount;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
}

void raisebill()
{
    obj2.prebill();

    int c;
    fstream bl;
    bl.open("d:\\c++ projects\\vmm restaurant menu project\\billno.txt",ios::in);
    bl.read((char*)&c,sizeof(c));
    obj2.billno=c+1;

    int value=0;
    value=value+obj2.billno;
    fstream wr;
    wr.open("d:\\c++ projects\\vmm restaurant menu project\\temp1.txt",ios::out);
    wr.write((char*)&value,sizeof(value));
    bl.close();
    wr.close();
    remove("d:\\c++ projects\\vmm restaurant menu project\\billno.txt");
    rename("d:\\c++ projects\\vmm restaurant menu project\\temp1.txt","d:\\c++ projects\\vmm restaurant menu project\\billno.txt");

    while(1)
    {
        obj2.cart();
        fstream wr2;
        wr2.open("d:\\c++ projects\\vmm restaurant menu project\\bill.txt",ios::app);
        wr2.write((char*)&obj2,sizeof(obj2));
        wr2.close();
        cout<<endl<<"Press 1 if you want to Add more items to Bill or Press 2 to create Bill";
        int choice;
        cout<<endl<<"Enter Choice :";
        cin>>choice;
        if (choice!=1)
        {
          printbill(obj2.billno);
          break;
        }

    }
}

void printbillbyno()
{
    int no;
    fstream pr;
    pr.open("d:\\c++ projects\\vmm restaurant menu project\\bill.txt",ios::in);
    pr.seekg(0,ios::end);
    cout<<endl<<"Enter Bill No. :";
    cin>>no;
    int s=pr.tellg();
    int c=s/sizeof(obj2);
    pr.seekg(0,ios::beg);

    for(int j=1;j<=c;j++)
    {
        pr.read((char*)&obj2,sizeof(obj2));
        if(obj2.billno==no)
        {
            printbill(no);
            break;
        }
        else if(j==c)
        {
            cout<<endl<<"Invalid Bill No.";
        }
    }
}

void searchbycode()
{
    int code;
    fstream se;
    se.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
    se.seekg(0,ios::end);
    cout<<endl<<"Enter Item Code :";
    cin>>code;

    int n=se.tellg();
    se.seekg(0,ios::beg);
    int c=n/sizeof(obj);
    for(int i=1;i<=c;i++)
    {
        se.read((char*)&obj,sizeof(obj));
        if(obj.itemcode==code)
        {
            cout<<endl<<"**************************************************************************************";
            cout<<endl<<"Item Code"<<setw(20)<<"Item Name"<<setw(15)<<"Price";
            cout<<endl<<"**************************************************************************************";
            obj.display();
            break;
        }
        else if(i==c)
        {
            cout<<endl<<"Invalid Item Code";
            break;
        }
    }
}

void searchbyname()
{
    char name[20];
    fstream se;
    se.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
    se.seekg(0,ios::end);
    cout<<endl<<"Enter Item Name :";
    cin>>name;

    int n=se.tellg();
    se.seekg(0,ios::beg);
    int c=n/sizeof(obj);
    for(int i=1;i<=c;i++)
    {
        se.read((char*)&obj,sizeof(obj));
        if(stricmp(obj.itemname,name)==0)
        {
            cout<<endl<<"**************************************************************************************";
            cout<<endl<<"Item Code"<<setw(20)<<"Item Name"<<setw(15)<<"Price";
            cout<<endl<<"**************************************************************************************";
            obj.display();
            break;
        }
        else if(i==c)
        {
            cout<<endl<<"Invalid Item Name";
            break;
        }
    }
}

void addmenu()
{
    obj.accept();
    fstream wr;
    wr.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::app);
    wr.write((char*)&obj,sizeof(obj));
    wr.close();
    cout<<endl<<"Item Added Successfully";
}

void removeitem()
{
    int icode;
    cout<<endl<<"Enter Item Code for deletion :";
    cin>>icode;

    fstream rd;
    rd.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int count=s/sizeof(obj);
    rd.seekg(0,ios::beg);

    fstream wr;
    wr.open("d:\\c++ projects\\vmm restaurant menu project\\temp.txt",ios::out);
    for (int i=1;i<=count;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(icode==obj.itemcode)
        {
            cout<<endl<<"Item Deleted";
        }
        else
        {
            wr.write((char*)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();

    remove("d:\\c++ projects\\vmm restaurant menu project\\menu.txt");
    rename("d:\\c++ projects\\vmm restaurant menu project\\temp.txt","d:\\c++ projects\\vmm restaurant menu project\\menu.txt");
}

void updateitem()
{
    int icode;
    cout<<endl<<"Enter Item Code for updation :";
    cin>>icode;

    fstream rd;
    rd.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int count=s/sizeof(obj);
    rd.seekg(0,ios::beg);

    fstream wr;
    wr.open("d:\\c++ projects\\vmm restaurant menu project\\temp.txt",ios::out);
    for (int i=1;i<=count;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(icode==obj.itemcode)
        {
            obj.accept();
            wr.write((char*)&obj,sizeof(obj));
            cout<<endl<<"Item Updated";
        }
        else
        {
            wr.write((char*)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();


    remove("d:\\c++ projects\\vmm restaurant menu project\\menu.txt");
    rename("d:\\c++ projects\\vmm restaurant menu project\\temp.txt","d:\\c++ projects\\vmm restaurant menu project\\menu.txt");
}

void readmenu()
{
    fstream rd;
    rd.open("d:\\c++ projects\\vmm restaurant menu project\\menu.txt",ios::in);
    int s;
    rd.seekg(0,ios::end);
    s=rd.tellg();
    rd.seekg(0,ios::beg);
    int c=s/sizeof(obj);
    cout<<endl<<"**************************************************************************************";
    cout<<endl<<setw(25)<<"MENU";
    cout<<endl<<"**************************************************************************************";
    cout<<endl<<"Item Code"<<setw(20)<<"Item Name"<<setw(15)<<"Price";
    cout<<endl<<"**************************************************************************************";

    for(int i=1;i<=c;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
    }
    cout<<endl<<endl<<endl<<endl<<endl;
}

void resetbillno()
{
    int no=0;
    fstream bl;
    bl.open("d:\\c++ projects\\vmm restaurant menu project\\billno.txt",ios::out);
    bl.write((char*)&no,sizeof(no));
    bl.close();
    cout<<endl<<"Bill No. Reset Done";
}

main()
{
  int e=0,choice;
  while(e!=1)
  {
      cout<<endl<<"**************************************************************************************";
      cout<<endl<<"Press 1 to Add New Item in Menu";
      cout<<endl<<"Press 2 to View Menu List";
      cout<<endl<<"Press 3 to Remove Item from Menu";
      cout<<endl<<"Press 4 to Update Item from Menu";
      cout<<endl<<"Press 5 to Search Item by Code";
      cout<<endl<<"Press 6 to Search Item by Name";
      cout<<endl<<"Press 7 to Raise New Invoice";
      cout<<endl<<"Press 8 to Reprint Bill";
      cout<<endl<<"Press 9 to Reset Bill No.";
      cout<<endl<<"Press 10 to Exit";
      cout<<endl<<"Enter Choice :";
      cin>>choice;
      switch(choice)
      {
      case 1:
        {
            addmenu();
            break;
        }
      case 2:
        {
            readmenu();
            break;
        }
      case 3:
        {
            removeitem();
            break;
        }
      case 4:
        {
            updateitem();
            break;
        }
        case 5:
        {
            searchbycode();
            break;
        }
      case 6:
        {
            searchbyname();
            break;
        }
      case 7:
        {
            raisebill();
            break;
        }
      case 8:
        {
            printbillbyno();
            break;
        }
        case 9:
        {
            resetbillno();
            break;
        }
      case 10:
        {
            e=1;
            break;
        }

      }
  }
}
