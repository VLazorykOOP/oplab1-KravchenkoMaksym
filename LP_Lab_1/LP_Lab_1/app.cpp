#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <clocale> 

struct Data {
    double x;
    double T;
    double U;
};

std::vector<Data> readData(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Data> data;
    Data temp;
    while (file >> temp.x >> temp.T >> temp.U) {
        data.push_back(temp);
    }
    return data;
}

double interpolateT(double x, const std::vector<Data>& data) {
    auto it = std::lower_bound(data.begin(), data.end(), x, [](const Data& d, double x) {
        return d.x < x;
        });
    if (it == data.end()) {
        return data.back().T;
    }
    if (it == data.begin()) {
        return data.front().T;
    }
    const Data& d1 = *(it - 1);
    const Data& d2 = *it;
    return d1.T + (d2.T - d1.T) * (x - d1.x) / (d2.x - d1.x);
}

double interpolateU(double x, const std::vector<Data>& data) {
    auto it = std::lower_bound(data.begin(), data.end(), x, [](const Data& d, double x) {
        return d.x < x;
        });
    if (it == data.end()) {
        return data.back().U;
    }
    if (it == data.begin()) {
        return data.front().U;
    }
    const Data& d1 = *(it - 1);
    const Data& d2 = *it;
    return d1.U + (d2.U - d1.U) * (x - d1.x) / (d2.x - d1.x);
}

double fun(double x, double y, double z, const std::vector<Data>& data1, const std::vector<Data>& data2, const std::vector<Data>& data3) {
    double T_x = interpolateT(x, data1);
    double U_x = interpolateU(x, data1);
    double T_y = interpolateT(y, data2);
    double U_y = interpolateU(y, data2);
    double T_z = interpolateT(z, data3);
    double U_z = interpolateU(z, data3);

    // Обчислення значення fun(x, y, z) згідно з алгоритмами
    double result;
    // Ваш код обчислення результату тут, наприклад:
    if (x > y) {
        result = T_x + U_y - T_z;
    }
    else {
        result = T_y + U_z - U_x;
    }

    return result;
}

int main() {
    setlocale(LC_CTYPE, "");
    std::vector<Data> data1 = readData("dat_X_1_1.dat");
    std::vector<Data> data2 = readData("dat_X1_00.dat");
    std::vector<Data> data3 = readData("dat_X00_1.dat");

    std::cout << "Введiть значення x, y i z (Приклад: 0.5 0.3 0.2): " << std::endl;
    double x, y, z;
    std::cin >> x >> y >> z;

   
    double result = fun(x, y, z, data1, data2, data3);
    std::cout << "fun(" << x << ", " << y << ", " << z << ") = " << result << std::endl;

    return 0;
}
