
//--------------------------------------------------------------
//
//--------------------------------------------------------------

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

//--------------------------------------------------------------
//                   CLASS USED IN PROJECT
//--------------------------------------------------------------
int nm,pn,prc;
char c;
char nam[50];
class seats
{ int vseat,nseat;
  public:

  seats()
  {vseat=nseat=10;}

   void ent_seat()
	 {
	   cout<<"Enter the no. of seats for veg. customers : ";
	   cin>>vseat;
	   cout<<"\nEnter the no. of seats for non-veg. customers : ";
	   cin>>nseat;
	 }

   void upd_vseat()
   { vseat=vseat-nm;}

   void upd_nseat()
   { nseat=nseat-nm;}

int retvseat()
{ return vseat;}

int retnseat()
{ return nseat;}

};

class product
{
 int pno;
 char name[50],cat;
 float price,qty,tax,dis;
 public:
	void create_product()
	{
	 cout<<"\nPlease Enter The Product No. of The Product ";
	 cin>>pno;
	 cout<<"\n\nPlease Enter The Name of The Product ";
	 gets(name);
	 cout<<"\nPlease Enter The Price of The Product ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 cout<<"\nPlease enter the category veg or non-veg(v/n) ";
	 cin>>cat;
	 }

	void show_product()
	{
	 cout<<"\nThe Product No. of The Product : "<<pno;
	 cout<<"\nThe Name of The Product : ";
	 puts(name);
	 cout<<"\nThe Price of The Product : "<<price;
	 cout<<"\nDiscount : "<<dis;
	 }



  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

  char retcat()
  { return cat;}

};         //class ends here



//--------------------------------------------------------------
//      global declaration for stream object, object
//--------------------------------------------------------------

 fstream fp;
 product pr,prod[200],u;
 seats st;

//--------------------------------------------------------------
//      function to allocate seats
//--------------------------------------------------------------

void alloc_seats()
  {  fp.open("seat.dat",ios::app);
     if(!fp)
     { cout<<"Enter the no. of seats for veg. and non-veg. tables\n";
       st.ent_seat();
       fp.write((char*)&st,sizeof(seats));
     }
     else
     { int pos=-1*sizeof(st);
       fp.seekp(pos,ios::cur);
       cout<<"Enter the new no. of seats for veg. and non-veg. tables\n";
       st.ent_seat();
       fp.write((char*)&st,sizeof(seats));
     }
  fp.close();
  }

//----------------------------------------------------------------------
//      function to check if required no. of seats are available or not
//----------------------------------------------------------------------

void asgn_seats()
{ char a;
  fp.open("seat.dat",ios::out|ios::app);
  if(c=='v')
  { if(st.retvseat()>nm)
    {
      cout<<"Welcome to the cafe your required no. of seats are available!!\n";
      getch();
      st.upd_vseat();
      int pos=-1*sizeof(st);
      fp.seekp(pos,ios::cur);
      fp.write((char*)&st,sizeof(seats));
    }
    else
    {
    cout<<"Sorry for the inconvinience but the required no. of seats are not available!!\n";
    getch();
    exit(0);
    }
  }

  else
  { if(st.retnseat()>nm)
    {
      cout<<"Welcome to the cafe your required no. of seats are available!!\n";
      getch();
      st.upd_nseat();
      int pos=-1*sizeof(st);
      fp.seekp(pos,ios::cur);
      fp.write((char*)&st,sizeof(seats));
    }
    else
    {
    cout<<"Sorry for the inconvinience but the required no. of seats are not available!!\n";
    getch();
    exit(0);
    }
  }
 fp.close();
}

void show_seats()
{
  cout<<"The no. of seats in veg. area is : ";
  cout<<st.retvseat();
  cout<<"\nThe no. of seats in non-veg. area is : ";
  cout<<st.retnseat();
}




//--------------------------------------------------------------
//      function to write in file
//--------------------------------------------------------------

void write_product()
   {
    fp.open("Shop.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\nThe Product Has Been Created ";
    getch();
   }

//--------------------------------------------------------------
//      function to read all records from file
//--------------------------------------------------------------


void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 pr.show_product();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}


//--------------------------------------------------------------
//      function to read specific record from file
//--------------------------------------------------------------


void display_sp(int n)
{
    int flag=0;
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()==n)
		{
		 clrscr();
		 pr.show_product();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";
    getch();
}


//--------------------------------------------------------------
//      function to modify record of file
//--------------------------------------------------------------


void modify_product()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_product();
		    cout<<"\nPlease Enter The New Details of Product"<<endl;
		    pr.create_product();
		    int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}


//--------------------------------------------------------------
//      function to delete record of file
//--------------------------------------------------------------


void delete_product()
   {
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

//--------------------------------------------------------------
//      function to check if the item is Veg or Non-Veg
//--------------------------------------------------------------

void cat_check()
{
  gotoxy(10,15);
  cout<<"Enter 'v' for veg food and 'n' for non veg food ";
  cin>>c;
  if(c=='V')
  c='v';
  if(c=='N')
  c='n';
  cout<<"\n\t Enter the no. of persons : ";
  cin>>nm;
  cout<<"\n";
  asgn_seats();
  clrscr();
 }


//--------------------------------------------------------------
//      function to display menu to customer
//--------------------------------------------------------------

    void menu()
    {
     clrscr();
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }
     fp.close();

    cat_check();

    fp.open("Shop.dat",ios::in);
   cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
  {
  if(pr.retcat()==c)
   {


	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;


  }
 }
  cout<<"\n\n";
  cout<<"\t\t ***TODAY'S SPECIAL*** \n ";
  cout<<pn<<"\t\t";
  puts(nam);
  cout<<"\t\t"<<prc<<endl;

fp.close();



  /*   cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
*/
}

//--------------------------------------------------------------
//      function to display menu to admin
//--------------------------------------------------------------

void adm_menu()
{  clrscr();
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
}

void disp_bprice()
{ int t,ct=0;
  cout<<"\n\nEnter the price below which you want to display the menu : ";
  cin>>t;

   cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";

  fp.open("Shop.dat",ios::in);
  { while(fp.read((char*)&pr,sizeof(product)))
     if(pr.retprice()<t&&pr.retcat()==c)
     {
      cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
      ct++;
     }
  }
  getch();
  if(ct==0)
 { cout<<"Sorry no items are available below this price ";
   getch();
   exit(0);
 }
 fp.close();
}
//--------------------------------------------------------------
//      function to place order and generating bill for Products
//--------------------------------------------------------------

   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y',a,b;
    menu();
    getch();
    clrscr();
    cout<<"How do you want to display the menu?\n\n";

	  cout<<"\n\n\t01. Sort the menu by price?";
	  cout<<"\n\n\t02. Sort the menu by name?";
	  cout<<"\n\n\t03. Display items below certain price?";
	  cout<<"\n\n\t04. Search an item by name?";
	  cout<<"\n\n\t Enter your choice : ";
	  b=getche();
	  getch();
	  clrscr();
	  switch(b)
	  {  case '1':  sortbyprice();
	                 break;
	     case '2':  sortbyname();
	                 break;
	     case '3':  disp_bprice();
			         break;
	     case '4':   break;
	  }


    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\nEnter The Product No. Of The Product : ";
	 cin>>order_arr[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";getch();clrscr();
      cout<<"\n\n********************************INVOICE************************\n";
      cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after product discount\n";
      for(int x=0;x<=c;x++)
	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\tTOTAL AFTER ADDING 8.3% sales tax  = "<<total+0.083*(total);
    getch();
    char d;
    cout<<"\n\nAre you a student?(y/n) : ";
    cin>>d;
    if(d=='y'||d=='Y')
    cout<<"\n So your final amount after 10% discount is = "<<total+(0.083*(total))-0.1*(total);
    getch();
    cout<<"\n\nEnter 'c' if you want to pay by Credit Card or enter 'm' if you want to pay by cash : ";
    cin>>a;
    if(a=='V')
    a='v';
    if(a=='M')
    a='m';
    cout<<"\n Okay your payment by the above chosen option will be completed! ";
    cout<<"\n\n Thankyou for dining in! Please do visit again! ";
    getch();
    }








//--------------------------------------------------------------
//      INTRODUCTION FUNCTION
//--------------------------------------------------------------

void intro()
{
 clrscr();
 gotoxy(24,11);
 cout<<"WELCOME TO DELIGHT 24 CAFE";
 gotoxy(17,14);
 cout<<"GET READY FOR SOME AMAZING MULTI CUISINE FOOD!!!  ";
 gotoxy(5,17);
 cout<<"MANAGERS";
 cout<<"\n\n NIHAR PANCHAL";
 cout<<"\n\n PRANAY KUMAR";
 getch();

}




//--------------------------------------------------------------
//      ADMINSTRATOR MENU FUNCTION
//--------------------------------------------------------------
void admin_menu()
{
  clrscr();
  char ch2;
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\ta.CREATE PRODUCT";
  cout<<"\n\n\tb.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\tc.QUERY ";
  cout<<"\n\n\td.MODIFY PRODUCT";
  cout<<"\n\n\te.DELETE PRODUCT";
  cout<<"\n\n\tf.VIEW PRODUCT MENU";
  cout<<"\n\n\tg.ENTER SEATS";
  cout<<"\n\n\th.SHOW AVAILABLE SEATS";
  cout<<"\n\n\ti.TODAY'S SPECIAL";
  cout<<"\n\n\tj.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (a-j) ";
  ch2=getche();
  switch(ch2)
  {
    case 'a': clrscr();
	      write_product();
	      break;
    case 'b': display_all();break;
    case 'c':
	       int num;
	       clrscr();
	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       display_sp(num);
	       break;
      case 'd': modify_product();break;
      case 'e': delete_product();break;
      case 'f': adm_menu();
		getch();break;
      case 'g': clrscr();
		alloc_seats();
		getch();
		break;
      case 'h': clrscr();
		show_seats();
		getch();
		break;
      case 'i': clrscr();
		cout<<"Enter the product no. ";
		cin>>pn;
		cout<<"Enter the name of product ";
		gets(nam);
		cout<<"Enter the price ";
		cin>>prc;
		break;
      case 'j': break;
      default:cout<<"\a";admin_menu();
   }
}



//--------------------------------------------------------------
//      THE MAIN FUNCTION OF PROGRAM
//--------------------------------------------------------------


void main()
{
  char ch;
  intro();
  do
    {
	  clrscr();
	  gotoxy(10,5);
	  cout<<" ***WELCOME TO DELIGHT 24 CAFE***\n\n";
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
			   place_order();
			   getch();
			   break;
		  case '2': admin_menu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
}

//--------------------------------------------------------------
//                      END OF PROJECT
//--------------------------------------------------------------



void sortbyname()
    {
    	int count=0,i=0,j,k;
     clrscr();
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }
     fp.close();

    cat_check();

    fp.open("Shop.dat",ios::in);
   cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
  {
  	count++
  }
  fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
  {
  if(pr.retcat()==c)
   {
   	prod[i].cat==c;
   	prod[i].pno==pr.pno;
   	prod[i].price=pr.price;
   	prod[i].qty=pr.qty;
   	prod[i].tax=pr.tax;
   	prod[i].dis=pr.dis;
   	strcpy(prod[i].nam,pr.nam);
	i++;   	
   }
  }
for(j=0;j<count-1;j++)
{
		if(strcmp(prod[k].nam,prod[k+1].nam)>0)

		{
			u=prod[k];
			prod[k]=prod[k+1];
			prod[k+1]=u;
		}
	k++;
}
for(j=0;j<count;j++)
{
	cout<<prod[j].retpno()<<"\t\t"<<prod[j].retname()<<"\t\t"<<prod[j].retprice()<<endl;
}
  cout<<"\n\n";
  cout<<"\t\t ***TODAY'S SPECIAL*** \n ";
  cout<<pn<<"\t\t";
  puts(nam);
  cout<<"\t\t"<<prc<<endl;

fp.close();

}


void sortbyprice()
    {
    	int count=0,i=0,j,k,u;
     clrscr();
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }
     fp.close();

    cat_check();

    fp.open("Shop.dat",ios::in);
   cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
  {
  	count++
  }
  fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
  {
  if(pr.retcat()==c)
   {
   	prod[i].cat==c;
   	prod[i].pno==pr.pno;
   	prod[i].price=pr.price;
   	prod[i].qty=pr.qty;
   	prod[i].tax=pr.tax;
   	prod[i].dis=pr.dis;
   	strcpy(prod[i].nam,pr.nam);
	i++;   	
   }
  }
for(j=0;j<count-1;j++)
{
		if(()prod[k].price,prod[k+1].price)>0)

		{
			u=prod[k];
			prod[k]=prod[k+1];
			prod[k+1]=u;
		}
	k++;
}
for(j=0;j<count;j++)
{
	cout<<prod[j].retpno()<<"\t\t"<<prod[j].retname()<<"\t\t"<<prod[j].retprice()<<endl;
}
  cout<<"\n\n";
  cout<<"\t\t ***TODAY'S SPECIAL*** \n ";
  cout<<pn<<"\t\t";
  puts(nam);
  cout<<"\t\t"<<prc<<endl;

fp.close();

}
