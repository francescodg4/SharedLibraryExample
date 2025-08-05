
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

#include <mylibrary.h>

static std::ostream& operator<<(std::ostream& os, const mylibrary::Object& object)
{
    os << "Object{" << object.a << ", " << object.b << '}';
    return os;
}

template <typename T>
static void print(const mylibrary::Array<T>& array)
{
    std::cout << "IsEmpty?: " << (array.empty() ? "True" : "False") << " ";

    std::cout << "[";

    auto it = std::cbegin(array);

    while (it != std::end(array)) {
        std::cout << *it;

        if (it + 1 != std::end(array)) {
            std::cout << ", ";
        }

        it++;
    }

    std::cout << "]\n";
}

int main()
{
    std::cout << "Is shared?: " << (mylibrary::is_shared() ? "True" : "False") << '\n';

    mylibrary::Array<int> arr;

    std::cout << "Sizeof(mylibrary::Array<int>): " << sizeof(mylibrary::Array<int>) << "\n";
    std::cout << "Sizeof(mylibrary::Array<double>): " << sizeof(mylibrary::Array<double>) << "\n";

    arr.push_back(1);

    mylibrary::Array<int> arr1(arr);

    std::cout << "IsEmpty?: " << (arr1.empty() ? "True" : "False") << "\n";

    arr.push_back(2);
    arr.push_back(3);

    arr[0] = arr[0] + 1;

    for (const auto& a : arr) {
        std::cout << a << std::endl;
    }

    std::cout << "Array.size(): " << arr.size() << "\n";
    std::cout << "Array.size(): " << arr1.size() << "\n";

    arr1 = arr;

    for (const auto& a : arr1) {
        std::cout << a << std::endl;
    }

    // std::move
    arr1 = mylibrary::Array<int>(3, -1);

    for (const auto& a : arr1) {
        std::cout << a << std::endl;
    }

    arr1.insert(std::begin(arr1), 3);

    print(arr1);

    print(mylibrary::Array<int>());

    {
        mylibrary::Array<int> arr;
        arr.push_back(1);
        arr.push_back(2);
        print(arr);
    }

    {
        print(mylibrary::Array<int> { 1, 2, 3, 4 });
    }

    {
        mylibrary::Array<int> in { 1, 2, 3, 4 };
        mylibrary::Array<int> out(std::begin(in) + 1, std::end(in));
        print(out);
    }

    {
        mylibrary::Array<int> in { 1, 2, 3, 4 };
        mylibrary::Array<int> arr;

        arr.assign({ 3, 4 });
        print(arr);

        arr.assign(5, 12);
        print(arr);

        arr.assign(std::begin(in), std::begin(in) + 2);
        print(arr);
    }

    {
        std::cout << "Are Equal?: "
                  << (mylibrary::Array<int> { 1, 2, 3, 4 } == mylibrary::Array<int> { 1, 2, 3, 4 })
                  << "\n";

        std::cout << "Are Different?: "
                  << (mylibrary::Array<int> { 1, 2, 3, 4 } != mylibrary::Array<int> { 1, 2, 3, 4 })
                  << "\n";
    }

    {
        mylibrary::Array<int> in = { 1, 2, 3, 4, 5 };
        mylibrary::Array<double> out;

        std::transform(std::begin(in), std::end(in), std::back_inserter(out), [](int value) -> double {
            return static_cast<double>(value / 10.0);
        });

        print(out);
    }

    {
        mylibrary::Array<int> arr = mylibrary::Array<int>::from(std::vector<int> { 1, 2 });
        print(arr);

        std::cout << "std::vector: {";
        for (const auto& v : arr.to_std_vector()) {
            std::cout << v << ", ";
        }
        std::cout << "}\n";
    }

    {
        using namespace mylibrary;

        Array<Object> objects;
        objects.push_back(Object { 1, 2 });
        objects.push_back(Object { 3, 4 });

        print(objects);

        std::cout << objects.front() << "\n";
        std::cout << objects.back() << "\n";
    }

    {
        using namespace mylibrary;

        Array<int> objects { 0, 1, 2, 3, 4, 5, 6 };

        objects.erase(std::begin(objects) + 1, std::begin(objects) + 2);
        print(objects);

        objects.erase(std::begin(objects));
        print(objects);
    }

    {
        using namespace mylibrary;

        Array<int> values { 45, 23, 12, 2, 45 };
        auto it = std::find(std::begin(values), std::end(values), 2);
        std::cout << "Value: " << *it << " at: " << std::distance(std::begin(values), it) << std::endl;

        auto it_1 = std::find(std::rbegin(values), std::rend(values), 2);
        std::cout << "Value: " << *it_1 << " at: " << std::distance(std::rbegin(values), it_1) << std::endl;
    }

    std::cout << "Done.";

    return 0;
}
