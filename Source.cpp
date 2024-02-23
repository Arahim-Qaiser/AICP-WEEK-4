#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Item {
private:
    int itemNumber;
    string description;
    double reservePrice;
    double highestBid;
    int numBids;

public:
   
    Item(int itemNum, string desc, double reserve) {
    
        itemNumber = itemNum;
        description = desc;
        reservePrice = reserve;
        highestBid = 0.0;
        numBids = 0;

    } 
   
    int getItemNumber() const {
        return itemNumber;
    }
    string getDescription() const {
        return description;
    }
    double getReservePrice() const {
        return reservePrice;
    }
    double getHighestBid() const {
        return highestBid;
    }
    int getNumBids() const { 
        return numBids; 
    }

    
    void setHighestBid(double bid) {
        highestBid = bid; 
    }

   
    void incNumBids() { 
        numBids++;
    }
};


void auctionSetup(vector<Item>& items) {
    cout << "Auction Setup\n";
    int numItems;
    do {
        cout << "Enter the number of items (should be at least 10): ";
        cin >> numItems;
    } while (numItems < 10);

    for (int i = 0; i < numItems; ++i) {
        int itemNum;
        string desc;
        double reserve;
        cout << "Enter details for item " << i + 1 << ":\n";
        cout << "Item Number: ";
        cin >> itemNum;
        cout << "Description: ";
        cin.ignore();
        getline(cin, desc);
        cout << "Reserve Price: $";
        cin >> reserve;
        items.push_back(Item(itemNum, desc, reserve));
    }
}

void buyerBid(vector<Item>& items) {
    cout << "Buyer Bids\n";
    int itemNumber, buyerNumber;
    double bidAmount;
    char anotherBid;
    do {
        cout << "Enter item number: ";
        cin >> itemNumber;
        cout << "Enter your buyer number: ";
        cin >> buyerNumber;
        cout << "Enter your bid amount: $";
        cin >> bidAmount;

        bool found = false;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].getItemNumber() == itemNumber) {
                found = true;
                if (bidAmount > items[i].getHighestBid()) {
                    items[i].setHighestBid(bidAmount);
                    items[i].incNumBids();
                    cout << "Bid accepted.\n";
                }
                else {
                    cout << "Your bid must be higher than the current highest bid.\n";
                }
                break;
            }
        }
        if (!found) {
            cout << "Item not found.\n";
        }

        cout << "Do you want to place another bid? (Y/N): ";
        cin >> anotherBid;
    } while (toupper(anotherBid) == 'Y');
}
void endAuction(const vector<Item>& items) {
    cout << "End of Auction\n";
    double totalFee = 0.0;
    int itemsSold = 0, itemsBelowReserve = 0, itemsWithNoBids = 0;

    cout << "Items sold:\n";
    for (const Item& item : items) {
        if (item.getHighestBid() >= item.getReservePrice()) {
            itemsSold++;
            totalFee += 0.1 * item.getHighestBid();
            cout << "Item Number: " << item.getItemNumber() << ", Final Bid: $" << item.getHighestBid() << "\n";
        }
        else if (item.getNumBids() > 0) {
            itemsBelowReserve++;
            cout << "Item Number: " << item.getItemNumber() << ", Final Bid: $" << item.getHighestBid() << " (Below Reserve)\n";
        }
        else {
            itemsWithNoBids++;
            cout << "Item Number: " << item.getItemNumber() << " (No Bids)\n";
        }
    }

    cout << "Total fee for sold items: $" << totalFee << "\n";
    cout << "Number of items sold: " << itemsSold << "\n";
    cout << "Number of items that did not meet the reserve price: " << itemsBelowReserve << "\n";
    cout << "Number of items with no bids: " << itemsWithNoBids << "\n";
}

int main() {
    vector<Item> items;
    auctionSetup(items);
    buyerBid(items);
    endAuction(items);
    return 0;
}




