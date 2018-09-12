# 78(10) = 7*10^1 + 8*10^0 

# 123(8) -> 10
# 3*8^0  + 2*8^1 + 1*8^2 = 3+16+64 = 83(10)

def base8_to_base10(x):
    place = 0
    sum = 0
    while x != 0:
        digit = x % 10
        x = x // 10
        sum += digit * (8 ** place)
        place += 1
    return sum

print(base8_to_base10(123))
   
# 83(10) -> 8
# 83 / 8 = 10, rem=3
# 10 / 8 = 1, rem=2
# 1 / 8 = 0, rem=1
# result = 123

def base10_to_base8(x):
    place = 0
    sum = 0
    while x != 0:
        rem = x % 8
        x = x // 8
        sum += rem * (10 ** place)
        place += 1
    return sum
    
print(base10_to_base8(83))


# python syntax stuff

class X:
    def quack(self):
        print('a')
        self.bla = 2

class Y:
    def quack(self):
        print('a')        
        
        
def do_something(x):
    x.quack()
 
a = X()
b = Y()
do_something(b)





