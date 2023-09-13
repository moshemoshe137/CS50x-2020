# Moshe Rubin
# 2/3/2021
# Credit card processing with Luhn's alogorithm 
# https://cs50.harvard.edu/x/2021/psets/6/credit/ and https://cs50.harvard.edu/x/2021/psets/1/credit/

def main():
    number = int(input("Number: "))
    print(identify(number))


def digit(number, n):
    # returns the nth digit of number
    length = len(str(number))
    if n >= length:
        return 0
    return int(str(number)[length - n - 1])
    
    
def luhns(cc_number):
    # returns True if you pass luhns alg
    # returns False if you fail
    length = len(str(cc_number))
    
    sum = 0
    for i in range(length):
        if i % 2 == 0:
            sum += digit(cc_number, i)
        else:
            two_x_digit = 2 * digit(cc_number, i)
            sum += digit(two_x_digit, 0)
            sum += digit(two_x_digit, 1)
    
    return (sum % 10 == 0)
 
    
def identify(cc_number):
    if not luhns(cc_number):
        return "INVALID"
    
    length = len(str(cc_number))
    
    if length == 16 and digit(cc_number, 15) == 5 and (1 <= digit(cc_number, 14) <= 5):
        return "MASTERCARD"
    elif length == 15 and digit(cc_number, 14) == 3 and digit(cc_number, 13) in [4, 7]:
        return "AMEX"
    elif (length == 13 and digit(cc_number, 12) == 4) or (length == 16 and digit(cc_number, 15) == 4):
        return "VISA"
    else:
        return "INVALID"
  
        
if __name__ == "__main__":
    main()
