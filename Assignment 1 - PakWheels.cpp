#include <iostream>
#include <string>
using namespace std;

class User;
class Vehicle;


//1. Component for User
class Account {
    string username;
    string password;
    const int accountID;          // CONSTANT MEMBER 1 - shouldn't be modified
    string dateCreated;
    int failedAttempts;
    bool isLocked;
    public:
    	// Parameterized Constructor (initializer list necessary for const id)
    	Account(int id, string user, string pass, string date) :
		accountID(id), username(user), password(pass), dateCreated(date), failedAttempts(0), isLocked(false) {}

    	// Default Constructor
    	Account() : accountID(0), username("Guest"), password(""), dateCreated("N/A"), failedAttempts(0), isLocked(false) {}
    	
		// Function 1: Security Logic
    	void loginAttempt(string inputPass) {
        	if (isLocked) {
            	cout<<"Account is locked. Please contact Admin."<<endl;
            	return;
        	}
        	if (inputPass == password) {
            	cout<<"Login Successful!"<<endl;
            	failedAttempts = 0;
        	} 
			else {
            	failedAttempts++;
            	cout<<"Incorrect password. Attempt: "<<failedAttempts<<endl;
            	if (failedAttempts >= 3) {
                	isLocked = true;
                	cout<<"Account has been locked due to security reasons."<<endl;
            	}
        	}
    	}

    // Function 2: Password Management
    void resetPassword(string newPass) {
        if (newPass.length() < 6) {
            cout<<"Error: Password too short."<<endl;
        } else {
            password = newPass;
            cout<<"Password updated successfully."<<endl;
        }
    }

    // Function 3: Display Logic (Constant Function so it allows only reading not modifying)
    void displayAccountInfo() const {
        cout<<"Account ID: "<<accountID<<" | User: "<<username<<endl;
        cout<<"Created on: "<<dateCreated<<" | Status: ";
        if(isLocked){
        	cout<<"Locked"<<endl;
		}
		else{
			cout<<"Active"<<endl;
		}
    }

    // Function 4: Admin Overwrite (Unlocked through admin approval)
    void unlockAccount() {
        isLocked = false;
        failedAttempts = 0;
    }
};

// 3. Component for Vehicle
class Engine {
    float capacityCC;
    string fuelType;			   // Petrol/Deisel/CNG 
    int horsepower;
    string transmissionType;      // Manual/Auto
    const string engineSerial;    // CONSTANT MEMBER 2 - shouldn't be modified
    int cylinderCount;
    public:
    	// Parameterized Constructor (initializer list necessary for const serial)
	    Engine(float cc, string fuel, int hp, string trans, string serial, int cylinders)
	    : capacityCC(cc), fuelType(fuel), horsepower(hp), transmissionType(trans), engineSerial(serial), cylinderCount(cylinders) {}
	
	    // Default Constructor
	    Engine() : capacityCC(0), fuelType("Petrol"), horsepower(0), transmissionType("Manual"), engineSerial("0000"), cylinderCount(4) {}
	
	    // Function 1: Display Engine Details
	    void displayEngine() const {
	        cout<<"Engine: "<<capacityCC<<"cc | Fuel: "<<fuelType<<endl;
	        cout<<"Transmission: "<<transmissionType<<" | HP: "<<horsepower<<endl;
	        cout<<"Serial: "<<engineSerial<<" | Cylinders: "<<cylinderCount<<endl;
	    }
	
	    // Function 2: Fuel Efficiency Logic
	    void checkFuelEfficiency() const {
	        if(fuelType == "CNG") {
	            cout<<"Efficiency: Maximum (Eco-Friendly)"<<endl;
	        } else if(fuelType == "Diesel") {
	            cout<<"Efficiency: High (Long Distance)"<<endl;
	        } else {
	            cout<<"Efficiency: Standard"<<endl;
	        }
	    }
	
	    // Function 3: Validation for Horsepower (to check performance)
	    bool isSportsGrade() const {
	        return (horsepower > 250 && cylinderCount >= 6);
	    }
	
	    // Function 4: Horsepower Modifier
	    void upgradeHorsepower(int boost) {
	        horsepower += boost;
	        cout<<"Horsepower upgraded to: "<<horsepower<<endl;
	    }
};

// 4. Component for Vehicle
class Category {
    string typeName;              // "Car", "Bike", "Truck"
    int wheelCount;
    string licenseRequired;       // "LTV", "HTV", etc.
    const double baseTaxRate;     // CONSTANT MEMBER 3 - Each type has fixed base tax
    bool isCommercial;
    public:
    	// Parameterized Constructor
	    Category(string name, int wheels, string license, double tax, bool comm)
	    : typeName(name), wheelCount(wheels), licenseRequired(license), baseTaxRate(tax), isCommercial(comm) {}
	
	    // Default Constructor
	    Category() : typeName("Car"), wheelCount(4), licenseRequired("LTV"), baseTaxRate(0.02), isCommercial(false) {}
	
	    // Function 1: Display Category Details
	    void displayCategory() const {
	        cout<<"Category: "<<typeName<<" | Wheels: "<<wheelCount<<endl;
	        cout<<"License: "<<licenseRequired<<" | Tax Rate: "<<baseTaxRate<<endl;
	        cout<<"Usage: ";
	        if(isCommercial){
	        	cout<<"Commercial"<<endl;
			}
			else{
				cout<<"Personal"<<endl;
			}
	    }
	
	    // Function 2: Tax Calculation
	    double calculateTax(double price) const {
	        double totalRate = baseTaxRate;
	        if(isCommercial){
	        	totalRate += 0.05;
			}
	        return price * totalRate;
	    }
	
	    // Function 3: License Validation
	    bool checkLicenseMatch(string userLicense) const {
	        return (userLicense == licenseRequired);
	    }
	
	    // Function 4: Capacity Labeler (Large/Small)
	    string getCapacityLabel() const {
	        if(wheelCount>4){
	            return "Large";
	        }else{
	            return "Small";
	        }
	    }
};

// 5. The Vehicle (Composes Engine, Category)
class Vehicle {
    string brand;
    string model;
    string condition;
    int year;
    int mileage;
    Engine eng;                   // COMPOSITION 2
    Category cat;                 // COMPOSITION 3
    static int vehicleCount;      // STATIC MEMBER 2
    public:
    	// Parameterized Constructor (each vehicle should have a brand, model, year, etc at the time of its exsistence. This is to avoid ghost vehicles)
	    Vehicle(string b, string m, int y, int mil, string cond, Engine e, Category c)
	        : brand(b), model(m), year(y), mileage(mil), condition(cond), eng(e), cat(c) {
	        	vehicleCount++;
			}
	
	    // Function 1: Complete Display (Vehicle, Engine, Category)
	    void displayVehicle() const {
	        cout<<"--- "<<year<<" "<<brand<<" "<<model<<" ---"<<endl;
	        cout<<"Condition: "<<condition<<" | Mileage: "<<mileage<<"km"<<endl;
	        eng.displayEngine();
	        cat.displayCategory();
	    }
	
	    // Function 2: Mileage Validation (Business Logic)
	    void updateMileage(int newMileage) {
	        if(newMileage>=mileage){
	            mileage=newMileage;
	            cout<<"Mileage updated successfully."<<endl;
	        }else{
	            cout<<"Error: Mileage tampering detected."<<endl;
	        }
	    }
	
	    // Function 3: Value Depreciation Logic
	    double calculateCurrentValue(double originalPrice) const {
	        int age=2026-year;
	        double factor=1.0;
	        // Lose 10% value per year of age
	        for(int i=0; i<age; i++){
	            factor*=0.90;
	        }
	        return originalPrice*factor;
	    }
	
	    // Function 4: Status Checker
	    void checkVehicleStatus() const {
	        if(mileage>100000 || (2026-year)>10){
	            cout<<"Status: High Mileage/Old Vehicle"<<endl;
	        }else{
	            cout<<"Status: Excellent Condition"<<endl;
	        }
	    }
	    
	    //Static Function to check total no. of vehicles
	    static int getvehicleCount() {
        	return vehicleCount;
    	}
	
	    // Getters for search functionality
	    string getBrand() const { return brand; }
	    string getModel() const { return model; }
	    int getYear() const { return year; }
	    int getMileage() const { return mileage; }
};
// Initializing static member
int Vehicle::vehicleCount = 0;

// 2. The User (Aggregates Favorites, Composes Account, Save Favourites Logic, Array of Objects) (After Vehicle bc Array of Objects)
class User {
    string name;
    const string userID;
    string email;
    string role;                  // "Buyer", "Seller", "Admin"
    bool isActive;				  // Activity Status
    Account acc;                  // COMPOSITION 1
    static int totalUsers;        // STATIC MEMBER 1 - to count total no. of users/accounts
    Vehicle* favorites[10];       // Array of pointers to vehicles - AGGERIGATION 1
    int favCount;                 // To track how many favorites exist
    public:
    	// Parameterized Constructor - (initializer list necessary for const id. Each user should have a name, id, email, role, etc at time of existence. This avoids ghost users)
    	User(string n, string id, string e, string r, Account a) : name(n), userID(id), email(e), role(r), acc(a), favCount(0) {
        	totalUsers++;
        	// Initialize favorites array with nullptrs
        	for(int i = 0; i < 10; i++){
        		favorites[i] = nullptr;
			}
    	}

	    // Function 1: Add to Favorites
	    void saveFavorite(Vehicle* vPtr) {
	        if (favCount < 10) {
	            favorites[favCount++] = vPtr;
	            cout<<vPtr->getModel()<<" added to favorites!"<<endl;
	        } 
			else {
	            cout<<"Favorites list is full."<<endl;
	        }
	    }
	
	    // Function 2: Profile Management
	    void updateEmail(string newEmail) {
	        email = newEmail;
	        cout<<"Email updated to: "<<email<<endl;
	    }
	
	    // Function 3: Login
	    void login(string pass) {
	        acc.loginAttempt(pass);
	    }
	
	    // Function 4: Display Profile Details
	    void viewProfile() const {
	        cout<<"--- USER PROFILE ---"<<endl;
	        cout<<"Name: "<<name<<" ("<<role<<")"<<endl;
	        acc.displayAccountInfo();
	        cout<<"Favorites saved: "<<favCount<<endl;
	    }
	
	    // Getter for Account (Needed for AdminPanel to unlock)
	    Account& getAccount() { return acc; }
	    string getUserID() const { return userID; }
	
	    // Static function to check total site population
	    static int getTotalUsers() { return totalUsers; }
};
// Initializing static member
int User::totalUsers = 0;

// 6. Spare Parts (Standalone product)
class SparePart {
    string partName;
    string manufacturer;
    string condition;             // New/Used
    const int partID;             // CONSTANT MEMBER 4 - shouldn't be modified
    string compatibleModel;
    double weight;
    public:
    	// Parameterized Constructor (initializer list necessary for const id. Each user should have a name, id, manufacturer, etc at time of existence. This avoids ghost spare parts)
	    SparePart(string name, string manu, string cond, int id, string model, double w)
	        : partName(name), manufacturer(manu), condition(cond), 
	          partID(id), compatibleModel(model), weight(w) {}
	
	    // Function 1: Display Spare part Details
	    void displaySparePart() const {
	        cout<<"Part: "<<partName<<" ("<<partID<<")"<<" | Brand: "<<manufacturer<<endl;
	        cout<<"Condition: "<<condition<<" | Weight: "<<weight<<"kg"<<endl;
	        cout<<"Compatible with: "<<compatibleModel<<endl;
	    }
	    
		// Function 2: Compatibility Check (If it matches OR is a universal part)
		bool isCompatible(string carModel) const {
		    if(carModel == compatibleModel || compatibleModel == "Universal") {
		        return true;
		    }
		    return false;
		}
		
		// Function 3: Shipping Cost Logic (Base rate 10 PKR per kg per km)
	    double calculateShipping(double distance) const {
	        return weight*distance*10.0;
	    }
	    // Function 4: Quality Status (New/Used)
		void printQualityStatus() const {
		    if(condition == "New") {
		        cout<<"Status: Brand New - 1 Year Warranty"<<endl;
		    } else {
		        cout<<"Status: Used - No Warranty"<<endl;
		    }
		}
};

// 7. The Listing (Aggregates User, Vehicle, Part & Associates User)
class Listing {
    const int listingID;          // CONSTANT MEMBER 5 - shouldn't be modified
    User* seller;                 // ASSOCIATION 1
    Vehicle* vPtr;                // AGGREGATION 2 (Null if it's a part)
    SparePart* pPtr;              // AGGREGATION 3 (Null if it's a vehicle)
    long price;
    string status;                // "Pending", "Approved", "Sold"
    public:
    	// Parameterized Constructor (initializer list for const id)
    Listing(int id, double p, User* s, Vehicle* v = nullptr, SparePart* sp = nullptr)
        : listingID(id), price(p), seller(s), vPtr(v), pPtr(sp), status("Pending") {}

    // Function 1: Display Logic
    void displayListing() const {
        cout<<"Listing ID: "<<listingID<<" | Price: "<<price<<" PKR"<<endl;
        cout<<"Status: "<<status<<endl;
        if(vPtr != nullptr){
            vPtr->displayVehicle();
        }else if(pPtr != nullptr){
            pPtr->displaySparePart();
        }
    }

    // Function 2: Price Update Logic
    void updatePrice(double newPrice) {
        if(newPrice>0){
            price = newPrice;
            cout<<"Price updated to: "<<price<<endl;
        }else{
            cout<<"Error: Invalid Price!"<<endl;
        }
    }

    // Function 3: Approval Logic (Used by Admin)
    void approveListing() {
        status = "Approved";
        cout<<"Listing "<<listingID<<" has been approved."<<endl;
    }

    // Function 4: Sale Logic
    void markAsSold() {
        status = "Sold";
        cout<<"Listing "<<listingID<<" is now SOLD."<<endl;
    }

    // Getters for AdminPanel
    int getID() const {return listingID;}
    string getStatus() const {return status;}
    double getPrice() const {return price;}
    Vehicle* getvPtr() const {return vPtr;}
};

// 8. Communication
class Message {
    string senderID;
    string receiverID;
    string textContent;
    string timestamp;
    bool isRead;
    int messagePriority;
    public:
	    //Parameterized Constructor (text should have some content)
	    Message(string s, string r, string text, string time, int priority)
	    : senderID(s), receiverID(r), textContent(text), timestamp(time), isRead(false), messagePriority(priority) {}
	
	    // Function 1: Display with Read-Status Update
	    void displayMessage() {
	        isRead=true;
	        cout<<"["<<timestamp<<"] From: "<<senderID<<" | Priority: "<<messagePriority<<endl;
	        cout<<"Content: "<<textContent<<endl;
	    }
	
	    // Function 2: Preview Generator (Logic for Inbox/Notification View)
	    string getPreview() const {
	        if(textContent.length()>15){
	            return textContent.substr(0,15)+"...";
	        }
	        return textContent;
	    }
	
	    // Function 3: Urgency Upgrader (Keyword Detection)
	    void upgradeIfUrgent() {
	        if(textContent.find("urgent")!=string::npos || textContent.find("cash")!=string::npos){
	            messagePriority=3;
	            cout<<"Priority upgraded based on keywords."<<endl;
	        }
	    }
	
	    // Function 4: View Status (Update Read)
	    string getStatus() const {
	        if(isRead){
	        	return "Seen";
			}
			else{
				return "Not Seen";
			}
	    }
	
	    // Getters for Search/Filtering
	    string getSender() const {
	    	return senderID;
		}
	    string getReceiver() const {
	    	return receiverID;
		}
};

// 9. Administrative Logic
class AdminPanel {
    int accessLevel;			   // 1-5
    string lastActionPerformed;	   // Approved/Deleted ad
    int totalApprovals;
    int totalRemovals;
    const string adminKey;        // CONSTANT MEMBER 6 - shouldn't be chnaged by anyone
    static int activeAdmins;      // STATIC MEMBER 3
    public:
    	// Parameterized Constructor (initializer list for const key. Each admin should have a name, id, access level at time of creation. Maintains integrity avoids security breaches.)
	    AdminPanel(int level, string key) 
	        : accessLevel(level), adminKey(key), totalApprovals(0), totalRemovals(0), lastActionPerformed("None") {
	        activeAdmins++;
	    }
	
	    // Function 1: Approve a Listing
	    void approveListing(Listing* l) {
	        if(accessLevel >= 2) {
	            l->approveListing();
	            totalApprovals++;
	            lastActionPerformed = "Approved Listing "+to_string(l->getID());
	            cout<<"Listing "<<l->getID()<<" approved successfully."<<endl;
	        }
			else{
	            cout<<"Access Denied: Level 2 required."<<endl;
	        }
	    }
	
	    // Function 2: Unlock User Account
	    void unlockUser(User* u) {
	        u->getAccount().unlockAccount();
	        lastActionPerformed = "Unlocked User: "+u->getUserID();
	        cout<<"User "<<u->getUserID()<<" has been manually unlocked."<<endl;
	    }
	
	    // Function 3: Reset User Password
	    void resetUserPassword(User* u, string newPass) {
	        if(accessLevel >= 4) {
	            u->getAccount().resetPassword(newPass);
	            lastActionPerformed = "Reset Password for: "+u->getUserID();
	            cout<<"Password reset successful."<<endl;
	        }else{
	            cout<<"Access Denied: Level 4 required for security."<<endl;
	        }
	    }
	
	    // Function 4: Display Admin Details
	    void displayAdmin() const {
	        cout<<"Admin Key: "<<adminKey<<" | Level: "<<accessLevel<<endl;
	        cout<<"Actions: "<<totalApprovals<<" Approvals | "<<totalRemovals<<" Removals"<<endl;
	        cout<<"Last Action: "<<lastActionPerformed<<endl;
	    }
	
	    // Static Function to check total admins
	    static int getactiveAdmins() {
	        return activeAdmins;
	    }
};
// Initializing the static member
int AdminPanel::activeAdmins = 0;

// 10. The Controller (Aggregation, Array of Objects)
class Marketplace {
    Listing* allAds[100];         // ARRAY OF OBJECTS (Pointers) AGGREGATION 4
    User* allUsers[50];           // ARRAY OF OBJECTS (Pointers) AGGREGATION 5
    int adCount;
    int userCount;
    string regionCode;
    static int totalVisits;       // STATIC MEMBER 4
    public:
    	// Constructor (marketplace should have listing, users, etc. Initializes count)
	    Marketplace(string region) : regionCode(region), adCount(0), userCount(0) {}
	
	    // Function 1: Register User (Limit 50 per Region)
	    void registerUser(User* u) {
	        if(userCount<50){
	            allUsers[userCount++] = u;
	            totalVisits++; 
	        }else{
	            cout<<"Error: Reigon user limit reached."<<endl;
	        }
	    }
	
	    // Function 2: Post an Ad (Limit 100 per Region)
	    void postAd(Listing* l) {
	        if(adCount<100){
	            allAds[adCount++]=l;
	            totalVisits++;
	            cout<<"Ad posted successfully in region: "<<regionCode<<endl;
	        }else{
	            cout<<"Error: Region Ad limit reached."<<endl;
	        }
	    }
	
	    // Function 3: Search Logic
	    void filterMarket() const {
	        int choice;
	        cout<<"--- Search & Filter Menu ---"<<endl;
	        cout<<"1. Search by Brand"<<endl;
	        cout<<"2. Search by Year"<<endl;
	        cout<<"3. Search by Max Price"<<endl;
	        cout<<"4. Search by Max Mileage"<<endl;
	        cout<<"Enter choice: ";
	        cin>>choice;
	
	        switch(choice) {
	            case 1: {
	                string b;
	                cout<<"Enter Brand: "; cin>>b;
	                for(int i=0; i<adCount; i++) {
	                    if(allAds[i]->getvPtr()!=nullptr && allAds[i]->getvPtr()->getBrand()==b) {
	                        allAds[i]->displayListing();
	                        cout<<endl;
	                    }
	                }
	                break;
	            }
	            case 2: {
	                int y;
	                cout<<"Enter Year: "; cin>>y;
	                for(int i=0; i<adCount; i++) {
	                    if(allAds[i]->getvPtr()!=nullptr && allAds[i]->getvPtr()->getYear()==y) {
	                        allAds[i]->displayListing();
	                        cout<<endl;
	                    }
	                }
	                break;
	            }
	            case 3: {
	                double p;
	                cout<<"Enter Max Price: "; cin>>p;
	                for(int i=0; i<adCount; i++) {
	                    if(allAds[i]->getPrice()<=p) {
	                        allAds[i]->displayListing();
	                        cout<<endl;
	                    }
	                }
	                break;
	            }
	            case 4: {
	                int m;
	                cout<<"Enter Max Mileage: "; cin>>m;
	                for(int i=0; i<adCount; i++) {
	                    if(allAds[i]->getvPtr() != nullptr && allAds[i]->getvPtr()->getMileage()<=m) {
	                        allAds[i]->displayListing();
	                        cout<<endl;
	                    }
	                }
	                break;
	            }
	            default:
	                cout<<"Invalid choice."<<endl;
	        }
	    }
	
	    // Function 4: Marketplace Stats
	    void displayMarketStats() const {
	        cout<<"Marketplace Region: "<<regionCode<<endl;
	        cout<<"Active Users: "<<userCount<<" | Total Ads: "<<adCount<<endl;
	        cout<<"Total Platform Visits: "<<totalVisits<<endl;
	    }
	
	    // Static Function to check website activity
		static int getTotalVisits() {
	    	return totalVisits;
		}
};
// Initialize static member
int Marketplace::totalVisits = 0;

int main() {
    Engine e1(1500, "Petrol", 180, "Auto", "ENG123", 4);
    Engine e2(8900, "Diesel", 200, "Manual", "ENG456", 6);
    Category c1("Car", 4, "LTV", 0.02, false);
    Category c2("Truck", 6, "HTV", 0.05, true);
    Vehicle v1("Toyota", "Corolla", 2022, 15000, "New", e1, c1);
    Vehicle v2("Kia", "Sportage", 2021, 2000, "New", e1, c1);
    Vehicle v3("Suzuki", "Carry", 2015, 67000, "Old", e2, c2);

    Account acc1(101, "shafeek", "fhaa123", "06/07/2016");
    User u1("Shafqat", "S0889", "shafqat@jameel.com", "Seller", acc1);
    Account acc2(102, "treemhehe", "hehe123", "07/01/2007");
    User u2("Treem", "T0667", "troomtroom@jameel.com", "Buyer", acc2);

    Listing l1(6700, 2700000, &u1, &v1);
    Listing l2(6701, 670000, &u1, &v2);
    Listing l3(6702, 8900000, &u1, &v3);
    Marketplace khiMarket("Karachi");
    
	khiMarket.registerUser(&u1);
    khiMarket.postAd(&l1);
    khiMarket.postAd(&l2);
    khiMarket.postAd(&l3);
    khiMarket.filterMarket();
    
    //Testing rest of functions
    
	//Vehicle, Engine, Category
	cout<<"===Vehicle, Engine, Category Testing==="<<endl;
	cout<<"Is v1 Sports Grade?"<<endl;
    if(e2.isSportsGrade()){
    	cout<<"Yes."<<endl;
	}
	else{
		cout<<"No."<<endl;
	}
	e2.upgradeHorsepower(250);
	cout<<"Is v1 Sports Grade?"<<endl;
    if(e2.isSportsGrade()){
    	cout<<"Yes."<<endl;
	}
	else{
		cout<<"No."<<endl;
	}
	cout<<"Current Value of v2 (2026): "<<v2.calculateCurrentValue(6700000)<<endl;
	cout<<"Vehicle Status: ";
	v2.checkVehicleStatus();
	v1.updateMileage(2000); 		// should detect tampering
	v1.updateMileage(20000);		//should allow modification
	cout<<"Tax for v3: "<<c2.calculateTax(8900000)<<endl;
	cout<<"Capacity for v3: "<<c2.getCapacityLabel()<<endl;
	
	//Spare Parts
	cout<<"===Spare Parts Testing==="<<endl;
	SparePart sp1("Alloy Rim", "Kamran Autos", "New", 6767, "Sportage", 45);
	sp1.displaySparePart();
	cout<<"Is compatible for Sportage?"<<endl;
	sp1.isCompatible("Sportage");
	cout<<endl<<"Is compatible for Corolla?"<<endl;
	sp1.isCompatible("Corolla");
	cout<<endl<<"Quality Status: ";
	sp1.printQualityStatus();
	cout<<"Shipping price for 20 km: "<<sp1.calculateShipping(20)<<endl;
	
	//User
	cout<<"===User Testing==="<<endl;
	u1.login("password");
	u1.login("password");
	u1.login("password");		//should be locked after 3 wrong attempts
	u1.login("fhaa123");
	u2.login("hehe123");		//should login
	u2.saveFavorite(&v1);
	u2.saveFavorite(&v2);		//favourites added
	u2.viewProfile();
	
	//Admin Panel
	cout<<"===Admin Testing==="<<endl;
	AdminPanel a1(4, "FOODHEHE");
	a1.approveListing(&l1);
	a1.unlockUser(&u1);
	a1.resetUserPassword(&u2, "meowmeow");
	u1.login("fhaa123");		//should be unlocked now
	u2.login("hehe123");		//wrong password (updated)
	u2.login("meowmeow");		//should login
	a1.displayAdmin();
	cout<<endl;
	cout<<"Total no. of admins online: "<<a1.getactiveAdmins()<<endl;
	
	//Message
	cout<<"===Message Testing==="<<endl;
	Message m1("S0667", "S0889", "Is this still available? I have urgent cash.", "11:40 PM", 1);
    cout << "Preview: " << m1.getPreview() << endl;
    m1.upgradeIfUrgent(); 		// Should upgrade priority to 3 because of keywords
    m1.displayMessage(); 			// Should mark as read
    cout<<"Message Status: "<<m1.getStatus()<<endl;
    
    //Marketplace
    cout<<"===Marketplace Testing==="<<endl;
    khiMarket.displayMarketStats();
    cout<<"Total website traffic: "<<khiMarket.getTotalVisits()<<endl;

    return 0;
}
