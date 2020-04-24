#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class student
{
    int rollno;
    string name;
    int p_marks,c_marks,m_marks,e_marks,cs_marks;
    double per;
    string grade;
    void calculate();//To calculate grade
public:
    void getdata();
    void showdata() const;
    void show_tabular() const;
    int retrollno() const;
};
void student:: calculate()
{
    per = (p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
    if(per>=90) grade = "A1";
    else if(per>=80) grade = "A2";
    else if(per>=70) grade = "B";
    else if(per>=60) grade = "C";
    else if(per>=50 ) grade = "D";
    else if(per>=40) grade = "E";
    else grade = "Failed";
}
void student:: getdata()
{
    cout<<"\nEnter the roll no of student ";
    cin>>rollno;
    cout<<"\nEnter the name of the student ";
    cin.ignore();
    getline(cin,name);
    cout<<"\n**** ENTER ALL MARKS OUT OF 100 ****\n";
    cout<<"Enter Physics Marks: ";
    cin>>p_marks;
     cout<<"Enter Chemistry Marks: ";
    cin>>c_marks;
     cout<<"Enter Maths Marks: ";
    cin>>m_marks;
     cout<<"Enter English Marks: ";
    cin>>e_marks;
     cout<<"Enter Computer Science Marks: ";
    cin>>cs_marks;
    calculate();
}

void student:: showdata() const
{
    cout<<"Name of the student is "<<name<<endl;
    cout<<"Roll No of student is "<<rollno<<endl;
    cout<<"---ALL MARKS ARE OUT OF 100---"<<endl;
    cout<<"Physics marks are: "<<p_marks<<endl;
    cout<<"Chemistry marks are: "<<c_marks<<endl;
    cout<<"Maths marka are : "<<m_marks<<endl;
    cout<<"Computer Science marks are: "<<cs_marks<<endl;
    cout<<"English marks are: "<<e_marks<<endl;
    cout<<"Percentage of student is "<<per<<endl;
    cout<<"Grade of the student is "<<grade<<endl;
}
void student:: show_tabular() const
{
    cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
 <<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}
int student:: retrollno() const
{
    return rollno;
}

void write_student();
void display_all();
void display_sp(int);//Accept roll number and read binary file from the record
void modify_student(int);
void delete_student(int);
void class_result();//display all records in tabular from
void result();
void intro();//display welcome screen
void entry_menu();

int main()
{
    int n;
    intro();
    do
    {
      system("cls");
      cout<<"\n\n\n\t MAIN MENU";
      cout<<"\n\n\n\t 1. Result Menu";
      cout<<"\n\n\n\t 2. Entry Edit Menu";
      cout<<"\n\n\n\t 3. Exit";
      cout<<"\n\n\n\t PLEASE SELECT YOUR OPTION(1-3)";
      cin>>n;
      switch(n)
      {
          case 1: result();
          break;
          case 2: entry_menu();
          break;
          case 3:
          break;
          default:
            cout<<"Pls enter a correct choice provided in main menu";
      }
    }while(n!=3);
    return 0;
}
void write_student()
{
    student st;
    ofstream outFile;
    outFile.open("students.dat",ios::binary | ios::app);
    st.getdata();
    outFile.write(reinterpret_cast<char *>(&st),sizeof(student));
    cout<<"\nStudent record has been created";
    cin.ignore();
    cin.get();
}

void display_all()
{
    student st;
    ifstream inFile;
    inFile.open("students.dat",ios::binary);
    if(!inFile)
    {
        cout<<endl<<"File could not be open !! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\nDISPLAYING ALL RECORD\n";
    while(inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n============================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student st;
    ifstream inFile;
    inFile.open("students.dat",ios::binary);
    if(!inFile)
    {
        cout<<endl<<"File couldn't be open !! Press any key...!";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while(inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag = true;
        }
    }
    if(flag == false)
    {
        cout<<endl<<"Record not exist\n";
    }
     cin.ignore();
     cin.get();
}
void modify_student(int n)
{
    bool found = false;
    student st;
    fstream File;
    File.open("student.dat",ios::in | ios::out | ios::binary);
    if(!File)
    {
        cout<<"File could not be open !! Press any key\n";
        cin.ignore();
        cin.get();
        return;
    }
    while(!File.eof() and found==false)
    {
      File.read(reinterpret_cast<char*>(&st),sizeof(student));
      if(st.retrollno()==n)
      {
          st.showdata();
          cout<<"\n\n\nPlease enter new details of the student"<<endl;
          st.getdata();
          int pos = (-1) * static_cast<int>(sizeof(st));
          File.seekp(pos,ios::cur);
          File.write(reinterpret_cast<char *> (&st),sizeof(student));
          cout<<endl<<"Record Updated"<<endl;
          found = true;
      }
    }
    File.close();
    if(found == false)
    {
        cout<<endl<<"Record not found!!"<<endl;
    }
    cin.ignore();
    cin.get();
}
void delete_student(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<endl<<"Could not open file!! Press any key to continue"<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat",ios::out);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
    {
        if(st.retrollno()!=n)
        {
            outFile.write(reinterpret_cast<char *>(&st),sizeof(student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cin.ignore();
    cin.get();
    return;
}
void class_result()
{
    student st;
    ifstream inFile;
    if(!inFile)
    {
        cout<<endl<<"File couldn't be open !! Press any key to continue!!"<<endl;
        cin.ignore();
        cin.get();
        return;
    }
     cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
 cout<<"==========================================================\n";
 cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;

 cout<<"==========================================================\n";
 while(inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
 {
     st.show_tabular();
 }
 cin.ignore();
 cin.get();
 inFile.close();
}

void result()
{
    int ch;
    int rno;
    system("cls");
    cout<<endl<<"====RESULT MENU===="<<endl;
    cout<<"\n\n\n\t1. Class Result";
    cout<<"\n\n\t2. Student Report Card";
    cout<<"\n\n\t3. Back to Main Menu";
    cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
    case 1:
        class_result();
        break;
    case 2:
        cout<<endl<<"Enter roll no of the student "<<endl;
        cin>>rno;
        display_sp(rno);
        break;
    case 3:
        break;
    default:
        cout<<endl<<"Please enter right choice"<<endl;
    }
}
void intro()
{
    cout<<"\n\n\n\t Welcome to student report card system";
    cout<<"\n\n\n\t Press Enter to Continue";
    cout<<"\n\n\n\t Made By: Kapil Sharma";
    cout<<"\n\n\n\t IMS Engineering College Ghaziabad";
    cin.get();
}

void entry_menu()
{
    int ch;
    int rnum;
    system("cls");
     cout<<"\n\n\n\tENTRY MENU";
     cout<<"\n\n\t1.CREATE STUDENT RECORD";
     cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
     cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
     cout<<"\n\n\t4.MODIFY STUDENT RECORD";
     cout<<"\n\n\t5.DELETE STUDENT RECORD";
     cout<<"\n\n\t6.BACK TO MAIN MENU";
     cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
     cin>>ch;
    system("cls");
    switch(ch)
 {
 case 1:
      write_student();
      break;
 case 2:
      display_all();
      break;
 case 3:
     cout<<"\n\n\tPlease Enter The roll number ";
     cin>>rnum;
     display_sp(rnum); break;
 case 4:
     cout<<"\n\n\tPlease Enter The roll number ";
     cin>>rnum;
     modify_student(rnum);break;
 case 5:
     cout<<"\n\n\tPlease Enter The roll number ";
     cin>>rnum;
     delete_student(rnum);
     break;
 case 6:
     break;
 default: cout<<"Enter right key!!";
   entry_menu();
 }
}

