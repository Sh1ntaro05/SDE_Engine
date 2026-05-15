import sde_module
import numpy as np
import matplotlib.pyplot as plt


def main():
   
    N = 10000
    T = 10.0
    X0 = 1.0
    Y0 = 1.0
    rho = 1.0
    m = 1.0
    gamma = 5.0
    sigma = 1.0


    Xpath, Ypath = sde_module.generatePath(N,T,X0,Y0,rho,m,gamma,sigma)

    plt.plot(Xpath, label="Position (X)")
    plt.plot(Ypath, label="Velty (Y)")
    plt.legend()
    plt.show()






if __name__ == "__main__":
    main()


