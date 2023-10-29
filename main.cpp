#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<stdbool.h>
#include <iomanip>
#include<fstream>
using namespace std;

class Exception;
class Customer;
class RoomCustomer;
class Employee;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;


class Exception 
{
	public:
	    int errNo;
	    std::string msg;
	
	    Exception(int errNo, const std::string& msg) : errNo(errNo), msg(msg) {}
	
	    void what() {
	        std::cout << "\t" << errNo << " :: " << msg << std::endl;
	    }
};



class Room
{
	public:
	    std::string roomType;
	    int noOfBeds;
	    double rent;
	    int roomNo;
	    int status;
	
	    Room(const std::string& roomType, int noOfBeds, double rent, int roomNo)
	        : roomType(roomType), noOfBeds(noOfBeds), rent(rent), roomNo(roomNo), status(0) {}
	
	    void setRoom() {
	        std::cout << "Enter Room Type, No of beds, Rent, RoomNo" << std::endl;
	        std::cin >> this->roomType;
	        std::cin >> this->noOfBeds;
	        std::cin >> this->rent;
	        std::cin >> this->roomNo;
	        status = 0;
	    }
	
	    bool isVacant() const {
	        return (status == 0);
	    }
	
	    void displayDetail() const {
	        std::cout << "Room Type :: " << this->roomType << std::endl;
	        std::cout << "Number of Beds :: " << this->noOfBeds << std::endl;
	        std::cout << "Rent :: " << this->rent << std::endl;
	        std::cout << "Room Number :: " << this->roomNo << std::endl;
	        if (status == 1)
	            std::cout << " Occupied" << std::endl;
	        else
	            std::cout << "Vacant" << std::endl;
	    }
	
	    void vacateRoom(int rno) {
	        if (this->roomNo == rno) {
	            status = 0;
	        }
	    }
	
	    static void displayAvailable(const Room r[], int size) {
	        for (int i = 0; i < size; i++) {
	            if (r[i].isVacant()) {
	                r[i].displayDetail();
	            }
	        }
	    }
};

class Dish 
{
	public:
	    std::string dishName;
	    double price;
	    std::string dishType;
	
	    Dish(const std::string& dishName, double price, const std::string& dishType)
	        : dishName(dishName), price(price), dishType(dishType) {}
	
	    Dish() {}
	
	    void setDish() {
	        std::cout << "Enter Dish Name, Price, and Dish Type" << std::endl;
	        std::cin >> this->dishName;
	        std::cin >> this->price;
	        std::cin >> this->dishType;
	    }
	
	    void displayDetail() const {
	        std::cout << "Dish Name :: " << this->dishName << std::endl;
	        std::cout << "Price :: " << this->price << std::endl;
	        std::cout << "Dish Type :: " << this->dishType << std::endl;
	    }
};




class Customer 
{
	public:
	    std::string custName;
	    std::string custAddress;
	    std::string custID;
	    long int custPhone;
	    std::string custEmail;
	    std::string checkInTime;
	    int status;
	
	    Customer() : status(0) {
	        time_t currentTime = time(0);
	        checkInTime = ctime(&currentTime);
	    }
	
	    void setData() {
	        time_t currentTime = time(0);
	        checkInTime = ctime(&currentTime);
	
	        std::ofstream customerFile("Customer.txt", std::ios::app);
	        if (customerFile.is_open()) {
	            std::cout << "Enter your Name: " << std::endl;
	            std::cin >> custName;
	            customerFile << "Name :: " << custName << "\n";
	
	            std::cout << "Enter your Address: " << std::endl;
	            std::cin >> custAddress;
	            customerFile << "Address :: " << custAddress << "\n";
	
	            std::cout << "Enter your Phone number: " << std::endl;
	            std::cin >> custPhone;
	            customerFile << "Phone :: " << custPhone << "\n";
	
	            std::cout << "Enter your Email: " << std::endl;
	            std::cin >> custEmail;
	            customerFile << "Email :: " << custEmail << "\n\n";
	
	            customerFile.close();
	        }
    }

    int selectChoice() {
        int ch;
        std::cout << "Hello!" << std::endl;
        std::cout << "Enter\n1. Accommodation\n2. Dine\n";
        std::cin >> ch;
        return ch;
    }

    virtual void printCustomer() {
        std::cout << "Name :: " << custName << std::endl;
        std::cout << "Address :: " << custAddress << std::endl;
        std::cout << "ID :: " << custID << std::endl;
        std::cout << "Phone Number :: " << custPhone << std::endl;
        std::cout << "Email :: " << custEmail << std::endl;
        std::cout << "Check-In Time :: " << checkInTime << std::endl;
    }

    virtual void viewTotalBill() {
    }

    virtual void allocateRoom(Room r1) {
    }

    virtual void allocateDish(Dish d1) {
    }

    virtual void checkout() {
    }
};
class RoomCustomer : public Customer
{
	private:
	    double rbill;
	    Room r;
	    int bookStatus;
	
	public:
	    RoomCustomer() : rbill(0), bookStatus(0) {
	        // You can initialize rbill and bookStatus if needed.
	    }
	
	    void viewTotalBill() {
	        std::cout << "Bill = " << rbill << std::endl;
	    }
	
	    void allocateRoom(Room r1) {
	        r = r1;
	    }
	
	    void printCustomer() {
	        Customer::printCustomer();
	        if (r.status == 1 && bookStatus == 1) {
	            std::cout << "Check-In Time :: " << checkInTime << std::endl;
	            std::cout << "Room type :: " << r.roomType << std::endl;
	            std::cout << "Room Number :: " << r.roomNo << std::endl;
	        }
	    }
	
	    void viewTotalBill() {
	        rbill = r.rent;
	        std::cout << "Bill :: " << rbill << std::endl;
	    }
	
	    void checkOut() {
	        std::cout << "Your bill is " << rbill << "/-" << std::endl;
	        rbill = 0;
	        r.status = 0;
	        std::cout << "Thank You! Visit Again." << std::endl;
	    }
};




class RestaurantCustomer : public Customer
{
	private:
	    double dbill;
	    Dish d;
	    int orderStatus;
	
	public:
	    RestaurantCustomer() : dbill(0), orderStatus(0) {
	        // You can initialize dbill and orderStatus if needed.
	    }
	
	    void viewTotalBill() {
	        std::cout << "Bill = " << dbill << std::endl;
	    }
	
	    void allocateDish(Dish d1) {
	        d = d1;
	    }
	
	    void printCustomer() {
	        Customer::printCustomer();
	        if (orderStatus) {
	            std::cout << "Dish Name :: " << d.dishName << std::endl;
	            std::cout << "Dish Type :: " << d.dishType << std::endl;
	        }
	    }
	
	    void viewTotalBill() {
	        dbill = d.price;
	        std::cout << "Bill :: " << dbill << std::endl;
   	 }
};



class Employee {
public:
    virtual void performDuty() = 0;
    virtual ~Employee() {}
};

class RoomService : public Employee {
public:
    void performDuty() override {
        std::cout << "Employee XYZ arriving at your doorstep..." << std::endl;
    }
    ~RoomService() override {}
};

class Waiter : public Employee {
public:
    void performDuty() override {
        std::cout << "Employee ABC arriving at your table to take your order." << std::endl;
    }
    ~Waiter() override {}
};

class SelectEmployee {
    Employee* e;

public:
    SelectEmployee(Employee* e1) : e(e1) {}

    void performDuty() {
        e->performDuty();
    }
};




class Dish {
public:
    std::string dishName;
    double price;
    std::string dishType;
};

class Restaurant {
private:
    Dish dish[8];

public:
    void addDishes() {
        std::ofstream menu("Menu.txt", std::ios::app);
        if (!menu.is_open()) {
            std::cerr << "Error opening Menu.txt for writing." << std::endl;
            return;
        }

        for (int i = 0; i < 8; i++) {
            std::cout << i + 1 << "] Enter Dish Name, Price, and Type: ";
            std::cin >> dish[i].dishName >> dish[i].price >> dish[i].dishType;
            menu << dish[i].dishName << "\t" << dish[i].price << "\t" << dish[i].dishType << "\n";
        }

        menu.close();
    }

    Dish getDish(const std::string& dnam) {
        for (int i = 0; i < 8; i++) {
            if (dish[i].dishName == dnam) {
                return dish[i];
            }
        }
        // Return a default Dish if not found
        return Dish{};
    }

    void displayDish(const Dish& d) {
        std::cout << "Dish Name: " << d.dishName << std::endl;
        std::cout << "Price: " << d.price << std::endl;
        std::cout << "Dish Type: " << d.dishType << std::endl;
    }

    void displayMenu() {
        for (int i = 0; i < 8; i++) {
            displayDish(dish[i]);
        }
    }
};


class Hotel {
private:
    static Hotel* instanceHotel;
    std::string hotelName;
    std::string hotelAddress;

    Employee* employee[5];
    Restaurant restaurant;
    Room room[6];
    Customer* customer[5];

private:
    Hotel(const std::string& hname, const std::string& add)
        : hotelName(hname), hotelAddress(add) {}

public:
    static Hotel* getHotel() {
        if (!instanceHotel)
            instanceHotel = new Hotel("RENNAISSANCE", "HUBLI");
        return instanceHotel;
    }

    void setHotel(const Restaurant& r, Room rs[6]) {
        for (int i = 0; i < 6; i++) {
            room[i] = rs[i];
        }
        for (int i = 0; i < 8; i++) {
            restaurant.dish[i] = r.dish[i];
        }
    }

    void generateID(Customer* c) {
        static const char m[] = "abcdefghijklmnopqrstuvwxyz";
        c->custID.clear();
        for (int i = 0; i < 6; i++) {
            c->custID += m[std::rand() % (sizeof(m) - 1)];
        }
    }

    Room getRoom(int rno) {
        for (int i = 0; i < 6; i++) {
            if (room[i].roomNo == rno) {
                return room[i];
            }
        }
        // Return a default Room if not found
        return Room();
    }

    void displayAvailableRooms() {
        std::cout << "\n\n----------------------------------------------Room Details----------------------------------------------\n\n";
        std::cout << std::left << std::setw(25) << "Room Type"
                  << std::setw(25) << "Number of Beds"
                  << std::setw(25) << "Rent"
                  << std::setw(25) << "Room Number" << std::endl;
        for (int i = 0; i < 6; i++) {
            if (room[i].status == 0) {
                std::cout << std::left << std::setw(25) << room[i].roomType
                          << std::setw(25) << room[i].noOfBeds
                          << std::setw(25) << room[i].rent
                          << std::setw(25) << room[i].roomNo << std::endl;
            }
        }
        std::cout << "\n\n";
    }

    void displayMenu() {
        std::cout << "\n\n-----------------------------------------------Menu-------------------------------------------------\n\n ";
        std::cout << std::left << std::setw(25) << "Dish Name"
                  << std::setw(25) << "Price"
                  << std::setw(25) << "Dish Type" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << std::left << std::setw(25) << restaurant.dish[i].dishName
                      << std::setw(25) << restaurant.dish[i].price
                      << std::setw(25) << restaurant.dish[i].dishType << std::endl;
        }
        std::cout << "\n\n";
    }

    void bookRoom(int r) {
        for (int i = 0; i < 6; i++) {
            if (room[i].roomNo == r) {
                room[i].status = 1;
            }
        }
    }

    void askFeedback() {
        int f;
        std::string cname;
        std::ofstream feedback("feedback.txt", std::ios::app);
        if (!feedback.is_open()) {
            std::cerr << "Error opening feedback.txt for writing." << std::endl;
            return;
        }
        feedback << "Customer Name: ";
        std::cout << "Enter your Name: ";
        std::cin >> cname;
        feedback << cname << "\t\t\t";
        std::cout << "Thanks for your time!\nHow likely are you to recommend Hotel Renaissance to a Friend or Colleague?\nRate on a scale of 1-10: ";
        std::cin >> f;
        feedback << "Feedback: " << f << "\n";
        feedback.close();
        std::cout << "Thanks for your valuable feedback!" << std::endl;
    }

    void getCustomerData(Customer* c) {
        std::cout << "Name: " << c->custName << std::endl;
        std::cout << "Address: " << c->custAddress << std::endl;
        std::cout << "Phone: " << c->custPhone << std::endl;
        std::cout << "Email: " << c->custEmail << std::endl;
        std::cout << "Check-In Time: " << c->checkInTime << std::endl;
    }

    void vacateRoom(int rno) {
        int j = 0;
        for (int i = 0; i < 6; i++) {
            if (room[i].roomNo == rno) {
                j = 1;
                room[i].status = 0;
                std::cout << "Thank You! Visit Again." << std::endl;
            }
        }
        if (j == 0) {
            throw Exception(8, "Sorry! Room Not Found or occupied at the moment.");
        }
    }

    void takeOrder(const std::string& dnm) {
        int j = 0;
        for (int i = 0; i < 8; i++) {
            if (restaurant.dish[i].dishName == dnm) {
                j = 1;
                std::cout << "Order Successful" << std::endl;
            }
        }
        if (j == 0) {
            throw Exception(9, "Sorry! Dish Not Found, Enter a valid entry.");
        }
    }
};
Hotel* Hotel::instanceHotel = nullptr;
int main()
{
	

	
		
		ifstream file("Description.txt");
		if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
        printf("%s", line.c_str());
    }
    file.close();
}

cout<<"\n";
	int ch,i,o,ch1,ch2,r,rno,rcount=0,dcount=0;
	Room r2;
	string dname;
	Dish d2;
	Hotel *Rennaisance=Rennaisance->getHotel();
	
	Dish d[8]={
		Dish("Chocolate_Fondue",140,"Desert"),
		Dish("Manchow_Soup",110,"Soup"),
		Dish("Shahi_Paneer",220,"Main Course"),
		Dish("Arizona_Tea",100,"Beverage"),
		Dish("Grilled_Romaine Salad",180,"Salad"),
		Dish("Mushroom_Manchurian",170,"Starter"),
		Dish("Pina_Colada",210,"Cocktail"),
		Dish("Raspberry_Ripple",120,"Ice Cream")
			};
			
	Customer *c[5];
	Restaurant res;
	for(i=0;i<8;i++)
	{
		res.dish[i]=d[i];
	}
	Rennaisance->restuarant=res;
	
	 Room rm[6] = {
		Room("Deluxe",2,3500,1),
 		Room("AC",1,5500,2),
 		Room("Non AC",2,2500,3),
		Room("AC",2,3500,4),
		Room("Deluxe",2,3500,5),
	 	Room("Deluxe",3,4500,6)
		 };
		 SelectEmployee *e;
	Rennaisance->setHotel(res,rm);
	while(1)
	{
		for(i=0;i<5;i++)
		{
			try{
			
	level2:	cout<<"Enter \n\t1. Accomadation\n\t2. Restaurant\n\t3. Exit\n";
		cin>>ch;
		if(ch==1)
		{
		 Rennaisance->customer[i]=new RoomCustomer;
		 Rennaisance->generateID(Rennaisance->customer[i]);
		 cout<<"Enter Your details\n";
		 Rennaisance->customer[i]->setData();
		level1:	cout<<"Enter \n\t\t1. To Display Rooms \n\t\t2. To Book a Room \n\t\t3. To Vacate Room \n\t\t4. To Get Invoice  \n\t\t5. Not Satisfied? \n\t\t6. Cancel Booking \n\t\t7. Give Feedback \n\t\t8. Back\n\n";
			cin>>ch1;
			switch(ch1)
			{
				case 1: Rennaisance->displayAvailble();
				goto level1;
				case 2: 
				if(Rennaisance->customer[i]->status)
				{
				cout<<"\n\n-----------------------------------------------------------------------------------------\n\n";
				throw Exception(1,"Sorry! You Cannot Book more than one room!\n");
				cout<<"\n\n-----------------------------------------------------------------\n\n";}
				else
				{
				Rennaisance->customer[i]->status=1;
				Rennaisance->displayAvailble();
				cout<<"Enter Room No\n";
				cin>>rno;
				Rennaisance->bookRoom(rno);
				r2=Rennaisance->getRoom(rno);
				Rennaisance->customer[i]->allocateRoom(r2);
				}
				
				goto level1;
				case 3: 
				if(!Rennaisance->customer[i]->status)
				{
				cout<<"\n\n-----------------------------------------------------------------------------------------\n\n";
				throw Exception(3,"Cannot vacate a book unless booked\n");
				cout<<"\n\n-----------------------------------------------------------------\n\n";}
				
				else
				{
				Rennaisance->customer[i]->status=0;
				cout<<"Enter Room No\n";
				cin>>rno;
				Rennaisance->vacateRoom(rno);
				cout<<"Room vacated\n";
			
				}
				goto level1;
				case 4: if(!Rennaisance->customer[i]->status)
			{
				cout<<"\n\n------------------------------------------------------------------------------------------\n\n";
				throw Exception(2,"Cannot get Invoice Details unless you book a Room\n");
				cout<<"\n\n-----------------------------------------------------------------\n\n";}
				
				else 
				{
				cout<<"\n\n-----------------------------------------------------------------\n\n";
				Rennaisance->customer[i]->printCustomer();
				Rennaisance->customer[i]->viewTotalBill();
					cout<<"\n\n-----------------------------------------------------------------\n\n";
				goto level1;}
				case 5: 
				if(!Rennaisance->customer[i]->status)
				
			{
			cout<<"\n\n--------------------------------------------------------------------------------------------\n\n";
				throw Exception(2,"Cannot call Room Service Unless you book a Room\n");
				cout<<"\n\n-----------------------------------------------------------------\n\n";}
				
				else
				{
					e=new SelectEmployee(new RoomService);
					e->performDuty();
				//Rennaisance->employee->performDuty()
			}
					goto level1;
				case 6: 	if(!Rennaisance->customer[i]->status)
			 {
				 	cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(2,"No Room Booked\n");
				}
				
				else
				{
					
					Rennaisance->customer[i]->status=0;
					cout<<"Enter Room No\n";
				cin>>rno;
				Rennaisance->vacateRoom(rno);
					cout<<"Cancellation Successful!\n";
					
				}
				goto level1;
				case 7: if(!Rennaisance->customer[i]->status)
			 {
				 	cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(2,"Cannot give feedback unless you order a Dish\n");
				}
				else

				Rennaisance->askFeedback();
				goto level1;
				case 8: goto level2;
			}
			
		}
		
		
		else if(ch==2)
		{
	 	Rennaisance->customer[i]=new RestaurantCustomer;
		 Rennaisance->generateID(Rennaisance->customer[i]);
		 cout<<"Enter Your details\n";
		 Rennaisance->customer[i]->setData();
	level3:	cout<<"Enter \n\t\t1. To display Menu \n\t\t2. To order a Dish \n\t\t3. To Get Invoice \n\t\t4. To Cancel Order\n\t\t5. Give FeedBack \n\t\t6. Go back\n\n";
		cin>>ch2;
		switch(ch2)
		{
			case 1:
				Rennaisance->displayMenu();
				goto level3;
			case 2:
				if(Rennaisance->customer[i]->status)
			{
				cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(4,"You cannot order more than one dish\n");
				cout<<"\n\n-----------------------------------------------------------------\n\n";}
				else
				{
					o=1;
					Rennaisance->customer[i]->status=1;
			 Rennaisance->displayMenu();
			 e=new SelectEmployee(new Waiter);
			 e->performDuty();
			 cout<<"Enter Dish Name you want to Order(Make sure you enter the exact same name.)\n";
	
		cin>>dname;
			 Rennaisance->takeOrder(dname);
			 
			 d2=Rennaisance->restuarant.getDish(dname);
			
			Rennaisance->customer[i]->allocateDish(d2);
		
			 if(o==0)
			 {
			 cout<<"\n\n-----------------------------------------------------------------------------------------\n\n";
			 throw Exception(6,"No such Dish Found");
		}
		
			 }
			 	 goto level3;
			 case 3:
			 	if(!Rennaisance->customer[i]->status)
			 {
				 	cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(2,"Cannot get Invoice Details unless you order a Dish\n");
				}
				
				else 
				{
				cout<<"\n\n-----------------------------------------------------------------\n\n";
				Rennaisance->customer[i]->printCustomer();
				Rennaisance->customer[i]->viewTotalBill();
					cout<<"\n\n-----------------------------------------------------------------\n\n";
			}
				goto level3;
				case 4: 	if(!Rennaisance->customer[i]->status)
			 {
				 	cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(2,"No Dish Ordered\n");
				}
				else
				{
					Rennaisance->customer[i]->status=0;
					cout<<"Cancelation Successful!\n";
					
				}
				
			case 5:	if(!Rennaisance->customer[i]->status)
			 {
				 	cout<<"\n\n-----------------------------------------------------------------------------------\n\n";
				throw Exception(2,"Cannot give feedback unless you order a Dish\n");
				}
				else

				Rennaisance->askFeedback();
				goto level1;
				case 6:
				goto level2;
				
				
			 
		}
		}
		else if(ch==3)
		exit(0);
		else
		{
			cout<<"-----------------------------------------------------------------------------------\n\n";
			throw Exception(5,"INVALID INPUT\n");
			
		}
		goto level2;
		}
	
	catch(Exception eh)
	{
		eh.what();
		cout<<"-----------------------------------------------------------------------------------\n\n";
	}
	}	}
return 0;
}	

