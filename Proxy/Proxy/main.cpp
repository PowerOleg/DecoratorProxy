#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : public VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object)
    {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }
        else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

//class TestDB : VeryHeavyDatabase {
//public:
//    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
//    std::string GetData(const std::string& key) noexcept {
//        return "test_data\n";
//    }
//private:
//    VeryHeavyDatabase* real_db_;
//};

class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots_ = 1) : real_db_{ real_object }, shots_max{ shots_ }, shots{ 0 }, last_key{ "" }
    {}
    std::string GetData(const std::string& key) noexcept {
        this->shots = last_key == key ? this->shots + 1 : 1;

        if (this->shots <= shots_max) {
            last_key = key;
            std::cout << "Get from real object\n";
            return real_db_->GetData(key);
        }
        else
        {
            //std::cout << "Error\n";
            return "Error\n";
        }
    }
private:
    //std::map<std::string, std::string> cache_;
    std::string last_key;
    VeryHeavyDatabase* real_db_;
    size_t shots_max;
    size_t shots;
};

int main(int argc, char** argv) {
    VeryHeavyDatabase real_db;//������ �������� ���� auto real_db = VeryHeavyDatabase();??? 
    CacheProxyDB cached_db(std::addressof(real_db));//auto cached_db = CacheProxyDB(std::addressof(real_db));
    //std::cout << cached_db.GetData("key") << std::endl;
    //std::cout << cached_db.GetData("key") << std::endl;

    OneShotDB limit_db(std::addressof(real_db), 2);
    std::cout << limit_db.GetData("key") << std::endl;//>>value
    std::cout << limit_db.GetData("key") << std::endl;//>>value
    std::cout << limit_db.GetData("key") << std::endl;//>>error
    return 0;
}