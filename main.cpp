#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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

  for (int i = length - 1; i > -1; i--) {
    current_digit = carry + (num1[i] - '0') + (num2[i] - '0');

    carry = current_digit / base;

    current_digit = current_digit % base;

    sum = (char)(current_digit + '0') + sum;
  }
  if (carry > 0) {
    sum = (char)(carry + '0') + sum;
  }
  return sum;
}

std::string subtract(const std::string& num1, const std::string& num2, int base) {
    std::string result;
    int borrow = 0;
    
    int len1 = num1.length();
    int len2 = num2.length();
    
    for (int i = 0; i < len1; ++i) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;
        
        int diff = digit1 - digit2 - borrow;
        
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result += diff + '0';
    }
    
    // Remove leading zeros
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    std::reverse(result.begin(), result.end());
    
    return result;
}


std::string karatsubaMultiplication(std::string num1, std::string num2, int base) {
  int num1_length = num1.length();
  int num2_length = num2.length();


  if (num1_length == 0 || num2_length == 0) {
    return "0";
  }

  int result = 0;

  if (num1_length == 1 && num2_length == 1) {
    result = (num1[0] - '0') * (num2[0] - '0');
    return std::to_string(result);
  }

  int half_length = std::max(num1_length, num2_length) / 2;

  std::string a = num1.substr(0,num1_length - half_length);
  std::string b = num1.substr(num1_length - half_length);

  std::string c = num2.substr(0,num2_length - half_length);
  std::string d = num2.substr(num2_length - half_length);

  std::string ac = karatsubaMultiplication(a,c, base);
  
  std::string bd = karatsubaMultiplication(b,d, base);

  std::string product_sum = karatsubaMultiplication(schoolAddition(a,b,base),schoolAddition(c,d,base),base); 
  
  std::string ad_plus_bc = subtract(product_sum, schoolAddition(ac,bd,base), base);

  std::string basePower(half_length, '0');

  basePower[0] = '1';

  std::string firstTerm = ac + basePower + basePower;
  std::string secondTerm = ad_plus_bc + basePower;

  return schoolAddition(firstTerm, secondTerm, base);
}



int main() {
  
  std::string a;
  std::string b;
  int base;

  std::cin >> a >> b >> base;

  std::string result = schoolAddition(a,b, base);

  std::string product = karatsubaMultiplication(a,b,base);
  
  std::cout << result << " " << product << std::endl;
  
  return 0;
}