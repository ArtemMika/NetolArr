#include <iostream>
#include <string>


struct Address 
{
    std::string city;
    std::string street;
    int houseNumber;
    int apartment;
    int index;
};

void printAddress(const Address& addr)
{
    std::cout << "Город: " << addr.city << std::endl;
    std::cout << "Улица: " << addr.street << std::endl;
    std::cout << "Номер дома: " << addr.houseNumber << std::endl;
    std::cout << "Номер квартиры: " << addr.apartment << std::endl;
    std::cout << "Индекс: " << addr.index << std::endl << std::endl;
}

int main() 
{
    setlocale(LC_ALL, "rus");
   
    Address address1;
    address1.city = "Москва";
    address1.street = "Арбат";
    address1.houseNumber = 12;
    address1.apartment = 8;
    address1.index = 123456;

    Address address2;
    address2.city = "Ижевск";
    address2.street = "Пушкина";
    address2.houseNumber = 59;
    address2.apartment = 143;
    address2.index = 953769;

    printAddress(address1);
    printAddress(address2);

    return 0;
}