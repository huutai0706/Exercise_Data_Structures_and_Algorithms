#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

struct Node {
    Company data;
    Node* next;
    Node(Company c) : data(c), next(nullptr) {}
};

struct HashTable {
    vector<Node*> table;
    HashTable(int size) {
        table.resize(size, nullptr);
    }
};

vector<Company> readCompanyList(string file_name) {
    vector<Company> companies;
    ifstream file(file_name);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        Company company;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        company.name = line.substr(0, pos1);
        company.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
        company.address = line.substr(pos2 + 1);

        companies.push_back(company);
    }

    file.close();
    return companies;
}

long long hashString(string company_name) {
    const int p = 31;
    const int m = 2000;
    long long hash_value = 0;

    string s = (company_name.length() > 20) 
               ? company_name.substr(company_name.length() - 20) 
               : company_name;

    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c * p_pow) % m) % m;
        p_pow = (p_pow * p) % m;
    }

    return (hash_value + m) % m; 
}

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hash_table = new HashTable(2000);

    for (const Company& company : list_company) {
        long long index = hashString(company.name);

        Node* new_node = new Node(company);

        if (hash_table->table[index] == nullptr) {
            hash_table->table[index] = new_node;
        } else {
            new_node->next = hash_table->table[index];
            hash_table->table[index] = new_node;
        }
    }

    return hash_table;
}

void insert(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);
    Node* new_node = new Node(company);

    if (hash_table->table[index] == nullptr) {
        hash_table->table[index] = new_node;
    } else {
        new_node->next = hash_table->table[index];
        hash_table->table[index] = new_node;
    }
}

Company* search(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);

    Node* current = hash_table->table[index];
    while (current != nullptr) {
        if (current->data.name == company_name) {
            return &(current->data);
        }
        current = current->next;
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./main <MST.txt> <input.txt> <output.txt>" << endl;
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    vector<Company> companies = readCompanyList(mst_file);

    HashTable* hash_table = createHashTable(companies);

    ifstream input(input_file);
    ofstream output(output_file);
    string company_name;

    while (getline(input, company_name)) {
        Company* result = search(hash_table, company_name);
        if (result != nullptr) {
            output << result->name << "|" << result->profit_tax << "|" << result->address << endl;
        } else {
            output << "Not found" << endl;
        }
    }

    input.close();
    output.close();

    for (Node* node : hash_table->table) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete hash_table;

    return 0;
}