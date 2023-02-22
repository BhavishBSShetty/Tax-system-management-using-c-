#include <bits/stdc++.h>

using namespace std;

// Global declaration of total tax collected and list of owners who paid tax
map<string, vector<int>> taxPaidList;
int totalTaxCollected = 0;

struct Property
{
    int khataID;
    double physicalDimension;
    int numberOfStories;
    double taxForProperty;
    string usage;
    string taxPaid;
};

class Owner
{
private:
    static int ID;

public:
    string name;
    string address;
    long long phone;
    string email;
    map<int, struct Property> khataList;
    string ans;

    Owner() {}

    // Function add new owner
    void addOwner(string ownerName)
    {
        name = ownerName;
    ADRSS:
        cout << endl
             << "Enter the address (maximum 120 characters):";
        getline(cin, address);
        if (address.size() > 120)
        {
            cout << "Please enter maximum of 120 characters\n";
            goto ADRSS;
        }
        cout << endl
             << "Enter the mobile number:";
        cin >> phone;
        cin.ignore();
        cin.sync();
        cout << endl
             << "Enter the email address:";
        getline(cin, email);

    ADDMORE:
        cout << endl
             << "Do you want to add property:(yes/no)";
        getline(cin, ans);
        transform(ans.begin(), ans.end(), ans.begin(), ::tolower);

        if (ans.compare("yes") == 0)
        {
            addProperty();

            goto ADDMORE;
        }
    }

    // Function to add Properties
    void addProperty()
    {
        Property pr;
        float length, breadth;
        pr.khataID = ++ID;
        cout << endl
             << "Enter the length:";
        cin >> length;
        cout << endl
             << "Enter the breadth:";
        cin >> breadth;
        pr.physicalDimension = length * breadth;
        cout << endl
             << "Enter the number of stories in range 0-25:";
    NOOFSTR:
        cin >> pr.numberOfStories;
        if (pr.numberOfStories > 25)
        {
            cout << endl
                 << "Please enter number of stories in range 0-25:";
            goto NOOFSTR;
        }
        cin.ignore();
        cin.sync();

    USA:
        cout << endl
             << "Enter the usage (self/rented):";
        getline(cin, pr.usage);
        transform(pr.usage.begin(), pr.usage.end(), pr.usage.begin(), ::tolower);
        if (pr.usage.compare("self") != 0 && pr.usage.compare("rented") != 0)
        {
            cout << "Please enter a valid input" << endl;
            goto USA;
        }

        pr.taxForProperty = calculateTax(pr.numberOfStories, pr.usage, pr.physicalDimension);
        cout << endl
             << "Tax paid(yes/no):";
        getline(cin, pr.taxPaid);
        transform(pr.taxPaid.begin(), pr.taxPaid.end(), pr.taxPaid.begin(), ::tolower);

        if (pr.taxPaid.compare("yes") == 0)
        {
            // taxPaidID.emplace_back(pr.khataID);
            taxPaidList[name].emplace_back(pr.khataID);
            totalTaxCollected += pr.taxForProperty;
        }

        khataList[pr.khataID] = pr;
    }

    // Function to calculate the tax
    double calculateTax(int numberofStories, string usage, double dimension)
    {
        double builtUpArea = dimension * numberofStories;
        float localityIndex, economicIndex;
        switch (numberofStories)
        {
        case 0:
            return dimension * 1;

        case 1:
            if (usage.compare("self") == 0)
            {
                return dimension * 1.5;
            }
            else
            {
                return dimension * 1.75;
            }

        case 2 ... 3:

            if (usage.compare("self") == 0)
            {
                return builtUpArea * 2;
            }
            else
            {
                return builtUpArea * 2.25;
            }

        case 4 ... 5:
            cout << endl
                 << "Enter the locality index (value in between 1.0 to 2.0):";
            cin >> localityIndex;
            cin.ignore();
            cin.sync();
            return localityIndex * builtUpArea * 3.5;

        case 6 ... 25:
            cout << endl
                 << "Enter the Economic index (value in between 1.0 to 2.0):";
            cin >> economicIndex;
            cin.ignore();
            cin.sync();
            return economicIndex * builtUpArea * 5;
        }
    }
};

// Function to print all details
void printAllDetails(map<string, Owner> ownerDictionary)
{
    int count = 0;

    for (auto it : ownerDictionary)
    {

        Owner c = it.second;
        cout << endl
             << "******"
             << "OWNER " << ++count << "******" << endl;
        cout << "i.Owners name:" << c.name << endl;
        cout << "ii.Address:" << c.address << endl;
        cout << "iii.Phone Number:" << c.phone << endl;
        cout << "iv.Email:" << c.email << endl;
        cout << endl
             << "List of properties:" << endl;

        cout << endl;
        for (auto x : c.khataList)
        {
            Property pr = x.second;
            cout << "*** Property ID:" << pr.khataID << " ***" << endl;
            cout << "Dimension:" << pr.physicalDimension << endl;
            cout << "Number of stories:" << pr.numberOfStories << endl;
            cout << "Tax for the property:" << pr.taxForProperty << endl;
            cout << "Usage:" << pr.usage << endl;
            cout << "Tax paid:" << pr.taxPaid << endl;
            cout << endl;
        }

        cout << "*************************";
    }
}

// Function to display the taxes
void displayTax(map<string, Owner> ownerDictionary)
{
    int katanumber;
    cout << "Enter the khata number: " << endl;
    cin >> katanumber;
    for (auto it : ownerDictionary)
    {
        Owner c = it.second;
        for (auto x : c.khataList)
        {
            Property pr = x.second;
            if (pr.khataID == katanumber)
            {

                cout << "*************************" << endl;
                if (pr.taxPaid.compare("yes") == 0)
                {
                    cout << endl
                         << "Tax for the property is " << pr.taxForProperty << " and it is PAID" << endl;
                }
                else
                {
                    cout << endl
                         << "Tax to be paid is " << pr.taxForProperty << endl;
                }
                cout << "*************************" << endl;
                return;
            }
        }
    }
    cout << "Property has not been added!!" << endl;
}

int Owner::ID = 0;

int main()
{
    map<string, Owner> ownerDictionary;
    string ownerName;

    cout << "----------------------------------------- PROPERTY TAX SYSTEM -----------------------------------------" << endl;

    while (1)
    {
        cout << endl;
        cout << "\n1. Add Owner\n";
        cout << "\n2. Add Property\n";
        cout << "\n3. Calculate tax\n";
        cout << "\n4. Pay tax\n";
        cout << "\n5. Print tax collected\n";
        cout << "\n6. Print all details\n";
        cout << "\n Enter 0 to Exit\n";

        int n;
        cin >> n;
        cin.ignore();
        cin.sync();

        switch (n)
        {
        case 1:
        {
            cout << endl
                 << "Enter the name of the owner:";
            getline(cin, ownerName);
            Owner own;
            own.addOwner(ownerName);
            ownerDictionary[ownerName] = own;
            cout << endl
                 << "********* Owner added to the database *********" << endl;
            break;
        }

        case 2:
        {
            cout << endl
                 << "Enter the name of the owner:";
            getline(cin, ownerName);
            if (ownerDictionary.find(ownerName) != ownerDictionary.end())
            {
                ownerDictionary[ownerName].addProperty();
                cout << endl
                     << "********* Property added to the database *********" << endl;
            }
            else
            {
                cout << "Owner not present in the database!! Please add the owner first" << endl
                     << endl;
                break;
            }
            break;
        }

        case 3:
        {
            displayTax(ownerDictionary);
            break;
        }

        case 4:
        {
            if (taxPaidList.size() == 0)
            {
                cout << endl
                     << "No tax payed yet!" << endl;
            }
            else
            {
                cout << endl
                     << "***************** TAX PAID ***************** " << endl;
                cout << "Owner and Properties" << endl;
                int i = 1;
                for (auto x : taxPaidList)
                {
                    cout << i++ << ". " << x.first << ":";
                    for (auto y : x.second)
                    {
                        cout << y << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            string answ;

            cout << "Do you want to update the tax paid list (yes/no):";
            getline(cin, answ);
            if (answ.compare("yes") == 0)
            {
                int propertyid;
                cout << endl
                     << "Enter the name of the owner:";
                getline(cin, ownerName);
                cout << endl
                     << "Enter the property id:";
                cin >> propertyid;

                int i = 1, flag = 0;
                for (auto x : taxPaidList)
                {
                    if (x.first.compare(ownerName) == 0)
                        for (auto y : x.second)
                        {
                            if (y == propertyid)
                            {
                                flag = 1;
                            }
                        }
                }
                if (flag == 1)
                {
                    cout << ownerName << " has already paid tax for property " << propertyid << endl;
                    break;
                }

                if (ownerDictionary.find(ownerName) != ownerDictionary.end() && ownerDictionary[ownerName].khataList.find(propertyid) != ownerDictionary[ownerName].khataList.end())
                {
                    taxPaidList[ownerName].emplace_back(propertyid);
                    ownerDictionary[ownerName].khataList[propertyid].taxPaid = "yes";
                    totalTaxCollected += ownerDictionary[ownerName].khataList[propertyid].taxForProperty;
                    cout << endl
                         << "*****************" << endl;
                    cout << ownerName << "'s property " << propertyid << " tax is paid" << endl;
                    cout << "*****************" << endl;
                }
                else if (ownerDictionary.find(ownerName) == ownerDictionary.end())
                {
                    cout << endl
                         << "Owner not present in the database!!!" << endl;
                }
                else
                {
                    cout << endl
                         << "Property is not present in " << ownerName << "'s list" << endl;
                }
            }
            break;
        }
        case 5:
        {
            cout << "**************************************" << endl;
            cout << "Total tax collected by the corporation:" << totalTaxCollected << endl;
            cout << "**************************************" << endl;
            break;
        }

        case 6:
        {
            printAllDetails(ownerDictionary);
            break;
        }
        case 0:
            exit(0);

        default:
            cout << "Enter a valid input!";
        }
    }

    return 0;
}
