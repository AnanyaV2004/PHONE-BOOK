#include <bits/stdc++.h>
using namespace std;

// Structure to hold contact details
struct ContactDetails {
    string name;
    string email;
};

// Trie node definition
struct TrieNode {
    char digit;
    unordered_map<char, TrieNode*> children;
    ContactDetails* data;
};

void printContact(ContactDetails* contact, string number)
{
    if(!contact)
    cout << "Contact does not exist"<< endl;

    else
    {
        cout << "Name: " << contact->name << endl;
        cout << "Email: " << contact->email << endl;
        cout << "Phone-Number: "<< number << endl;
    }
}
// Function to insert a contact into the trie
void insertContact(TrieNode* root, const string& phoneNumber, const string& name, const string& email) {
    TrieNode* node = root;
    for (char digit : phoneNumber) {
        if (!node->children[digit]) {
            node->children[digit] = new TrieNode();
            node->children[digit]->data =NULL;
        }
        node = node->children[digit];
    }
    if(!node->data)
    {
        node->data = new ContactDetails{name, email};
        cout << "Contact successfully added"<<endl;
    }
    else
    {
        cout << "Contact already exists." << endl;
    }
}

void insert(TrieNode* root, const string& phoneNumber, const string& name, const string& email) {
    TrieNode* node = root;
    for (char digit : phoneNumber) {
        if (!node->children[digit]) {
            node->children[digit] = new TrieNode();
            node->children[digit]->data =NULL;
        }
        node = node->children[digit];
    }
    if(!node->data)
    {
        node->data = new ContactDetails{name, email};
    }
    else
    {
        cout << "Contact already exists." << endl;
    }
}

// Function to search for a contact in the trie
void searchContact(TrieNode* root, const string& phoneNumber) {
    TrieNode* node = root;
    for (char digit : phoneNumber) {
        if (!node->children[digit]) {
            cout << "Contact not found" << endl;
            return; // Contact not found
        }
        node = node->children[digit];
    }
    if(!node->data)
    {
            cout << "Contact not found" << endl;
            return; // Contact not found
        }
    else
    {
        printContact(node->data,phoneNumber);
    }
}

// Function to delete a contact from the trie
void deleteContact(TrieNode* root, const string& phoneNumber) {
    TrieNode* node = root;
    for (char digit : phoneNumber) {
        if (!node->children[digit]) {
            cout << "Contact not found" << endl;
            return; // Contact not found
        }
        node = node->children[digit];
    }
    if (node->data) {
        delete node->data;
        node->data = NULL;
        cout <<"Successfully deleted"<<endl;
    }
    else
    cout << "Contact not found" << endl;
}

// Function to display all contacts stored in the trie
int displayAllContacts(TrieNode* node, string phoneNumber = "") {
    if (!node) {
        return 0;
    }

    if (node->data) {
        printContact(node->data, phoneNumber);
        cout<<"\n";
        return 1;
    }
    int no_contacts = 0;
    for (const auto& kv : node->children) {
        no_contacts+= displayAllContacts(kv.second, phoneNumber + kv.first);
    }
    return no_contacts;
}

void displayAll(TrieNode* node)
{  
    int no_contacts = displayAllContacts(node,"");
    if(no_contacts==0)
    cout<<"No contacts found"<<endl;
}

void suggestContacts(TrieNode*root, string partial_num)
{
    TrieNode* node = root;
    for (char digit : partial_num) {
        if (!node->children[digit]) {
            cout << "No contacts found" << endl;
            return; // Contact not found
        }
        node = node->children[digit];
    }
    displayAllContacts(node,partial_num);
}

// Function to delete all contacts from the trie
void deleteAllContacts(TrieNode* node) {
    if (!node) {
        return;
    }

    for (auto& kv : node->children) {
        deleteAllContacts(kv.second);
    }

    delete node->data;
    node->data = nullptr;
}

// Function to write contacts to the input file
void writeContactsToFile(TrieNode* node, ofstream& outputFile, string phoneNumber = "") {
    if (!node) {
        return;
    }

    if (node->data) {
        outputFile << phoneNumber << " " << node->data->name << " " << node->data->email << "\n";
    }

    for (const auto& kv : node->children) {
        writeContactsToFile(kv.second, outputFile, phoneNumber + kv.first);
    }
}


int main(int argc, char* argv[]) {

    cout << "-------------Welcome to the phone directory!-------------"<<endl;
    cout << "Given are the required inputs for the specific instructions"<<endl;
    cout << "INSTRUCTIONS                    INPUTS REQUIRED"<<endl;
    cout << "Add a new contact               1 <Phone number> <Name> <Email>"<<endl;
    cout << "Delete a contact                2 <Phone number>"<<endl;
    cout << "Display all contacts            3"<<endl;
    cout << "Search for a contact            4 <Phone number>"<<endl;
    cout << "Suggest contacts                5 <Partial Phone number>"<<endl;
    cout << "Delete all contacts             6"<<endl;
    cout << "Save and close                  7"<<endl;

    if (argc < 2) {
        cout << "Give an input contacts file"<<endl;
        return 1;
    }

    TrieNode* root = new TrieNode(); // Create the root of the trie

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cout << "Failed to open input file.\n";
        return 1;
    }

    string phoneNumber, name, email;
    while (inputFile >> phoneNumber >> name >> email) {
        insert(root, phoneNumber, name, email);
    }

    inputFile.close();

    while (true) {
        char temp;
        cin >> temp;
        int instruction = temp-'0';
        
        if (instruction == 1) {
            string phoneNumber, name, email;
            cin >> phoneNumber >> name >> email;
            insertContact(root, phoneNumber, name, email);
        } else if (instruction == 2) {
            string phoneNumber;
            cin >> phoneNumber;
            deleteContact(root, phoneNumber);
        } else if (instruction == 3) {
            displayAll(root);
        } else if (instruction == 4) {
            string phoneNumber;
            cin >> phoneNumber;
            searchContact(root, phoneNumber);
        } else if (instruction == 5) {
            string phoneNumber;
            cin >> phoneNumber;
            suggestContacts(root,phoneNumber);
        } else if (instruction == 6) {
            deleteAllContacts(root);
        } else if (instruction == 7) {
            
            ofstream outputFile(argv[1]);
            if (!outputFile.is_open()) {
                cerr << "Failed to open output file for writing.\n";
                return 1;
            }

            // Write contacts to the input file
            writeContactsToFile(root, outputFile);

            outputFile.close();

            return 0;
        }
        else
        cout << "Instruction no recognised"<<endl;
    }

    return 0;
}
