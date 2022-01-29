#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

//проверка числа на четность наложением битовой маски
bool isEven(int value) {
    return !(value & 1);
}

//слияние двух отсортированных массивов
template<typename T>
std::vector<T> mergeSorted(std::vector<T>& l, std::vector<T>& r) {
    std::vector<T> result;
    auto l_end = l.end();
    auto r_end = r.end();
    auto it_l = l.begin();
    auto it_r = r.begin();
    while ((it_l != l_end) && (it_r != r_end)) {
        if (*it_l < *it_r) {
            result.push_back(*it_l);
            ++it_l;
        }
        else {
            result.push_back(*it_r);
            ++it_r;
        }
    }
    while (it_l != l_end) {
        result.push_back(*it_l);
        ++it_l;
    }
    while (it_r != r_end) {
        result.push_back(*it_r);
        ++it_r;
    }
    return result;
} 

//сортировка слиянием
template<typename T>
std::vector<T> mergeSort(std::size_t l, std::size_t r, std::vector<T>& arr) {
    if ((r - l) < 1) return std::vector<T> {arr[l]};
    std::size_t m = (l+r) / 2;
    std::vector<T> left = mergeSort(l, m, arr);
    std::vector<T> right = mergeSort(m+1, r, arr);
    std::vector<T> result = mergeSorted(left, right);
    return result;
}

//обертка функции сортировки
template<typename T>
std::vector<T> sort(std::vector<T>& arr) {
    if (arr.size() <= 1) return arr;
    return mergeSort(0, arr.size(), arr);
}


int main(int argc, char* argv[]) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {1, 10000};
    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };
    std::vector<int> arr(1000001);
    std::generate(arr.begin(), arr.end(), gen);
    std::vector<int> arr_sorted = sort(arr);
    bool sorted = true;
    for (std::size_t i = 1; i < arr_sorted.size(); ++i)
        if (arr_sorted[i] < arr_sorted[i - 1])
            sorted = false;
    std::cout << sorted << std::endl;
    return 0;
}
