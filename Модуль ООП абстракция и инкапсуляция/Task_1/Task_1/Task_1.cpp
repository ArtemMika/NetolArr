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
    Address(const std::string& c, const std::string& s, int h, int a) : city(c), street(s), house(h), apartment(a) { }

    std::string get_output_address() const
    {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(apartment);
    }
};

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

    std::string temp;
    std::getline(in_file, temp);

    Address** addresses = new Address * [n];

    try
    {
        for (int i = 0; i < n; i++)
        {
            std::string city, street;
            int house, apartment;

            std::getline(in_file, city);
            std::getline(in_file, street);
            in_file >> house >> apartment;

            std::getline(in_file, temp);

            addresses[i] = new Address(city, street, house, apartment);
        }
    }
    catch (...)
    {
        for (int i = 0; i < n; i++)
        {
            if (addresses[i]) delete addresses[i];
        }
        delete[] addresses;
        in_file.close();
        return 1;
    }

    std::ofstream out_file("out.txt");
    if (!out_file.is_open())
    {
        std::cerr << "Ошибка открытия файла out.txt" << std::endl;

        for (int i = 0; i < n; i++)
        {
            delete addresses[i];
        }
        delete[] addresses;
        in_file.close();
        return 1;
    }

    out_file << n << std::endl;

    for (int i = n - 1; i >= 0; i--)
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