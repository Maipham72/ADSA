#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::string removeZeros (std::string num) {
  num.erase(0, num.find_first_not_of('0'));

  if (num.empty()) {
    return "0";
  }

  return num;
}

std::string schoolAddition(std::string num1, std::string num2, int base) {
  int num1_length = num1.length();
  int num2_length = num2.length();
  int length = std::max(num1_length, num2_length);

  std::string sum = "";
  std::string zeros = "";

  int diff = abs(num1_length - num2_length);

  for (int i = 1; i <= diff; i++) {
    zeros += "0";
  }

  if (num1_length < num2_length) {
    num1 = zeros + num1;
  } else {
    num2 = zeros + num2;
  }

  int carry = 0;
  int current_digit = 0;

  for (int i = length - 1; i >= 0; i--) {
    current_digit = carry + (num1[i] - '0') + (num2[i] - '0');

    carry = current_digit / base;

    current_digit = current_digit % base;

    sum = (char)(current_digit + '0') + sum;
  }
  if (carry > 0) {
    sum = (char)(carry + '0') + sum;
  }

  return removeZeros(sum);
}

// bool compareNum(std::string num1, std::string num2) {
//   int num1_length = num1.length();
//   int num2_length = num2.length();

//   if (num1_length < num2_length) {
//     return true;
//   } else if (num1_length > num2_length) {
//     return false;
//   }

//   for (int i = 0; i < num1_length; i++) {
//     if (num1[i] < num2[i]) {
//       return true;
//     } else if (num1[i] > num2[i]) {
//       return false;
//     }
//   }

//   return false;
// }

std::string schoolSubtraction(std::string num1, std::string num2, int base) {
  int num1_length = num1.length();
  int num2_length = num2.length();
  int length = std::max(num1_length, num2_length);

  std::string zeros = "";
  std::string result = "";

  if (num1_length < num2_length) {
    std::swap(num1, num2);
    std::swap(num1_length, num2_length);
  }

  int diff = abs(num1_length - num2_length);

  for (int i = 1; i <= diff; i++) {
    zeros += "0";
  }

  if (num1_length > num2_length) {
    num2 = zeros + num2;
  }

  int borrow = 0;

  for (int i = length - 1; i >= 0; i--) {
    int digit1 = num1[i] - '0';
    int digit2 = num2[i] - '0';

    int sub = digit1 - digit2 - borrow;

    if (sub < 0) {
      sub += base;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result = (char)(sub + '0') + result;
  }


  return removeZeros(result);
}

std::string karatsubaMultiplication(std::string num1, std::string num2,int base) {
  int num1_length = num1.length();
  int num2_length = num2.length();
  int length = std::max(num1_length, num2_length);

  if (num1_length == 0 || num2_length == 0) {
    return "0";
  }

  if (num1_length == 1 && num2_length == 1) {
    int result = (num1[0] - '0') * (num2[0] - '0');
    return std::to_string(result);
  }

  if (length % 2 != 0) {
    length++;
  }

  num1 = num1.insert(0, length - num1_length, '0');
  num2 = num2.insert(0, length - num2_length, '0');

  int half_length = length / 2;

  std::string a = num1.substr(0, half_length);
  std::string b = num1.substr(half_length);
  std::string c = num2.substr(0, half_length);
  std::string d = num2.substr(half_length);


  std::string ac = karatsubaMultiplication(a, c, base);
  std::string bd = karatsubaMultiplication(b, d, base);

  std::string a_plus_b = schoolAddition(a, b, base);
  std::string c_plus_d = schoolAddition(c, d, base);

  std::string ab_cd = karatsubaMultiplication(a_plus_b, c_plus_d, base); //ab + cd

  std::string ad_bc = schoolSubtraction(ab_cd,ac,base);

  ad_bc = schoolAddition(ad_bc, bd, base); //(a+b)*(c+d) - ac - bd = ad + bc

  std::string r1 = ac + std::string(2*half_length, '0');

  std::string r2 = ad_bc + std::string(half_length,'0');
  std::string r3 = bd;

  std::string result = schoolAddition(r1, r2,base);
  result = schoolAddition(result, r3,base);


  return removeZeros(result);
}


int main() {
  std::string a;
  std::string b;
  int base;

  std::cin >> a >> b >> base;

  std::string result = schoolAddition(a, b, base);
  // std::string sub = schoolSubtraction(a, b, base);
  std::string product = karatsubaMultiplication(a, b, base);

  std::cout << result << " " << product << " " << 0 << std::endl;

  return 0;
}