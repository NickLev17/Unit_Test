#include <gtest/gtest.h>
#include <math.h>
#include <stdexcept>

const double e = std::numeric_limits<double>::epsilon();

std::vector<double> solve(double a, double b, double c,double e)
{
    if (!std::isfinite(e) || e < 0.0) {
        throw std::invalid_argument("Эпсилон e - должен быть конечным положительным числом!");
    }

       if (!std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c)) 
       {
        throw std::invalid_argument("Коэффициенты a, b, c  - должны быть конечными числами!");
    }

if(abs(a)<=e)
  throw std::invalid_argument("Коэффициент a - не может быть равен нулю!");

    double D = b * b - 4 * a * c;

    if (D < -e)
    {
        return std::vector<double>{};
    }
    else if (abs(D) <=e)
    {
        double root = -b / (2 * a);
        return std::vector<double>{root};
    }
    else 
    {
        double root1 = (-b + std::sqrt(D)) / (2 * a);
        double root2 = (-b - std::sqrt(D)) / (2 * a);
        
        return std::vector<double>{root1, root2};
    }
}


TEST(solve, NotSquareRoot) {
    std::vector<double> vec{};

     EXPECT_EQ(solve(1.0,0.0,1.0,e), vec);
    
     
}

TEST(solve, OneSquareRoot) {
    std::vector<double> vec=solve(1.0,2.0,1.0,e);
     EXPECT_EQ(vec.size(),1);
     EXPECT_EQ(vec.at(0),-1);
}

TEST(solve, TwoSquareRoot) {
    std::vector<double> vec=solve(1.0,0.0,-1.0,e);
     EXPECT_EQ(vec.size(),2);
}

TEST(solve, ArgumentAException ){
   EXPECT_THROW(solve(0.0, 1.0, 2.0, 0.0), std::invalid_argument);

}
TEST(solve, AllArgumentException) 
{
    const double nan_value = std::numeric_limits<double>::quiet_NaN();
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -pos_inf;

    EXPECT_THROW(solve(1.0, 1.0, 1.0, nan_value), std::invalid_argument);
    EXPECT_THROW(solve(1.0, 1.0, 1.0, neg_inf), std::invalid_argument);
    EXPECT_THROW(solve(1.0, 1.0, 1.0, pos_inf), std::invalid_argument);

    EXPECT_THROW(solve(nan_value, 1.0, 1.0, e), std::invalid_argument);
    EXPECT_THROW(solve(pos_inf, 1.0, 1.0, e), std::invalid_argument);
    EXPECT_THROW(solve(neg_inf, 1.0, 1.0, e), std::invalid_argument);

    EXPECT_THROW(solve(1.0, nan_value, 1.0, e), std::invalid_argument);

    EXPECT_THROW(solve(1.0, 1.0, pos_inf, e), std::invalid_argument);
    EXPECT_THROW(solve(1.0, 1.0, neg_inf, e), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
