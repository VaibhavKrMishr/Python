import time


print("select a option")
print "1. Add"
print "2. Subtract"
print "3. Multiply"
print "4. Divide"

a = input("Opt>>>")

if a==1:
    print "Welcome to Add"
    print "input 2 numbers"
    num1 = input("Num1>>>")
    num2 = input("Num2>>>")
    print "Adding..."
    time.sleep(2)
    print num1 + num2
    
if a==2:
    print "Welcome to Subtract"
    print "Input 2 Numbers"
    num1 = input("Num1>>>")
    num2 = input("Num2>>>")
    print "Subtracting..."
    time.sleep(2)
    print num1 - num2
    
if a==3:
    print "Welcome to Multiply"
    print "input 2 Numbers"
    num1 = input("Num1>>>")
    num2 = input("Num2>>>")
    print "Multiplying..."
    time.sleep(2)
    print num1 * num2

if a==4:
    print "Welcome to Divide"
    print "Input 2 Numbers"
    num1 = input("Num1>>>")
    num2 = input("Num2>>>")
    float(num1)
    float(num2)
    print "Dividing..."
    time.sleep(2)
    print num1 / num2


while True:
    pass


    
