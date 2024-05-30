#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include<bits/stdc++.h>

using namespace std;
enum IPClass {
    UNICAST,
    MULTICAST,
    BROADCAST,
    LOOPBACK,
    LINK_LOCAL,
    PRIVATE,
    RESERVED,
    INVALID
};

vector<int> split(const string &str, char delim) {
    vector<int> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delim)) {
        tokens.push_back(stoi(token));
    }
    return tokens;
}

IPClass check_ip_cast(const string &ip_address) {
    vector<int> octets = split(ip_address, '.');

    if (octets.size() != 4) {
        return INVALID;
    }

    for (int i = 0; i < 4; ++i) {
        if (octets[i] < 0 || octets[i] > 255) {
            return INVALID;
        }
    }

    int first_octet = octets[0];

    if (first_octet >= 1 && first_octet <= 223) {
        if (first_octet == 10 || 
           (first_octet == 172 && octets[1] >= 16 && octets[1] <= 31) || 
           (first_octet == 192 && octets[1] == 168)) {
            return PRIVATE;
        } else if (first_octet == 127) {
            return LOOPBACK;
        } else if (first_octet == 169 && octets[1] == 254) {
            return LINK_LOCAL;
        }
        return UNICAST;
    }

    if (first_octet >= 224 && first_octet <= 239) {
        return MULTICAST;
    }

    if (first_octet >= 240 && first_octet <= 255) {
        return RESERVED;
    }

    return INVALID;
}

void Checking_type_of_Address(void){
    string ip_address;
    cout << "\nEnter an IPv4 address: ";
    cin >> ip_address;

    IPClass result = check_ip_cast(ip_address);

    switch (result) {
        case UNICAST:
            cout << "Unicast" << endl;
            break;
        case MULTICAST:
            cout << "Multicast" << endl;
            break;
        case BROADCAST:
            cout << "Broadcast" << endl;
            break;
        case LOOPBACK:
            cout << "Loopback" << endl;
            break;
        case LINK_LOCAL:
            cout << "Link-local" << endl;
            break;
        case PRIVATE:
            cout << "Private Unicast" << endl;
            break;
        case RESERVED:
            cout << "Reserved" << endl;
            break;
        case INVALID:
        default:
            cout << "Invalid IP address" << endl;
            break;
    }
}

unsigned int ip_to_int(const string &ip_address) {
    vector<int> octets = split(ip_address, '.');
    if (octets.size() != 4) {
        throw invalid_argument("Invalid IP address");
    }
    unsigned int ip_int = 0;
    for (int i = 0; i < 4; ++i) {
        if (octets[i] < 0 || octets[i] > 255) {
            throw invalid_argument("Invalid IP address");
        }
        ip_int = (ip_int << 8) + octets[i];
    }
    return ip_int;
}

unsigned int count_ips_in_range(const string &start_ip, const string &end_ip) {
    unsigned int start = ip_to_int(start_ip);
    unsigned int end = ip_to_int(end_ip);
    if (start > end) {
        throw invalid_argument("Start IP must be less than or equal to End IP");
    }
    return end - start + 1;
}

void Find_No_IP(void){
    string start_ip, end_ip;
    cout << "Enter the starting IP address: ";
    cin >> start_ip;
    cout << "Enter the ending IP address: ";
    cin >> end_ip;

    try {
        unsigned int count = count_ips_in_range(start_ip, end_ip);
        cout << "Number of IP addresses in the range: " << count << endl;
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

char get_ip_class(const string &ip_address) {
    vector<int> octets = split(ip_address, '.');
    if (octets.size() != 4) {
        throw invalid_argument("Invalid IP address");
    }

    int first_octet = octets[0];

    if (first_octet >= 1 && first_octet <= 126) {
        return 'A';
    } else if (first_octet >= 128 && first_octet <= 191) {
        return 'B';
    } else if (first_octet >= 192 && first_octet <= 223) {
        return 'C';
    } else if (first_octet >= 224 && first_octet <= 239) {
        return 'D';
    } else if (first_octet >= 240 && first_octet <= 255) {
        return 'E';
    } else {
        return 'Invalid';
    }
}

void Find_Class_Of_IP(void){
    string ip_address;
    cout << "Enter an IPv4 address: ";
    cin >> ip_address;

    try {
        char ip_class = get_ip_class(ip_address);
        if (ip_class == 'Invalid') {
            cout << "Invalid IP address" << endl;
        } else {
            cout << "IP address belongs to Class " << ip_class << endl;
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Function to convert IP address from string to an integer
unsigned int ipToInt(const string& ip) {
    unsigned int result = 0;
    stringstream ss(ip);
    string octet;
    for (int i = 0; i < 4; ++i) {
        getline(ss, octet, '.');
        result = (result << 8) + stoi(octet);
    }
    return result;
}

// Function to convert an integer to an IP address string
string intToIp(unsigned int ip) {
    stringstream ss;
    for (int i = 3; i >= 0; --i) {
        ss << ((ip >> (i * 8)) & 0xFF);
        if (i != 0) ss << ".";
    }
    return ss.str();
}

// Function to calculate the IP details for each organization
void calculateIpDetails(const string& startIp, int numOrganizations) {
    unsigned int startIpInt = ipToInt(startIp);
    int numIps = pow(2, ceil(log2(256 / numOrganizations)));  // Number of IPs per organization
    vector<pair<string, string>> ipRanges;

    for (int i = 0; i < numOrganizations; ++i) {
        unsigned int firstIpInt = startIpInt + (i * numIps);
        unsigned int lastIpInt = firstIpInt + numIps - 1;
        ipRanges.push_back({intToIp(firstIpInt), intToIp(lastIpInt)});
    }

    for (int i = 0; i < numOrganizations; ++i) {
        cout << "Organization " << i + 1 << ":\n";
        cout << "First IP: " << ipRanges[i].first << "\n";
        cout << "Last IP: " << ipRanges[i].second << "\n";
        cout <<"According to RFC-950 :- Number of Host: " << numIps - 2<<"\n";
        cout<<"According to RFC-1812 :- Number Of Host :"<<numIps<<"\n\n\n";
    }
}

void Find_first_last_ip_of_each_organization(void){
    string startIp;
    int numOrganizations;

    cout << "Enter starting IP address: ";
    cin >> startIp;
    cout << "Enter number of organizations: ";
    cin >> numOrganizations;

    calculateIpDetails(startIp, numOrganizations);
}

int main() {
    cout<<"\t\t\t\t\tThese Are The Functionality Present In Software.";

    cout<<"\n\n1. Checking Type Of Address.";
    cout<<"\n\n2. Find Number Of IP Present In Range.";
    cout<<"\n\n3. Find Class Of IP Address.";
    cout<<"\n\n4.Finding First and Last IP Of Each Organization And Total Number Of Host in Each Organization.";

    int option;
    cout<<"\n\nEnter Option You Want To Calculate:- ";
    cin>>option;
    cout<<"n\n\n";

    switch(option){
        case 1: Checking_type_of_Address();
        break;
        case 2: Find_No_IP();
        break;
        case 3: Find_Class_Of_IP();
        break;
        case 4: Find_first_last_ip_of_each_organization();
        break;
    }
    

    return 0;
}
