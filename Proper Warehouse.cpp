//Lab 6 Mohammadzadeh,Hiva Thursday
//Proper Warehouse- Queues


#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>

using namespace std;

class WidgetType {

private:

    int quantity;
    double cost;
    WidgetType * next;

public:

    WidgetType();
    ~WidgetType();

    void SetCost(double newCost) {
        cost = newCost;
    }

    void SetQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void SetNext(WidgetType * newNext) {
        next = newNext;
    }

    WidgetType * GetNext() {
        return next;
    }

    double GetCost() {
        return cost;
    }

    int GetQuantity() {
        return quantity;
    }

};

WidgetType::WidgetType() {
    //Constructor
    quantity = 0;
    cost = 0;
    next = nullptr;
}

WidgetType::~WidgetType() {
    //Destructor
    quantity = 0;
    cost = 0;
    next = nullptr;
}

class QueueType {

private:

    WidgetType * first;
    WidgetType * last;
    int lengthOfQueue;

public:

    QueueType();
    ~QueueType();

    bool isEmpty();
    void Enqueue(int quantity, double cost);
    void Dequeue();
    WidgetType *Peek();
    WidgetType *Peek2();
    void MakeEmpty();
    void Inventory(int, double);
    void Ship(int);
    void Print();
    
    WidgetType getLast(){
        return *last;
    }

};

QueueType::QueueType() {
    //Constructor for StackType class
    first = nullptr;
    last = nullptr;
    lengthOfQueue = 0;
}

QueueType::~QueueType() {
    MakeEmpty();
}

void QueueType::MakeEmpty() {
    while (first != nullptr)
        Dequeue();
}

bool QueueType::isEmpty() {
    return (first == nullptr);
}

void QueueType::Enqueue(int quantity, double cost = 0) {

    WidgetType *newItem = new (nothrow) WidgetType;

    if (newItem == nullptr) {

        cout << "\nERROR: Item was not created. There is not enough memory.\n" << endl;
        MakeEmpty();
        system("pause");
        exit(1);

    }

    newItem->SetCost(cost);
    newItem->SetQuantity(quantity);

    if (isEmpty()) {
        first = newItem;
        last = newItem;
    }
    else {
        last->SetNext(newItem);
        last = last->GetNext();
    }
}

void QueueType::Dequeue() {

    WidgetType * temp = nullptr;

    if (first != nullptr) {
        temp = first;
        first = first->GetNext();
        delete temp;
    }

    temp = nullptr;
}

WidgetType* QueueType::Peek(){

    return first;
}
WidgetType* QueueType :: Peek2(){
    return last;
}

void QueueType::Print() {
    WidgetType *temp = first;

    while (temp != nullptr) {

        if (temp->GetCost() != 0) {

            cout << "\t\t" << temp->GetQuantity()<< "\t\t\t\t" << temp->GetCost() << endl;
        }

        else {
            cout << "\t\t" << temp->GetQuantity() << endl;
        }
        temp = temp->GetNext();
    }
}

void QueueType::Inventory(int quantity, double price) {

    cout << "\nDELIVERY\nPlease enter the amount of orders: ";
    cin >> quantity;

    while (quantity < 1 || cin.fail()) {

        cout << "\nERROR: Quantity must be a positive whole number greater than zero. Please try again.\n" << endl;
        cout << "Please enter the amount of orders: ";
        cin >> quantity;
        cin.clear();
        cin.ignore(200, '\n');
    }

    cout << "Please enter the price: $";
    cin >> price;

    while (price < 0.01 || cin.fail()) {

        cout << "\nERROR: Price must be a positive number greater than zero. Please try again.\n" << endl;
        cout << "Please enter the price: $";
        cin >> price;
        cin.clear();
        cin.ignore(200, '\n');
    }

    Enqueue(quantity, price);
}

void QueueType::Ship(int quantity) {

    cout << "\nPlease enter the amount of orders: ";
    cin >> quantity;

    while (quantity < 1 || cin.fail()) {

        cout << "\nERROR: Orders must be a positive whole number. Please try again.\n" << endl;
        cout << "Please enter the amount of orders: ";
        cin >> quantity;
        cin.clear();
        cin.ignore(200, '\n');
    }

    Enqueue(quantity);
}

void SellOrders(QueueType&, QueueType&);

enum Option { Inventory = 1, Order, Current, CurrentOrders, Quit };

int main() {
    int userInput = 0;
    QueueType Widgets;
    QueueType Orders;
    double price = 0;
    int quantity = 0;
    int orderNumber = 1000;

    cout << showpoint << fixed << setprecision(2);
    cout << "WELCOME!" << endl;

    do {
        cout << "\n1. Add new widgets to the inventory.\n"
            << "2. Place an order.\n"
            << "3. Print the current inventory.\n"
            << "4. Print the outstanding orders.\n"
            << "5. Quit the program.\n" << endl;
        
        cin >> userInput;


        switch (userInput) {

        case Inventory:

            cout << "\n====================================" << endl;
            Widgets.Inventory(quantity, price);
            SellOrders(Widgets, Orders);
            cout << "====================================" << endl;
            break;

        case Order:

            cout << "\n====================================" << endl;
            cout << "\nORDER #" << orderNumber;
            orderNumber++;
            Orders.Ship(quantity);
            SellOrders(Widgets, Orders);
            cout << "\n====================================" << endl;
            break;

        case Current:

            cout << "\nQuantity in stock\t   price($)"
                 << "\n====================================" << endl;

            if (Orders.isEmpty() && !(Widgets.isEmpty()))
                           Widgets.Print();
            else
                cout << "\nInventory is empty.\n" << endl;

            cout << "\n====================================" << endl;
            break;
                
        case CurrentOrders:
                cout << "\nQuantity to be shiped"
                     << "\n====================================" << endl;
                if (Widgets.isEmpty() && !(Orders.isEmpty())){
                    Orders.Print();
                }
                else
                cout << "\nThere have been no orders." << endl;
                 cout << "\n====================================" << endl;
                break;
                

        case Quit:

            cout << "\nProgram is now terminating..." << endl;
            break;

        default:

            cout << "\nERROR: Input must be between 1 and 4. Please try again." << endl;
            cin.clear();
            cin.ignore(200, '\n');
            break;
        }

    } while (userInput != Quit);

    system("pause");
    return 0;
}

void SellOrders(QueueType & Widgets, QueueType & Orders) {

    QueueType *TempStack = new QueueType;
    int quantityShipped = 0;
    double costToWarehouse = 0, costToCustomer = 0, totalProfit = 0;
    int i = 0;

    while (!(Widgets.isEmpty()) && !(Orders.isEmpty())) {

        if (Widgets.Peek()->GetQuantity() >= Orders.Peek()->GetQuantity()) {

            if (i == 0) {

                cout << "\nSHIPMENT DETAILS" << endl;
                cout << right << setw(15) << "QTY. SHIPPED" << setw(15) << "UNIT PRICE" << setw(20) << "COST TO WAREHOUSE" << setw(20) << "COST TO CUSTOMER" << endl;
            }

            quantityShipped += Orders.Peek()->GetQuantity();

            totalProfit = costToCustomer + 1.5 * Widgets.Peek()->GetCost() * Orders.Peek()->GetQuantity() - (costToWarehouse + Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost());

            cout << right << setw(15) << Orders.Peek()->GetQuantity() << setw(15) <<    Widgets.Peek()->GetCost() << setw(20) << Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost() << setw(20) << Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5 << endl;

            cout << "\nSHIPMENT SUMMARY" << "\nQTY. ORDERED" << right << setw(15)
                 << quantityShipped << "\nQTY. SHIPPED" << setw(15) << quantityShipped
                 << "\nQTY. TO BE SHIPPED" << setw(9) << "0"
                 << "\nCOST TO WAREHOUSE" << setw(10) << costToWarehouse + Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost()
                 << "\nCOST TO CUSTOMER" << setw(11) << costToCustomer + 1.5 * Widgets.Peek()->GetCost() * Orders.Peek()->GetQuantity()
                 << "\nTOTAL PROFIT" << setw(15) << totalProfit << endl;

            Widgets.Peek()->SetQuantity(Widgets.Peek()->GetQuantity() - Orders.Peek()->GetQuantity());

            Orders.Dequeue();

            if (Widgets.Peek()->GetQuantity() == 0)
                Widgets.Dequeue();
        }

        else {

            if (i == 0) {

                cout << "\nSHIPMENT DETAILS\n"
                     << right << setw(15) << "QTY. SHIPPED" << setw(15) << "UNIT PRICE"
                     << setw(20) << "COST TO WAREHOUSE" << setw(20) << "COST TO CUSTOMER"
                     << endl;

                i++;
            }

            cout << right << setw(15) << Widgets.Peek()->GetQuantity() << setw(15)
                 << Widgets.Peek()->GetCost() << setw(20) << Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() << setw(20) << Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5 << endl;

            quantityShipped += Widgets.Peek()->GetQuantity();
            costToWarehouse += Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost();
            costToCustomer += Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5;

            Orders.Peek()->SetQuantity(Orders.Peek()->GetQuantity() - Widgets.Peek()->GetQuantity());
            Widgets.Dequeue();
        }
    }

    if (Orders.isEmpty() && !(Widgets.isEmpty())) {

        int totalWidgets = 0;

        while (!(Widgets.isEmpty())) {

            totalWidgets += Widgets.Peek()->GetQuantity();
            TempStack->Enqueue(Widgets.Peek()->GetQuantity(), Widgets.Peek()->GetCost());
            Widgets.Dequeue();
        }

        while (!(TempStack->isEmpty())) {

            Widgets.Enqueue(TempStack->Peek()->GetQuantity(), TempStack->Peek()->GetCost());
            TempStack->Dequeue();
        }

        cout << "\nWidgets in stock: " << totalWidgets << endl<< endl;
        delete TempStack;
    }

    else if (Widgets.isEmpty() && !(Orders.isEmpty())) {
        
        cout << "\nInventory is empty. " << Orders.Peek2()->GetQuantity() << " orders of widgets will be backlogged.\n" << endl;
    }
}

/*
TEST DATA FOR LABS 5 & 6

1. Add 0 new widgets->ERROR
2. Add - 5 new widgets->ERROR
3. Add ABC new widgets->ERROR
4. Add 4 new widgets at a price of $ - 4.00->ERROR - > price of $4.00
5. Add 3 new widgets at a price of ABC->ERROR->$3.00
6. Print Current Inventory
7. Place an order for 2 widgets
8. Place an order for 3 widgets
9. Add 5 new widgets for $5.00
10. Place an order for 9 widgets -> 2 should be backlogged
11. Add 3 new widgets for $3.00
12. Print Current Inventory
13. Place an order for 5 widgets -> 4 should be backlogged
14. Print Current Inventory
15. Place an order for - 5 widgets->ERROR -> 4 widgets
16. Quit the Program
*/
/*
 WELCOME!

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 hgdjasj

 ERROR: Input must be between 1 and 4. Please try again.

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 78278

 ERROR: Input must be between 1 and 4. Please try again.

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 89

 ERROR: Input must be between 1 and 4. Please try again.

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 0

 ERROR: Input must be between 1 and 4. Please try again.

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 -4

 ERROR: Input must be between 1 and 4. Please try again.

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 0

 ERROR: Quantity must be a positive whole number greater than zero. Please try again.

 Please enter the amount of orders: -5

 ERROR: Quantity must be a positive whole number greater than zero. Please try again.

 Please enter the amount of orders: as

 ERROR: Quantity must be a positive whole number greater than zero. Please try again.

 Please enter the amount of orders: 4
 Please enter the price: $-4

 ERROR: Price must be a positive number greater than zero. Please try again.

 Please enter the price: $0

 ERROR: Price must be a positive number greater than zero. Please try again.

 Please enter the price: $er

 ERROR: Price must be a positive number greater than zero. Please try again.

 Please enter the price: $4

 Widgets in stock: 4

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 3
 Please enter the price: $3

 Widgets in stock: 7

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================
         4                4.00
         3                3.00

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1000
 Please enter the amount of orders: 2

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           4.00                8.00               12.00

 SHIPMENT SUMMARY
 QTY. ORDERED              2
 QTY. SHIPPED              2
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE      8.00
 COST TO CUSTOMER      12.00
 TOTAL PROFIT           4.00

 Widgets in stock: 5


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1001
 Please enter the amount of orders: 3

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           4.00                8.00               12.00
               1           3.00                3.00                4.50

 SHIPMENT SUMMARY
 QTY. ORDERED              3
 QTY. SHIPPED              3
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     11.00
 COST TO CUSTOMER      16.50
 TOTAL PROFIT           5.50

 Widgets in stock: 2


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 5
 Please enter the price: $5

 Widgets in stock: 7

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1002
 Please enter the amount of orders: 9

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           3.00                6.00                9.00
               5           5.00               25.00               37.50

 Inventory is empty. 2 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         2

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 3
 Please enter the price: $3

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           3.00                6.00                9.00

 SHIPMENT SUMMARY
 QTY. ORDERED              2
 QTY. SHIPPED              2
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE      6.00
 COST TO CUSTOMER       9.00
 TOTAL PROFIT           3.00

 Widgets in stock: 1

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================
         1                3.00

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1003
 Please enter the amount of orders: 5

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               1           3.00                3.00                4.50

 Inventory is empty. 4 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         4

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1004
 Please enter the amount of orders: 5

 Inventory is empty. 5 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1005
 Please enter the amount of orders: 4

 Inventory is empty. 4 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         4
         5
         4

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 13
 Please enter the price: $13

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               4          13.00               52.00               78.00

 SHIPMENT SUMMARY
 QTY. ORDERED              4
 QTY. SHIPPED              4
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     52.00
 COST TO CUSTOMER      78.00
 TOTAL PROFIT          26.00

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               5          13.00               65.00               97.50

 SHIPMENT SUMMARY
 QTY. ORDERED              9
 QTY. SHIPPED              9
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     65.00
 COST TO CUSTOMER      97.50
 TOTAL PROFIT          32.50

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               4          13.00               52.00               78.00

 SHIPMENT SUMMARY
 QTY. ORDERED             13
 QTY. SHIPPED             13
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     52.00
 COST TO CUSTOMER      78.00
 TOTAL PROFIT          26.00
 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================

 There have been no orders.

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 5
 Please enter the price: $1

 Widgets in stock: 5

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 4
 Please enter the price: $2

 Widgets in stock: 9

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 3
 Please enter the price: $3

 Widgets in stock: 12

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================
         5                1.00
         4                2.00
         3                3.00

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1006
 Please enter the amount of orders: 3

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               3           1.00                3.00                4.50

 SHIPMENT SUMMARY
 QTY. ORDERED              3
 QTY. SHIPPED              3
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE      3.00
 COST TO CUSTOMER       4.50
 TOTAL PROFIT           1.50

 Widgets in stock: 9


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1007
 Please enter the amount of orders: 7

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           1.00                2.00                3.00
               4           2.00                8.00               12.00
               1           3.00                3.00                4.50

 SHIPMENT SUMMARY
 QTY. ORDERED              7
 QTY. SHIPPED              7
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     13.00
 COST TO CUSTOMER      19.50
 TOTAL PROFIT           6.50

 Widgets in stock: 2


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1008
 Please enter the amount of orders: 3

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               2           3.00                6.00                9.00

 Inventory is empty. 1 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         1

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1009
 Please enter the amount of orders: 5

 Inventory is empty. 5 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         1
         5

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 6
 Please enter the price: $2

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               1           2.00                2.00                3.00

 SHIPMENT SUMMARY
 QTY. ORDERED              1
 QTY. SHIPPED              1
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE      2.00
 COST TO CUSTOMER       3.00
 TOTAL PROFIT           1.00

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               5           2.00               10.00               15.00

 SHIPMENT SUMMARY
 QTY. ORDERED              6
 QTY. SHIPPED              6
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     10.00
 COST TO CUSTOMER      15.00
 TOTAL PROFIT           5.00
 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1010
 Please enter the amount of orders: 4

 Inventory is empty. 4 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         4

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1011
 Please enter the amount of orders: 5

 Inventory is empty. 5 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 2

 ====================================

 ORDER #1012
 Please enter the amount of orders: 6

 Inventory is empty. 6 orders of widgets will be backlogged.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================
         4
         5
         6

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 1

 ====================================

 DELIVERY
 Please enter the amount of orders: 15
 Please enter the price: $4

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               4           4.00               16.00               24.00

 SHIPMENT SUMMARY
 QTY. ORDERED              4
 QTY. SHIPPED              4
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     16.00
 COST TO CUSTOMER      24.00
 TOTAL PROFIT           8.00

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               5           4.00               20.00               30.00

 SHIPMENT SUMMARY
 QTY. ORDERED              9
 QTY. SHIPPED              9
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     20.00
 COST TO CUSTOMER      30.00
 TOTAL PROFIT          10.00

 SHIPMENT DETAILS
    QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
               6           4.00               24.00               36.00

 SHIPMENT SUMMARY
 QTY. ORDERED             15
 QTY. SHIPPED             15
 QTY. TO BE SHIPPED        0
 COST TO WAREHOUSE     24.00
 COST TO CUSTOMER      36.00
 TOTAL PROFIT          12.00
 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 3

 Quantity in stock       price($)
 ====================================

 Inventory is empty.


 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 4

 Quantity to be shiped
 ====================================

 There have been no orders.

 ====================================

 1. Add new widgets to the inventory.
 2. Place an order.
 3. Print the current inventory.
 4. Print the outstanding orders.
 5. Quit the program.

 5

 Program is now terminating...
 sh: pause: command not found
 Program ended with exit code: 0
*/


