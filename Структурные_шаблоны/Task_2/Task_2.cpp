#include <iostream>
#include <cstddef>
#include <string>
#include <unordered_map>

class VeryHeavyDatabase 
{
public:
    virtual ~VeryHeavyDatabase() = default;

    virtual std::string GetData(const std::string& key) 
    {
        // поиск в «базе»
        static const std::unordered_map<std::string, std::string> data = 
        {
            {"key", "value"},
            {"other", "other_value"}
        };
        auto it = data.find(key);
        return (it != data.end()) ? it->second : "not_found";
    }
};

class OneShotDB : public VeryHeavyDatabase
{
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object_(real_object), remaining_shots_(shots) 
    {
    }

    std::string GetData(const std::string& key) override
    {
        if (remaining_shots_ == 0) 
        {
            return "error";
        }

        std::string result = real_object_->GetData(key);
        --remaining_shots_;
        return result;
    }

private:
    VeryHeavyDatabase* real_object_;
    size_t remaining_shots_;
};

int main()
{
    VeryHeavyDatabase real_db;
    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << "\n";  // value
    std::cout << limit_db.GetData("key") << "\n";  // value
    std::cout << limit_db.GetData("key") << "\n";  // error

    return 0;
}