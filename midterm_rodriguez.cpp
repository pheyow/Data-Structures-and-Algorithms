#include <iostream>
#include <vector>
#include <string>

class Contact {
public:
    int contactID;
    std::string contactName;
    std::string phoneNumber;
    std::string email;

    Contact(int id, const std::string& name, const std::string& phone, const std::string& email)
        : contactID(id), contactName(name), phoneNumber(phone), email(email) {}
};

class AddressBook {
private:
    std::vector<Contact> contacts;
    int nextContactID;

public:
    AddressBook() : nextContactID(1) {}

    void createContact(const std::string& name, const std::string& phone, const std::string& email) {
        contacts.emplace_back(nextContactID++, name, phone, email);
        std::cout << "Contact created: ID " << nextContactID - 1
                  << ", Name: " << name << ", Phone: " << phone << ", Email: " << email << "\n";
    }

    void readContacts() {
        if (contacts.empty()) {
            std::cout << "No contacts found.\n";
            return;
        }
        std::cout << "\nContact List:\n";
        for (const auto& contact : contacts) {
            std::cout << "ID: " << contact.contactID
                      << ", Name: " << contact.contactName
                      << ", Phone: " << contact.phoneNumber
                      << ", Email: " << contact.email << "\n";
        }
    }

    void updateContact(int id) {
        for (auto& contact : contacts) {
            if (contact.contactID == id) {
                std::string newName, newPhone, newEmail;
                char updateChoice;

                std::cout << "Current Name: " << contact.contactName << "\nUpdate name? (y/n): ";
                std::cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    std::cout << "Enter new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, newName);
                    contact.contactName = newName;
                }

                std::cout << "Current Phone number: " << contact.phoneNumber << "\nUpdate phone? (y/n): ";
                std::cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    std::cout << "Enter new phone number: ";
                    std::cin.ignore();
                    std::getline(std::cin, newPhone);
                    contact.phoneNumber = newPhone;
                }

                std::cout << "Current Email: " << contact.email << "\nUpdate email? (y/n): ";
                std::cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    std::cout << "Enter new email: ";
                    std::cin.ignore();
                    std::getline(std::cin, newEmail);
                    contact.email = newEmail;
                }

                std::cout << "Contact updated: ID " << id
                          << ", Name: " << contact.contactName
                          << ", Phone: " << contact.phoneNumber
                          << ", Email: " << contact.email << "\n";
                return;
            }
        }
        std::cout << "Contact with ID " << id << " not found.\n";
    }

    bool deleteContact(int id) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->contactID == id) {
                std::cout << "Contact deleted: ID " << it->contactID
                          << ", Name: " << it->contactName << "\n";
                contacts.erase(it);
                return true;
            }
        }
        std::cout << "Contact with ID " << id << " not found.\n";
        return false;
    }
};

int main() {
    AddressBook addressBook;
    int choice;
    std::string name, phone, email;
    int id;

    do {
        std::cout << "\nYellow Pages:\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Read Contacts\n";
        std::cout << "3. Update Contact\n";
        std::cout << "4. Delete Contact\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter contact name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phone);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                addressBook.createContact(name, phone, email);
                break;
            case 2:
                addressBook.readContacts();
                break;
            case 3:
                std::cout << "Enter ID of the contact to update: ";
                std::cin >> id;
                addressBook.updateContact(id);
                break;
            case 4:
                std::cout << "Enter ID of the contact to delete: ";
                std::cin >> id;
                if (addressBook.deleteContact(id)) {
                    addressBook.readContacts();
                }
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
