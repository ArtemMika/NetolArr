#include <iostream>
#include <fstream>
#include <string>

class Address
{
private:
    std::string city;
    std::string street;
    int house;
    int apartment;

public:
    Address(const std::string& c, const std::string& s, int h, int a) : city(c), street(s), house(h), apartment(a) {}

    std::string get_output_address() const 
    {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(apartment);
    }

    const std::string& get_city() const 
    {
        return city;
    }
};

void sort_addresses(Address** addresses, int size) 
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (addresses[j]->get_city() > addresses[j + 1]->get_city())
            {
                // Обмен элементов
                Address* temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    setlocale(LC_ALL, "rus");

    std::ifstream in_file("in.txt");
    if (!in_file.is_open()) 
    {
        std::cerr << "Ошибка открытия файла in.txt" << std::endl;
        return 1;
    }

    int n;
    in_file >> n;

    Address** addresses = new Address * [n];

    for (int i = 0; i < n; i++)
    {
        std::string city, street;
        int house, apartment;

        std::getline(in_file, city);
        std::getline(in_file, city);
        std::getline(in_file, street);

        in_file >> house;
        in_file >> apartment;

        addresses[i] = new Address(city, street, house, apartment);
    }

    sort_addresses(addresses, n);

    std::ofstream out_file("out.txt");
    if (!out_file.is_open()) 
    {
        std::cerr << "Ошибка открытия файла out.txt" << std::endl;
        return 1;
    }

    out_file << n << std::endl;

    for (int i = 0; i < n; i++)
    {
        out_file << addresses[i]->get_output_address() << std::endl;
    }

    for (int i = 0; i < n; i++) 
    {
        delete addresses[i];
    }
    delete[] addresses;

    in_file.close();
    out_file.close();

    return 0;
}