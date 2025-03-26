#include<iostream>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<time.h>
#include<ctime>
#include<conio.h>
#include<unistd.h>
using namespace std;

fstream f;

// functions
void Add();
void Update(int ch);
void Delete();
void Product_Displayall();
void Search();
void Dailyreport();
void Addoffer();
void Display_bills();
void Seach_bill();
void Date_bill_display();

void Bill();
void Display_all_review();
void Show_offer();

class Admin
{
	private:
		char product_name[20];
		int product_no,product_qty;
		float product_price;
		
		float lowest[10],highest[10],dis[10];
		int to;
		
	public:
		void Add_product()
	   	{
	   		cout<<endl<<"Enter Product No   : ";cin>>product_no;
	   		cout<<endl<<"Enter Product Name : ";fflush(stdin);gets(product_name);
			cout<<endl<<"Enter Qty          : ";cin>>product_qty;
			cout<<endl<<"Enter Price        : ";cin>>product_price;	
		}
		
		void Display_all_product()
		{
			cout<<endl<<"|"<<setw(5)<<product_no<<setw(5)<<"|"<<setw(20)<<product_name<<setw(5)<<"|"<<setw(5)<<product_qty;
			cout<<setw(5)<<"|"<<setw(7)<<product_price<<setw(5)<<"|";
		}
		
		void Add_offer()
		{
			int i=0;
			char yn;
			while(yn!='n')
			{
				cout<<endl<<"Enter lowest price    : ";cin>>lowest[i];
				cout<<endl<<"Enter highest  price  : ";cin>>highest [i];
				cout<<endl<<"Enter Discount        : ";cin>>dis[i];
				i++;
				cout<<endl<<"Do you Want To add More Offers : ";cin>>yn;
			}
			to=i;
		}
		
		void Display_offer(int n)
		{
			for(int i=0;i<n;i++)
			{
					cout<<endl<<"|"<<setw(8)<<lowest[i]<<setw(3)<<"-"<<setw(8)<<highest[i]<<setw(6)<<"|"<<setw(6)<<dis[i]<<"%"<<setw(6)<<"|";
	
			}
		}
		// return pro no
		int Get_product_no()
		{
			return product_no;
		}
		
		//return discount amt
		int Get_dis(int n,float Amount)
		{
			for(int i=0;i<n;i++)
			{
				if(Amount<=highest[i])
				{
					return dis[i];
				}
			}
		}
		
		//return total offer
		int get_total_offer()
		{
			return to;
		}
		//return Price
		int Get_price()
		{
			return product_price;
		}
		
		// return qty
		int Get_Qty()
		{
			return product_qty;
		}
		
		// Set new Qty
		void Set_qty(int q)
		{
			product_qty=q;
		}
		//Set New Price
		void Set_price(float amt)
		{
			product_price=amt;
		}
		
		//purchase qty
		void Purchase_qty(int p_qty)
		{
			product_qty=product_qty-p_qty;
		}
		
		void display_no_name()
		{
			cout<<endl<<"|"<<setw(5)<<product_no<<setw(5)<<"|"<<setw(20)<<product_name<<setw(8)<<"|";
		}
};

Admin a;

class User
{
	private:
		
		char customer_name[20],total_products,purchase_name[20][20]={},Type[10];
		char customer_no[100],cname[20]={};
		int purchase_qty[20],purchase_no[20], bill_no;
		float purchase_product_price[20],purchase_product_total_price[20];
		float Amount,Finale_amt,Gst,Discount,P_amt;
		char rate[13];
		int dd,mm,yy,hour,min,sec;
		
	
		int Check_mono(string customer_no)
		{
			int i=0,c=0;
			int l=customer_no.length();
			while(i<l)
			{
				if(isdigit(customer_no[i])==0)
				{
					c=1;
					break;
				}
				i++;
			}
		
			if(l!=10 || c==1 )
			{
				cout<<endl<<"Enter Valid Mobile No ....";
				return -1;
					
			}
		}
		
	public:
		int Review()
		{
			char yn;
			int r;
			
			cout<<endl<<"Do you Want to give Review y/yes n/no :";cin>>yn;
			if(yn=='y')
			{
				strcpy(cname,customer_name);
				c1:
				cout<<endl<<"Give us Rating out Of 5 : ";cin>>r;
				switch(r)
				{
					case 1 : strcpy(rate,"    *    ");break;
					case 2 : strcpy(rate,"   * *   ");break;
					case 3 : strcpy(rate,"  * * *  ");break;
					case 4 : strcpy(rate," * * * * ");break;
					case 5 : strcpy(rate,"* * * * *");break;
					default:cout<<endl<<"Invalid give between 5......";gotoc1:break;
				}
				return 1;
			}
		}
		void Purchase(int last_billno)
		{
			Amount=0;
			bill_no=last_billno+1;
			
			cout<<endl<<"Enter Your Name : ";fflush(stdin);gets(customer_name);
			l1:
			cout<<endl<<"Enter Mobile No : ";fflush(stdin);cin.getline(customer_no,100);
			if(Check_mono(customer_no)==-1)
			{
				goto l1;
			}
			
			int i=0;
			char yn;
			while(yn!='n')
			{
				int flag=0,qflag=0;
				int choice,p_qty;
			
				
				Product_Displayall();
				f.open("Admin.dat",ios::binary|ios::out|ios::in);
				cout<<endl<<"Enter Your Choice : ";cin>>choice;
				while(f.read((char*)&a,sizeof(a)))
				{
					char product_name[20]={};
					int tel=f.tellp();
					if(choice==a.Get_product_no())
					{
						flag=1;
						
						cout<<endl<<"Enter Qty : ";cin>>p_qty;
						int h=a.Get_Qty();
						if(p_qty<h)
						{
							qflag=1;
							a.Purchase_qty(p_qty);
							f.seekp(tel-sizeof(a));
							f.write((char*)&a,sizeof(a));
							
							purchase_no[i]=choice;
							purchase_qty[i]=p_qty;
							purchase_product_price[i]=a.Get_price();
							purchase_product_total_price[i]=purchase_product_price[i]*p_qty;
							Amount=Amount+purchase_product_total_price[i];
							f.seekp(f.tellp()-sizeof(a));
							f>>product_name;
							strcpy(purchase_name[i],product_name);
							i++;
							break;
						}	
					}	
				}
				f.close();
				
				
				if(flag==0)
				{
					cout<<endl<<"Invalid Product No......\n";
				}
				else if(qflag==0)
				{
					cout<<endl<<"Sorry.....Not In Stock......\n";
				}
				cout<<endl<<"Do You Want To Continue y/yes n/no : ",cin>>yn;				
			}
			
			float c;	
			f.open("Offer.dat",ios::binary | ios::in);			
			while(f.read((char*)&a,sizeof(a)))
			{
				int u=a.get_total_offer();
				c=a.Get_dis(u,Amount);
			}
			f.close();
			total_products=i;
			Discount=(c*(Amount))/100;
			P_amt=Amount-Discount;
			Gst=P_amt*0.05;
			
			Finale_amt=Gst+P_amt;
			
			time_t now = time(0);

			tm *ltm = localtime(&now);
			yy= 1900 + ltm->tm_year;
		
		   mm= 1 + ltm->tm_mon;
		   dd=ltm->tm_mday;
		   hour=ltm->tm_hour;
		   min=ltm->tm_min;
		   sec=ltm->tm_sec;
	   		
	   		int p_type;
	   		p1:
	   		cout<<endl<<"Enter Payment Type ";
	   		cout<<endl<<"1. Cash";
	   		cout<<endl<<"2. Upi";
	   		cout<<endl<<"3. Credit / Debit Card";
	   		cout<<endl<<"Enter Your Choice : ";cin>>p_type;
	   		if(p_type<1 || p_type>3)
	   		{
	   			cout<<endl<<"Invalid...........";
	   			goto p1;
			   }
		}
		
		void Write_bill_in_file(int tp,int ch)
		{
			if(ch==3)
			{
				total_products=tp;
			}
			cout<<endl<<"----------------------------------------------------------------------------------------------------------";
			cout<<endl<<"|                                                Mahalaxmi Canteen                                       |";
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			cout<<endl<<"| Bill Number   : "<<setw(5)<<bill_no<<setw(83)<<"|";
			cout<<endl<<"| Customer Name : "<<setw(20)<<customer_name<<setw(52)<<"Date : "<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<yy<<setw(6)<<"|";
			cout<<endl<<"| Mobile No     : "<<setw(12)<<customer_no<<setw(60)<<"Time : "<<setw(2)<<hour<<":"<<setw(2)<<min<<":"<<setw(2)<<sec<<setw(8)<<"|";
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			cout<<endl<<"|  Product no  |            Prodcut name        |    Product qty    |   Product price   |      Amount    |";
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			for(int i=0; i<total_products;i++)
			{
				cout<<endl<<"|"<<setw(10)<<purchase_no[i]<<setw(5)<<"|"<<setw(20)<<purchase_name[i];
				cout<<setw(13)<<"|"<<setw(10)<<purchase_qty[i]<<setw(10)<<"|"<<setw(10)<<purchase_product_price[i];
				cout<<setw(10)<<"|"<<setw(10)<<purchase_product_total_price[i]<<setw(7)<<"|";
			}
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			cout<<endl<<"| Amount : "<<setw(78)<<"|"<<setw(10)<<Amount<<setw(7)<<"|";
			cout<<endl<<"| Discount : "<<setw(76)<<"|"<<setw(10)<<Discount<<setw(7)<<"|";
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			cout<<endl<<"| Amount     "<<setw(76)<<"|"<<setw(10)<<P_amt<<setw(7)<<"|";
			cout<<endl<<"| Gst    : "<<setw(78)<<"|"<<setw(10)<<Gst<<setw(7)<<"|";
			cout<<endl<<"|--------------------------------------------------------------------------------------------------------|";
			cout<<endl<<"| Paying amt : "<<setw(74)<<"|"<<setw(10)<<Finale_amt<<setw(7)<<"|";
			cout<<endl<<"----------------------------------------------------------------------------------------------------------";
			
					
		}
		void Customer_bill()
		{
			
			cout<<endl<<"|"<<setw(6)<<bill_no<<setw(5)<<"|"<<setw(20)<<customer_name<<setw(5)<<"|"<<setw(3)<<"  "<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<yy;
			cout<<setw(5)<<"|"<<setw(3)<<"  "<<setw(2)<<hour<<":"<<setw(2)<<min<<":"<<setw(2)<<sec;
			cout<<setw(5)<<"|"<<setw(10)<<Amount;
			cout<<setw(7)<<"|"<<setw(10)<<Discount;
				cout<<setw(7)<<"|"<<setw(10)<<P_amt;
			cout<<setw(7)<<"|"<<setw(10)<<Gst;
			cout<<setw(7)<<"|"<<setw(10)<<Finale_amt<<setw(7)<<"|";
		
		}
		
		
		int get_products()
		{
			return total_products;
		}
		int get_bill_no()
		{
			return bill_no;
		}
		int get_gst()
		{
			return Gst;
		}
		int get_dis()
		{
			return Discount;
		}
		int calc_pur_qty(int sa, int p)
		{
			int tqty=0;
			
			for(int i=0; i<p; i++)
			{
				if(sa==purchase_no[i])
				{
					tqty=tqty+purchase_qty[i];
				}
			}
			return tqty;
		}
		
		int Check_date(int date,int mon,int year)
		{
			if(date==dd && mon==mm && year==yy )
			{
				return 1;
			}
		}
		
		void Display_review()
		{
			cout<<endl<<"|"<<setw(20)<<cname<<setw(10)<<"|"<<setw(13)<<rate<<setw(5)<<"|";
		}
		
		
};

User u;


int main()
{
	int mch,ch,uch;
	char username[30],pass[30];
	while(1)
	{
		m1:
		system("cls");
		cout<<endl<<"\t\t----------------------------------------";
		cout<<endl<<"\t\t|                   Menu               |";
		cout<<endl<<"\t\t|--------------------------------------|";
		cout<<endl<<"\t\t| 1. Admin                             |";
		cout<<endl<<"\t\t| 2. User                              |";
		cout<<endl<<"\t\t| 3. Exit                              |";
		cout<<endl<<"\t\t----------------------------------------";
		cout<<endl<<"\t\tEnter Choice : ";cin>>mch;
		
		switch(mch)
		{
			case 1 :cout<<endl<<"\t\tEnter Username : ";fflush(stdin);gets(username);
					cout<<endl<<"\t\tEnter Password : ";fflush(stdin);gets(pass);
					cout<<endl<<"\n\t\tLoading...";
					for(int i=1; i<=5;i++)
					{
						cout<<".";
						sleep(1);
					}
					if((strcmp(username,"Admin")!=0)&&(strcmp(pass,"Admin@123")!=0))
					{
						cout<<endl<<"\nInvalid.........Please try again......";
						getch();
						goto m1;
					}
					 while(1)
					{
						system("cls");
						cout<<endl;
						cout<<endl<<"\t-----------------------------------------------------------";
						cout<<endl<<"\t|                          Menu                           |";
						cout<<endl<<"\t|---------------------------------------------------------|";
						cout<<endl<<"\t| 1.  Add Product           | 7.  Daily Report            |";
						cout<<endl<<"\t| 2.  Delete Product        | 8.  Add Offers              |";
						cout<<endl<<"\t| 3.  Update QTY            | 9.  Display All Bills       |";
						cout<<endl<<"\t| 4.  Update Price          | 10. Search Customer Bill    |";
						cout<<endl<<"\t| 5.  Display All Product   | 11. Search Bills Date Wise  |";
						cout<<endl<<"\t| 6.  Search Product        | 12. Exit                    |";
						cout<<endl<<"\t-----------------------------------------------------------";
						cout<<endl<<"\n\tEnter Your Choice : ";cin>>ch;
						system("cls");
		
						switch(ch)
						{
							case 1 : Add();	getch();break;
							case 2 : Delete();getch();break;
							case 3 : Update(ch);getch();break;
							case 4 : Update(ch);getch();break;
							case 5 : Product_Displayall();getch();break;
							case 6 : Search();getch();break;
							case 7 : Dailyreport();getch();break;
							case 8 : Addoffer();getch();break;
							case 9 : Display_bills();getch();break;
							case 10: Seach_bill();getch();break;
							case 11 : Date_bill_display();getch();break;
							case 12 : goto m1;
							default:cout<<endl<<"Invalid......";
						}
					}break;
					
			case 2 : while(1)
					{
						system("cls");
						cout<<endl<<"\t-----------------------------";
						cout<<endl<<"\t|          Canteen          |";
						cout<<endl<<"\t|---------------------------|";
						cout<<endl<<"\t| 1. Place Order            |";
						cout<<endl<<"\t| 2. Review                 |";
						cout<<endl<<"\t| 3. Offers                 |";
						cout<<endl<<"\t| 4. Exit                   |";
						cout<<endl<<"\t|---------------------------|";
						cout<<endl<<"\tEnter Your Choice : ";cin>>uch;
						system("cls");
						
						switch(uch)
						{
							case 1 : Bill();getch();break;
							case 2 : Display_all_review();getch();break;
							case 3 : Show_offer();getch();break;
							case 4 : goto m1;
							default:cout<<endl<<"Invalid...";
						}
						
					}break;
			case 3 : exit(0);
			default : cout<<endl<<"Invalid........";
		}
	}	
}

void Add()
{
	f.open("Admin.dat",ios::binary | ios::app);
	a.Add_product();
	f.write((char*)&a,sizeof(a));
	f.close();
}

void Product_Displayall()
{
	f.open("Admin.dat",ios::binary | ios::in);
	cout<<endl<<"----------------------------------------------------------";
	cout<<endl<<"|                           Menu                         |";
	cout<<endl<<"|--------------------------------------------------------|";
	cout<<endl<<"|  Pro No |      Product Name      |   Qty   |   Price   |";
	cout<<endl<<"|---------|------------------------|---------|-----------|";
	while(f.read((char*)&a,sizeof(a)))
	{
		a.Display_all_product();
	}
	f.close();
	cout<<endl<<"----------------------------------------------------------";
}

void Update(int ch)
{
	int p_n,q,flag=0;
	int tel;
	float amt;
	
	cout<<endl<<"Enter Product No : ";cin>>p_n;
	f.open("Admin.dat",ios::binary | ios::in | ios::out);
	while(f.read((char*)&a,sizeof(a)))
	{
		tel=f.tellp();
		if(p_n==a.Get_product_no())
		{
			flag=1;
			if(ch==3)
			{
				cout<<endl<<"Enter New Qty : ";cin>>q;
				a.Set_qty(q);
				f.seekp(tel-sizeof(a));
				f.write((char*)&a,sizeof(a));
				cout<<endl<<"\nQty Updated Successfully..............";
			}
			if(ch==4)
			{
				cout<<endl<<"Enter New Price : ";cin>>amt;
				a.Set_price(amt);
				f.seekp(tel-sizeof(a));
				f.write((char*)&a,sizeof(a));
				cout<<endl<<"\nPrice Updated Successfully..............";
			}
		}
	}
	if(flag==0)
	{
		cout<<endl<<"Invalid Product No......";
	}
	f.close();
}


void Delete()
{
	int p_n,flag=0;
	
	cout<<endl<<"Enter Product No : ";cin>>p_n;
	f.open("Admin.dat",ios::binary | ios::in );
	ofstream fout;
	fout.open("new.dat",ios::binary | ios::app);
	while(f.read((char*)&a,sizeof(a)))
	{
		if(p_n==a.Get_product_no())
		{
			flag=1;		
		}
		else
		{
			fout.write((char*)&a,sizeof(a));
		}
	}
	if(flag==0)
	{
		cout<<endl<<"Invalid Product No......";
	}
	else
	{
		cout<<endl<<"Product Deleted Successfully\n";
	}
	f.close();
	fout.close();
	remove("Admin.dat");
	rename("new.dat","Admin.dat");
	
}

void Search()
{
	int p_n,flag=0;
	cout<<endl<<"Enter Product No : ";cin>>p_n;
	f.open("Admin.dat",ios::binary | ios::in );
	while(f.read((char*)&a,sizeof(a)))
	{
		if(p_n==a.Get_product_no())
		{
			cout<<endl<<"----------------------------------------------------------";
			cout<<endl<<"|  Pro No |      Product Name      |   Qty   |   Price   |";
			cout<<endl<<"|---------|------------------------|---------|-----------|";
			flag=1;
			a.Display_all_product();
				cout<<endl<<"----------------------------------------------------------";
		}
	}
	f.close();
	if(flag==0)
	{
		cout<<endl<<"Invalid Product No....";
	}
}

void Dailyreport()
{
	float t_amt=0,gst=0,Profit=0,tgst=0,tdis=0,disc=0,pos=0;
	ifstream fin;
	int tyy,tmm,tdd;
	time_t now = time(0);

	tm *ltm = localtime(&now);
	tyy= 1900 + ltm->tm_year;		
	tmm= 1 + ltm->tm_mon;
	tdd=ltm->tm_mday;
		  
	cout<<endl<<"---------------------------------------------------------------------";
	cout<<endl<<"|                               Report                              |";
	cout<<endl<<"|-------------------------------------------------------------------|";
	cout<<endl<<"|  Pro No |         Product Name      |   Sold Qty   |     Amount   |";
	cout<<endl<<"|---------|---------------------------|--------------|--------------|";
	f.open("Admin.dat",ios::binary | ios::in);
	while(f.read((char*)&a,sizeof(a)))
	{
		a.display_no_name();
		int p_t_qty=0,p;
		float p_t_amt=0;
		
		int sa=a.Get_product_no();
		float sp=a.Get_price();
		fin.open("Customers.dat",ios::binary | ios::in);
		while(fin.read((char*)&u,sizeof(u)))
		{
			if(u.Check_date(tdd,tmm,tyy)==1)
			{
				if(pos==0)
				{
					tgst=tgst+u.get_gst();
					tdis=tdis+u.get_dis();
					
				}
				p=u.get_products();
				p_t_qty=p_t_qty+u.calc_pur_qty(sa,p);
				p_t_amt=p_t_qty*sp;
			}
			
		}
		pos++;
		t_amt=t_amt+p_t_amt;
		cout<<setw(10)<<p_t_qty<<setw(5)<<"|"<<setw(10)<<p_t_amt<<setw(5)<<"|";
		fin.close();
	}
	f.close();
	
	gst=tgst;
	disc=tdis;
	Profit=t_amt-tgst-tdis;
	cout<<endl<<"|-------------------------------------------------------------------|";
	cout<<endl<<"| Total Amount   "<<setw(37)<<"|"<<setw(10)<<t_amt<<setw(5)<<"|";
	cout<<endl<<"| Gst            "<<setw(37)<<"|"<<setw(10)<<gst<<setw(5)<<"|";
	cout<<endl<<"| Discount       "<<setw(37)<<"|"<<setw(10)<<disc<<setw(5)<<"|";
	cout<<endl<<"|-------------------------------------------------------------------|";
	cout<<endl<<"| Cash On Hand   "<<setw(37)<<"|"<<setw(10)<<Profit<<setw(5)<<"|";
	cout<<endl<<"----------------------------------------------------------------------";
	

			
}
void Addoffer()
{
	f.open("Offer.dat",ios::binary | ios::out);
	a.Add_offer();
	f.write((char*)&a,sizeof(a));
	f.close();
}

void Seach_bill()
{
	int a,sbillno,flag=0;
	f.open("Customers.dat",ios::binary | ios::in);
	cout<<endl<<"Enter Bill No : ";cin>>sbillno;
	while(f.read((char*)&u,sizeof(u)))
	{
		if(u.get_bill_no()==sbillno)
		{
			flag=1;
			int ch=3;
			a=u.get_products();
			u.Write_bill_in_file(a,ch);
		}
	
	}
	f.close();
	if(flag==0)
	{
		cout<<endl<<"Sorry.........No Data Found...";
	}
}

void Date_bill_display()
{
	int a,day,mon,year,flag=0;
	f.open("Customers.dat",ios::binary | ios::in);
	cout<<endl<<"      Enter Date  ";
	cout<<endl<<"Enter DD   : ";cin>>day;
	cout<<endl<<"Enter MM  : ";cin>>mon;
	cout<<endl<<"Enter YY   : ";cin>>year;
	while(f.read((char*)&u,sizeof(u)))
	{
		if(u.Check_date(day,mon,year)==1)
		{
			flag=1;
			a=u.get_products();
			u.Write_bill_in_file(a,3);
			cout<<endl<<endl;
		}
	
	}
	f.close();
	if(flag==0)
	{
		cout<<endl<<"Sorry.........No Data Found...";
	}
}



void Display_bills()
{
	int a;
	f.open("Customers.dat",ios::binary | ios::in);
	cout<<endl<<"------------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<endl<<"|                                                                     Mahalaxmi Canteen                                                                    |";
	cout<<endl<<"|----------------------------------------------------------------------------------------------------------------------------------------------------------|";
	cout<<endl<<"|  Bill No |     Customer Name      |       Date      |     Time      |     Amount     |    Discount    |      Amount    |       Gst      |  Finale Amount |";
	cout<<endl<<"|----------|------------------------|-----------------|---------------|----------------|----------------|----------------|----------------|----------------|";
	while(f.read((char*)&u,sizeof(u)))
	{
		u.Customer_bill();
	
	}
	cout<<endl<<"-----------------------------------------------------------------------------------------------------------------------------------------------------------";
	f.close();
}

void Bill()
{
	
	
	int a;
	f.open("Customers.dat",ios::binary | ios::in);
	while(f.read((char*)&u,sizeof(u)))
	{
		a=u.get_bill_no();
	}
	f.close();
	u.Purchase(a);
	f.open("Customers.dat",ios::binary | ios::app );
	u.Write_bill_in_file(1,1);
	f.write((char*)&u,sizeof(u));
	f.close();
	f.open("Reviews.dat",ios::binary | ios::app );
	int k=u.Review();
	if(k==1)
	{
		f.write((char*)&u,sizeof(u));
	}
	
	f.close();
	
}



void Display_all_review()
{
	int a;
	f.open("Reviews.dat",ios::binary | ios::in);
	
	cout<<endl<<"-------------------------------------------------";
	cout<<endl<<"|                     Reviews                   |";
	cout<<endl<<"|-----------------------------------------------|";
	cout<<endl<<"|             Name            |       Rate      |";
	cout<<endl<<"|-----------------------------|-----------------|";
	while(f.read((char*)&u,sizeof(u)))
	{
		u.Display_review();
	
	}
	cout<<endl<<"-------------------------------------------------";
	f.close();
}

void Show_offer()
{
	f.open("Offer.dat",ios::binary | ios::in);
	
	
	cout<<endl<<"---------------------------------------";
	cout<<endl<<"|                Offers               |";
	cout<<endl<<"|-------------------------------------|";
	cout<<endl<<"|          Amount        |  Discount  |";
	cout<<endl<<"|------------------------|------------|";
	while(f.read((char*)&a,sizeof(a)))
	{
		int o=a.get_total_offer();
		a.Display_offer(o);
	}
	f.close();
		cout<<endl<<"---------------------------------------";
}
