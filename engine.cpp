#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Vital for converting std::vector
#include <vector>
#include <random>
#include <cmath>

namespace py = pybind11;

std::pair<std::vector<double>,std::vector<double>> generatePath(int N, double T, double X0, double Y0, double rho, double m, double gamma, double sigma){
   
    std::vector<double> Xpath(N);
    std::vector<double> Ypath(N);
    Xpath[0] = X0;
    Ypath[0] = Y0;
    double dt = T / static_cast<double>(N);
    double sqrt_dt = std::sqrt(dt);
    double std_dev = sigma * sqrt_dt;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0,1.0);

    for(int i = 1; i < N; i++){
        double Z = dist(gen);

        Ypath[i] = Ypath[i-1] + (m - (gamma * Ypath[i-1])) * dt + std_dev * Z;
        Xpath[i] = Xpath[i-1] + rho * Ypath[i-1] * dt;
    }

    return {Xpath,Ypath};
}

PYBIND11_MODULE(sde_module, m) {
    m.doc() = "C++ Ornstein-Ulhenbeck simulator module";
    m.def("generatePath", &generatePath, "Generates a 2D path that follows the mean-reverting Ornstein-Ulhenbeck process");
}
